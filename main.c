#include <stdio.h>
#include "Archivos/Archivo.h"
#include "Listas/ListaJugador.h"
#include "Listas/ListaFichas.h"
#include "Negocio/LogicaJuego.h"
#include "Listas//ListaMesa.h"
#include "Listas//ListaPosibles.h"
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>


//variables
int turnoActual = 0;// control del turno de los hilos
int numeroRonda = 0;// Control de rondas
int nJugadores=0;// total de jugadores
int fichasXjugador=0;//numero de fichas para cada jugador
bool estadoJuego = true; //bandera que va sostener el estado del juego
pthread_t *hilosJugadores;//hilos cada jugador
pthread_t administrador; //hilo maestro que inicia el juego

ListaJugador *listaJugadores;//lista de jugadores
ListaMesa *listaMesa;//lista de extremos disponibles para jugar
ListaFichas *listaMaso;//crear maso de fichas


//funciones
void *turno_jugador(void *parametro);


void crearListas();
void iniciarMazo();
void ingresarNumeroJugadores();
void iniciarJugadores();
void validarNumeroPares();
void ordenarMostrarFichasJugador();
void asignarOrdenJuego();

void ponerFicha();
void *empezarTurno(void * args);
void *empezarJuego(void *args);


int main() {


    //crear todas las listas
    crearListas();

    //Mensaje de bienvenida
    printf("\nBienvenido al juego Dominó Sistemas Operativos 2023\n\n");

    //llenar mazo y revolver fichas
    iniciarMazo();

    //ingresar la cantidad de jugadores
    ingresarNumeroJugadores();

    //crear archivo log.txt
    crearArchivo();

    //Iniciar jugadores - nombre y lista de ficha
    iniciarJugadores();

    validarNumeroPares();

    asignarOrdenJuego();

    //array de hilos
    hilosJugadores = (pthread_t*)malloc(sizeof(pthread_t)*nJugadores); //se setean n cantidad de hilos

    //hilo maestro inicia juego
    pthread_create(&(administrador), NULL, &empezarJuego, NULL); //este hilo llama al

    //método de iniciar juego y es el que pone a los demás hilos a funcionar
    pthread_join(administrador, NULL); //se sincroniza


    //pthread_exit(NULL);// destruye los hilos
    return 0;
}

void crearListas(){
    listaJugadores = crearListaJugador();// Crea la lista de jugadores y contiene la lista de fichas de cada uno
    listaMaso = crearLista();//Crear lista fichas para comer y repartir
    listaMesa = crearListaMesa();//Lista de Mesa - lista de extremos
}

void iniciarMazo(){
    insertarFichas(listaMaso);//llenar lista de mazo

    //mostrar el maso
    printf("\n Mostrando el maso de fichas\n");
    imprimir(listaMaso);

    //revolver el maso
    printf("\n Revolviendo el maso de fichas\n");
    desordenar(listaMaso);
    imprimir(listaMaso);
}

