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
        printf("Se añade al jugador: %s\n", nombreJugador);

        //almacenar en lista de jugadores
        NodoJugador *nodoJugador = crearJugador(nombreJugador, 0);
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

    for(int i = 0; i < nJugadores; i++) {

        printf("\nCreando hilo jugador %ld\n", (i+1));
        errorHilo = pthread_create(&hilosJugadores[i], NULL, turnoJugador(nJugadores), (void *)i);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_create()\n", errorHilo);
            exit(-1);
        }
    }

    // Ejecutar hilos
    for(int i = 0; i < nJugadores; i++) {
        errorHilo = pthread_join(hilosJugadores[i], NULL);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_join()\n", errorHilo);
            exit(-1);
        }
    }

    //establecer el orden de juego


    pthread_exit(NULL);// destruye los hilos

    return 0;
}

