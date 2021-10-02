#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string PATH_MATERIALES ="materiales.txt";
const string PATH_EDIFICIOS = "edificios.txt";
const int ERROR = -1;

const int LISTAR_MATERIALES = 1;
const int CONSTRUIR_EDIFICIO = 2;
const int LISTAR_EDIFICIOS_CONSTRUIDOS = 3;
const int LISTAR_TODOS_LOS_EDIFICIOS = 4;
const int DEMOLER_EDIFICIO = 5;
const int SALIR = 6;

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
int ingresar_opcion(string texto, int opciones_minimas, int opciones_maximas){
    
    cout<<texto;
    
    int opcion;
    cin >> opcion;

    bool es_opcion_valida = (opcion >= opciones_minimas && opcion <= opciones_maximas);
    while(!es_opcion_valida){
        cout << "por favor ingrese una opcion valida: ";
        cin >> opcion;
        es_opcion_valida = (opcion >= opciones_minimas && opcion <= opciones_maximas);
    }
    cout<<endl;
    return opcion;
}


void agregar_edificio(Lista_edificios* lista_edificios, Edificio* edificio){
    int tope_viejo = lista_edificios -> cantidad_de_edificios;

    // int ** matriz;
    // matriz = new int*[4];
    Edificio** nuevo_vector_edificios = new Edificio*[tope_viejo + 1];

    // for (int i = 0; i < 4; i++){ //xa cada fila
    for(int i = 0; i < lista_edificios -> cantidad_de_edificios; i++){
        nuevo_vector_edificios[i] = lista_edificios -> edificios[i];
        //matriz[i] = new int[5] };
    }
    nuevo_vector_edificios[tope_viejo] = edificio;

    if(lista_edificios -> cantidad_de_edificios != 0){
        delete[] lista_edificios -> edificios;
    }

    lista_edificios-> edificios = nuevo_vector_edificios;
    lista_edificios -> cantidad_de_edificios++;
};


void cargar_edificios(Lista_edificios* lista_edificios){
    lista_edificios -> cantidad_de_edificios = 0;

    fstream archivo_edificios(PATH_EDIFICIOS, ios::in);

    if(archivo_edificios.is_open()){

        string nombre_edificio;
        string cantidad_piedra;
        string cantidad_madera;
        string cantidad_metal;
        string cantidad_construidos;
        string max_cantidad_permitidos;

        Edificio* edificio;

        while(archivo_edificios >> nombre_edificio){
            archivo_edificios >> cantidad_piedra;
            archivo_edificios >> cantidad_madera;
            archivo_edificios >> cantidad_metal;
            archivo_edificios >> cantidad_construidos;
            archivo_edificios >> max_cantidad_permitidos;

            edificio = new Edificio;
            
            edificio -> nombre_edificio = nombre_edificio;
            edificio -> cantidad_piedra = stoi(cantidad_piedra);
            edificio -> cantidad_madera = stoi(cantidad_madera);
            edificio -> cantidad_metal = stoi(cantidad_metal);
            edificio -> cantidad_construidos = stoi(cantidad_construidos);
            edificio -> max_cantidad_permitidos = stoi(max_cantidad_permitidos);

            agregar_edificio(lista_edificios, edificio);
        }

        archivo_edificios.close();
    }
    else{
        lista_edificios -> cantidad_de_edificios = -1;//para chequear si se abrio o no el archivo
        cout<<"NO SE ENCONTRO EL ARCHIVO "<<PATH_EDIFICIOS<<endl;
    }
}


void agregar_material(Lista_materiales* lista_materiales, Material* material){
    int tope_viejo = lista_materiales -> cantidad_de_materiales;

    // int ** matriz;
    // matriz = new int*[4];
    Material** nuevo_vector_materiales = new Material*[tope_viejo + 1];

    // for (int i = 0; i < 4; i++){ //xa cada fila
    for(int i = 0; i < lista_materiales -> cantidad_de_materiales; i++){
        nuevo_vector_materiales[i] = lista_materiales -> materiales[i];
        //matriz[i] = new int[5] };
    }
    nuevo_vector_materiales[tope_viejo] = material;

    if(lista_materiales -> cantidad_de_materiales != 0){
        delete[] lista_materiales -> materiales;
    }

    lista_materiales -> materiales = nuevo_vector_materiales;
    lista_materiales -> cantidad_de_materiales++;
}


