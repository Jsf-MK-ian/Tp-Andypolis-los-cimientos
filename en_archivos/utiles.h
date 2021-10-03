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
    Edificio** edificios;
    int cantidad_de_edificios;   
};


/*
PRE: recibe el string "texto" con el mensaje a mostrar por pantalla y los enteros "opciones_maximas" 
y "opciones_minimas" con el numero de maximas y minimas opciones que es posible elegir.

POST: Devuelve el entero "opcion" con la opcion elegida por el usuario cumpliendose la condicion de
que esta entre las permitidas.
*/
int ingresar_opcion(string texto, int opciones_minimas, int opciones_maximas);


/*
PRE: Recibe los structs "lista_edificios" con todos los edificios cargados hasta el momento y "edificio"
con el nuevo edificio que se cargara.

POST: Agrega el nuevo edificio a la lista de edificios.
*/
void agregar_edificio(Lista_edificios* lista_edificios, Edificio* edificio);


/*
PRE: Recibe el struct "lista_edificios" e intenta abrir el archivo "edificios.txt". 

POST: Abre el archivo "edificios.txt" y carga su contenido en el struct "lista_edificios".
*/
void cargar_edificios(Lista_edificios* lista_edificios);


/*
PRE: Recibe los structs "lista_materiales" con todos los materiales cargados hasta el momento y "material"
con el nuevo material que se cargara.

POST: Agrega el nuevo material la lista de edificios.
*/
void agregar_material(Lista_materiales* lista_materiales, Material* material);


/*
PRE: Recibe el struct "lista_materiales" e intenta abrir el archivo "materiales.txt". 

POST: Abre el archivo "materiales.txt" y carga su contenido en el struct "lista_materiales".
*/
void cargar_materiales(Lista_materiales* lista_materiales);


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles.

POST: Muestra por pantalla los materiales de contruccion y sus respectivas cantidades disponibles.
*/
void listar_materiales_de_construccion(Lista_materiales *lista_materiales);


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios.

POST: Muestra por pantalla el listado de  todos los edificios indicando para cada uno de ellos, 
cuantas unidades de cada material se requieren para construir uno, cuantos fueron construidos hasta 
el momento y cuantos más puedo construir sin superar el máximo permitido ('Restantes sin superar limite').
*/
void listar_todos_los_edificios(Lista_edificios *lista_edificios);


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios.

POST: Muestra por pantalla el listado de edificios actualmente construidos indicando cuantos hay
de cada uno.
*/
void listar_edificios_construidos(Lista_edificios *lista_edificios);


/*
PRE: Recibe el la direccion de memoria del string "nombre_edificio".

POST: Guarda el nombre del edificio en la direccion de memoria de "nombre_edificio".
*/
void obtener_nombre_edificio(string &nombre_edificio);


/*
PRE: Recibe el struct "lista_edificios" con los edificios existentes y el string "edificio_a_construir"
con un nombre valido de un edificio a construir.

POST: Devuelve el booleano "existe" con true si el edificio se encuentra entre los disponibles o
con false en caso contrario.
*/
bool existe_edificio(Lista_edificios *lista_edificios, string edificio_a_construir);


/*
PRE: Recibe el string "nombre_edificio" y el struct "lista_edificios" con los 
edificios disponibles.
POST: Devuelve el entero "posicion" con la posicion del edificio "nombre_edificio".
*/
int obtener_posicion_edificio(string edificio_a_construir, Lista_edificios* lista_edificios);


/*
PRE: Recibe los enteros "cantidad_disponible" con la cantidad desponible de un material y  
"cantidad_material_necesaria" con la cantidad necesaria de ese mismo material para la construccion de
un edificio; y la direecion de memoria del booleano "alcanza".

POST: Guarda true en "alcanza" si la cantidad de material disponible
supera la cantidad necesaria de dicho material y false en caso contrario.
*/
void chequear_material(int cantidad_disponible, int cantidad_material_nec, bool &alcanza);


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles, y los enteros
"cantidad_piedra_nec", "cantidad_madera_nec", "cantidad_metal_nec" con las cantidades necesarias de
cada uno para la construccion de un edificio.

POST: devuelve el booleano "alcanza" por true si la cantidad de material disponible de los 3 materiales
supera la cantidad necesaria de cada uno de ellos y por false en caso 
de que al menos una de ellas no lo haga.
*/
bool alcanzan_materiales(Lista_materiales *lista_materiales,int cantidad_piedra_nec, int cantidad_madera_nec, 
    int cantidad_metal_nec);


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles y
el entero "posicion_edificio" con una posicion valida en el vector de edificios 
del estruct "lista_edificios".

POST: Devuelve el booleano "supera" por true en caso de que la cantidad de edificios 
construidos '+ 1' supere la maxima cantidad permitida.
*/
bool supera_max_cant_permitida(Lista_edificios *lista_edificios, int posicion_edificio);


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles y el
entero "posicion_edificio" con una posicion valida en el vector de 
edificios del struct "lista_edificios.""

POST: Suma 1 a la cantidad de edificios construidos del tipo que indico el usuario.
*/
void registrar_edificio(Lista_edificios *lista_edificios, int posicion_edificio);


/*PRE: Recibe el puntero "cantidad_disponible" con la direccion de memoria de la cantidad disponible
del material que estoy utilizando.

POST: Modifica la cantidad disponible de dicho material a traves del 
puntero "cantidad_disponoble" restandole la que es necesaria para 
la construccion del edificio en cuestion.
*/
void restar_material(int *cantidad_disponible, int cantidad_material_nec);


