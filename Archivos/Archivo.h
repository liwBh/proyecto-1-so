#ifndef PROYECTO_01_SO_ARCHIVO_H
#define PROYECTO_01_SO_ARCHIVO_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int crearArchivo(char* ruta){
    //"playbin uri=file:////home/liwbh/CLionProjects/Proyecto-01-SO/Sonidos/victoria.wav"
    // usando el modo w crea el archivo, si ya hay uno con ese nombre lo sobre escribe "../Archivos/log.txt"
    FILE *archivo = fopen(ruta, "w");

    if(archivo == NULL){
        //mensaje de error
        printf("Ocurrio un error, el archivo no fue creado con exito!\n\n");

        //cerrar el archivo
        fclose(archivo);

        //detener el metodo
        return 0;
    }

    //mensaje de exito
    printf("\nEl archivo a sido creado con exito!\n\n");

    //cerrar el archivo
    fclose(archivo);

    return 1;
}


//metodo que permite escribir en un archivo
int registrarPuntaje(char nombreJugador[50], int puntos, int contadorTurnos, int ganador){

    //inicializar archivo, modo agregar
    FILE *archivo = fopen("Archivos/log.txt", "a");

    //validar si el archivo existe
    if(archivo == NULL) {
        //mensaje de error
        printf("Ocurrio un error, el archivo no fue encontrado!\n\n");

        //cerrar el archivo
        fclose(archivo);

        //detener metodo
        return 0;
    }

    //realizar la escritura en el archivo
    if(ganador == 1){
        fprintf(archivo, "\n\nEl jugador ganador es: %s, Puntos: %d\n", nombreJugador,puntos);
    }else{
        fprintf(archivo, "Jugador:%s, Puntos:%d, N° Turno:%d\n", nombreJugador,puntos,contadorTurnos);
    }

    //mensaje de exito
    //printf("\nSe agrego el registro correctamente en el archivo!\n\n");

    //cerrar el archivo
    fclose(archivo);

    return 1;
}

//metodo que permite la lectura de un archivo
void leerArchivo( char* ruta ){

    char texto[5000];
    //inicializar el array
    memset(texto, '\0', sizeof(texto));

    //inicializa archivo modo lectura
    FILE *archivo = fopen(ruta, "r");

    //validar que el archivo existe
    if( archivo == NULL ){
        //mensaje de error
        printf("El archivo que desea leer no fue encontrado!\n");

        //cerrar el archivo
        fclose(archivo);
    }

    //realizar lectura del archivo
    char letra = ' ';
    int indice = 0;
    while( letra != EOF ) {
        //letra = fgetc(archivo);
        letra = getc(archivo);

        if( letra != -1){
            //strcat(texto,&letra);
            texto[indice] = letra;
            indice++;
        }

        //printf("%c", &letra);
    }

    //imprimir datos del archivo
    printf("\n%s\n", texto);

    //mensaje de exito
    //printf("\nEl archivo fue leido de forma exitosa!\n");


    //cerrar archivo
    fclose(archivo);

}

//metodo que permite la lectura de un archivo
 void actualizarGanadores(char* ruta, char* nombre) {
     // Abrir el archivo en modo lectura/escritura
     FILE* fp = fopen(ruta, "r+");
     if (fp == NULL) {
         printf("\nNo se pudo abrir el archivo %s\n", ruta);
         return;
     }

     // Variables para leer el archivo y buscar el registro
     char linea[100];
     int encontrado = 0;
     // Leer cada línea del archivo
     while (fgets(linea, 100, fp) != NULL) {
         // Buscar el nombre en la línea
         char nombre_original[50]; // variable auxiliar para almacenar el nombre original
         strcpy(nombre_original, linea); // copiar la línea completa en la variable auxiliar
         char* token = strtok(linea, ",");
         if (strcmp(token, nombre) == 0) {
             // Incrementar el puntaje si se encuentra el nombre
             char* puntos_str = strtok(NULL, ",");
             int puntos = atoi(puntos_str);
             fseek(fp, -strlen(nombre_original), SEEK_CUR); // posicionarse al inicio de la linea
             fprintf(fp, "%s,%d\n", nombre, (puntos + 1)); // escribir la nueva linea
             encontrado = 1;
             break;
         }
     }
     // Si no se encontró el nombre, registrar el puntaje en el archivo
     if (!encontrado) {
         fprintf(fp, "%s,%d\n", nombre, 1);
     }
     printf("\n\nEl puntaje de %s ha sido modificado en el archivo %s\n", nombre, ruta);

     // Cerrar el archivo
     fclose(fp);
 }


/*************************************************/

void verHistorialJugadas(){
    char input;
    printf("\n\n¿Desea ver el historial de juego?\n Presione la tecla de espacio si es así, de lo contrario, presione cualquier otra tecla: ");
    scanf("%c", &input);
    if(input == ' ') {
        printf("\n\n............{Historial de puntos}...............\n\n");
        leerArchivo("Archivos/log.txt");
    }

}

void verHistorialGanadores(){
    char input2;
    printf("\n\n¿Desea ver el historial de Ganadores?\n Presione la tecla de espacio si es así, de lo contrario, presione cualquier otra tecla: ");
    scanf("%c", &input2);
    if(input2 == ' ') {
        printf("\n\n............{Historial de Ganadores}...............\n\n");
        leerArchivo("Archivos/ganadores.txt");
    }

}


#endif //PROYECTO_01_SO_ARCHIVO_H