void cargar_materiales(Lista_materiales* lista_materiales){
    lista_materiales -> cantidad_de_materiales = 0;

    fstream archivo_materiales(PATH_MATERIALES, ios::in);

    if(archivo_materiales.is_open()){

        string nombre;
        string cant;

        Material* material;

        while(archivo_materiales >> nombre){
            archivo_materiales >> cant;
            material = new Material;
            material -> nombre_material = nombre;
            material -> cantidad_material = stoi(cant);

            agregar_material(lista_materiales, material);
        }

        archivo_materiales.close();
    }
    else{
        lista_materiales -> cantidad_de_materiales = -1;//para chequear si se abrio o no el archivo
        cout<<"NO SE ENCONTRO EL ARCHIVO "<<PATH_MATERIALES<<endl;
    }
}


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles
POST: Muestra por pantalla los materiales de contruccion disponibles y sus respectivas cantidades
*/
void listar_materiales_de_construccion(Lista_materiales *lista_materiales){
    cout << setfill(' ') << setw(64)<<"MATERIALES DE CONSTRUCCION"<<"\n\n"
    << setfill(' ') <<setw(48) <<"NOMBRE"<< setfill(' ')<<setw(13)<<"MATERIAL"<<endl
    << setfill(' ') <<setw(70)<<"______________________________________" <<endl<<endl;
    
    for(int i = 0; i < lista_materiales -> cantidad_de_materiales; i++){
        cout<<setfill(' ')<<setw(48)<<lista_materiales -> materiales[i] -> nombre_material
        <<setfill(' ')<<setw(11)<<lista_materiales -> materiales[i] -> cantidad_material <<endl;
        }

    cout<<endl;    
}


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios

POST: Muestra por pantalla el listado de  todos los edificios indicando para cada uno de ellos, 
cuantas unidades de cada material se requieren para construir uno, cuantos fueron construidos hasta 
el momento y cuantos más puedo construir sin superar el máximo permitido.
*/
void listar_todos_los_edificios(Lista_edificios *lista_edificios){

    cout<< setfill(' ') << setw(64)<<"EDIFICIOS DE ANDYPOLIS \n\n";
    cout<<setfill(' ')<<setw(20)<<"NOMBRE"<< setfill(' ')<<setw(11)<<"PIEDRA"
    <<setfill(' ') << setw(8)<<"MADERA"<< setfill(' ') << setw(8)<<"METAL"
    <<setfill(' ') << setw(13)<<"CONSTRUIDOS"
    <<setfill(' ') << setw(31)<<"RESTANTES SIN SUPERAR LIMITE"<<endl;
    cout<<"\t"<<"_______________________________________________________________________________________";
    cout<<endl<<endl;
    for(int i = 0; i < lista_edificios -> cantidad_de_edificios; i++){
        cout << setfill(' ')<<setw(20)<< lista_edificios -> edificios[i] -> nombre_edificio
        << setfill(' ')<<setw(10)<< lista_edificios -> edificios[i] -> cantidad_piedra
        << setfill(' ')<<setw(8)<< lista_edificios -> edificios[i] -> cantidad_madera
        << setfill(' ')<<setw(8) << lista_edificios -> edificios[i] -> cantidad_metal;
        
        int construidos = lista_edificios -> edificios[i] -> cantidad_construidos;        
        int max_cantidad_permitidos =  lista_edificios -> edificios[i] -> max_cantidad_permitidos; 

        int restantes =  max_cantidad_permitidos - construidos;

        cout << setfill(' ') << setw(10) << construidos
        <<setfill(' ') << setw(17)<< restantes <<endl;
        
        };
        
        cout<<endl;
}


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios

