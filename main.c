#include <stdio.h>
#include "Archivos/Archivo.h"
#include "Listas/ListaJugador.h"
#include "Listas/ListaFichas.h"
#include "Negocio/LogicaJuego.h"
#include <pthread.h>
#include <unistd.h>


void *turno_jugador(void *parametro);

pthread_mutex_t turno_mutex;// hilos sincronos
int turno_actual = 1;// control del turno de los hilos
int numeroRondas = 0;// Control de rondas
int nJugadores;// total de jugadores

int main() {
    //variables
   // int nJugadores = 0;//total de jugadores
    //pthread_mutex_t turno_mutex;//variable para aplicar hilos sincronos

    nJugadores = 0;
    int fichasXjugador=0;//numero de fichas para cada jugador
    char *fgets(char *str, int num, FILE *stream);
    pthread_mutex_init(&turno_mutex, NULL); // inicializa el mutex
    pthread_mutex_lock(&turno_mutex);//bloquear ejecucion de hilos

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

    //array de hilos
    pthread_t hilosJugadores[nJugadores];
    //pthread_t *hilosJugadores = (pthread_t *) malloc(nJugadores * sizeof(pthread_t));

    //crear archivo log.txt
    crearArchivo();

    getchar();//????

    //Ingresar nombres de jugadores
    for(int i = 0; i < nJugadores; i++){

        //almacenar nombre de jugadores
        char nombreJugador[50];

        printf("Ingrese el nombre del jugador #%d\n", (i+1));
        //gets(nombreJugador);

        fgets(nombreJugador, sizeof(nombreJugador), stdin);
        nombreJugador[strcspn(nombreJugador, "\n")] = '\0';

        printf("Se añade al jugador: %s\n", nombreJugador);

        //almacenar en lista de jugadores
        NodoJugador *nodoJugador = crearJugador(nombreJugador, 0, (i+1));
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
    printf("\n\n");
    while (aux != NULL){

        printf("Creando hilo jugador %i\n", (indice+1));

        //struct ParametrosTurno parametrosTurno = {aux, nJugadores, turno_mutex};
        //errorHilo = pthread_create(&hilosJugadores[indice], NULL, turnoJugador,(void *)aux);
        //errorHilo = pthread_create(&hilosJugadores[indice], NULL, turnoJugador, (void *) &parametrosTurno);
        //errorHilo = pthread_create(&hilosJugadores[indice], NULL, funcion_hilo, (void *) &aux);

        pthread_create(&hilosJugadores[indice], NULL, turno_jugador, (void *)aux);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_create()\n", errorHilo);
            exit(-1);
        }

        indice++;

        aux = aux->sig;
    }
    printf("\n\n");

    errorHilo = 0;

    pthread_mutex_unlock(&turno_mutex); // libera el mutex mientras espera
    for(int i = 0; i < nJugadores; i++) {
        errorHilo = pthread_join(hilosJugadores[i], NULL);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_join()\n", errorHilo);
            exit(-1);
        }
    }



    printf("Los hilos han terminado\n");
    pthread_mutex_destroy(&turno_mutex); // detruye el mutex
    pthread_exit(NULL);// destruye los hilos

    return 0;
}

void *turno_jugador(void *parametro) {

    NodoJugador *nodoJugador = (NodoJugador *) parametro;

    int terminar = 1;
    // Realizar el turno

    while (terminar != 0) {

        // Esperar a que sea el turno del jugador
        pthread_mutex_lock(&turno_mutex);

        while (nodoJugador->nTurno != turno_actual) {
            pthread_mutex_unlock(&turno_mutex);
            sched_yield();
            pthread_mutex_lock(&turno_mutex);
        }

        //si todos jugaron su ronda se reinicia el contador de ronda
        printf("Turno del jugador %s (turno=%d)\n", nodoJugador->nombre, nodoJugador->nTurno);
        // Esperar un poco antes de continuar con el siguiente turno
        usleep(2000000);

        // Pasar al siguiente jugador
        turno_actual = (turno_actual % nJugadores) + 1;
        pthread_mutex_unlock(&turno_mutex);

        //aumentar la ronda
        if(turno_actual == turno_actual){
            numeroRondas++;
            //printf("Se ejecuto la ronda: %d\n", numeroRondas);
        }

        //condicion de terminar
        if(numeroRondas > 2){
            terminar=0;
           // printf("\nEl juego termino!\n");
        }

    }


    pthread_exit(NULL);// destruye los hilos
}