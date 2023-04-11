#include <stdio.h>
#include "Archivos/Archivo.h"
#include "Listas/ListaJugador.h"
#include "Listas/ListaFichas.h"
#include "Negocio/LogicaJuego.h"
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

//variables
int turnoActual = 0;// control del turno de los hilos
int numeroRonda = 0;// Control de rondas
int nJugadores=0;// total de jugadores
int fichasXjugador=0;//numero de fichas para cada jugador
int contadorTurnos= 1;
bool estadoJuego = true; //bandera que va sostener el estado del juego

pthread_t *hilosJugadores;//hilos cada jugador
pthread_t administrador; //hilo maestro que inicia el juego

ListaJugador *listaJugadores;//lista de jugadores
ListaMesa *listaMesa;//lista de extremos disponibles para jugar
ListaFichas *listaMaso;//crear maso de fichas
ListaPosibles *listaPosibles;

//funciones
void crearListas();
void iniciarMazo();
void ingresarNumeroJugadores();
void iniciarJugadores();
void validarNumeroPares();
void ordenarMostrarFichasJugador();
void asignarOrdenJuego();
void *empezarTurno(void *args);
void *empezarJuego();

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
    crearArchivo("Archivos/log.txt");

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


    printf("\n");
    //imprimir historial de partida
    verHistorialJugadas();

    getchar();
    //Imprimi historial de los ganadores
    verHistorialGanadores();

    printf("\n                           Como arroz!!!!!!!!!!!!!!!!!!!!!!!\n");


    //pthread_exit(NULL);// destruye los hilos
    return 0;
}

void crearListas(){
    listaJugadores = crearListaJugador();// Crea la lista de jugadores y contiene la lista de fichas de cada uno
    listaMaso = crearLista();//Crear lista fichas para comer y repartir
    listaMesa = crearListaMesa();//Lista de Mesa - lista de extremos
    listaPosibles = crearListaPosibles();
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
    obtenerFichaDoble(listaJugadores, nJugadores);
    printf("\n\n\n");

    //imprimir la lista de jugadores
    printf("El orden de los participantes es: \n");
    mostrar(listaJugadores);
}

void *empezarTurno(void * args) {

    //reseteo de la lista de fichas posibles para jugar
    listaPosibles = crearListaPosibles();

    //inicializando datos del jugdor
    NodoJugador *nodoJugador = (NodoJugador *) args;

    printf("\n\n****Numero de turno: %d ****\n", (turnoActual + 1));

    //SI es el primer turno
    if (turnoActual == 0 && isVacia(listaMesa)) {

        //coloca ficha
        jugarTurno(listaMesa, nodoJugador, listaPosibles,listaMaso);

    } else {
        //agregar todas las fichas que puede usar en el turno
        llenarListaPosibles(listaPosibles, listaMesa, nodoJugador->listaFichasJugador);

        //coloca ficha
        jugarTurno(listaMesa, nodoJugador, listaPosibles, listaMaso);

    }
                                                                                                                             
    return 0;
}

void *empezarJuego(){


    printf("Iniciando juego....\n\n");

    while(estadoJuego) {

        //buscar datos jugador
        NodoJugador *nodoJugador = listaJugadores->primero;
        while (nodoJugador != NULL){

            if(nodoJugador->nTurno == (turnoActual+1)){
                break;
            }
            //pasar al siguiente nodo/jugador
            nodoJugador = nodoJugador->sig;
        }


        //crear y iniciar hilo jugador
        if (pthread_create(&(hilosJugadores[turnoActual]), NULL, &empezarTurno,(void *)nodoJugador) !=0 ){
            printf("Error al crear hilos\n");
        }

        pthread_join(hilosJugadores[turnoActual], NULL);
        turnoActual++;


        //reseteo de turno y numero de ronda
        if(turnoActual==nJugadores){
            turnoActual=0;
            numeroRonda++;
        }

        //escribir el nombre y puntaje en un archivo
        registrarPuntaje(nodoJugador->nombre, nodoJugador->puntos, contadorTurnos, 0);
        contadorTurnos++;


        //verificar si hay algun jugador con fichas para colocar
        bool nadieJuega = verificarNoJugadas(listaJugadores, listaMaso, listaMesa);

        //condicion de terminar
        if( verificarFinJuego(listaJugadores, listaMaso) || nadieJuega){
            estadoJuego =  false;
            if(nadieJuega){
                printf("\n\n~~Ningun jugador tiene fichas para jugar~~");
            }
            printf("\n\n...............{FIN DE JUEGO}...............");

            //buscar el jugador con el puntaje mas alto
            NodoJugador *jugadorGanador = buscarPuntaGanador(listaJugadores);

            //crear archivo ganadores.txt
            //crearArchivo("../Archivos/ganadores.txt");
            //actualizar los puntajes de los jugadores
            actualizarGanadores("Archivos/ganadores.txt",jugadorGanador->nombre);

            //registrar el jugador ganador y numero de victorias
            registrarPuntaje(jugadorGanador->nombre, jugadorGanador->puntos, contadorTurnos, 1);

        }

        sleep(2); //con esto pueden alterar la velocidad con que muestran las cosas


    }


    return 0;
}