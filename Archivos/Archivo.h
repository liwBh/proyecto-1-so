#ifndef PROYECTO_01_SO_ARCHIVO_H
#define PROYECTO_01_SO_ARCHIVO_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//metodo para crear archivos
int crearArchivo(){

    // usando el modo w crea el archivo, si ya hay uno con ese nombre lo sobre escribe
    FILE *archivo = fopen("log.txt", "w");

    if(archivo == NULL){
        //mensaje de error
        printf("Ocurrio un error, el archivo no fue creado con exito!\n\n");

        //cerrar el archivo
        fclose(archivo);

        //detener el metodo
        return 0;
    }

    //mensaje de exito
    printf("El archivo a sido creado con exito!\n\n");

    //cerrar el archivo
    fclose(archivo);

    return 1;
}


//metodo que permite escribir en un archivo
int acertarPuntos(char nombreJugador[50], int puntos){

    //inicializar archivo, modo agregar
    FILE *archivo = fopen("log.txt", "a");

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
    fprintf(archivo, "Jugador:%s", nombreJugador);
    fprintf(archivo, ", Puntos:%d", puntos);
    fprintf(archivo, "%s", "\n");

    //mensaje de exito
    printf("Se agrego el texto ingresado correctamente en el archivo!\n\n");

    //cerrar el archivo
    fclose(archivo);

    return 1;
}

#endif //PROYECTO_01_SO_ARCHIVO_H
