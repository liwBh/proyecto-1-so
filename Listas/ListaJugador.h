#ifndef CLIONPROJECTS_LISTAJUGADOR_H
#define CLIONPROJECTS_LISTAJUGADOR_H

#include "NodoJugador.h"

typedef struct ListaJugador{
    struct NodoJugador *primero; //Puntero que referencia al primero de lista
    struct NodoJugador *ultimo; //Puntero que referencia al ultimo de la lista
}ListaJugador;

//Creo la lista de jugadores, reservando espacio en memoria e inicializo los atributos
ListaJugador *crearListaJugador(){
    ListaJugador *listaJugador = (ListaJugador*) malloc(sizeof(ListaJugador)); //Reserva espacio
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
        NodoFicha *nodoActual = nodoJugador->listaFichasJugador->primero; //Nodo que apunta al primero de la lista de fichas que tiene cada jugador
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
        nodoJugador = nodoJugador->sig; //Va avanzado en la lista de jugadores
    }
}

//Valido cuantas dobles tiene cada jugador
int validarDobles(ListaJugador *listaJugador){


    //recorre la lista de jugadores
    NodoJugador *nodo = listaJugador->primero;
    while (nodo != NULL) {

        //recorro la lista de fichas de cada jugador
        NodoFicha *nodoFicha1 = nodo->listaFichasJugador->primero;
        int indice=0;

        while (nodoFicha1 != NULL){
            if(nodoFicha1->a == nodoFicha1->b){ //Cada vez que un jugador contenga una doble en su mazo entonces se incrementa
                indice++;
            }
            nodoFicha1 = nodoFicha1->siguiente;
        }

        if(indice >= 4){ //Si el incremente da 4 o mas entonces se retorna que tiene 4 o mas pares para revolver las fichas
            printf("\n\nEl jugador %s tiene 4 o mas pares, numero de pares: %d\n", nodo->nombre, indice);
            return 1;
        }

        nodo = nodo->sig;

    }
    return 0; //Si el indice no llega a 4 en ningun jugador por lo tanto devuelve que no se encontraron 4 o mas pares
}

void mostrar(ListaJugador *lista){ //imprime la lista
    NodoJugador *aux = lista->primero; //se crea un nodo aux para recorrer la lista
    while(aux!=NULL) { //Mientras sea diferente de null me recorre la lista
        mostrarJugadores(aux); //Este metodo me imprime los nodos de la lista
        aux = aux->sig; //El aux se va moviendo
    }
}

void asignarTurno(ListaJugador *listaJugador, NodoFicha *fichaMasAlta, int nTurno ){

    //encontro al jugador
    int flag = 0;

    //recorrer lista de jugadores
    NodoJugador *recorreJugadores = listaJugador->primero;
    while(recorreJugadores != NULL){

        //si no tiene turno asignado
        if( recorreJugadores->nTurno == 0 ){

            //recorremos la lista de fichas
            NodoFicha *recorreFichas = recorreJugadores->listaFichasJugador->primero;
            while (recorreFichas != NULL ) {

                //buscar ficha igual a mas alta
                if( fichaMasAlta->a == recorreFichas->a && fichaMasAlta->b == recorreFichas->b){
                    //asignar tuno al jugador
                    recorreJugadores->nTurno = nTurno;
                    flag = 1;
                    //salir del ciclo
                    break;
                }

                //pasar a la siguente ficha
                recorreFichas = recorreFichas->siguiente;
            }
        }

        //ya encontro al jugador, salir del ciclo
        if( flag == 1){
            break;
        }

        //pasar al siguente jugador
        recorreJugadores = recorreJugadores->sig;
    }
}

void obtenerFichaDoble(ListaJugador *lista,int nJugadores) {

    //contador de turnos repartidos
    int contadorTurno = 1;

    //asgnarle un turno a cada jugador
    for (int i = 0; i < nJugadores; ++i) {
        //nodo temporal con la ficha mas alta
        NodoFicha *alta = crearFicha(0,0);

        //bandera, si algun jugador tiene
        int flagHayPar = 0;

        //recorre la lista jugadores
        NodoJugador *nodoJugador = lista->primero;
        while (nodoJugador != NULL){

            //badera si tiene par
            int flag = 0;

            if( nodoJugador->nTurno == 0 ){//si el jugador no tiene turno asignado

                //recorre lista de fichas de jugador
                NodoFicha *nodoFichaJugador = nodoJugador->listaFichasJugador->primero;
                while (nodoFichaJugador != NULL) {

                    //si la ficha es par Y el par es mas alto
                    if(nodoFichaJugador->a == nodoFichaJugador->b){
                        //tiene par
                        flag = 1;
                        flagHayPar = 1;

                        //si alta no hay un par resetear alta
                        if(alta->a != alta->b){
                            //resetar nodo
                            alta = crearFicha(0,0);
                        }

                        //busca la ficha par mas alta
                        if(nodoFichaJugador->a > alta->a){
                            alta->a = nodoFichaJugador->a;
                            alta->b = nodoFichaJugador->b;
                        }


                    }else if(flag == 0 && flagHayPar == 0){//si no tiene par

                        //buscar la ficha mas alta
                        if( (nodoFichaJugador->a + nodoFichaJugador->b ) > (alta->a + alta->b ) ){
                            alta->a = nodoFichaJugador->a;
                            alta->b = nodoFichaJugador->b;
                        }

                    }

                    //pasar a la siguente ficha
                    nodoFichaJugador = nodoFichaJugador->siguiente;
                }

            }

            //pasar al siguente jugador
            nodoJugador = nodoJugador->sig;

            //llegar al ultimo jugador, seteo el numero nturno al jugador
            if(nodoJugador == NULL){

                // cual jugador tiene la ficha mas alta y asignarle el numero de turno
                asignarTurno(lista, alta, contadorTurno);

                //pasar al siguient turno
                contadorTurno++;
            }
        }
    }

}
int sumarFichasRestrantes(ListaFichas *listaFichas){
    int sumatoria = 0;

    if(listaFichas->primero != NULL){
        NodoFicha *recorre = listaFichas->primero;
        while (recorre != NULL) {
            sumatoria += (recorre->a + recorre->b);
            recorre = recorre->siguiente;
        }
    }

    return sumatoria;
}

NodoJugador *buscarPuntaGanador(ListaJugador *listaJugador){
    NodoJugador *recorre = listaJugador->primero;
    NodoJugador *devolver = crearJugador(recorre->nombre,recorre->puntos,recorre->nTurno);


    while (recorre != NULL) {
        if(recorre->puntos >= devolver->puntos){
            if(recorre->puntos == devolver->puntos){
                //si tiene el mismo puntaje, gana el jugador con menos puntos
                int a = sumarFichasRestrantes(recorre->listaFichasJugador);
                int b = sumarFichasRestrantes();

            } else{
                //es extrictamente mayor
            }
        }
        recorre = recorre->sig;
    }
    printf("\n***El nombre del ganador es: %s***",devolver->nombre);
    return devolver;
}



#endif //CLIONPROJECTS_LISTAJUGADOR_H