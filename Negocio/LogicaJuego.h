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

void *turnoJugador(void* parametro) {

    NodoJugador *nodoJugador = (NodoJugador *) parametro;
    //printf("El nombre del jugador en el turno es: %s\n",nodoJugador->nombre);

    




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