/*PRE: Recibe el struct "lista_materiales" con los materiales disponibles (y sus 
respectivas cantidades) y los enteros "cantidad_piedra_nec", "cantidad_madera_nec"
"cantidad_metal_nec" con las cantidades necesarias de cada uno de ellos para la 
construccion de un edificio.

POST: Modifica la cantidad disponible de piedra, mader y metal restandole las que 
son necesarias para necesarias para la construccion de un edificio.
*/
void utilizar_materiales(Lista_materiales *lista_materiales, int cantidad_piedra_nec, int cantidad_madera_nec,
    int cantidad_metal_nec);


/*
PRE: Recibe el string "edificio_a_construir" con un nombre valido de un edificio que se quiere
construir y los structs "lista_materiales" y "lista_edificios" con los edificios y 
materiales disponibles.

POST: Construye el edificio "edificio_a_construir" agregandolo en "lista_edificios"
y restando las cantidades de los materiales necesarios de "lista_materiales". En 
caso de no ser posible, se le informa al usuario la razon.
*/
void construir_edificio(string edificio_a_construir, Lista_edificios *lista_edificios, 
Lista_materiales *lista_materiales);


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles y el enetro "posicion_edificio"
con la posicion del edificio en el vector edificios del struct "lista_edificios".

POST: Resta '1' a la cantidad de edificios construidos del tipo en cuestion.
*/
void quitar_edificio(Lista_edificios *lista_edificios, int posicion_edificio);


/*
PRE: Recibe el puntero "cantidad_disponible" con la direccion de memoria de la cantidad disponible
del material que estoy usando

POST: Modifica la cantidad disponible de dicho material a traves del 
puntero "cantidad_disponible" sumandole la mitad de la que es
necesaria para la la construccion del edificio en cuestion
*/
void sumar_material(int *cantidad_disponible, int cantidad_material_nec);


/*PRE: Recibe el struct "lista_materiales" con los materiales disponibles (y sus 
respectivas cantidades) y los enteros "cantidad_piedra_nec", "cantidad_madera_nec"
"cantidad_metal_nec" con las cantidades necesarias de cada uno de ellos para la 
construccion de un edificio.

POST: Modifica la cantidad disponible de piedra, mader y metal sumandole la mitad 
de las que son necesarias para necesarias para la construccion de un edificio.
*/
void devolver_materiales(Lista_materiales *lista_materiales, int cantidad_piedra_nec, int cantidad_madera_nec,
    int cantidad_metal_nec);


/*
PRE: Recibe el struct "lista_edificios" con la lista de edificios y el entero "posicion_edificio"
con la posicion del edificio en el vector edificios del struct "lista_edificios"

POST:Devuelve el booleano "construido" por true si hay algun edificio construido 
de ese tipo y por false en caso contrario.
*/
bool construido_alguna_vez(Lista_edificios *lista_edificios, int posicion_edificio);



/*
PRE: Recibe el string "edificio_a_demoler" con un nombre valido de un edificio que se quiere
demoler y los structs "lista_materiales" y "lista_edificios" con los edificios y 
materiales disponibles.

POST: Demuele el edificio "edificio_a_construir" quitandolo de "lista_edificios"
y sumando la mitad de las cantidades de los materiales necesarios para 
su construccion en "lista_materiales". En caso de no ser posible, se 
le informa al usuario la razon.
*/
void demoler_edificio(string edificio_a_demoler ,Lista_edificios *lista_edificios, Lista_materiales *lista_materiales);


/*
PRE: Recibe el objeto de tipo osfstream "archivo_edificios" correspondiente al archivo con los datos,
el struct "lista_edificios" con todos los edificios y su respectiva informacion y el entero "i" que
representa la posicion en el vector edificios del struct "lista_edificios"

POST: Escribe en el archivo el edificio de indice "i" con su respectivos datos.
*/
void escribir_edificio(ofstream *archivo_edificios,Lista_edificios * lista_edificios, int i);


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles.

POST: Libera el heap que utilizo el vecto de edificios dentro del struct y escribe 
el archivo "edificios.txt" con las modificaciones que se hayan realizado sobre
el listado de edificios.
*/
void guardar_edificios(Lista_edificios *lista_edificios);


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles.

POST: Libera el heap que utilizo el vector de materiales dentro del struct y escribe 
el archivo "materiales.txt" con las modificaciones que se hayan realizado sobre
el listado de materiales.
*/
void guardar_materiales(Lista_materiales* lista_materiales);


/*
PRE: Recibe los structs "lista_materiales" con los materiales disponibles y "lista_edificios" con los
edificios disponibles

POST: Libera el heap que utilizaron las matrices de materiales y edificios dentro de cada struct si
loas archivos se pudieron abrir y leer correctamente.
*/
void guardar_archivos(Lista_materiales *lista_materiales, Lista_edificios * lista_edificios);


/*
PRE:-

POST: Muestra por pantalla el menu de opciones.
*/
void mostrar_menu();

/*
PRE: Recibe el entero "opcion" con una opcion valida y los structs "lista_materiales" y "lista_edificios"
con la lista de materiales y edifcios respectivamente.

POST: Realiza la operacion indicada.
*/
void procesar_opcion(Lista_materiales *lista_materiales, Lista_edificios *lista_edificios, int opcion);



#endif //ANDYPOLIS_UTILES_H
