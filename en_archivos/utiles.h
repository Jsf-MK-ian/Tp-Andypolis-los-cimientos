#ifndef ANDYPOLIS_UTILES_H
#define ANDYPOLIS_UTILES_H
#include <string>

using namespace std;

const string PATH_MATERIALES ="materiales.txt";
const string PATH_EDIFICIOS = "edificios.txt";
const int SALIR = 6;
const int ERROR = -1;


struct Material{
    string nombre_material;
    int cantidad_material;
};

struct Lista_materiales{
    // int ** matriz; //creo el doble puntero
    Material** materiales;
    int cantidad_de_materiales;   
};

struct Edificio{
    string nombre_edificio;
    int cantidad_piedra;
    int cantidad_madera;
    int cantidad_metal;
    int cantidad_construidos;
    int max_cantidad_permitidos;
};

struct Lista_edificios{
    // int ** matriz; //creo el doble puntero
    Edificio** edificios;
    int cantidad_de_edificios;   
};

/*
PRE: recibe el string "texto" con el mensaje a mostrar por pantalla y los entero "opciones_maximas" 
y "opciones_minimas" con el numero de maximas y minimas opciones que es posible elegir.

POST: Devuelve el entero "opcion" con la opcion elegida por el usuario cumpliendose la condicion de
que es valida
*/
int ingresar_opcion(string texto, int opciones_minimas, int opciones_maximas);


void agregar_edificio(Lista_edificios* lista_edificios, Edificio* edificio);


void cargar_edificios(Lista_edificios* lista_edificios);


void agregar_material(Lista_materiales* lista_materiales, Material* material);



void cargar_materiales(Lista_materiales* lista_materiales);


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles
POST: Muestra por pantalla los materiales de contruccion disponibles y sus respectivas cantidades
*/
void listar_materiales_de_construccion(Lista_materiales *lista_materiales);


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios

POST: Muestra por pantalla el listado de  todos los edificios indicando para cada uno de ellos, 
cuantas unidades de cada material se requieren para construir uno, cuantos fueron construidos hasta 
el momento y cuantos más puedo construir sin superar el máximo permitido.
*/
void listar_todos_los_edificios(Lista_edificios *lista_edificios);


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios

POST: Muestra por pantalla el listado de edificios construidos indicando cuantos hay de cada uno
*/
void listar_edificios_construidos(Lista_edificios *lista_edificios);

/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles a elegir y el string 
mensaje con el mensaje a imprimir por pantalla
POST: Devuelve el string "edificio_a_construir"
*/
string obtener_nombre_edificio(string mensaje, Lista_edificios *lista_edificios);


//Precondiciones: Recibe el struct "lista_edificios" con los edificios existentes
//Postcondiciones: Devuelve el booleano 'existe' con true si se encuentra entre los disponibles o
//con false en caso contrario
bool existe_edificio(Lista_edificios *lista_edificios, string edificio_a_construir);


//Precondiciones: Recibe el string "edificio_a_construir", el objeto "lista_edificios" con los 
//edificios disponibles.
//Postcondiciones: Devuelve el entero "posicion" con la posicion del edificio_a_construir.
int obtener_posicion_edificio(string edificio_a_construir, Lista_edificios* lista_edificios);


/*
Precondiciones: Recibe la el entero "cantidad_disponible" con la cantidad desponible de x material,
el entero "cantidad_material_necesaria" con la cantidad necesaria de ese mismo matrial, y el 
booleano "alcanza".

Postcondiciones: Devuelve el booleano "alcanza"
*/
void chequear_material(int cantidad_disponible, int cantidad_material_nec, bool &alcanza);

//Precondiciones: Recibe el objeto "lista_materiales" con los materiales disponibles, y los enteros
//"cantidad_piedra_nec", "cantidad_madera_nec", "cantidad_metal_nec" con las cantidades necesarias de
//cada uno
//Postcondiciones: devuelve el booleano "alcanza"
bool alcanzan_materiales(Lista_materiales *lista_materiales,int cantidad_piedra_nec, int cantidad_madera_nec, 
    int cantidad_metal_nec);


//Precondiciones: Recibe el string el objeto "lista_edificios" con los edificios disponibles y el 
//entero "posicion_edificio" con la posicion del edificio en la lista de edificios.
//POST: 
bool supera_max_cant(Lista_edificios *lista_edificios, int posicion_edificio);


