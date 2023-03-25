//
// Created by liwbh on 24/03/23.
//

#ifndef PROYECTO_01_SO_LISTAPOSIBLES_H
#define PROYECTO_01_SO_LISTAPOSIBLES_H
#include "NodoPosibles.h"
#include "ListaJugador.h"
#include "ListaMesa.h"

typedef struct ListaPosibles{

    struct NodoPosibles *primero;
    struct NodoPosibles *ultimo;

}ListaPosibles;

ListaPosibles *crearListaPosibles(){
    ListaPosibles *listaPosibles = (ListaPosibles*) malloc(sizeof(listaPosibles));
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

/*
ListaPosibles  *llenarListaPosibles(ListaJugador *listaJugador, ListaPosibles  *listaPosibles, int a, int b){
    NodoJugador *nodoJugador = listaJugador->primero;
    while(nodoJugador != NULL){
        NodoFicha *nodoFicha = nodoJugador->listaFichasJugador->primero;

        while(nodoFicha != NULL){

            if(nodoFicha->a || nodoFicha->b == a || b){
                insertarNodoPosible(listaPosibles,nodoFicha->a);
            }
            nodoFicha = nodoFicha->siguiente;

        }
        nodoJugador = nodoJugador->sig;
    }
}*/

int calcularPuntos(ListaMesa *listaMesa, int extremo, int isDoble){

    int sumatoria = extremo;

    //recorrer listaMesa y sumo todos los extremos
    NodoMesa *recorreMesa = listaMesa->primero;
    while (recorreMesa != NULL){
        sumatoria += recorreMesa->numero;
        recorreMesa = recorreMesa->siguiente;
    }

    if(isDoble){//si es doble y posicion vertical
        sumatoria += extremo;
    }

    return sumatoria / 5;
}

void insertarPuntajeFicha(ListaPosibles *listaPosibles, ListaMesa *listaMesa, NodoFicha *nodoFicha){
    int nPuntos = 0;

    //hacer calculos con cada extremo disponible
    NodoMesa *recorreMesa = listaMesa->primero;
    // revisando como poner la ficha
    while(recorreMesa != NULL){



        //si entra a alguno de los if hay al menos un extremo que coincide
        if(recorreMesa->numero == nodoFicha->a && recorreMesa->numero == nodoFicha->b){
            printf("Entrooo!, if pares");

            /*
            //Aqui trabaja con la doble
           //revisar si la coloca vertical, suma ambos extremos
            int posicionVertical = calcularPuntos(listaMesa, nodoFicha->a, 1);
            //revisar si la coloca  horizontal, solo suma un extremo
            int posicionHorizontal = calcularPuntos(listaMesa, nodoFicha->a, 0);

            //sumar todos los extremos y dividirlo entre 5
           //comparar cual es mas alto, el numero mas alto me dice que posicion colocar
            if( posicionVertical >  posicionHorizontal){
                //si es vertical agrego ambos extremos
                //creo nodoMesa
                NodoPosibles *nodoPosibles = crearNodoPosible( posicionVertical,nodoFicha);
                //inserto nodo mesa extremo a
                insertarNodoPosible(listaPosibles,nodoPosibles);
                //inserto nodo mesa extremo b
                insertarNodoPosible(listaPosibles,nodoPosibles);

            }else{
                //si es horizontal agrego 1 extremo
                //creo nodoMesa
                NodoPosibles *nodoPosibles = crearNodoPosible( posicionHorizontal,nodoFicha);
                //inserto nodo mesa
                insertarNodoPosible(listaPosibles,nodoPosibles);
            }*/

        }else if( recorreMesa->numero == nodoFicha->a){//Hay cocidencia con extremo a
            printf("if extremo a -");
            //Aqui trabaja con la B, Siempre juega horizontal
           /* nPuntos = calcularPuntos(listaMesa, nodoFicha->b, 0);
            //agrego la ficha a listaPosible y nPuntaje
            //creo nodoMesa
            NodoPosibles *nodoPosibles = crearNodoPosible( nPuntos,nodoFicha);
            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);*/

        }else if(recorreMesa->numero == nodoFicha->b){//Hay cocidencia con extremo b
            printf("if extremo b -");
            //Aqui trabaja con la A, Siempre juega horizontal
           /* nPuntos = calcularPuntos(listaMesa, nodoFicha->a, 0);
            //agrego la ficha a listaPosible y nPuntaje
            //creo nodoMesa
            NodoPosibles *nodoPosibles = crearNodoPosible( nPuntos,nodoFicha);
            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);*/
        }

        recorreMesa = recorreMesa->siguiente;
    }

}

ListaPosibles  *llenarListaPosibles(ListaPosibles  *listaPosibles, ListaMesa *listaMesa, ListaFichas *listaFichas){
    NodoFicha *nodoFicha = listaFichas->primero;

    while(nodoFicha != NULL){

        insertarPuntajeFicha(listaPosibles,listaMesa,nodoFicha);
        nodoFicha = nodoFicha->siguiente;
    }
}

void mostrarListaPosibles(ListaPosibles *lista){
    NodoPosibles *aux = lista->primero;
    while (aux != NULL){
        mostrarNodoPosible(aux);
        aux = aux->siguiente;
    }
}
#endif //PROYECTO_01_SO_LISTAPOSIBLES_H