POST: Muestra por pantalla el listado de edificios construidos indicando cuantos hay de cada uno
*/
void listar_edificios_construidos(Lista_edificios *lista_edificios){
    cout<< setfill(' ') << setw(66)<<"EDIFICIOS CONSTRUIDOS \n\n"
    <<setfill(' ')<<setw(45)<<"NOMBRE"<<setfill(' ')<<setw(24)<<"CANTIDAD CONSTRUIDOS"<<endl
    <<setfill(' ')<<setw(77)<<"____________________________________________________"<<endl<<endl;
    
    for(int i = 0; i < lista_edificios -> cantidad_de_edificios; i++){
        
        string nombre_edificio = lista_edificios -> edificios[i] -> nombre_edificio;
        int construidos = lista_edificios -> edificios[i] -> cantidad_construidos;
        
        if (construidos > 0){
            cout << setfill(' ')<<setw(45) << nombre_edificio
            <<setfill(' ')<<setw(12)<< construidos << endl;
        
        }
    }
    cout<<endl;
}

/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles a elegir y el string 
mensaje con el mensaje a imprimir por pantalla
POST: Devuelve el string "edificio_a_construir"
*/
string obtener_nombre_edificio(string &nombre_edificio){

    cin >> nombre_edificio;
    
    return nombre_edificio;
}

//Precondiciones: Recibe el struct "lista_edificios" con los edificios existentes
//Postcondiciones: Devuelve el booleano 'existe' con true si se encuentra entre los disponibles o
//con false en caso contrario
bool existe_edificio(Lista_edificios *lista_edificios, string edificio_a_construir){
    bool existe = false;
    int i = 0;
    while ( !existe && i < lista_edificios -> cantidad_de_edificios){
        if (lista_edificios -> edificios[i] -> nombre_edificio == edificio_a_construir){
            existe = true;
        }
        i++;
    }

    return existe;   
}


//Precondiciones: Recibe el string "edificio_a_construir", el objeto "lista_edificios" con los 
//edificios disponibles.
//Postcondiciones: Devuelve el entero "posicion" con la posicion del edificio_a_construir.
int obtener_posicion_edificio(string edificio_a_construir, Lista_edificios* lista_edificios){
    bool encontrado = false;
    int posicion = ERROR;
    int i = 0;
    while (!encontrado && i< lista_edificios -> cantidad_de_edificios){
        if (lista_edificios -> edificios[i] -> nombre_edificio == edificio_a_construir){
            encontrado = true;
            posicion = i;
        }
        i++;
    }
    return posicion;
}


/*
Precondiciones: Recibe la el entero "cantidad_disponible" con la cantidad desponible de x material,
el entero "cantidad_material_necesaria" con la cantidad necesaria de ese mismo matrial, y el 
booleano "alcanza".

Postcondiciones: Devuelve el booleano "alcanza"
*/
void chequear_material(int cantidad_disponible, int cantidad_material_nec, bool &alcanza){
    if (cantidad_disponible < cantidad_material_nec){
                alcanza = false;
    }
}

//Precondiciones: Recibe el objeto "lista_materiales" con los materiales disponibles, y los enteros
//"cantidad_piedra_nec", "cantidad_madera_nec", "cantidad_metal_nec" con las cantidades necesarias de
//cada uno
//Postcondiciones: devuelve el booleano "alcanza"
bool alcanzan_materiales(Lista_materiales *lista_materiales,int cantidad_piedra_nec, int cantidad_madera_nec, 
    int cantidad_metal_nec){

    bool alcanza = true;
    int i = 0;
    while (alcanza && i < lista_materiales -> cantidad_de_materiales){
        
        string material_a_chequear = lista_materiales -> materiales[i] ->nombre_material;
        int cantidad_disponible = lista_materiales -> materiales[i] -> cantidad_material;
        
        
        if (material_a_chequear == "piedra"){
            chequear_material(cantidad_disponible, cantidad_piedra_nec, alcanza);
        }
        if (material_a_chequear == "madera"){
            chequear_material(cantidad_disponible, cantidad_madera_nec, alcanza);
        } 
        if (material_a_chequear == "metal"){
            chequear_material(cantidad_disponible, cantidad_metal_nec, alcanza);
        }
        i++;
    }
    return alcanza;
}


