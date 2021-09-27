#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string PATH_MATERIALES ="materiales.txt";

struct Material{
    string nombre;
    int cant;
};

struct Lista_materiales{
    // int ** matriz; //creo el doble puntero
    Material** materiales;
    int cantidad_de_materiales;   
};


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

    // if(!archivo_materiales.is_open()){
    //     cout << "No se encontro un archivo con nombre \"" << PATH_CONTACTOS << "\", se va a crear el archivo" << endl;
    //     archivo_contactos.open(PATH_CONTACTOS, ios::out);
    //     archivo_contactos.close();
    //     archivo_contactos.open(PATH_CONTACTOS, ios::in);
    //}

    string nombre;
    int cant;

    Material* material;

    while(archivo_materiales >> nombre){
        archivo_materiales >> cant;

        material = new Material;
        material -> nombre = nombre;
        material -> cant = cant;

        agregar_material(lista_materiales, material);
    }

    archivo_materiales.close();
}


int main(){

    Lista_materiales*lista_materiales = new Lista_materiales;

    cargar_materiales(lista_materiales);

    // Material* nuevo_vector_materiales = new Material[1];
    
    // int tope_viejo = 1; 

    // Material *material = new Material;
    // material -> nombre = "piedra";
    // material -> cant = 1;

    // nuevo_vector_materiales[0] = *material;

    // nuevo_vector_materiales = *nuevo_vector_materiales[tope_viejo+1])
    cout<<"NOMBRE\t"<<"MATERIAL"<<endl;
    for(int i = 0; i < lista_materiales -> cantidad_de_materiales; i++){
        cout<<lista_materiales -> materiales[i] -> nombre<<"\t";
        cout<<lista_materiales -> materiales[i] -> cant<<endl;
    }


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

    //borro la lista de materiales
    delete lista_materiales;

    return 0;


}
    