void ingresarNumeroJugadores(){
    int validarEntrada = 0;
    //Solicitar numero jugadores
    do{
        char entrada[50];
        printf("\nIngrese el numero de jugadores entre un rango de 2 a 7:\n");
        fgets(entrada, 50, stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        //validar numero
        nJugadores = validarNJugadores(entrada);

    }while ( nJugadores == 0);
}

void iniciarJugadores(){

    printf("Iniciando partida para %d Jugadores.\n\n", nJugadores);
    //calcular numero de fichas jugadores - mazo
    fichasXjugador = calcularFichasXjugador(nJugadores);

    //Ingresar nombres de jugadores
    for(int i = 0; i < nJugadores; i++){

        //almacenar nombre de jugadores
        char nombreJugador[50];

        printf("Ingrese el nombre del jugador #%d\n", (i+1));
        //gets(nombreJugador);
        fgets(nombreJugador, sizeof(nombreJugador), stdin);
        nombreJugador[strcspn(nombreJugador, "\n")] = '\0';

        printf("Se añade al jugador: %s\n", nombreJugador);

        //almacenar en lista de jugadores
        NodoJugador *nodoJugador = crearJugador(nombreJugador, 0, 0);
        insertarJugador(listaJugadores, nodoJugador);

        //escribir el nombre y puntaje en un archivo
        acertarPuntos(nombreJugador, 0);
        printf("\n");

        //repartir fichas a jugador
        repartirFichas(listaMaso, fichasXjugador, nodoJugador->listaFichasJugador);

    }

    //********************************
    ordenarMostrarFichasJugador();
    //********************************
}

void validarNumeroPares(){

    //validar el numero de fichas pares
    if( validarDobles(listaJugadores) ){
        do{
            printf("\n\nRevolviendo el maso de fichas ...");
            sleep(3);

            // reiniciar la lista de maso
            listaMaso = crearLista();
            insertarFichas(listaMaso);

            //desordenar las fichas
            desordenar(listaMaso);
            printf("\nRepartiendo fichas de nuevo...\n");
            sleep(2);

            //repartir las fichas de nuevo
            NodoJugador *aux = listaJugadores->primero;
            while(aux != NULL){
                aux->listaFichasJugador = crearLista();
                repartirFichas(listaMaso, fichasXjugador, aux->listaFichasJugador);
                aux = aux->sig;
            }

        }while( validarDobles(listaJugadores) != 0);

        //********************************
        ordenarMostrarFichasJugador();
        //********************************
    }


}

void ordenarMostrarFichasJugador(){
    //ordenar lista de fichas de los jugadores
    metodoBurbujaMazoJugador(listaJugadores);

    //imprimir la lista de jugadores
    printf("\n\nLos participantes son: \n");
    mostrar(listaJugadores);


    //Imprimir la lista de mazo para comer
    printf("Lista del mazo a comer: ");
    mostrarMazoComer(listaMaso);
}

void asignarOrdenJuego(){

    // Asignar el orden de turno a cada jugador, segun fichas pares
    obtenerFichaDoble(*listaJugadores, nJugadores);
    printf("\n\n\n");

    //imprimir la lista de jugadores
    printf("El orden de los participantes es: \n");
    mostrar(listaJugadores);
}

void *empezarTurno(void * args){

    // semaforo de bloqueo

    printf("Turno jugador %d", turnoActual+1);
    printf("\n");
    //AQUI CODIGO DE ACCIONES POR TURNO
    ponerFicha();



    // semaforo de desbloqueo
}

void ponerFicha(){
    printf("Poniendo x ficha\n");
    //aquí estaría la lógica de poner la ficha
}


void *empezarJuego(void *args){


    printf("Iniciando juego....\n\n");
    while(estadoJuego){

        if (pthread_create(&(hilosJugadores[turnoActual]), NULL, &empezarTurno,NULL)!=0){
            printf("Error al crear hilos\n");
        }

        pthread_join(hilosJugadores[turnoActual], NULL);
        turnoActual++;

        if(turnoActual==nJugadores){
            turnoActual=0;
            numeroRonda++;
        }

        //condicion de terminar
        if(numeroRonda >= 3){
            estadoJuego =  false;
        }

        sleep(2); //con esto pueden alterar la velocidad con que muestran las cosas
    }
}



/*

     //**************************+ Arreglar los Hilos !!!!!!!!!!!!!!

    int errorHilo;// Variable para manejo de error en hilos
    int indice = 0; // indice para array de hilos

    //crear hilos
    NodoJugador *aux = listaJugadores->primero;
    printf("\n\n");
    while (aux != NULL){

        printf("Creando hilo jugador %i\n", (indice+1));
        //struct ParametrosTurno parametrosTurno = {aux, nJugadores, turno_mutex};
        //errorHilo = pthread_create(&hilosJugadores[indice], NULL, turnoJugador, (void *) &parametrosTurno);

        pthread_create(&hilosJugadores[indice], NULL, turno_jugador, (void *)aux);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_create()\n", errorHilo);
            exit(-1);
        }

        //pasar al siguiente nodo/hilo
        indice++;
        aux = aux->sig;
    }

    printf("\n\n");
    errorHilo = 0;

    //iniciar ejecucion de los hilos
    pthread_mutex_unlock(&turno_mutex); // libera el mutex mientras espera
    for(int i = 0; i < nJugadores; i++) {
        errorHilo = pthread_join(hilosJugadores[i], NULL);

        if(errorHilo) {
            printf("ERROR: retorno del código %d desde pthread_join()\n", errorHilo);
            exit(-1);
        }
    }


void *turno_jugador(void *parametro) {

    NodoJugador *nodoJugador = (NodoJugador *) parametro;

    int terminar = 1;
    // Realizar el turno

   do {

        // Esperar a que sea el turno del jugador
        pthread_mutex_lock(&turno_mutex);

        while (nodoJugador->nTurno != turno_actual && terminar != 0) {
            pthread_mutex_unlock(&turno_mutex);
            sched_yield();
            pthread_mutex_lock(&turno_mutex);
        }

        //******** temporal
       /* if(turno_actual == 1 && isVacia(listaMesa)){
            printf("\nPrimera jugada!\n");
            jugarTurno( listaMesa, nodoJugador);
            mostrarListaMesa(listaMesa);
            printf("\n");
            imprimir(nodoJugador->listaFichasJugador);
        }*/

       /* if(turno_actual == 2 && nodoJugador->nTurno != 1){
            ListaPosibles *listaPosibles = crearListaPosibles();

            printf("\nSegunda jugada!\n");

            llenarListaPosibles(listaPosibles,listaMesa,nodoJugador->listaFichasJugador);

            printf("\n\n Lista de posibles juegos: ");
            mostrarListaPosibles(listaPosibles);

            exit(0);
        }



        //si todos jugaron su ronda se reinicia el contador de ronda
        printf("Turno del jugador %s (turno=%d)\n", nodoJugador->nombre, nodoJugador->nTurno);

        // Esperar un poco antes de continuar con el siguiente turno
        usleep(2000000);

       printf("turno: %d , njugadores: %d \n", turno_actual, nJugadores);
       //aumentar la ronda
       if(turno_actual == nJugadores){
           printf("Se ejecuto la ronda: %d\n", numeroRondas);
           numeroRondas++;
       }

       // Pasar al siguiente jugador
        turno_actual = (turno_actual % nJugadores) + 1;
        pthread_mutex_unlock(&turno_mutex);

        //condicion de terminar
        if(numeroRondas > 2){
            pthread_mutex_lock(&turno_mutex);
            terminar=0;
            printf("\nEl juego termino!\n");
           // pthread_mutex_unlock(&turno_mutex);

           // pthread_cancel();

            pthread_exit(0);

            return NULL;
        }

    } while (terminar != 0);

    //exit(0);
    pthread_exit(NULL);// destruye los hilos
}


*/