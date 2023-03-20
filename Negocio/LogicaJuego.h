#ifndef PROYECTO_01_SO_LOGICAJUEGO_H
#define PROYECTO_01_SO_LOGICAJUEGO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


int  calcularFichasXjugador( int nJugadores){
   return 28/ (nJugadores+1);
}

int validarNJugadores(char input[50] ){

    int entradaValida = 0;

    for (int i = 0; input[i] != '\0'; i++) {

        //validar si todoslos caracteres son numericos
        if (!isdigit(input[i])) {
            entradaValida = 0;
            break;
        }else {
            entradaValida = 1;
        }
    }

    if (entradaValida != 0) {
        //convertir a numerico
        entradaValida = atoi(input);

        if ((entradaValida<2) || (entradaValida>7) ){
            entradaValida = 0;
        }
    }

    return entradaValida;
}


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








#endif //PROYECTO_01_SO_LOGICAJUEGO_H



