//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_NODOPOSIBLES_H
#define PROYECTO_01_SO_NODOPOSIBLES_H
#include "NodoFichas.h"

typedef struct NodoPosibles{
    int nPuntos;
    NodoFicha *NodoFicha;
    struct NodoPosibles *siguiente;
    struct NodoPosibles *anterior;
}NodoPosibles;

NodoPosibles *crearNodoPosible(int nPuntos, NodoFicha *nodoFicha1){
    NodoPosibles *nodo = malloc(sizeof(nodo));
    nodo->nPuntos = nPuntos;
    nodo->NodoFicha->a = nodoFicha1->a;
    nodo->NodoFicha->b = nodoFicha1->b;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    return nodo;
}

void mostrarNodoPosible(NodoPosibles *nodo){
    printf("Puntos: %d, Ficha: [%d|%d]",nodo->nPuntos,nodo->NodoFicha->a,nodo->NodoFicha->b);
}

#endif //PROYECTO_01_SO_NODOPOSIBLES_H
