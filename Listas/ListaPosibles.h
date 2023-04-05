//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_LISTAPOSIBLES_H
#define PROYECTO_01_SO_LISTAPOSIBLES_H
#include "NodoPosibles.h"
#include "ListaJugador.h"
#include "ListaPosibles.h"
#include "ListaMesa.h"


typedef struct ListaPosibles{

    struct NodoPosibles *primero;
    struct NodoPosibles *ultimo;

}ListaPosibles;


ListaPosibles *crearListaPosibles(){
    ListaPosibles *listaPosibles = (ListaPosibles*) malloc(sizeof(ListaPosibles));
    listaPosibles->primero = NULL;
    listaPosibles->ultimo = NULL;
    return listaPosibles;
}

int vaciaPosibles(ListaPosibles *lista){ //Metodo que verifica si la lista esta vacia
    if(lista->primero == NULL){
        return 1;
    }else{
        return 0;
    }
}

void insertarNodoPosible(ListaPosibles *lista, NodoPosibles *nodo){ //Metodo de inserccion dentro de la lista
    if(vaciaPosibles(lista)){
        lista->primero = nodo;
        lista->ultimo =  nodo;
    }else{
        lista->ultimo->siguiente = nodo;
        nodo->anterior = lista->ultimo;
        lista->ultimo = nodo;
    }
}


void mostrarListaPosibles(ListaPosibles *lista){
    NodoPosibles *aux = lista->primero;
    while (aux != NULL){
        mostrarNodoPosible(aux);
        aux = aux->siguiente;
    }
}

NodoPosibles *obtenerFichaJugar(ListaPosibles *lista){
    NodoPosibles *aux = lista->primero;
    NodoPosibles *valor = crearNodoPosible(0,0,0,0);
    int puntajeAlto = 0;
    while (aux != NULL){
        if(aux->nPuntos >= puntajeAlto && aux->a + aux->b > valor->a + valor->b) {
            puntajeAlto = aux->nPuntos;
            valor = crearNodoPosible(aux->nPuntos,aux->a,aux->b,aux->posicion);
        }
        aux = aux->siguiente;
    }
    return valor;
}

#endif //PROYECTO_01_SO_LISTAPOSIBLES_H