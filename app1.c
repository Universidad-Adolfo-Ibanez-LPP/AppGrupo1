//Lenguajes y paradigmas: APP 1
//Participantes:
//Andres Guerra
//Vicente Garay
//Vicente Garcia
//Felipe Gonzalez
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

void buscar_libro();

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
//Guardar archivo
void GuardarArchivo(char path[]){

    FILE *archivo;
    char cadena[255];
    int numero=100;
    printf("\n");

    archivo=fopen(path,"w");

    if (archivo !=NULL){
        for (int i = 0; i < tope; ++i)
        {
            if (libro_especifico[i].anio!=0)
            {
                if (i < arreglado-1)
                {
                    fprintf(archivo, "%s,%s,%d,%d,%s,%d,%s,%s",libro_especifico[i].titulo,libro_especifico[i].autor, libro_especifico[i].anio, libro_especifico[i].estante_numero,libro_especifico[i].estante_seccion, libro_especifico[i].piso, libro_especifico[i].edificio, libro_especifico[i].sede);
                }
                else
                {
                    fprintf(archivo, "%s,%s,%d,%d,%s,%d,%s,%s\n",libro_especifico[i].titulo,libro_especifico[i].autor, libro_especifico[i].anio, libro_especifico[i].estante_numero,libro_especifico[i].estante_seccion, libro_especifico[i].piso, libro_especifico[i].edificio, libro_especifico[i].sede);
                }
            }

        }
    }
    fclose(archivo);
    system( "\tread -n 1 -s -p \"Presione cualquier tecla para finalizar...\"" );
}

//Menu principal que contiene la mayoria de procesos
void menuprincipal()
{
    int opcion;
    bool repetir = true;


    do{
            system("@cls||clear");

            printf("\n");
            printf("\n\n\t\t\tMenu\n");
            printf("\n");
            printf("\n\t0: Revisar inventario.\n");
            printf("\t1: Agregar datos a la biblioteca.\n");
            printf("\t2: Eliminar datos de la biblioteca.\n");
            printf("\t3: Cambiar datos de la biblioteca.\n");
            printf("\t4: Buscar libro de la biblioteca.\n");
            printf("\t5: Salir.\n");

            printf("\n");

            printf("\tIngrese una opcion: ");
            scanf("%d",&opcion);

            switch(opcion){
                case 0:
                    printValues(libro_especifico);
                    system( "read -n 1 -s -p \"Presione cualquier tecla para volver al menu...\"" );
                    break;
                case 1:
                    agregar();
                    break;
                case 2:
                    quitar();
                    break;
                case 3:
                    cambiar();
                    break;
                case 4:
                    buscar_libro();
                    break;
                case 5:
                    repetir= false;
                    break;


            }
    }while (repetir);
}

//Buscar Libro
void buscar_libro(){
    char buscar[255];
    bool encontrado = false;

    printf("\n\tPor favor diga el titulo del libro que busca: ");
    scanf(" %[^\n]s",buscar);

    printf("\n");
    for (int i =0; i<tope; i++){
        if (strncmp(buscar, libro_especifico[i].titulo, 100) ==0){
            printf("titulo: %s, autor: %s, anio: %d, estante_numero: %d, estante_seccion: %s, piso: %d, edificio: %s, sede: %s\n",libro_especifico[i].titulo,libro_especifico[i].autor, libro_especifico[i].anio, libro_especifico[i].estante_numero,libro_especifico[i].estante_seccion, libro_especifico[i].piso, libro_especifico[i].edificio, libro_especifico[i].sede);
            printf("\n");
            encontrado=true;
            break;
        }
    }

    if (encontrado==false)
    {
        printf("\tEl libro que busca no esta en la biblioteca.\n");
        printf("\n");
    }

    system( "\tread -n 1 -s -p \"Presione cualquier tecla para volver al menu...\"" );

}

