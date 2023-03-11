//
// Created by jurguen on 11/03/23.
//

#ifndef CLIONPROJECTS_LISTAJUGADOR_H
#define CLIONPROJECTS_LISTAJUGADOR_H

#include "NodoJugador.h"

typedef struct ListaJugador{
    struct NodoJugador *primero;
    struct NodoJugador *ultimo;
}ListaJugador;

ListaJugador *crearListaJugador(){
    ListaJugador *listaJugador = (ListaJugador*) malloc(sizeof(listaJugador));
    listaJugador->primero = NULL;
    listaJugador->ultimo = NULL;
    return listaJugador;
}

int vacia(ListaJugador *lista){
    if(lista->primero == NULL){
        return 1;
    }else{
        return 0;
    }
}

void insertarJugador(ListaJugador *lista, NodoJugador *nodo){
    if(vacia(lista)){
        lista->primero = nodo;
        lista->ultimo =  nodo;

    }else{
        lista->ultimo->sig = nodo;
        nodo->ant = lista->ultimo;
        lista->ultimo = nodo;
    }

}

void mostrar(ListaJugador *lista){ //imprime la lista
    NodoJugador *aux = lista->primero; //se crea un nodo aux para recorrer la lista
    while(aux!=NULL) { //Mientras sea diferente de null me recorre la lista
        mostrarJugadores(aux); //Este metodo me imprime los nodos de la lista
        aux = aux->sig; //El aux se va moviendo
    }
}

void most(ListaJugador *listaJugador){
    nodoFicha *aux = listaJugador->primero->listaFichasJugador->primero;
    while(aux != NULL){
        mostrarFicha(aux);
        aux = aux->siguiente;
    }
}


#endif //CLIONPROJECTS_LISTAJUGADOR_H
