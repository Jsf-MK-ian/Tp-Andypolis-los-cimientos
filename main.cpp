#include <iostream>
#include "utiles.h"

int main() {

    cout << sizeof(int) << " " << sizeof(long) << endl;

    Agenda* agenda = new Agenda;
    int opcion = 0;

    cargar_agenda(agenda);

    mostrar_menu();
    opcion = pedir_opcion();
    validar_opcion_elegida(opcion);

    while(opcion != SALIR){
        procesar_opcion(agenda, opcion);

        mostrar_menu();
        opcion = pedir_opcion();
        validar_opcion_elegida(opcion);
    }

    cerrar_agenda(agenda);

    delete agenda;

    return 0;
}
