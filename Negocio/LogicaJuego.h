#ifndef PROYECTO_01_SO_LOGICAJUEGO_H
#define PROYECTO_01_SO_LOGICAJUEGO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../Listas/ListaMesa.h"


int  calcularFichasXjugador( int nJugadores){
   return 28/ (nJugadores+1);
}

int validarNJugadores(char input[50] ){

    int entradaValida = 0;

    for (int i = 0; input[i] != '\0'; i++) {

        //validar si todoslos caracteres son numericos
        if (!isdigit(input[i])) {
            entradaValida = 0;
            break;
        }else {
            entradaValida = 1;
        }
    }

    if (entradaValida != 0) {
        //convertir a numerico
        entradaValida = atoi(input);

        if ((entradaValida<2) || (entradaValida>7) ){
            entradaValida = 0;
        }
    }

    return entradaValida;
}

void actualizarListaMesa(ListaMesa *listaMesa, NodoPosibles *nodoPosibles){

    //recorrer la lista de mesa
    NodoMesa *nodoAux = listaMesa->primero;
    while(nodoAux != NULL){

        if(nodoPosibles->a == nodoPosibles->b){// si la ficha seleccionada es par, modificar y agregar otro extremo
            //Verificar si horizontal o vertical da mas puntos


        }else{//si no es par, modificar un extremo
            if(nodoAux->numero == nodoPosibles->a){//si el extremo disponible en mesa es igual al extremo a de la ficha
                nodoAux->numero = nodoPosibles->b;
                break;
            }else if(nodoAux->numero == nodoPosibles->b){//si el extremo disponible en mesa es igual al extremo b de la ficha
                nodoAux->numero = nodoPosibles->a;
                break;
            }
        }
        nodoAux = nodoAux->siguiente;
    }



}

void jugarTurno(ListaMesa *lista, NodoJugador *nodoJugador, ListaPosibles *listaPosibles){

    if( isVacia(lista) && nodoJugador->nTurno == 1){//si la lista esta vacia es el primero en jugar
        //buscar el doble mas alto
        NodoFicha *parMasAlto = buscarFichaDoble( *nodoJugador->listaFichasJugador );

        //insertar ambos extremos en la listaMesa
        NodoMesa *nodoExtremo1  = crearNodoMesa(parMasAlto->a);
        NodoMesa *nodoExtremo2  = crearNodoMesa(parMasAlto->b);
        insertarExtremo(lista,nodoExtremo1);
        insertarExtremo(lista,nodoExtremo2);

        //si es el [5|5], suma 2 puntos
        if(parMasAlto->a == 5 && parMasAlto->b == 5){
            nodoJugador->puntos+=2;
        }

        //eliminar ficha colocada de la lista del jugador
        eliminarFichaJugada(nodoJugador->listaFichasJugador, parMasAlto);
    } else{

        if(vaciaPosibles(listaPosibles)){//si no tiene fichas para jugar
            printf("\nEl jugador debe comer una ficha y pasar turno");

        }else{//si tiene fichas para jugar
            printf("\n*Posibles fichas para jugar el turno: ");
            mostrarListaPosibles(listaPosibles);

            //buscar la ficha con el puntaje mas alto y con la suma de sus extremos que sea menor
            NodoPosibles *fichaJugar = obtenerFichaJugar(listaPosibles);
            printf("\n\n*La ficha a colocar: [%d|%d]\n", fichaJugar->a, fichaJugar->b);

            //modificar o agregar el nuevo extremo en la lisa de mesa
            actualizarListaMesa(lista, fichaJugar);

            //sumarle los puntos
            nodoJugador->puntos+= fichaJugar->nPuntos;

            //eliminar la ficha colocada de la lista del jugador
            NodoFicha  *nodoEliminar = crearFicha(fichaJugar->a,fichaJugar->b);
            eliminarFichaJugada(nodoJugador->listaFichasJugador, nodoEliminar);

            //imprimir datos del jugador
            printf("\n--------Datos del jugador-------- \n");
            mostrarJugadores(nodoJugador);

            //imprimir extremos en mesa

            printf("\n--------Mesa------\n");
            mostrarListaMesa(lista);
        }

    }

}

int calcularPuntos(ListaMesa *listaMesa, int extremoSumar,int extremoRestar, int isDoble){

    int sumatoria = extremoSumar;

    //recorrer listaMesa y sumo todos los extremos
    NodoMesa *recorreMesa = listaMesa->primero;
    while (recorreMesa != NULL){
        sumatoria += recorreMesa->numero;
        recorreMesa = recorreMesa->siguiente;
    }

    if(isDoble){//si es doble y posicion vertical
        sumatoria += extremoSumar;
    }

    sumatoria -= extremoRestar;

    return (sumatoria % 5 == 0)? (sumatoria / 5) : 0;
}

void agregarFichaConPuntaje(ListaPosibles *listaPosibles, ListaMesa *listaMesa, NodoFicha *nodoFicha){
    int nPuntos = 0;

    //hacer calculos con cada extremo disponible en la mesa
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

            //Aqui trabaja con la B, Siempre juega horizontal
            nPuntos = calcularPuntos(listaMesa, nodoFicha->b,nodoFicha->a, 0);

            //agrego la ficha a listaPosible y nPuntaje
            //creo nodoMesa
            NodoPosibles *nodoPosibles = crearNodoPosible( nPuntos,nodoFicha->a, nodoFicha->b,0);

            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);


        }else if(recorreMesa->numero == nodoFicha->b){//Hay cocidencia con extremo b

            //Aqui trabaja con la A, Siempre juega horizontal
            nPuntos = calcularPuntos(listaMesa, nodoFicha->a,nodoFicha->b, 0);

            //agrego la ficha a listaPosible y nPuntaje
            //creo nodoMesa
            NodoPosibles *nodoPosibles = crearNodoPosible( nPuntos,nodoFicha->a, nodoFicha->b,0);
            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);
        }

        recorreMesa = recorreMesa->siguiente;
    }

}

ListaPosibles  *llenarListaPosibles(ListaPosibles  *listaPosibles, ListaMesa *listaMesa, ListaFichas *listaFichas){

    //recorrer lista de fichas del jugador
    NodoFicha *nodoFicha = listaFichas->primero;

    while(nodoFicha != NULL){
        //envio la ficha a un metodo para calcular puntaje y posicion
        agregarFichaConPuntaje(listaPosibles,listaMesa,nodoFicha);
        //paso a la siguiente ficha
        nodoFicha = nodoFicha->siguiente;
    }
}












#endif //PROYECTO_01_SO_LOGICAJUEGO_H