//Precondiciones: Recibe el string el objeto "lista_edificios" con los edificios disponibles y el 
//entero "posicion_edificio" con la posicion del edificio en la lista de edificios.
//POST: 
bool supera_max_cant(Lista_edificios *lista_edificios, int posicion_edificio){
    bool supera = false;
    
    int construidos = lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos;
    int max_permitidos = lista_edificios -> edificios[posicion_edificio] -> max_cantidad_permitidos;

    if (construidos + 1 > max_permitidos){
        supera = true;
    }

    return supera;    
}

/*
PRE: Recibe el struct "lista_edificios" con los edificios y su informacion y el entero 
"posicion_edificio" con la posicion del edificio en el vector edificios del struct lista_edificios.
POST: Suma 1 a la cantidad de edificios construidos del tipo que indico el usuario
*/
void registrar_edificio(Lista_edificios *lista_edificios, int posicion_edificio){
    
    lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos +=1;

}


/*PRE: Recibe el puntero "cantidad_disponible" con la direccion de memoria de la cantidad disponible
del material que estoy usando
POST: Modifica dicha la cantidad disponible del material restandole la que es necesaria para 
la construccion
*/
void restar_material(int *cantidad_disponible, int cantidad_material_nec){
    *cantidad_disponible =  *cantidad_disponible - cantidad_material_nec;
}


void utilizar_materiales(Lista_materiales *lista_materiales, int cantidad_piedra_nec, int cantidad_madera_nec,
    int cantidad_metal_nec){
    int i = 0;
    
    int *cantidad_disponible;

    while (i < lista_materiales -> cantidad_de_materiales){
    
        string material_a_chequear = lista_materiales -> materiales[i] ->nombre_material;
        
        cantidad_disponible = & (lista_materiales -> materiales[i] -> cantidad_material);

        if (material_a_chequear == "piedra"){
            restar_material(cantidad_disponible, cantidad_piedra_nec);
        }
        if (material_a_chequear == "madera"){
            restar_material(cantidad_disponible, cantidad_madera_nec);
        } 
        if (material_a_chequear == "metal"){
            restar_material(cantidad_disponible, cantidad_metal_nec);
        }
        i++;
    }

}


//Precondiciones: Recibe los objetos "lista_edificios" y "lista_materiales" con los edificios y 
//materiales disponibles
//Potscondiciones: Devueleve??
void construir_edificio(string edificio_a_construir ,Lista_edificios *lista_edificios, 
    Lista_materiales *lista_materiales){

    if (existe_edificio(lista_edificios, edificio_a_construir)){
            
            int posicion_edificio = obtener_posicion_edificio(edificio_a_construir, lista_edificios);

            int cantidad_piedra_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_piedra;
            int cantidad_madera_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_madera;
            int cantidad_metal_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_metal;
        if ( alcanzan_materiales(lista_materiales,cantidad_piedra_nec, cantidad_madera_nec, 
                                 cantidad_metal_nec)){
            
            if( !supera_max_cant(lista_edificios, posicion_edificio) ){
                string mensaje = "Desea iniciar la construccion? 1-SI 0-No: ";
                if (ingresar_opcion(mensaje,0,1)){  //observar que 0 es false
                    
                    utilizar_materiales(lista_materiales, cantidad_piedra_nec, cantidad_madera_nec, 
                                        cantidad_metal_nec);
                    
                    registrar_edificio(lista_edificios, posicion_edificio);
                    cout <<"Se construyo exitoamente el/la " << edificio_a_construir;
                }else{
                    cout <<"Se cancelo la construccion del/la " << edificio_a_construir;
                }

            }else{
                cout<<"No se puede construir porque se supera la maxima cantidad de edificios del tipo " 
                << edificio_a_construir<< " permitidos ";
            }
        }else{
            cout <<"No alcanzan los materiales para construir el/la "<< edificio_a_construir;
        }
    }else{
        cout << "El edificio " << edificio_a_construir<< " no se encuentra dispoible para construir";
    };

    cout<<endl;
    
};


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles y el enetro "posicion_edificio"
con la posicion del edificio en cuestion
POST: Resta 1 a la cantidad de edificios construidos del tipo en cuestion
*/
void quitar_edificio(Lista_edificios *lista_edificios, int posicion_edificio){
    
    lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos --;

}


