#ifndef PROYECTO_01_SO_LOGICAJUEGO_H
#define PROYECTO_01_SO_LOGICAJUEGO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>



int  calcularFichasXjugador( int nJugadores){
   return 28/ (nJugadores+1);
}

/*void *turnoJugador(void* parametro) {

    int *valor_parametro = (int *) parametro;

    printf("\n\n Entro! Hilo %i",  *valor_parametro);

}*/

/*
void *turnoJugador(void* parametro) {

    //sacar el nodo de parametros
    // int *nJugadores = (int *) parametro;
    NodoJugador *nodoJugador = (NodoJugador *) parametro;

    char nombre[50] = "";
    strcpy(nombre,nodoJugador->nombre);

    printf("El nombre del jugador en el turno es: %s\n", nombre);
    return NULL;
}*/

/*
typedef struct parametrosHilo{
    pthread_mutex_t turno_mutex;
    NodoJugador *nodoJugador;
    int nJugadores;
} parametrosHilo;
*/

typedef struct ParametrosTurno{
    NodoJugador* nodoJugador;
    int nJugadores;
    pthread_mutex_t turno_mutex;
}ParametrosTurno;

/*
void iniciarParametros (pthread_mutex_t turno_mutex, NodoJugador *nodoJugador,int nJugadores ){

    pthread_mutex_t turno_mutex = turno_mutex;
    NodoJugador *nodoJugador = nodoJugador;
    int nJugadores = nJugadores;

    parametrosHilo;
}
*/

//void turnoJugador(void parametro) {
//    ParametrosTurno* parametros = (ParametrosTurno*) parametro;
//    NodoJugador* nodoJugador = parametros->nodoJugador;
//    int nJugadores = parametros->nJugadores;
//    int nRondas = parametros->nRondas;
//
//    // Resto del código de la función
//}
// Para llamar la función y pasar los parámetros:
//ParametrosTurno parametros = {nodoJugador, 2, 3};
//pthread_create(&hiloJugador, NULL, turnoJugador, (void*) &parametros);

void *turnoJugador(void *parametro) {

    ParametrosTurno *parametros = (ParametrosTurno*) parametro;
    NodoJugador *nodoJugador = (NodoJugador *) parametros->nodoJugador;
    //printf("El nombre del jugador en el turno es: %s\n",nodoJugador->nombre);

   // printf("El nombre del jugador en el turno es: %s\n",nodoJugador->nombre);

    int jugadorActual = 0;
    int nRondas = 3;


    long tid = (long)pthread_self(); // corrección

    srand(time(NULL) + tid); // semilla diferente para cada hilo

    for(int i = 0; i < nRondas; i++) {//ciclo de juego

        pthread_mutex_lock(&parametros->turno_mutex); // bloquea el mutex para obtener el turno
//        pthread_self() != parametros->jugadores[jugadorActual]
        while(tid != jugadorActual) { // espera a que sea el turno del jugador
            pthread_mutex_unlock(&parametros->turno_mutex); // libera el mutex mientras espera
            pthread_mutex_lock(&parametros->turno_mutex); // vuelve a bloquear el mutex para obtener el turn0
        }

        //acciones del jugador

        printf("El nombre del jugador es: %s\n",nodoJugador->nombre);
        printf("El turno del jugador es: %i\n", (i+1));


        jugadorActual = (jugadorActual + 1) % parametros->nJugadores; // pasa el turno al siguiente jugador

        pthread_mutex_unlock(&parametros->turno_mutex); // libera el mutex para el siguiente jugador
    }




}



/*

void *turnoJugador( void* parametro ) {
    int *turno_mutex = (pthread_mutex_t *) parametro;

    int *nJugadores = (int *) parametro;

    printf("entro!");

    int jugadorActual = 0;
    int nRondas = 3;


    void *threadid;
    long tid = (long)threadid;
    srand(time(NULL) + tid); // semilla diferente para cada hilo

    for(int i = 0; i < nRondas; i++) {//ciclo de juego

        pthread_mutex_lock(&turno_mutex); // bloquea el mutex para obtener el turno

        while(tid != jugadorActual) { // espera a que sea el turno del jugador
            pthread_mutex_unlock(&turno_mutex); // libera el mutex mientras espera
            pthread_mutex_lock(&turno_mutex); // vuelve a bloquear el mutex para obtener el turn0
        }


        int num = rand() % 100 + 1; // número aleatorio entre 1 y 100
        printf("Jugador %ld: turno %d, número aleatorio: %d\n", tid, (i+1), num);

        jugadorActual = (jugadorActual + 1) % *nJugadores; // pasa el turno al siguiente jugador

        pthread_mutex_unlock(&turno_mutex); // libera el mutex para el siguiente jugador
    }


    pthread_exit(NULL);
}
*/




#endif //PROYECTO_01_SO_LOGICAJUEGO_H



