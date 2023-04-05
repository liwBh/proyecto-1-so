#ifndef PROYECTO_01_SO_ARCHIVO_H
#define PROYECTO_01_SO_ARCHIVO_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int crearArchivo(char* ruta){

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
int acertarPuntos(char nombreJugador[50], int puntos){

    //inicializar archivo, modo agregar
    FILE *archivo = fopen("../Archivos/log.txt", "a");

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
    fprintf(archivo, "Jugador:%s, Puntos:%d\n", nombreJugador,puntos);
    //fprintf(archivo, ", Puntos:%d\n", puntos);

    //mensaje de exito
    printf("\nSe agrego el registro correctamente en el archivo!\n\n");

    //cerrar el archivo
    fclose(archivo);

    return 1;
}

//metodo que permite la lectura de un archivo
void leerArchivo( char nombre[50]) {

    char texto[500];

    //concatenar la extension del archivo
    strcat(nombre,".txt");

    //inicializa archivo modo lectura
    FILE *archivo = fopen(nombre, "r");

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
    printf("\nEl archivo fue leido de forma exitosa!\n");

    //cerrar archivo
    fclose(archivo);
}

//metodo que permite modificar la linea de un archivo de texto
void modificarLinea(char* ruta, int num_linea, char* nueva_linea) {
    // Abrir el archivo en modo lectura/escritura
    FILE* fp = fopen(ruta, "r+");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s\n", ruta);
        return;
    }

    // Buscar la línea que deseamos modificar
    int linea_actual = 0;
    char linea[50];
    while (fgets(linea, 50, fp) != NULL && linea_actual < num_linea) {
        linea_actual++;
    }

    if (linea_actual == num_linea) {
        // Si encontramos la línea, posicionarnos al principio de la misma
        fseek(fp, -strlen(linea), SEEK_CUR);

        // Escribir la nueva línea en el archivo
        fprintf(fp, "%s\n", nueva_linea);
        printf("La línea %d ha sido modificada en el archivo %s\n", num_linea, ruta);
    } else {
        printf("No se encontró la línea %d en el archivo %s\n", num_linea, ruta);
    }

    // Cerrar el archivo
    fclose(fp);
}


#endif //PROYECTO_01_SO_ARCHIVO_H
