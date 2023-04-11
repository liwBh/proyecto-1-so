#ifndef PROYECTO_01_SO_LOGICAJUEGO_H
#define PROYECTO_01_SO_LOGICAJUEGO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../Listas/ListaMesa.h"
#include "../Sonidos/Sonido.h"
#include <unistd.h>

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

        entradaValida = (int) strtol(input,NULL,10);


        if ((entradaValida<2) || (entradaValida>7) ){
            entradaValida = 0;
        }
    }

    return entradaValida;
}

//metodo que modifica y inserta nuevos extremos
void actualizarListaMesa(ListaMesa *listaMesa, NodoPosibles *nodoPosibles){

    //recorrer la lista de mesa
    NodoMesa *nodoAux = listaMesa->primero;
    while(nodoAux != NULL){

        if(nodoPosibles->a == nodoPosibles->b && nodoPosibles->posicion == 1 ){// si la ficha seleccionada es par, modificar y agregar otro extremo
            //Verificar si la posicion es vertical da mas puntos
            NodoMesa *nodoMesa = crearNodoMesa(nodoPosibles->b);
            //Agrega un nuevo extremo
            insertarExtremo(listaMesa, nodoMesa);
            printf("\nAgregando un nuevo nodo\n");
            break;
        }else{//si no es par, modificar un extremo
            if( (nodoAux->numero == nodoPosibles->numeroRemplazar) && (nodoAux->numero == nodoPosibles->a) ){//si el extremo disponible en mesa es igual al extremo a de la ficha
                nodoAux->numero = nodoPosibles->b;
                break;
            }else if( (nodoAux->numero == nodoPosibles->numeroRemplazar) && (nodoAux->numero == nodoPosibles->b)){//si el extremo disponible en mesa es igual al extremo b de la ficha
                nodoAux->numero = nodoPosibles->a;
                break;
            }
        }
        nodoAux = nodoAux->siguiente;
    }



}

