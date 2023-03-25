//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_NODOMESA_H
#define PROYECTO_01_SO_NODOMESA_H
#include "malloc.h"
#include <stdio.h>

typedef struct NodoMesa{
    int numero;
    struct NodoMesa *siguiente;
    struct NodoMesa *anterior;
}NodoMesa;

NodoMesa *crearNodoMesa(int numero){
    NodoMesa *nodo = malloc(sizeof(nodo));
    nodo->numero = numero;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    return nodo;
}

void mostrarNodoMesa(NodoMesa *nodoMesa, int nExtremo){
    printf("\nExtremo #%d = %d",nExtremo, nodoMesa->numero);
}

#endif //PROYECTO_01_SO_NODOMESA_H
