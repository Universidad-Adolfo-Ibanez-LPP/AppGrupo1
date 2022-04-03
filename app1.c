//Lenguajes y paradigmas: APP 1
//Participantes:
//Andres Guerra
//Vicente Garay
//Vicente Garcia
//Felipe Gonzales
//Tomas Loyola

//librerias
#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//funciones menu y submenus
void menuprincipal();

void agregar();

void quitar();

void cambiar();

//Creamos el tipo de dato libro
typedef struct libro
{
    char titulo[255];
    char autor[255];
    int anio;
    int estante_numero;
    char estante_seccion[255];
    int piso;
    char edificio[255];
    char sede[255];
}libro;

//Se realiza un array de structs para manipular
libro libro_especifico[999];
int tope=0;
int arreglado=0;


//Pasamos del csv al array de structs que creamos anteriormente
int openingFile(char *filename){
    FILE *fp;
    fp = fopen(filename,"r");

    if (!fp)
    {
        printf("Archivo no encontrado");
        return 0;
    }
    char buff[1024];
    int row_count=0;
    int field_count = 0;


    int i=0;
    while(fgets(buff,1024,fp))
    {
        field_count = 0;
        row_count++;
        //if(row_count == 1)
        //    continue;

        char *field = strtok(buff, ",");
        while(field)
        {
            if(field_count == 0)
                strcpy(libro_especifico[i].titulo, field);

            if(field_count == 1)
                strcpy(libro_especifico[i].autor, field);

            if(field_count == 2)
                libro_especifico[i].anio = atoi(field);

            if(field_count == 3)
                libro_especifico[i].estante_numero= atoi(field);

            if(field_count == 4)
                strcpy(libro_especifico[i].estante_seccion , field);

            if(field_count == 5)
                libro_especifico[i].piso = atoi(field);

            if(field_count == 6)
                strcpy(libro_especifico[i].edificio, field);

            if(field_count == 7)
                strcpy(libro_especifico[i].sede, field);

            field = strtok(NULL, ",");
            field_count++;
        }
        i++;
    }
    fclose(fp);
    return i;
}

//Creamos el proceso para imprimir el inventario de la biblioteca
void printValues(libro libro_especifico[])
{
    printf("\n");

    for(int i=0; i<tope; i++) 
    {
        if (libro_especifico[i].anio!=0)
        {
            printf("titulo: %s, autor: %s, anio: %d, estante_numero: %d, estante_seccion: %s, piso: %d, edificio: %s, sede: %s\n",libro_especifico[i].titulo,libro_especifico[i].autor, libro_especifico[i].anio, libro_especifico[i].estante_numero,libro_especifico[i].estante_seccion, libro_especifico[i].piso, libro_especifico[i].edificio, libro_especifico[i].sede);
            printf("\n");
        }
    }
}