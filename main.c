#include <stdio.h>
#include "Archivos/Archivo.h"
#include "Listas/ListaJugador.h"
#include "Listas/ListaFichas.h"
#include "Negocio/LogicaJuego.h"
#include <pthread.h>





int main() {
    //variables
    int terminar = 0;//Finalizar juego
    int nJugadores = 0;//total de jugadores
    int fichasXjugador=0;//numero de fichas para cada jugador
    char *fgets(char *str, int num, FILE *stream);
    pthread_mutex_t turno_mutex;//variable para aplicar hilos sincronos
    pthread_mutex_init(&turno_mutex, NULL); // inicializa el mutex

    //lista de jugadores
    ListaJugador *listaJugadores;
   // NodoJugador *nodoJugador;
    listaJugadores = crearListaJugador();

    //crear maso de fichas
    ListaFichas *listaMaso;
    listaMaso = crearLista();
    insertarFichas(listaMaso);

    //Mensaje de bienvenida
    printf("\nBienvenido al juego Dominó Sistemas Operativos 2023\n\n");


    //mostrar el maso
    printf("\n Mostrando el maso de fichas\n");
    imprimir(listaMaso);

    //revolver el maso
    printf("\n Revolviendo el maso de fichas\n");
    desordenar(listaMaso);
    imprimir(listaMaso);

    //Solicitar numero jugadores
    while ( (nJugadores<2) || (nJugadores>7)){
        printf("\nIngrese el numero de jugadores entre un rango de 2 a 7:\n");
        scanf("%d", &nJugadores);
        //2fflush(stdin);

    };

    printf("Iniciando partida para %d Jugadores.\n", nJugadores);
    //calcular numero de fichas jugadores - mazo
    fichasXjugador = calcularFichasXjugador(nJugadores);
    //repartirFichas(listaMaso, (nJugadores+1));
    //repartirFichas(listaMaso, fichasXjugador, listaMaso);

    //array de hilos
    pthread_t hilosJugadores[nJugadores];

    //crear archivo log.txt
    crearArchivo();

    getchar();//????

    //Ingresar nombres de jugadores
    for(int i = 0; i < nJugadores; i++){

        //almacenar nombre de jugadores
        char nombreJugador[50];

        printf("Ingrese el nombre del jugador #%d\n", (i+1));
        gets(nombreJugador);

//        fgets(nombreJugador, sizeof(nombreJugador), stdin);
//        nombreJugador[strcspn(nombreJugador, "\n")] = '\0';

        printf("Se añade al jugador: %s\n", nombreJugador);

        //almacenar en lista de jugadores
        NodoJugador *nodoJugador = crearJugador(nombreJugador, i);
        insertarJugador(listaJugadores, nodoJugador);

        printf("\n");
        //escribir el nombre y puntaje en un archivo
        acertarPuntos(nombreJugador, 0);

        //repartir fichas a jugador
        repartirFichas(listaMaso, fichasXjugador, nodoJugador->listaFichasJugador);
        printf("\n\n");
    }

    metodoBurbujaMazoJugador(listaJugadores);
    //imprimir la lista de jugadores
    printf("Los participantes son: \n");
    mostrar(listaJugadores);


    //Imprimir la lista de mazo para comer
    printf("Lista del mazo a comer: ");
    mostrarMazoComer(listaMaso);

    //inicializa hilos
    int errorHilo;


    // recorrer lista de jugadores
    int indice = 0;
    NodoJugador *aux = listaJugadores->primero;
    while (aux != NULL){

        printf("\n\nCreando hilo jugador %i\n", (indice+1));

        errorHilo = pthread_create(&hilosJugadores[indice], NULL, turnoJugador,(void *)aux);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_create()\n", errorHilo);
            exit(-1);
        }else{

            //iniciar la ejecucion del hilo
            pthread_join(hilosJugadores[indice], NULL);
        }

        indice++;

        aux = aux->sig;
    }




    pthread_mutex_destroy(&turno_mutex); // detruye el mutex
    pthread_exit(NULL);// destruye los hilos

    return 0;
}

