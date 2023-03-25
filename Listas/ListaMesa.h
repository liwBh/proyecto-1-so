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


typedef struct ListaMesa{
    struct NodoMesa *primero;
    struct NodoMesa *ultimo;
}ListaMesa;

ListaMesa *crearListaMesa(){
    ListaMesa *listaMesa = (ListaMesa *) malloc(sizeof(listaMesa)); //Reserva espacio
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
void insertarExtremo(ListaMesa *lista, NodoMesa *nodo){ //Metodo de inserccion dentro de la lista

    if(isVacia(lista)){
        lista->primero = nodo;
        lista->ultimo =  nodo;
    }else{
        lista->ultimo->siguiente = nodo;
        nodo->anterior = lista->ultimo;
        lista->ultimo = nodo;
    }
}


void jugarTurno(ListaMesa *lista,  NodoJugador *nodoJugador){

    if( isVacia(lista) && nodoJugador->nTurno == 1){//si la lista esta vacia es el primero en jugar
        //buscar el doble mas alto
        NodoFicha *parMasAlto = buscarFichaDoble( *nodoJugador->listaFichasJugador );
        //insertar ambos extremos en la listaMesa
        NodoMesa *nodoExtremo1  = crearNodoMesa(parMasAlto->a);
        NodoMesa *nodoExtremo2  = crearNodoMesa(parMasAlto->b);
        insertarExtremo(lista,nodoExtremo1);
        insertarExtremo(lista,nodoExtremo2);
        //eliminar ficha colocada
        eliminarFichaJugada(nodoJugador->listaFichasJugador, parMasAlto);
    } else{
        //lista de posibles fichas

        //ficha que mas putos genere

        //por tanto agregamos ambos extremos

    }

}




void mostrarListaMesa(ListaMesa *lista){
    int nExtremo = 1;
    NodoMesa *nodo = lista->primero;
    while(nodo != NULL){
        mostrarNodoMesa(nodo, nExtremo);
        nodo = nodo->siguiente;
        nExtremo++;
    }
}
void insertarFichaHorizontal(ListaMesa *lista){

}

#endif //PROYECTO_01_SO_LISTAMESA_H