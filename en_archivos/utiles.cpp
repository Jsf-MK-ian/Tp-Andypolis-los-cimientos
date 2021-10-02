#include <iostream>
#include "utiles.h"
#include <fstream>
#include <iomanip>

using namespace std;

const int LISTAR_MATERIALES = 1;
const int CONSTRUIR_EDIFICIO = 2;
const int LISTAR_EDIFICIOS_CONSTRUIDOS = 3;
const int LISTAR_TODOS_LOS_EDIFICIOS = 4;
const int DEMOLER_EDIFICIO = 5;


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
    cout << endl;
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


void listar_materiales_de_construccion(Lista_materiales *lista_materiales){
    cout << setfill(' ') << setw(64)<<"MATERIALES DE CONSTRUCCION"<<"\n\n"
    << setfill(' ') <<setw(45) <<"MATERIAL"<< setfill(' ')<<setw(21)<<"CANTIDAD DISPONIBLE"<<endl
    << setfill(' ') <<setw(72)<<"__________________________________________" <<endl<<endl;
    
    for(int i = 0; i < lista_materiales -> cantidad_de_materiales; i++){
        cout<<setfill(' ')<<setw(45)<<lista_materiales -> materiales[i] -> nombre_material
        <<setfill(' ')<<setw(12)<<lista_materiales -> materiales[i] -> cantidad_material <<endl;
        }

    cout<<endl;    
}


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


void listar_edificios_construidos(Lista_edificios *lista_edificios){
    cout<< setfill(' ') << setw(66)<<"EDIFICIOS CONSTRUIDOS \n\n"
    <<setfill(' ')<<setw(45)<<"NOMBRE"<<setfill(' ')<<setw(24)<<"CANTIDAD CONSTRUIDOS"<<endl
    <<setfill(' ')<<setw(77)<<"_________________________________________________"<<endl<<endl;
    
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


void obtener_nombre_edificio(string &nombre_edificio){
    
    cin >> nombre_edificio;
    cout<<endl;
}


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


int obtener_posicion_edificio(string nombre_edificio, Lista_edificios* lista_edificios){
    bool encontrado = false;
    int posicion = ERROR;
    int i = 0;
    while (!encontrado && i< lista_edificios -> cantidad_de_edificios){
        if (lista_edificios -> edificios[i] -> nombre_edificio == nombre_edificio){
            encontrado = true;
            posicion = i;
        }
        i++;
    }
    return posicion;
}


void chequear_material(int cantidad_disponible, int cantidad_material_nec, bool &alcanza){
    if (cantidad_disponible < cantidad_material_nec){
                alcanza = false;
    }
}


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


bool supera_max_cant_permitida(Lista_edificios *lista_edificios, int posicion_edificio){
    bool supera = false;
    
    int construidos = lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos;
    int max_permitidos = lista_edificios -> edificios[posicion_edificio] -> max_cantidad_permitidos;

    if (construidos + 1 > max_permitidos){
        supera = true;
    }

    return supera;    
}


void registrar_edificio(Lista_edificios *lista_edificios, int posicion_edificio){
    
    lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos +=1;

}


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


void construir_edificio(string edificio_a_construir,Lista_edificios *lista_edificios, Lista_materiales *lista_materiales){
    
    if (existe_edificio(lista_edificios, edificio_a_construir)){
            
            int posicion_edificio = obtener_posicion_edificio(edificio_a_construir, lista_edificios);

            int cantidad_piedra_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_piedra;
            int cantidad_madera_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_madera;
            int cantidad_metal_nec = lista_edificios -> edificios[posicion_edificio] -> cantidad_metal;
        if ( alcanzan_materiales(lista_materiales,cantidad_piedra_nec, cantidad_madera_nec, 
                                 cantidad_metal_nec)){
            
            if( !supera_max_cant_permitida(lista_edificios, posicion_edificio) ){
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
        cout << "El edificio " << edificio_a_construir<< " no se encuentra en los planes de Andypolis";
    };

    cout<<endl;
    
};


void quitar_edificio(Lista_edificios *lista_edificios, int posicion_edificio){
    
    lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos --;
}


void sumar_material(int *cantidad_disponible, int cantidad_material_nec){
    *cantidad_disponible =  *cantidad_disponible + cantidad_material_nec/2; 
                        //truncado (redondeo hacia abajo)                                            
}


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


bool construido_alguna_vez(Lista_edificios *lista_edificios, int posicion_edificio){
    bool construido = false;

    int construidos = lista_edificios -> edificios[posicion_edificio] -> cantidad_construidos;

    if (construidos > 0){
        construido = true;
    }

    return construido;    
}


void demoler_edificio(string edificio_a_demoler, Lista_edificios *lista_edificios, Lista_materiales *lista_materiales){
 
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
                cout<<"No hay ningun/a "<< edificio_a_demoler << " construido todavia";
            }
    }else{
        cout << "El edificio " << edificio_a_demoler<< " no se encuentra en los planes de Andypolis";
    };

    cout<<endl;
}


void escribir_edificio(ofstream *archivo_edificios,Lista_edificios * lista_edificios, int i){
    
    *archivo_edificios << lista_edificios -> edificios[i] -> nombre_edificio <<' '
    << lista_edificios -> edificios[i] -> cantidad_piedra << ' '
    << lista_edificios -> edificios[i] -> cantidad_madera << ' '
    << lista_edificios -> edificios[i] -> cantidad_metal << ' '
    << lista_edificios -> edificios[i] -> cantidad_construidos << ' '
    << lista_edificios -> edificios[i] -> max_cantidad_permitidos << endl;
}


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
        case LISTAR_MATERIALES:
            listar_materiales_de_construccion(lista_materiales);
            break;

        case CONSTRUIR_EDIFICIO:{
            cout<<"Indique el nombre del edificio que desea construir: ";
            
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