//
// Created by jurguen on 07/03/23.
//

#ifndef PRUEBAS_NODOFICHAS_H
#define PRUEBAS_NODOFICHAS_H

#include "malloc.h"
#include <stdio.h>

//La estructura de las fichas
typedef struct nodoFicha{
    int a;//extremo a
    int b;//extremo b
    struct nodoFicha *siguiente;
    struct nodoFicha *anterior;
}nodoFicha;

//Metodos de las fichas

//Constructor
nodoFicha *crearFicha(int a, int b){
    nodoFicha *ficha = malloc(sizeof(nodoFicha));
    ficha->a=a;
    ficha->b=b;
    ficha->siguiente = NULL;
    ficha->anterior = NULL;
    return ficha;
}


//toString ficha
void mostrarFicha(nodoFicha *ficha){
    printf("[%d|%d] ",ficha->a,ficha->b);
}

#endif //PRUEBAS_NODOFICHAS_H
