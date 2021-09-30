#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string PATH_MATERIALES ="materiales.txt";
const string PATH_EDIFICIOS = "edificios.txt";
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
PRE: recibe el string "texto" con el mensaje a mostrar por pantalla y los entero "ocpiones_maximas" 
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
        cout<<"No se encontro el archivo "<<PATH_EDIFICIOS<<endl;
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
        cout<<"No se encontro el archivo "<<PATH_MATERIALES<<endl;
    }
}


/*
PRE: Recibe el struct "lista_edificios" con todos los edificios

POST: Muestra por pantalla el listado de edificios con su informacion relacionada respectiva
*/
void listar_todos_edificios(Lista_edificios *lista_edificios){
    cout<<"NOMBRE EDIFICIO\t"<<"CANTIDAD CONSTRUIDOS\t"<<"MAX CANTIDAD PERMITIDA"<<endl;
    for(int i = 0; i < lista_edificios -> cantidad_de_edificios; i++){
        cout<<lista_edificios -> edificios[i] -> nombre_edificio <<" \t\t";
        cout<<lista_edificios -> edificios[i] -> cantidad_construidos << " \t\t";
        cout<<lista_edificios -> edificios[i] -> max_cantidad_permitidos<<endl;
    }
}

//PRE: Recibe el struct "lista_edificios" con los edificios disponibles a elegir
//POST: Devuelve el string "edificio_a_construir"
string obtener_nombre_edificio(Lista_edificios *lista_edificios){
    listar_todos_edificios(lista_edificios);
    string edificio_a_construir;
    cout<<"Indique el nombre del edifico que desea construir: ";
    cin >> edificio_a_construir;
    
    return edificio_a_construir;
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
        if (material_a_chequear == "piedra"){
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
void construir_edificio(Lista_edificios *lista_edificios, Lista_materiales *lista_materiales){
    //Construir edificios por nombreSe deberá 
    //verificar que exista el edificio, 
    //se cuente con la cantidad de materiales necesaria para poder construir y 
    //que no se haya superado el máximo de construcciones permitidas del mismo.
    // Si no cumple dichas condicionesse le avisara porque no es posible construir el edificio pedido, 
    //en caso contrario, se le deberá consultar al usuario si 
    //desea o no construir el edificio.
    bool construir = true;
    string edificio_a_construir = obtener_nombre_edificio(lista_edificios);
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

                }else{
                    cout <<"Se cancelo la construccion de " << edificio_a_construir<<endl;
                }

            }else{
                cout<<"se supero la maxima cantidad de edificios construidos de dicho tipo";
            }
        }else{
            cout <<"No alcanzan los materiales para construir el edificio solicitado";
        }
    }else{
        cout << "El edificio solicitado no se encuentra dispoible para construir";
    };

    cout<<endl;
    
};


int main(){

    Lista_materiales*lista_materiales = new Lista_materiales;
    cargar_materiales(lista_materiales);
    
    Lista_edificios*lista_edificios = new Lista_edificios;
    cargar_edificios(lista_edificios);

    if (lista_materiales->cantidad_de_materiales != -1 && lista_materiales->cantidad_de_materiales != 0 &&  
    lista_edificios -> cantidad_de_edificios !=-1 && lista_edificios -> cantidad_de_edificios !=0 ){
    
        //Si se pudieron abrir (!= -1) y no estan vacios (!=0), muestro el menu
        //listar_todos_edificios(lista_edificios);
    
        construir_edificio(lista_edificios, lista_materiales);

        cout<<"NOMBRE\t"<<"MATERIAL"<<endl;
        for(int i = 0; i < lista_materiales -> cantidad_de_materiales; i++){
            cout<<lista_materiales -> materiales[i] -> nombre_material<<"\t";
            cout<<lista_materiales -> materiales[i] -> cantidad_material <<endl;
            }

    }



    //El sig chequeo de si los archivos se encuentran vacios evitan el sig mensaje de error:
    //free(): double free detected in tcache 2
    //Aborted (core dumped)
    //que salta porque estoy liberando memoria de una supuesta matriz que que no he pedido 
    //ya sea por no poder abrir el archivo o porque estaba vacio. 
    //El problema surge al no saber cual es el archivo q causa problemas.

    if (lista_materiales -> cantidad_de_materiales == 0 || lista_materiales -> cantidad_de_materiales == -1){
        if (lista_materiales -> cantidad_de_materiales == 0){
        cout<<"EL ARCHIVO '"<<PATH_MATERIALES<<"' ESTA VACIO"<<endl;
        }
    }else{
        //libero el heap q use para la matriz
        //borro las filas de la matriz materiales que hay dentro de lista_materiales

        int cantidad_de_materiales = lista_materiales -> cantidad_de_materiales;

            for(int i = 0; i < cantidad_de_materiales; i++){    //xa cada fila
                delete lista_materiales -> materiales[i];   //se elimina el espacio de la fila
                //delete[] matriz[i]
                lista_materiales -> cantidad_de_materiales--;
            }
            //delete[] matriz;   //se elimina el vector de vectores
            delete[] lista_materiales -> materiales;
            lista_materiales -> materiales = nullptr;
    }

    if (lista_edificios -> cantidad_de_edificios == 0 || lista_edificios -> cantidad_de_edificios ==-1){
        if (lista_edificios -> cantidad_de_edificios == 0){
            cout<<"EL ARCHIVO '"<<PATH_EDIFICIOS<<"' ESTA VACIO"<<endl; 
        }
    }else{
        //Libero el heap q use para la matriz de edificios
        //borro las filas de la matriz materiales que hay dentro de lista_materiales

        int cantidad_de_edificios = lista_edificios -> cantidad_de_edificios;

        for(int i = 0; i < cantidad_de_edificios; i++){    //xa cada fila
            delete lista_edificios -> edificios[i];   //se elimina el espacio de la fila
            //delete[] matriz[i]
            lista_edificios -> cantidad_de_edificios--;
        }
        //delete[] matriz;   //se elimina el vector de vectores
        delete[] lista_edificios -> edificios;
        lista_edificios -> edificios = nullptr;
    }
    

    //borro la lista de materiales
    delete lista_edificios;
    //borro la lista de materiales
    delete lista_materiales;

    return 0;

}



    