/*
PRE: Recibe el puntero "cantidad_disponible" con la direccion de memoria de la cantidad disponible
del material que estoy usando
POST: Modifica dicha la cantidad disponible del material sumandole la mitad de la que es necesaria 
para la construccion del edificio en cuestion
*/
void sumar_material(int *cantidad_disponible, int cantidad_material_nec){
    *cantidad_disponible =  *cantidad_disponible + cantidad_material_nec/2; 
                        //truncado (redondeo hacia abajo)                                            
}


/*
Recibe los structs "lista_materiales" con los materiales disponibles y los enteros 
"cantidad_piedra_nec", "cantidad_madera_nec", "cantidad_metal_nec" con las respectivas cantidades de
piedra madera y metal que usa el edificio que se quiere demoler
*/
void devolver_materiales(Lista_materiales *lista_materiales, int cantidad_piedra_nec, int cantidad_madera_nec,
    int cantidad_metal_nec){
    int i = 0;
    
    int *cantidad_disponible;

    while (i < lista_materiales -> cantidad_de_materiales){
    
        string material_a_chequear = lista_materiales -> materiales[i] ->nombre_material;
        
        cantidad_disponible = & (lista_materiales -> materiales[i] -> cantidad_material);

        if (material_a_chequear == "piedra"){
            sumar_material(cantidad_disponible, cantidad_piedra_nec);
        }
        if (material_a_chequear == "madera"){
            sumar_material(cantidad_disponible, cantidad_madera_nec);
        } 
        if (material_a_chequear == "metal"){
            sumar_material(cantidad_disponible, cantidad_metal_nec);
        }
        i++;
    }

}


/*
PRE: Recibe el struct "lista_edificios" con la lista de edificios y el entero "posicion_edificio"
con la posicion del edificio en el vector edificios
POST:Devuelve el booleano "construido" por true si se construyo algun edificio de ese tipo y por
false en caso contrario
*/
bool construido_alguna_vez(Lista_edificios *lista_edificios, int posicion_edificio){
    bool construido = false;

    int construidos = lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos;
    int max_permitidos = lista_edificios -> edificios[posicion_edificio] -> max_cantidad_permitidos;

    if (construidos - 1 >= 0){
        construido = true;
    }

    return construido;    
}



/*
PRE: Recibe los structs "lista_edificios" y "lista_materiales" con los edificios y 
materiales disponibles
POST: demuele el edificio indicado cumpliendo las condiciones del enunciado
*/
void demoler_edificio(string edificio_a_demoler ,Lista_edificios *lista_edificios, 
    Lista_materiales *lista_materiales){
    
    if ( existe_edificio(lista_edificios, edificio_a_demoler) ){
            
        int posicion_edificio = obtener_posicion_edificio(edificio_a_demoler, lista_edificios);

        int cantidad_piedra_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_piedra;
        int cantidad_madera_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_madera;
        int cantidad_metal_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_metal;
        
        if( construido_alguna_vez(lista_edificios, posicion_edificio) ){
                string mensaje = "Desea iniciar la demolicion? 1-SI 0-No: ";
                if (ingresar_opcion(mensaje,0,1)){  //observar que 0 es false
                    
                    devolver_materiales(lista_materiales, cantidad_piedra_nec, cantidad_madera_nec, 
                                        cantidad_metal_nec);
                    
                    quitar_edificio(lista_edificios, posicion_edificio);
                    cout<< "Se demolio exitoamente  el/la "<< edificio_a_demoler;

                }else{
                    cout <<"Se cancelo la demolicion del /la " << edificio_a_demoler;
                }

            }else{
                cout<<"Todavia no se ha construido aun ningun/a "<< edificio_a_demoler;
            }
    }else{
        cout << "El edificio " << edificio_a_demoler<< " no se encuentra dispoible para demoler";
    };

    cout<<endl;
}


