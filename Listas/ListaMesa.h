//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_LISTAMESA_H
#define PROYECTO_01_SO_LISTAMESA_H
#include "NodoMesa.h"
#include "NodoFichas.h"
#include "NodoJugador.h"
#include "ListaJugador.h"
#include "ListaFichas.h"
#include "ListaPosibles.h"


typedef struct ListaMesa{
    struct NodoMesa *primero;
    struct NodoMesa *ultimo;
}ListaMesa;

ListaMesa *crearListaMesa(){
    ListaMesa *listaMesa = (ListaMesa *) malloc(sizeof(ListaMesa)); //Reserva espacio
    listaMesa->primero = NULL; //Inicializo los punteros
    listaMesa->ultimo = NULL; //Inicializo los punteros
    return listaMesa;
}

int isVacia(ListaMesa *lista){ //Metodo que verifica si la lista esta vacia
    if(lista->primero == NULL){
        return 1;
    }else{
        return 0;
    }
}

//realiza la accion de insertar un nodo extremo ficha
void insertarExtremo(ListaMesa *lista, NodoMesa *nodo){
    //Metodo de inserccion dentro de la lista
    if(isVacia(lista)){//primer ficha par colocada
        lista->primero = nodo;
        lista->ultimo =  nodo;
    }else{//si ya colocaron la primer ficha
        lista->ultimo->siguiente = nodo;
        nodo->anterior = lista->ultimo;
        lista->ultimo = nodo;

    }
}

void mostrarListaMesa(ListaMesa *lista){ //Muestra la lista de mesa
    int nExtremo = 1;
    NodoMesa *nodo = lista->primero;
    while(nodo != NULL){ //Hace un recorrido
        mostrarNodoMesa(nodo, nExtremo); //Va mostrando los nodos de la mesa
        nodo = nodo->siguiente;
        nExtremo++;
    }
}




#endif //PROYECTO_01_SO_LISTAMESA_H
