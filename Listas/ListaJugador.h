//
// Created by jurguen on 11/03/23.
//

#ifndef CLIONPROJECTS_LISTAJUGADOR_H
#define CLIONPROJECTS_LISTAJUGADOR_H

#include "NodoJugador.h"

typedef struct ListaJugador{
    struct NodoJugador *primero; //Puntero que referencia al primero de lista
    struct NodoJugador *ultimo; //Puntero que referencia al ultimo de la lista
}ListaJugador;

//Creo la lista de jugadores, reservando espacio en memoria e inicializo los atributos
ListaJugador *crearListaJugador(){
    ListaJugador *listaJugador = (ListaJugador*) malloc(sizeof(listaJugador)); //Reserva espacio
    listaJugador->primero = NULL; //Inicializo los punteros
    listaJugador->ultimo = NULL; //Inicializo los punteros
    return listaJugador;
}

int vacia(ListaJugador *lista){ //Metodo que verifica si la lista esta vacia
    if(lista->primero == NULL){
        return 1;
    }else{
        return 0;
    }
}

void insertarJugador(ListaJugador *lista, NodoJugador *nodo){ //Metodo de inserccion dentro de la lista
    if(vacia(lista)){
        lista->primero = nodo;
        lista->ultimo =  nodo;

    }else{
        lista->ultimo->sig = nodo;
        nodo->ant = lista->ultimo;
        lista->ultimo = nodo;
    }
}

//Metodo burbuja para ordenar el mazo de cada jugador
void metodoBurbujaMazoJugador(ListaJugador *listaJugador){
    NodoJugador *nodoJugador = listaJugador->primero; //Nodo que apunta al primero de la lista de jugadores
    while(nodoJugador != NULL){ //Ciclo para recorrer la lista de jugadores
        nodoFicha *nodoActual = nodoJugador->listaFichasJugador->primero; //Nodo que apunta al primero de la lista de fichas que tiene cada jugador
        while (nodoActual != NULL){ //Ciclo para recorrer la lista de las fichas de cada jugador
            nodoFicha *nodoSiguiente = nodoActual->siguiente; //Un nodo que va adelante del primero de referencia
            while (nodoSiguiente != NULL){ //Empiezo a recorrer el nodo que va adelante
                if (nodoSiguiente->a < nodoActual->a || (nodoSiguiente->a == nodoActual->a && nodoSiguiente->b < nodoActual->b)) { //Posibles opciones de poder intercambiar
                    // Intercambiar los datos de los nodos
                    int tempA = nodoActual->a;
                    int tempB = nodoActual->b;
                    nodoActual->a = nodoSiguiente->a;
                    nodoActual->b = nodoSiguiente->b;
                    nodoSiguiente->a = tempA;
                    nodoSiguiente->b = tempB;
                }
                nodoSiguiente = nodoSiguiente->siguiente; //Va avanzando en la lista con uno mas adelante en la lista de fichas
            }
            nodoActual = nodoActual->siguiente; //Va avanzando en la lista de fichas
        }
        nodoJugador = nodoJugador->sig; //Va avanzado en la lista de jugadores
    }
}

//Valido cuantas dobles tiene cada jugador, pero problemas en el main
int validarDobles(ListaJugador *listaJugador){
    NodoJugador *nodo = listaJugador->primero;
    int indice=0;
    while (nodo != NULL) {
        nodoFicha *nodoFicha1 = nodo->listaFichasJugador->primero;
        while (nodoFicha1 != NULL){
            if(nodoFicha1->a == nodoFicha1->b){
                indice++;
                printf("%d",indice);
            }
            nodoFicha1 = nodoFicha1->siguiente;
        }
        nodo = nodo->sig;
    }
    return indice;
}

void mostrar(ListaJugador *lista){ //imprime la lista
    NodoJugador *aux = lista->primero; //se crea un nodo aux para recorrer la lista
    while(aux!=NULL) { //Mientras sea diferente de null me recorre la lista
        mostrarJugadores(aux); //Este metodo me imprime los nodos de la lista
        aux = aux->sig; //El aux se va moviendo
    }
}

#endif //CLIONPROJECTS_LISTAJUGADOR_H