/*
PRE: Recibe el objeto de tipo osfatream "archivo_edificios" correspondiente al archivo con los datos,
el struct "lista_edificios" con todos los edificios y su respectiva informacion y el entero "i" que
representa la posicion en el vector edificios del struct "lista_edificios"

POST: Escribe en el archivo el edificio de indice "i" con su respectiva info
*/
void escribir_edificio(ofstream *archivo_edificios,Lista_edificios * lista_edificios, int i){
    
    *archivo_edificios << lista_edificios -> edificios[i] -> nombre_edificio <<' '
    << lista_edificios -> edificios[i] -> cantidad_piedra << ' '
    << lista_edificios -> edificios[i] -> cantidad_madera << ' '
    << lista_edificios -> edificios[i] -> cantidad_metal << ' '
    << lista_edificios -> edificios[i] -> cantidad_construidos << ' '
    << lista_edificios -> edificios[i] -> max_cantidad_permitidos << endl;
}


/*
PRE: Recibe el struct "lista_edificios" con los edificios disponibles
POST: Libera el heap que utilizo la matriz de edificios dentro del struct
*/
void guardar_edificios(Lista_edificios *lista_edificios){

    //borro las filas de la matriz materiales que hay dentro de lista_edificios
    
    ofstream archivo_edificios(PATH_EDIFICIOS);

    int cantidad_de_edificios = lista_edificios -> cantidad_de_edificios;

    for(int i = 0; i < cantidad_de_edificios; i++){    //xa cada fila
        
        escribir_edificio(&archivo_edificios, lista_edificios, i);

        delete lista_edificios -> edificios[i];   //se elimina el espacio de la fila
        //delete[] matriz[i]
        lista_edificios -> cantidad_de_edificios--;
    }
    //delete[] matriz;   //se elimina el vector de vectores
    delete[] lista_edificios -> edificios;
    lista_edificios -> edificios = nullptr;
    
}


/*
PRE: Recibe el struct "lista_materiales" con los materiales disponibles

POST: Libera el heap que utilizo la matriz de materiales dentro del struct
*/
void guardar_materiales(Lista_materiales* lista_materiales){
  
    //borro las filas de la matriz materiales que hay dentro de lista_materiales
    
    ofstream archivo_materiales(PATH_MATERIALES);

    int cantidad_de_materiales = lista_materiales -> cantidad_de_materiales;

        for(int i = 0; i < cantidad_de_materiales; i++){    //xa cada fila
            archivo_materiales << lista_materiales -> materiales[i] -> nombre_material << ' '
                << lista_materiales -> materiales[i] -> cantidad_material << '\n';
            
            delete lista_materiales -> materiales[i];   //se elimina el espacio de la fila
            //delete[] matriz[i]
            lista_materiales -> cantidad_de_materiales--;
        }
        //delete[] matriz;   //se elimina el vector de vectores
        delete[] lista_materiales -> materiales;
        lista_materiales -> materiales = nullptr;

}

