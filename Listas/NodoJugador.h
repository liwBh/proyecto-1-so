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
    char nombre[50];
    int puntos;
    //crear maso de fichas
    ListaFichas *listaFichasJugador;

    struct NodoJugador *sig;
    struct NodoJugador *ant;
}NodoJugador;

NodoJugador *crearJugador(char nombre[50],int puntos){
    NodoJugador *jugador = malloc(sizeof(NodoJugador));
    strcpy(jugador->nombre, nombre);
    jugador->listaFichasJugador = crearLista();

    jugador->puntos = puntos;
    jugador->sig = NULL;
    jugador->ant = NULL;

    return jugador;
}

void mostrarJugadores(NodoJugador *jugador){
    printf("Nombre: %s, Puntos: %d\n",jugador->nombre,jugador->puntos);
}

#endif //CLIONPROJECTS_NODOJUGADOR_H
