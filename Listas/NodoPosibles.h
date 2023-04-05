//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_NODOPOSIBLES_H
#define PROYECTO_01_SO_NODOPOSIBLES_H
#include "NodoFichas.h"

typedef struct NodoPosibles{
    int nPuntos;
    int posicion;//0 = horizontal y 1 = vertical
    int a;
    int b;
    int numeroRemplazar;
    struct NodoPosibles *siguiente;
    struct NodoPosibles *anterior;
}NodoPosibles;

NodoPosibles *crearNodoPosible(int nPuntos, int a, int b, int posicion, int numeroRemplazar){
    NodoPosibles *nodo = malloc(sizeof(NodoPosibles));
    nodo->nPuntos = nPuntos;
    nodo->a = a;
    nodo->b = b;
    nodo->numeroRemplazar = numeroRemplazar;
    nodo->posicion = posicion;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    return nodo;
}

void mostrarNodoPosible(NodoPosibles *nodo){
    printf("\nPuntos: %d, Ficha: [%d|%d]",nodo->nPuntos,nodo->a,nodo->b);
}

#endif //PROYECTO_01_SO_NODOPOSIBLES_H