//Agregar
void agregar()
{
    int i= tope;
    char titulos[255];
    char autors[255];
    char anios[255];
    char estante_n[255];
    char estante_s[255];
    char pizo[255];
    char edif[255];
    char sed[255];
    
    system("@cls||clear");
    //agregar titulo
    printf("\tIngrese un titulo: ");
    scanf(" %[^\n]s",titulos);
    strcpy(libro_especifico[i].titulo, titulos);

    //agregar autor
    printf("\tIngrese un/unos autor/autores: ");
    scanf(" %[^\n]s",autors);
    strcpy(libro_especifico[i].autor, autors);

    //agregar ano
    printf("\tIngrese un año: ");
    scanf(" %[^\n]s",anios);
    libro_especifico[i].anio= atoi(anios);

    //agregar estante numero
    printf("\tIngrese el numero del estante: ");
    scanf(" %[^\n]s",estante_n);
    libro_especifico[i].estante_numero = atoi(estante_n);

    //agregar estante seccion
    printf("\tIngrese la seccion del estante: ");
    scanf(" %[^\n]s",estante_s);
    strcpy(libro_especifico[i].estante_seccion, estante_s);

    //agregar piso
    printf("\tIngrese un piso: ");
    scanf(" %[^\n]s",pizo);
    libro_especifico[i].piso= atoi(pizo);

    //agregar edificio
    printf("\tIngrese el edificio: ");
    scanf(" %[^\n]s",edif);
    strcpy(libro_especifico[i].edificio, edif);

    //agregar sede
    printf("\tIngrese la sede: ");
    scanf(" %[^\n]s",sed);
    strcpy(libro_especifico[i].sede, sed);

    tope=tope+1;
    system( "read -n 1 -s -p \"Presione cualquier tecla para volver al menu...\"" );
}
//Quitar
void quitar()
{
    char eliminar[255];
    char borrar[255];
    printf("\n\tPuede eliminar las siguientes cosas:\n");
    printf("\tLibro. \n");
    printf("\tSede. \n");
    printf("\tPiso. \n");
    printf("\tSeccion. \n");
    printf("\tEscriba que busca eliminar: ");
    scanf(" %[^\n]s",eliminar);
    if((strncmp(eliminar, "libro", 100) ==0) || (strncmp(eliminar,"Libro",100)==0)){
                char libro[255];
                printf("\tIngrese el libro: ");
                scanf(" %[^\n]s",libro);
        for (int i =0; i<tope; i++){
                if (strncmp(libro, libro_especifico[i].titulo, 100) ==0){
                    memset(libro_especifico[i].titulo, 0, 100);
                    memset(libro_especifico[i].autor, 0, 100);
                    memset(libro_especifico[i].estante_seccion, 0, 100);
                    memset(libro_especifico[i].edificio, 0, 100);
                    memset(libro_especifico[i].sede, 0, 100);
                    libro_especifico[i].anio=0;
                    libro_especifico[i].piso=0;
                    libro_especifico[i].estante_numero=0;

                }
        }
    }
    //Sede
    if((strncmp(eliminar, "sede", 100) ==0) || (strncmp(eliminar,"Sede",100)==0)){ 

        int count= 0;
        int contador= 0;
        char sd[255];
        printf("\tIngrese el nombre de la Sede: ");
        scanf(" %[^\n]s",sd);

        for (int i = 0; i < tope; i++)
        {
            if (i < tope)
            {

                if (strcmp(sd, libro_especifico[i].sede)==-10 || strcmp(sd, libro_especifico[i].sede)== 0 ) 
                {
                    contador=contador+1;
                }
            }

        }


        if (contador!=0)
        {
            printf("\n");
            printf("\tExisten libros asociados a la sede ingresada\n");
            printf("\t¿Desea borrarla de todos modos?(Si/No): ");
            scanf(" %[^\n]s",borrar);
        }
        for (int i = 0; i < tope; i++)
        {   
                if((strncmp(borrar, "Si",100)==0)||(strncmp(borrar,"si",100)==0))
                {                        
                    if (strncmp(sd, libro_especifico[i].sede, 100) ==-10 || strncmp(sd, libro_especifico[i].sede, 100) == 0 )
                    {
                    memset(libro_especifico[i].titulo, 0, 100);
                    memset(libro_especifico[i].autor, 0, 100);
                    memset(libro_especifico[i].estante_seccion, 0, 100);
                    memset(libro_especifico[i].edificio, 0, 100);
                    memset(libro_especifico[i].sede, 0, 100);
                    libro_especifico[i].anio=0;                        
                    libro_especifico[i].piso=0;
                    libro_especifico[i].estante_numero=0;
                    }
                }
        }
        if((strncmp(borrar, "No",100)==0)||(strncmp(borrar,"no",100)==0))
            {
                printf("\tOk, no se ha borrado ninguna sede\n");
            }
        
           
    }
    if((strncmp(eliminar, "piso", 100) ==0) || (strncmp(eliminar,"Piso",100)==0)){ 
        int count= 0;
        int ps=0;
        printf("\tIngrese el numero del piso: ");
        scanf("%d",&ps);

        for (int i = 0; i < tope; i++)
        {
            if (ps==libro_especifico[i].piso)
            {
                
                count= count + 1;
            }

        }


        if (count!=0)
        {
            printf("\tExisten libros asociados a la sede ingresada\n");
            printf("\t¿Desea borrarla de todos modos?(Si/No): ");
            scanf(" %[^\n]s",borrar);
        }
        for (int i = 0; i < tope; i++)
        {   
                if((strncmp(borrar, "Si",100)==0)||(strncmp(borrar,"si",100)==0))
                {                        
                    if (ps==libro_especifico[i].piso)
                    {
                    memset(libro_especifico[i].titulo, 0, 100);
                    memset(libro_especifico[i].autor, 0, 100);
                    memset(libro_especifico[i].estante_seccion, 0, 100);
                    memset(libro_especifico[i].edificio, 0, 100);
                    memset(libro_especifico[i].sede, 0, 100);
                    libro_especifico[i].anio=0;                        
                    libro_especifico[i].piso=0;
                    libro_especifico[i].estante_numero=0;
                    }
                }
        }
        if((strncmp(borrar, "No",100)==0)||(strncmp(borrar,"no",100)==0))
            {
                printf("\tOk, no se ha borrado ningun piso\n");
            }
        
    }

    //seccion
    if((strncmp(eliminar, "seccion", 100) ==0) || (strncmp(eliminar,"Seccion",100)==0)){ 
        int count= 0;
        char sc[255];
        char borrar[255];
        printf("\tIngrese el nombre de la Seccion: ");
        scanf(" %[^\n]s",sc);

        for (int i = 0; i < tope; i++)
        {
            if (strncmp(sc, libro_especifico[i].estante_seccion, 100) ==0)
            {
                count= count + 1;
            }
      
        }


        if (count!=0)
        {
            printf("\tExisten libros asociados a la seccion ingresada\n");
            printf("\t¿Desea borrarla de todos modos?(Si/No): ");
            scanf(" %[^\n]s",borrar);
        }
        for (int i = 0; i < tope; i++)
        {   
                if((strncmp(borrar, "Si",100)==0)||(strncmp(borrar,"si",100)==0))
                {                        
                    if (strncmp(sc, libro_especifico[i].estante_seccion, 100) ==0)
                    {
                    memset(libro_especifico[i].titulo, 0, 100);
                    memset(libro_especifico[i].autor, 0, 100);
                    memset(libro_especifico[i].estante_seccion, 0, 100);
                    memset(libro_especifico[i].edificio, 0, 100);
                    memset(libro_especifico[i].sede, 0, 100);
                    libro_especifico[i].anio=0;                        
                    libro_especifico[i].piso=0;
                    libro_especifico[i].estante_numero=0;
                    }
                }
        }
        if((strncmp(borrar, "No",100)==0)||(strncmp(borrar,"no",100)==0))
            {
                printf("\tOk, no se ha borrado ninguna seccion\n");
            }
        
           
    }
}
//Cambiar
void cambiar()
{
    char cambiar[255];
    char seguir_cambiando;

    do 
    {
    printf("\n\tPor favor diga el libro que busca cambiar los datos: ");
    scanf(" %[^\n]s",cambiar);
    int palabra_encontrada = 0;

    for (int i =0; i<tope; i++){
        if (strncmp(cambiar, libro_especifico[i].titulo, 100) ==0){
            char cosa[255];
            printf("\n\tPuede cambiar las siguientes cosas. \n");
            printf("\ttitulo. \n");
            printf("\tautor. \n");
            printf("\tanio. \n");
            printf("\tsede. \n");
            printf("\tpiso. \n");
            printf("\tnumero estante. \n");
            printf("\tseccion estante. \n");
            printf("\tEscriba que busca cambiar: ");
            scanf(" %[^\n]s", cosa);
            
            palabra_encontrada = 1;

            if(strncmp(cosa, "titulo", 100) ==0){
                char n_titulo[255];
                printf("\tIngrese el nuevo titulo: ");
                scanf(" %[^\n]s",n_titulo);
                strcpy(libro_especifico[i].titulo, n_titulo);
            }
            if(strncmp(cosa, "autor", 100) ==0){
                char n_autor[255];
                printf("\tIngrese el nuevo/os autor/es: ");
                scanf(" %[^\n]s", n_autor);
                strcpy(libro_especifico[i].autor, n_autor);
            }
            if(strncmp(cosa, "sede", 100) ==0){
                char n_sede[255];
                printf("\tIngrese la nueva sede: ");
                scanf(" %[^\n]s", n_sede);
                strcpy(libro_especifico[i].sede, n_sede);
            }
            if(strncmp(cosa, "piso", 100) ==0){
                char n_piso[255];
                printf("\tIngrese el nuevo piso: ");
                scanf(" %[^\n]s",n_piso);
                libro_especifico[i].piso= atoi(n_piso);
            }
            if(strncmp(cosa, "anio", 100) ==0){
                char n_anio[255];
                printf("\tIngrese el nuevo año: ");
                scanf(" %[^\n]s",n_anio);
                libro_especifico[i].anio= atoi(n_anio);
            }
            if(strncmp(cosa, "numero estante", 100) ==0){
                char n_num_estan[255];
                printf("\tIngrese el nuevo numero de estante: ");
                scanf(" %[^\n]s",n_num_estan);
                libro_especifico[i].estante_numero= atoi(n_num_estan);
            }
            if(strncmp(cosa, "seccion estante", 100) ==0){
                char n_sec_estan[255];
                printf("\tIngrese la nueva seccion: ");
                scanf(" %[^\n]s", n_sec_estan);
                strcpy(libro_especifico[i].estante_seccion, n_sec_estan);
            }
        }    
    }
    if (palabra_encontrada == 0)
    {
        //En el caso que el libro este mal ingresado
        printf("\n");
        printf("\tNo se a encontrado ningun libro con ese nombre \n");
        printf("\n");
        system("\tread -n 1 -s -p \"Presione cualquier tecla para continuar...\"" );
        printf("\n"); 
    }    
    printf("\t¿Quieres seguir cambiando datos?[s/n] ");
    scanf(" %[^\n]s",&seguir_cambiando);
    }while(seguir_cambiando == 's');
}   


int main(int argc, char *argv[]){
    tope = openingFile(argv[1]);
    arreglado= tope;

    printf("\n");
    menuprincipal();

    char nombre_del_csv[strlen(argv[1]) + 1];
    strcpy(nombre_del_csv, argv[1]);
    GuardarArchivo(nombre_del_csv);
    printf("\n");
    return 0;
}