/*
PRE: Recibe el struct "lista_edificios" con los edificios y su informacion y el entero 
"posicion_edificio" con la posicion del edificio en el vector edificios del struct lista_edificios.
POST: Suma 1 a la cantidad de edificios construidos del tipo que indico el usuario
*/
void registrar_edificio(Lista_edificios *lista_edificios, int posicion_edificio);


/*PRE: Recibe el puntero "cantidad_disponible" con la direccion de memoria de la cantidad disponible
del material que estoy usando
POST: Modifica dicha la cantidad disponible del material restandole la que es necesaria para 
la construccion
*/
void restar_material(int *cantidad_disponible, int cantidad_material_nec);


void utilizar_materiales(Lista_materiales *lista_materiales, int cantidad_piedra_nec, int cantidad_madera_nec,
    int cantidad_metal_nec);


//Precondiciones: Recibe los objetos "lista_edificios" y "lista_materiales" con los edificios y 
//materiales disponibles
//Potscondiciones: Devueleve??
void construir_edificio(string nombre_edificio, Lista_edificios *lista_edificios, Lista_materiales *lista_materiales);


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles y el enetro "posicion_edificio"
con la posicion del edificio en cuestion
POST: Resta 1 a la cantidad de edificios construidos del tipo en cuestion
*/
void quitar_edificio(Lista_edificios *lista_edificios, int posicion_edificio);


/*
PRE: Recibe el puntero "cantidad_disponible" con la direccion de memoria de la cantidad disponible
del material que estoy usando
POST: Modifica dicha la cantidad disponible del material sumandole la mitad de la que es necesaria 
para la construccion del edificio en cuestion
*/
void sumar_material(int *cantidad_disponible, int cantidad_material_nec);


/*
Recibe los structs "lista_materiales" con los materiales disponibles y los enteros 
"cantidad_piedra_nec", "cantidad_madera_nec", "cantidad_metal_nec" con las respectivas cantidades de
piedra madera y metal que usa el edificio que se quiere demoler
*/
void devolver_materiales(Lista_materiales *lista_materiales, int cantidad_piedra_nec, int cantidad_madera_nec,
    int cantidad_metal_nec);


/*
PRE: Recibe el struct "lista_edificios" con la lista de edificios y el entero "posicion_edificio"
con la posicion del edificio en el vector edificios
POST:Devuelve el booleano "construido" por true si se construyo algun edificio de ese tipo y por
false en caso contrario
*/
bool construido_alguna_vez(Lista_edificios *lista_edificios, int posicion_edificio);


/*
PRE: Recibe los structs "lista_edificios" y "lista_materiales" con los edificios y 
materiales disponibles
POST: demuele el edificio indicado cumpliendo las condiciones del enunciado
*/
void demoler_edificio(string nombre_edificio ,Lista_edificios *lista_edificios, Lista_materiales *lista_materiales);


/*
PRE: Recibe el objeto de tipo osfatream "archivo_edificios" correspondiente al archivo con los datos,
el struct "lista_edificios" con todos los edificios y su respectiva informacion y el entero "i" que
representa la posicion en el vector edificios del struct "lista_edificios"

POST: Escribe en el archivo el edificio de indice "i" con su respectiva info
*/
void escribir_edificio(ofstream *archivo_edificios,Lista_edificios * lista_edificios, int i);


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles
POST: Libera el heap que utilizo la matriz de edificios dentro del struct
*/
void guardar_edificios(Lista_edificios *lista_edificios);


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles

POST: Libera el heap que utilizo la matriz de materiales dentro del struct
*/
void guardar_materiales(Lista_materiales* lista_materiales);

/*
PRE: Recibe los structs "lista_materiales" con los materiales disponibles y "lista_edificios" con los
edificios disponibles

POST: Libera el heap que utilizo la matriz de materiales dentro del struct
*/
void guardar_archivos(Lista_materiales *lista_materiales, Lista_edificios * lista_edificios);

void mostrar_menu();


void menu_opciones(Lista_materiales *lista_materiales, Lista_edificios *lista_edificios, int opcion);



#endif //ANDYPOLIS_UTILES_H
