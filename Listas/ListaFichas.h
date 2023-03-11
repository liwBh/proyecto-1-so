//
// Created by jurguen on 07/03/23.
//

#ifndef PRUEBAS_LISTAFICHAS_H
#define PRUEBAS_LISTAFICHAS_H
#include "NodoFichas.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListaFichas{
    struct nodoFicha *primero;
    struct nodoFicha *ultimo;
}ListaFichas;

ListaFichas *crearLista(){
    ListaFichas *lista = (ListaFichas*) malloc(sizeof(ListaFichas));
    lista->primero=NULL; //Se inicializan las variables
    lista->ultimo=NULL;
    return lista; //Me devuelve una lista
}

int estaVacia(ListaFichas *lista){
    if(lista->primero == NULL){
        return 1;
    }else{
        return 0;
    }
}

void insertar(ListaFichas *lista, nodoFicha *nodo){
    if(estaVacia(lista)){
        lista->primero = nodo;
        lista->ultimo = nodo;
    }else{
        lista->ultimo->siguiente = nodo;
        nodo->anterior = lista->ultimo;
        lista->ultimo = nodo;
    }
}

void insertarFichas(ListaFichas *lista){
    nodoFicha *nodo;
    for(int i = 0; i <= 6; i++) {
        nodo = crearFicha(i,i);
        insertar(lista,nodo);
        for(int j = i+1; j <= 6; j++) {
           nodo = crearFicha(i,j);
            insertar(lista,nodo);
        }
    }
}

void desordenar(ListaFichas *lista) {
    int n = 0;
    nodoFicha *aux = lista->ultimo; // Se empieza desde el último nodo
    while (aux != NULL) {
        n++; // Se cuenta la cantidad de nodos
        aux = aux->anterior;
    }

    srand(time(NULL)); // Se inicializa el generador de números aleatorios con el tiempo actual

    aux = lista->ultimo;
    while (aux != NULL) {
        int k = rand() % n; // Se genera un número aleatorio entre 0 y n-1
        nodoFicha *auxK = lista->primero;
        for (int i = 0; i < k; i++) {
            auxK = auxK->siguiente; // Se busca el nodo en la posición k
        }
        // Se intercambian los nodos en las posiciones aux y auxK
        int tempA = aux->a;
        int tempB = aux->b;
        aux->a = auxK->a;
        aux->b = auxK->b;
        auxK->a = tempA;
        auxK->b = tempB;

        aux = aux->anterior;
        n--; // Se reduce la cantidad de nodos por recorrer
    }
}

void primerNodo(ListaFichas *lista){
    mostrarFicha(lista->primero);
}

void agregarUnaFicha(ListaFichas *lista, nodoFicha *nodo){
    mostrarFicha(nodo);
    insertar(lista,nodo);
}

void repartirFichas(ListaFichas *lista, int fichasXjugador, ListaFichas *fichasJugador) {

    int i = 0;
    nodoFicha *aux = lista->primero;

    while ( (i < fichasXjugador) ){

        //añadir fichas a la mano del jugador
        agregarUnaFicha(fichasJugador, aux);

        //eliminar la ficha del maso
        //eliminarUna(lista, aux);

        //printf("ficha #%d", i);
        aux = aux->siguiente;
        i++;
    }

    nodoFicha *aux2 = aux->anterior;
    aux2->siguiente = NULL;
    aux->anterior = NULL;
    lista->primero = aux;


}

//Tengo problemas en este metodo
void eliminarFichas(ListaFichas *lista, int n){
    nodoFicha *aux = lista->primero;
    nodoFicha *aux1 = NULL;
    int x=0;
    while(x<3){
        aux1 = aux;
        aux = aux->siguiente;
        aux1->siguiente = NULL;
        x++;
    }
}

void imprimir(ListaFichas *lista){ //imprime la lista

    int indice = 1;

    nodoFicha *aux = lista->primero; //se crea un nodo aux para recorrer la lista
    while(aux!=NULL) { //Mientras sea diferente de null me recorre la lista
        if(indice==5){
            printf("\n");
            indice=1;
        }

        mostrarFicha(aux); //Este metodo me imprime los nodos de la lista
        aux = aux->siguiente; //El aux se va moviendo

        indice++;
    }
    printf("\n");
}

#endif //PRUEBAS_LISTAFICHAS_H
