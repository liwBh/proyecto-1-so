#ifndef PROYECTO_01_SO_LOGICAJUEGO_H
#define PROYECTO_01_SO_LOGICAJUEGO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>



int  calcularFichasXjugador( int nJugadores){
   return 28/ (nJugadores+1);
}

void *turnoJugador(int nJugadores) {
    pthread_mutex_t turno_mutex;//variable para aplicar hilos sincronos
    pthread_mutex_init(&turno_mutex, NULL); // inicializa el mutex
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
        printf("Jugador %ld: turno %d, número aleatorio: %d\n", tid, i+1, num);
        jugadorActual = (jugadorActual + 1) % nJugadores; // pasa el turno al siguiente jugador
        pthread_mutex_unlock(&turno_mutex); // libera el mutex para el siguiente jugador
    }


    pthread_mutex_destroy(&turno_mutex); // c el mutex
    pthread_exit(NULL);
}





#endif //PROYECTO_01_SO_LOGICAJUEGO_H
