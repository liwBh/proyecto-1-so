//
// Created by jurguen on 07/03/23.
//

#ifndef PRUEBAS_NODOFICHAS_H
#define PRUEBAS_NODOFICHAS_H

#include "malloc.h"
#include <stdio.h>

//La estructura de las fichas
typedef struct NodoFicha{
    int a;//extremo a
    int b;//extremo b
    struct NodoFicha *siguiente;
    struct NodoFicha *anterior;
}NodoFicha;

//Metodos de las fichas

//Constructor
NodoFicha *crearFicha(int a, int b){
    NodoFicha *ficha = malloc(sizeof(NodoFicha));
    ficha->a=a;
    ficha->b=b;
    ficha->siguiente = NULL;
    ficha->anterior = NULL;
    return ficha;
}


//toString ficha
void mostrarFicha(NodoFicha *ficha){
    printf("[%d|%d] ",ficha->a,ficha->b);
}

#endif //PRUEBAS_NODOFICHAS_H