/*
PRE: Recibe los structs "lista_materiales" con los materiales disponibles y "lista_edificios" con los
edificios disponibles

POST: Libera el heap que utilizo la matriz de materiales dentro del struct
*/
void guardar_archivos(Lista_materiales *lista_materiales, Lista_edificios * lista_edificios){
    if (lista_materiales -> cantidad_de_materiales == 0 || lista_materiales -> cantidad_de_materiales == -1){
        
        if (lista_materiales -> cantidad_de_materiales == 0){
            cout<<"EL ARCHIVO '"<<PATH_MATERIALES<<"' ESTA VACIO"<<endl;
        }
    }else{
        guardar_materiales(lista_materiales);
    }

    if (lista_edificios -> cantidad_de_edificios == 0 || lista_edificios -> cantidad_de_edificios ==-1){
        
        if (lista_edificios -> cantidad_de_edificios == 0){
            cout<<"EL ARCHIVO '"<<PATH_EDIFICIOS<<"' ESTA VACIO"<<endl; 
        }
    }else{
        guardar_edificios(lista_edificios);
    }
}


void mostrar_menu(){
    cout << endl; // << endl << endl;
    cout << "MENU" << endl
    << "\t" << "1 - Listar materiales de construccion " << endl
    << "\t" << "2 - construir edificio por nombre " << endl
    << "\t" << "3 - Listar los edificios construidos" << endl
    << "\t" << "4 - Listar todos los edificios " << endl
    << "\t" << "5 - Demoler un edificio por nombre " << endl
    << "\t" << "6 - Guardar y salir"<<endl;
    cout<<endl;
}


void menu_opciones(Lista_materiales *lista_materiales, Lista_edificios *lista_edificios, int opcion){

    switch (opcion){
        case LISTAR_MATERIALES:{
            listar_materiales_de_construccion(lista_materiales);
            break;
        }
        case CONSTRUIR_EDIFICIO:{
            cout << "Indique el nombre del edificio que desea construir: ";
            string edificio_a_construir;
            obtener_nombre_edificio(edificio_a_construir);

            construir_edificio(edificio_a_construir,lista_edificios, lista_materiales);
            
            break;
        }
        case LISTAR_EDIFICIOS_CONSTRUIDOS:
            //agregar caso no hay edificios construidos
            listar_edificios_construidos(lista_edificios);
            break;

        case LISTAR_TODOS_LOS_EDIFICIOS:
            listar_todos_los_edificios(lista_edificios);
            break;
            
        case DEMOLER_EDIFICIO:{
            cout<<"Indique el nombre del edificio que desea demoler: ";
            string edificio_a_demoler;
            obtener_nombre_edificio(edificio_a_demoler);
            
            demoler_edificio(edificio_a_demoler,lista_edificios, lista_materiales);
            
            break;
        }
        case SALIR:

            break;
        
    }

}


int main(){

    Lista_materiales*lista_materiales = new Lista_materiales;
    cargar_materiales(lista_materiales);
    
    Lista_edificios*lista_edificios = new Lista_edificios;
    cargar_edificios(lista_edificios);

    if (lista_materiales->cantidad_de_materiales != -1 && lista_materiales->cantidad_de_materiales != 0 &&  
    lista_edificios -> cantidad_de_edificios !=-1 && lista_edificios -> cantidad_de_edificios !=0 ){
    //Si se pudieron abrir LOS DOS ARCHIVOS (!= -1) y no estan vacios (!=0), muestro el menu

        mostrar_menu();
        int opcion = ingresar_opcion("Ingrese una opcion: ",1,6);

        while(opcion != SALIR){
            menu_opciones(lista_materiales, lista_edificios, opcion);
            mostrar_menu();
            opcion = ingresar_opcion("Ingrese una opcion: ",1,6);
        }

    }
    //El objetivo de guardar fuera del menu, es que en caso de que 1 SOLO de los archivos no se pueda
    //abrir o leer, no se libere memoria en el heap innecesariamente ( free(): free detected in 
    //tcache  Aborted (core dumped)") pero si se libere la que uso el archivo 
    //que SE PUDO ABRIR CON EXITO.
    
    guardar_archivos(lista_materiales, lista_edificios );

    delete lista_materiales;

    delete lista_edificios;
    
    return 0;

}



    