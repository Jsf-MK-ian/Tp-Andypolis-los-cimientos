#ifndef AGENDA_UTILES_H
#define AGENDA_UTILES_H
#include <string>

using namespace std;

const int OPCIONES_VALIDAS = 5;
const string PATH_CONTACTOS = "contactos.txt";
const int SALIR = 5;
const int CANTIDAD_NUMEROS_EN_TELEFONO = 10;

struct Contacto{
    string nombre;
    long numero;
};

struct Agenda{
    Contacto** contactos;
    int cantidad_de_contactos;
};

//Precondiciones: -
//Postcondiciones: Carga la agenda con los datos del archivo de contactos
void cargar_agenda(Agenda* agenda);

//Precondiciones: -
//Postcondiciones: imprime por pantalla el menu
void mostrar_menu();

//Precondiciones: -
//Postcondiciones: Le solicita al usuario que ingrese el numero de la opcion que desea seleccionar
int pedir_opcion();

//Precondiciones: recibe la opcion elegida precargada
//Postcondiciones: Verifica que la opcion sea un numero entre 0 y el valor de OPCIONES_VALIDAS y si no lo es vuelve a solicitar los datos
void validar_opcion_elegida(int &opcion_elegida);

//Precondiciones: El contacto debe estar bien cargado
//Postcondiciones: Añade el contacto a la agenda
void agregar_contacto(Agenda* agenda, Contacto* contacto);

//Precondiciones: La opcion es valida.
//Postcondiciones: Realiza la opcion indicada.
void procesar_opcion(Agenda* agenda, int opcion);

//Precondiciones: -
//Postcondiciones: Guarda los contactos en el archivo contactos y elimina la agenda
void cerrar_agenda(Agenda* agenda);

//Precondiciones: -
//Postcondiciones: Imprime por pantalla los contactos que contiene la agenta o un mensaje si esta vacia
void mostrar_contactos(Agenda* agenda);

//Precondiciones: La posicion debe existir dentro de la agenda
//Postcondiciones: Muestra por pantalla los datos del contacto que se encuentra en la posicion indicada
void mostrar_contacto(Agenda* agenda, int posicion);

//Precondiciones: La posicion debe existir dentro de la agenda
//Postcondiciones: Elimina el contacto que se encuentra en la posicion indicada
void eliminar_contacto(Agenda* agenda, int posicion);

//Precondiciones: -
//Postcondiciones: Solicita al usuario el numero de telefono hasta que sea valido
long pedir_numero();

//Precondiciones: -
//Postcondiciones: Devuelve true si el numero de telefono esta en la agenda y false en caso contrario
bool existe_el_numero(long numero, Agenda* agenda);

//Precondiciones: -
//Postcondiciones: Devuelve la posicion en la que se encuentra el numero recibido o -1 si no es encontrado
int obtener_posicion_del_contacto(long numero, Agenda* agenda);

//Precondiciones: -
//Postcondiciones: Verifica que sea un numero de telefono (solo hay numeros y tiene la longitud correcta)
bool es_numero_valido(string numero);

//Precondiciones: -
//Postcondiciones: Solicita al usuario que ingrese el nombre del contacto y su numero telefonico
Contacto* pedir_contacto();

//Precondiciones: Las posiciones deben estar dentro de la agenda
//Postcondiciones: Intercambia los contactos de las posiciones recibidas
void swap(Agenda* agenda, int posicion1, int posicion2);

#endif //AGENDA_UTILES_H
