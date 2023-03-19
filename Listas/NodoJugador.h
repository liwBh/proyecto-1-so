//
// Created by jurguen on 11/03/23.
//

#ifndef CLIONPROJECTS_NODOJUGADOR_H
#define CLIONPROJECTS_NODOJUGADOR_H

#include "malloc.h"
#include "ListaFichas.h"
#include <stdio.h>
#include <string.h>
typedef struct NodoJugador{
    char nombre[50]; //Nombre de los jugadores dentro del nodo
    int puntos; //Contiene los puntos de los jugadores
    int nTurno;
    //crear maso de fichas
    ListaFichas *listaFichasJugador;
    struct NodoJugador *sig; //Puntero siguiente
    struct NodoJugador *ant; //Puntero anterior
}NodoJugador;

NodoJugador *crearJugador(char nombre[50],int puntos){ //Inicializo las variables
    NodoJugador *jugador = malloc(sizeof(NodoJugador));
    strcpy(jugador->nombre, nombre);
    jugador->listaFichasJugador = crearLista();
    jugador->nTurno = 0;
    jugador->puntos = puntos;
    jugador->sig = NULL;
    jugador->ant = NULL;
    return jugador;
}

void mostrarJugadores(NodoJugador *jugador){ //Muestra los jugadores
    printf("Nombre: %s \nPuntos: %d \n",jugador->nombre,jugador->puntos);
    printf("Fichas del jugador: ");
    nodoFicha *aux = jugador->listaFichasJugador->primero;
    while(aux != NULL){
        mostrarFicha(aux);
        aux = aux->siguiente;
    }
    printf("\n\n");
}

#endif //CLIONPROJECTS_NODOJUGADOR_H
