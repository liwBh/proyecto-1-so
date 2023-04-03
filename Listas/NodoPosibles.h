//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_NODOPOSIBLES_H
#define PROYECTO_01_SO_NODOPOSIBLES_H
#include "NodoFichas.h"

typedef struct NodoPosibles{
    int nPuntos;
    int a;
    int b;
    struct NodoPosibles *siguiente;
    struct NodoPosibles *anterior;
}NodoPosibles;

NodoPosibles *crearNodoPosible(int nPuntos, int a, int b){
    NodoPosibles *nodo = malloc(sizeof(NodoPosibles));
    nodo->nPuntos = nPuntos;
    nodo->a = a;
    nodo->b = b;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    return nodo;
}

void mostrarNodoPosible(NodoPosibles *nodo){
    printf("Puntos: %d, Ficha: [%d|%d]",nodo->nPuntos,nodo->a,nodo->b);
}

#endif //PROYECTO_01_SO_NODOPOSIBLES_H
