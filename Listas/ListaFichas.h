//
// Created by jurguen on 07/03/23.
//

#ifndef PRUEBAS_LISTAFICHAS_H
#define PRUEBAS_LISTAFICHAS_H
#include "NodoFichas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListaFichas{
    struct NodoFicha *primero;
    struct NodoFicha *ultimo;
}ListaFichas;

ListaFichas *crearLista(){
    ListaFichas *lista = (ListaFichas*) malloc(sizeof(ListaFichas));
    lista->primero=NULL; //Se inicializan las variables
    lista->ultimo=NULL;
    return lista; //Me devuelve una lista
}

int estaVacia(ListaFichas *lista){ //Verifica si la lista esta vacia
    if(lista->primero == NULL){
        return 1;
    }else{
        return 0;
    }
}

void insertar(ListaFichas *lista, NodoFicha *nodo){ //Inserta un nodo dentro de la lista de fichas
    if(estaVacia(lista)){
        lista->primero = nodo;
        lista->ultimo = nodo;
    }else{
        lista->ultimo->siguiente = nodo;
        nodo->anterior = lista->ultimo;
        lista->ultimo = nodo;
    }
}

void insertarFichas(ListaFichas *lista){ //Genera las fichas y las va insertando por medio de un ciclo
    NodoFicha *nodo;
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
    NodoFicha *aux = lista->ultimo; // Se empieza desde el último nodo
    while (aux != NULL) {
        n++; // Se cuenta la cantidad de nodos
        aux = aux->anterior;
    }
    srand(time(NULL)); // Se inicializa el generador de números aleatorios con el tiempo actual
    aux = lista->ultimo;
    while (aux != NULL) {
        int k = rand() % n; // Se genera un número aleatorio entre 0 y n-1
        NodoFicha *auxK = lista->primero;
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

void agregarUnaFicha(ListaFichas *lista, NodoFicha *nodo){ //Agrega una sola ficha
    insertar(lista,nodo);
}

void repartirFichas(ListaFichas *lista, int fichasXjugador, ListaFichas *fichasJugador) { //Reparte fichas a cada jugador

    int i = 0;
    NodoFicha *aux = lista->primero;

    while ( (i < fichasXjugador) ){
        //añadir fichas a la mano del jugador
        agregarUnaFicha(fichasJugador, aux);
        aux = aux->siguiente;
        i++;
    }

    //Elimina las fichas que se van repartiendo
    NodoFicha *aux2 = aux->anterior;
    aux2->siguiente = NULL;
    aux->anterior = NULL;
    lista->primero = aux;
}

void imprimir(ListaFichas *lista){ //imprime la lista

    int indice = 1;

    NodoFicha *aux = lista->primero; //se crea un nodo aux para recorrer la lista
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

//Se recorre la lista para mostrar las fichas
void mostrarMazoComer(ListaFichas *lista){
    NodoFicha *aux = lista->primero;
    while(aux != NULL){
        mostrarFicha(aux);
        aux = aux->siguiente;
    }
}

//busca la ficha doble más alta
NodoFicha *buscarFichaDoble(ListaFichas listaFichas) {

    //recorre lista de fichas de jugador
    NodoFicha *aux = listaFichas.primero;

    //nodo temporal con la ficha más alta
    NodoFicha *alta;
    alta = crearFicha(0, 0);

    while (aux != NULL) {

        //si la ficha es par Y el par es más alto
        if ((aux->a == aux->b) && (aux->a > alta->a)) {
            //busca la ficha par más alta
            alta->a = aux->a;
            alta->b = aux->b;
        }

        //pasar a la siguente ficha
        aux = aux->siguiente;
    }

    return alta;
}



void eliminarFichaJugada(ListaFichas *lista, NodoFicha *nodoEliminar){ //ELimina un nodo (ficha) de una lista de fichas

    if(estaVacia(lista)){ //Primero se verifica que la lista no este vacia
        printf("La lista esta vacia");
    }else{ //En caso de no estar vacia
        NodoFicha *aux1 = lista->primero; //Un nodo que recorre la lista
        NodoFicha *aux2 = crearFicha(nodoEliminar->a,nodoEliminar->b); //Clonamos la ficha a eliminar y se busca

        while (aux1 != NULL){
            //Si la ficha a eliminar es la ultima igualamos las variables de la lista a NULL
            if((aux2->a == lista->ultimo->a) && (aux2->b == lista->ultimo->b) &&  (aux2->a == lista->primero->a) && (aux2->b == lista->primero->b)){
                lista->primero = NULL;
                lista->ultimo = NULL;
                //si elimina la ultima ficha y solo hay 2 fichas
            }else if(  (aux2->a == lista->ultimo->a) && (aux2->b == lista->ultimo->b) && (lista->primero->siguiente == lista->ultimo) && (lista->ultimo->anterior == lista->primero)){
                lista->ultimo = lista->primero;
                lista->primero->siguiente = NULL;
                lista->primero->anterior = NULL;

                //si elimina la primera ficha y solo hay 2 fichas
            }else if( (aux2->a == lista->primero->a) && (aux2->b == lista->primero->b) && (lista->ultimo->anterior == lista->primero) && (lista->primero->siguiente == lista->ultimo) ){
                lista->primero = lista->ultimo;
                lista->ultimo->anterior = NULL;
                lista->ultimo->siguiente = NULL;

                //elimina el último de la lista, si hay más 2 fichas
            }else if((aux2->a == aux1->a && aux2->b  == aux1->b) && (aux1->a == lista->ultimo->a && aux1->b == lista->ultimo->b)) {
                lista->ultimo = aux1->anterior;
                aux1->anterior->siguiente = NULL;
                aux1->anterior = NULL;

                //elimina el primero de la lista, si hay más 2 fichas
            }else if((aux2->a == aux1->a && aux2->b  == aux1->b) && (aux1->a == lista->primero->a && aux1->b == lista->primero->b)) {
                lista->primero = aux1->siguiente;
                aux1->siguiente = NULL;
                aux1->anterior = NULL;

                //Elimina en el medio de la lista
            }else if(aux2->a == aux1->a && aux2->b  == aux1->b){
                aux1->anterior->siguiente = aux1->siguiente;
                aux1->siguiente->anterior = aux1->anterior;
                aux1->anterior = NULL;
                aux1->siguiente = NULL;
            }

            aux1 = aux1->siguiente;
        }
    }
}

#endif //PRUEBAS_LISTAFICHAS_H