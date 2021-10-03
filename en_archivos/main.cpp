#include <iostream>
#include "utiles.h"


int main(){

    Lista_materiales *lista_materiales = new Lista_materiales;
    cargar_materiales(lista_materiales);
    
    Lista_edificios *lista_edificios = new Lista_edificios;
    cargar_edificios(lista_edificios);

    if (lista_materiales -> cantidad_de_materiales != ERROR && lista_materiales -> cantidad_de_materiales != 0
        && lista_edificios -> cantidad_de_edificios != ERROR && lista_edificios -> cantidad_de_edificios !=0 ){
        //Si se pudieron abrir LOS DOS ARCHIVOS (!= -1 (!=ERROR) ) y no estan vacios (!=0), entro al menu

        mostrar_menu();
        int opcion = ingresar_opcion("Ingrese una opcion: ",1,6);

        while(opcion != SALIR){
            procesar_opcion(lista_materiales, lista_edificios, opcion);
            mostrar_menu();
            opcion = ingresar_opcion("Ingrese una opcion: ",1,6);
        }

    }

    /*El objetivo de guardar fuera del menu, es que en caso de que 1 SOLO de los archivos no se pueda
    abrir o leer, no se libere memoria en el heap innecesariamente error: ( free(): free detected in 
    tcache  Aborted (core dumped)") pero si se libere la que uso el archivo 
    que SE PUDO ABRIR CON EXITO.*/
    
    guardar_archivos(lista_materiales, lista_edificios );

    delete lista_materiales;

    delete lista_edificios;
    
    return 0;

}