//metodo que ordena las fichas del jugador
void ordenarFichasJugador(ListaFichas *lista){
    NodoFicha *nodoActual = lista->primero; //Nodo que apunta al primero de la lista de fichas que tiene cada jugador
    while (nodoActual != NULL){ //Ciclo para recorrer la lista de las fichas de cada jugador
        NodoFicha *nodoSiguiente = nodoActual->siguiente; //Un nodo que va adelante del primero de referencia
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
}


//metodo que elige la ficha que es colocada por el jugador
NodoFicha *elegirFichaComer(ListaFichas *lista){
    //Agarra el primero de la lista de fichas
    NodoFicha *devolver = crearFicha(lista->primero->a,lista->primero->b);
    //Elimina la ficha de esa lista
    eliminarFichaJugada(lista,devolver);
    return devolver;
}

//Come la ficha por lo tanto se le agrega a la lista del jugador
void comerFicha(NodoJugador *nodoJugador, NodoFicha *nodoComer){

    //Si el jugador no tiene fichas y tiene que comer
    if(estaVacia(nodoJugador->listaFichasJugador)){
        nodoJugador->listaFichasJugador = crearLista(); //Se le crea una lista nuevamente
        insertar(nodoJugador->listaFichasJugador,nodoComer); //Se le inserta el nodo que comio en lista nueva
        ordenarFichasJugador(nodoJugador->listaFichasJugador); //Hace un metodo burbuja para acomodar las fichas de un jugador
    }else{
        //Se pasan referencias para insertar el nodo que comio al inicio de la lista
        NodoFicha *aux = nodoJugador->listaFichasJugador->primero;
        nodoJugador->listaFichasJugador->primero = nodoComer;
        nodoComer->siguiente = aux;
        aux->anterior = nodoComer;
        //Luego se ordenan las fichas de la lista
        ordenarFichasJugador(nodoJugador->listaFichasJugador);
    }
}

void imprimirDatosJugador(ListaMesa *lista, NodoJugador *nodoJugador){
    //imprimir datos del jugador
    printf("\n--------Datos del jugador-------- \n");
    mostrarJugadores(nodoJugador);

    //imprimir extremos en mesa
    printf("\n--------Mesa------\n");
    mostrarListaMesa(lista);
}

void jugarTurno(ListaMesa *lista, NodoJugador *nodoJugador, ListaPosibles *listaPosibles, ListaFichas *listaMaso){

    if( isVacia(lista) && nodoJugador->nTurno == 1){//si la lista esta vacia es el primero en jugar
        printf("\n[Primer Ficha en Mesa]\n");
        //buscar el doble mas alto
        NodoFicha *parMasAlto = buscarFichaDoble( *nodoJugador->listaFichasJugador );
        printf("\n*La ficha a colocar: [%d|%d]\n", parMasAlto->a, parMasAlto->b);
        reproducirSonido("/Sonidos/ponerFicha.wav");

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

        //imprimir datos del jugador
        imprimirDatosJugador(lista, nodoJugador);
    } else{

        if(vaciaPosibles(listaPosibles)){//si no tiene fichas para jugar
            printf("\nEl jugador debe comer una ficha y pasar turno");

            if(!estaVacia(listaMaso)){
                NodoFicha *fichaComerJugador  = elegirFichaComer(listaMaso);

                reproducirSonido("/Sonidos/comerFicha.wav");
                printf("\nLa ficha comida es: [%d|%d]\n", fichaComerJugador->a, fichaComerJugador->b);
                comerFicha(nodoJugador, fichaComerJugador);

                printf("\n--------Lista de comer despues de que el jugador -------- \n");
                mostrarMazoComer(listaMaso);
                printf("\n");
            }else{
                printf("\nNo hay fichas para comer!\n");
            }

            //Imprimir datos del jugador
            imprimirDatosJugador(lista, nodoJugador);

        }else{//si tiene fichas para jugar
            printf("\n*Posibles fichas para jugar el turno: ");
            mostrarListaPosibles(listaPosibles);

            //buscar la ficha con el puntaje mas alto y con la suma de sus extremos que sea menor
            NodoPosibles *fichaJugar = obtenerFichaJugar(listaPosibles);
            printf("\n\n*La ficha a colocar: [%d|%d]\n", fichaJugar->a, fichaJugar->b);
            reproducirSonido("/Sonidos/ponerFicha.wav");

            if(estaVacia(nodoJugador->listaFichasJugador)){//si es la ultima ficha
                printf("El jugador coloco su ultima!");

            }else {//si aun tiene fichas para colocar

                //modificar o agregar el nuevo extremo en la lisa de mesa
                actualizarListaMesa(lista, fichaJugar);

                //sumarle los puntos
                nodoJugador->puntos += fichaJugar->nPuntos;

                //eliminar la ficha colocada de la lista del jugador
                NodoFicha *nodoEliminar = crearFicha(fichaJugar->a, fichaJugar->b);
                eliminarFichaJugada(nodoJugador->listaFichasJugador, nodoEliminar);

                //imprimir datos del jugador
                imprimirDatosJugador(lista, nodoJugador);
            }
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

    if(isDoble ==1){//si es doble y posicion vertical
        sumatoria += extremoSumar;//queda pendiente restar el extremo de la mesa donde se coloco la ficha doble
    }

    sumatoria -= extremoRestar;

    return (sumatoria % 5 == 0)? (sumatoria / 5) : 0;
}

void agregarFichaConPuntaje(ListaPosibles *listaPosibles, ListaMesa *listaMesa, NodoFicha *nodoFicha){
    int nPuntos;

    //hacer calculos con cada extremo disponible en la mesa
    NodoMesa *recorreMesa = listaMesa->primero;

    // revisando como poner la ficha
    while(recorreMesa != NULL){

        //si entra a alguno de los if hay al menos un extremo que coincide
        if(recorreMesa->numero == nodoFicha->a && recorreMesa->numero == nodoFicha->b){
            //Aqui trabaja con la doble
            printf("\n[Tiene un par para colocar]\n");
            NodoPosibles *nodoPosibles;
            //falta eliminar el extremo, que se tapa, extremo a restar vertical

           //revisar si la coloca vertical, suma ambos extremos
            int ptsVertical = calcularPuntos(listaMesa, nodoFicha->a,nodoFicha->b ,1);

            //revisar si la coloca  horizontal, solo suma un extremo
            int ptsHorizontal = calcularPuntos(listaMesa, nodoFicha->a,nodoFicha->b, 0);

            //sumar todos los extremos y dividirlo entre 5
           //comparar cual es mas alto, el numero mas alto me dice que posicion colocar
            if( ptsVertical >  ptsHorizontal){
                //si es vertical agrego ambos extremos
                nodoPosibles = crearNodoPosible( ptsVertical,nodoFicha->a, nodoFicha->b,1,0);
                printf("Puede jugar vertical");

            }else{
                //si es horizontal agrego 1 extremo
                nodoPosibles = crearNodoPosible( ptsHorizontal,nodoFicha->a, nodoFicha->b,0,nodoFicha->a);
                printf("Puede jugar horizontal");
            }

            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);

        }else if( recorreMesa->numero == nodoFicha->a){//Hay cocidencia con extremo a

            //Aqui trabaja con la B, Siempre juega horizontal
            nPuntos = calcularPuntos(listaMesa, nodoFicha->b,nodoFicha->a, 0);

            //agrego la ficha a listaPosible y nPuntaje
            //creo nodoMesa
            NodoPosibles *nodoPosibles = crearNodoPosible( nPuntos,nodoFicha->a, nodoFicha->b,0,nodoFicha->a);

            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);


        }else if(recorreMesa->numero == nodoFicha->b){//Hay cocidencia con extremo b

            //Aqui trabaja con la A, Siempre juega horizontal
            nPuntos = calcularPuntos(listaMesa, nodoFicha->a,nodoFicha->b, 0);

            //agrego la ficha a listaPosible y nPuntaje
            //creo nodoMesa
            NodoPosibles *nodoPosibles = crearNodoPosible( nPuntos,nodoFicha->a, nodoFicha->b,0,nodoFicha->b);
            //inserto nodo mesa
            insertarNodoPosible(listaPosibles,nodoPosibles);
        }

        recorreMesa = recorreMesa->siguiente;
    }

}

void llenarListaPosibles(ListaPosibles  *listaPosibles, ListaMesa *listaMesa, ListaFichas *listaFichas){

    //recorrer lista de fichas del jugador
    NodoFicha *nodoFicha = listaFichas->primero;

    while(nodoFicha != NULL){
        //envio la ficha a un metodo para calcular puntaje y posicion
        agregarFichaConPuntaje(listaPosibles,listaMesa,nodoFicha);
        //paso a la siguiente ficha
        nodoFicha = nodoFicha->siguiente;
    }
}

int verificarNoJugadas(ListaJugador *listaJugadores, ListaFichas *listaMaso, ListaMesa *listaMesa){
    int flag = 0;
    if(listaMaso->primero == NULL){
        NodoMesa  *recorreExtremos = listaMesa->primero;
        while (recorreExtremos != NULL){
            NodoJugador *recorreJugadores = listaJugadores->primero;
            while(recorreJugadores != NULL){
                NodoFicha *recorreFichas = recorreJugadores->listaFichasJugador->primero;
                while (recorreFichas != NULL) {
                    if(recorreExtremos->numero == recorreFichas->a || recorreExtremos->numero == recorreFichas->b){
                        return 0;
                    }else{
                        flag = 1;
                    }
                    recorreFichas = recorreFichas->siguiente;
                }
                recorreJugadores = recorreJugadores->sig;
            }
            recorreExtremos = recorreExtremos->siguiente;
        }
    }
    return flag;
}

int verificarFinJuego(ListaJugador *lista, ListaFichas *listaMaso){
    int flag = 0;

    //si no hay fichas en el mazo para comer
    if(listaMaso->primero == NULL){
        NodoJugador *recorreJug = lista->primero;
        while(recorreJug != NULL){

            //si un jugador no tiene fichas
            if(recorreJug->listaFichasJugador->primero == NULL){
                flag = 1;
                break;
            }
            recorreJug = recorreJug->sig;
        }
    }

    return flag;
}

#endif //PROYECTO_01_SO_LOGICAJUEGO_H