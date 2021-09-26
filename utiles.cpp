#include <iostream>
#include "utiles.h"
#include <fstream>

using namespace std;

const int MOSTRAR_CONTACTOS = 1;
const int ELIMINAR_CONTACTO = 2;
const int AGREGAR_CONTACTO = 3;
const int BUSCAR_CONTACTO = 4;
const int ERROR = -1;

void mostrar_menu(){
    cout << endl << endl << endl;
    cout << "MENU" << endl
    << '\t' << "1_ Ver todos los contactos" << endl
    << '\t' << "2_ Eliminar un contacto" << endl
    << '\t' << "3_ Agregar un contacto" << endl
    << '\t' << "4_ Buscar un contacto " << endl
    << '\t' << "5_ Guardar contactos y salir" << endl;
}

int pedir_opcion(){
    int opcion_elegida = ERROR;
    cout << "Ingrese el número de su acción elegida : ";
    cin >> opcion_elegida;

    return opcion_elegida;
}

void validar_opcion_elegida(int &opcion_elegida){
    bool es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    //Si es valida no pasa nada pues no entra al while. Si es falsa, queda atrapada
    //en el ciclo hasta q ingrese un opcion valida. Obs: la var se modifica por parametro!
    while(!es_opcion_valida){
        cout << "La opción elegida no es una opcion válida, por favor ingrese otra opción: ";
        cin >> opcion_elegida;
        es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    }
}

void cargar_agenda(Agenda* agenda){
    agenda -> cantidad_de_contactos = 0;

    fstream archivo_contactos(PATH_CONTACTOS, ios::in);

    if(!archivo_contactos.is_open()){
        cout << "No se encontro un archivo con nombre \"" << PATH_CONTACTOS << "\", se va a crear el archivo" << endl;
        archivo_contactos.open(PATH_CONTACTOS, ios::out);
        archivo_contactos.close();
        archivo_contactos.open(PATH_CONTACTOS, ios::in);
    }

    string nombre, numero;

    Contacto* contacto;

    while(archivo_contactos >> nombre){
        archivo_contactos >> numero;

        contacto = new Contacto;
        contacto -> nombre = nombre;
        contacto -> numero = stoll(numero);

        agregar_contacto(agenda, contacto);
    }

    archivo_contactos.close();
}

void agregar_contacto(Agenda* agenda, Contacto* contacto){
    int tope_viejo = agenda -> cantidad_de_contactos;
    Contacto** nuevo_vector_contactos = new Contacto*[tope_viejo + 1];

    for(int i = 0; i < agenda -> cantidad_de_contactos; i++){
        nuevo_vector_contactos[i] = agenda -> contactos[i];
    }
    nuevo_vector_contactos[tope_viejo] = contacto;

    if(agenda -> cantidad_de_contactos != 0){
        delete[] agenda -> contactos;
    }

    agenda -> contactos = nuevo_vector_contactos;
    agenda -> cantidad_de_contactos++;
}

void cerrar_agenda(Agenda* agenda){
    ofstream archivo_contactos(PATH_CONTACTOS);

    int cantidad_de_contactos = agenda -> cantidad_de_contactos;

    for(int i = 0; i < cantidad_de_contactos; i++){
        archivo_contactos << agenda -> contactos[i] -> nombre << ' '
                          << agenda -> contactos[i] -> numero << '\n';
        delete agenda -> contactos[i];
        agenda -> cantidad_de_contactos--;
    }

    delete[] agenda -> contactos;
    agenda -> contactos = nullptr;

}

void procesar_opcion(Agenda* agenda, int opcion){
    long numero = 0;
    Contacto* contacto = nullptr;
    int posicion_del_contacto = ERROR;

    switch (opcion) {
        case MOSTRAR_CONTACTOS:
            mostrar_contactos(agenda);
            break;

        case ELIMINAR_CONTACTO:
            numero = pedir_numero();
            if(!existe_el_numero(numero, agenda)){
                cout << "No existe contacto cuyo número sea " << numero << endl;
            } else {
                posicion_del_contacto = obtener_posicion_del_contacto(numero, agenda);
                eliminar_contacto(agenda, posicion_del_contacto);
                cout << endl << "Contacto eliminado correctamente" << endl;
            }
            break;

        case AGREGAR_CONTACTO:
            contacto = pedir_contacto();
            if(existe_el_numero(contacto -> numero, agenda)){
                cout << "El número " << contacto -> numero << " ya se encuentra en uso" << endl;
                delete contacto;
            } else {
                agregar_contacto(agenda, contacto);
                cout << endl << "Contacto guardado correctamente" << endl;
            }
            break;

        case BUSCAR_CONTACTO:
            numero = pedir_numero();
            if(!existe_el_numero(numero, agenda)){
                cout << "No existe contacto cuyo número sea " << numero << endl;
            } else {
                posicion_del_contacto = obtener_posicion_del_contacto(numero, agenda);
                mostrar_contacto(agenda, posicion_del_contacto);
            }

    }
}

void mostrar_contacto(Agenda* agenda, int posicion){
    cout << "-----------------------" << endl
         << '\t' << "Nombre: " << agenda -> contactos[posicion] -> nombre << endl
         << '\t' << "Número: " << agenda -> contactos[posicion] -> numero << endl
         << "-----------------------" << endl;
}

void mostrar_contactos(Agenda* agenda){
    cout << "CONTACTOS" << endl;
    if(agenda -> cantidad_de_contactos == 0){
        cout << "-------------------" << endl
             << '\t' << "LA AGENDA ESTA VACIA" << endl
             << "-------------------" << endl;
    }

    for(int i = 0; i < agenda -> cantidad_de_contactos; i++){
        mostrar_contacto(agenda, i);
    }
}

bool es_numero_valido(string numero){
    bool son_caracteres_numericos = true;
    int i = 0;

    if(numero.length() != CANTIDAD_NUMEROS_EN_TELEFONO){
        return false;
    }
    while(son_caracteres_numericos && i < CANTIDAD_NUMEROS_EN_TELEFONO){
        son_caracteres_numericos = isdigit(numero[i]);
        i++;
    }

    return son_caracteres_numericos;

}

long pedir_numero(){
    string numero;

    cout << "Ingrese un número de telefono: ";
    cin >> numero;

    while(!es_numero_valido(numero)){
        cout << "El numero ingresado no tiene un formato valido, por favor ingrese otro número: ";
        cin >> numero;
    }

    return stoll(numero);
}

bool existe_el_numero(long numero, Agenda* agenda){
    bool existe_el_numero = false;
    int i = 0;

    while(!existe_el_numero && i < agenda -> cantidad_de_contactos){
        if(numero == agenda -> contactos[i] -> numero){
            existe_el_numero = true;
        }
        i++;
    }

    return existe_el_numero;
}

int obtener_posicion_del_contacto(long numero, Agenda* agenda) {
    int posicion = ERROR;
    int i = 0;
    bool contacto_encontrado = false;

    while(i < agenda -> cantidad_de_contactos && !contacto_encontrado){
        if(agenda -> contactos[i] -> numero == numero){
            contacto_encontrado = true;
            posicion = i;
        }
        i++;
    }
    return posicion;
}

Contacto* pedir_contacto(){
    Contacto* contacto = new Contacto;
    string nombre;

    cout << "Ingrese el nombre de su contacto: ";
    cin >> nombre;
    long numero = pedir_numero();

    //se usa " -> " xq lo modifico a traves de un puntero
    contacto -> nombre = nombre;
    contacto -> numero = numero;

    return contacto;
}

void eliminar_contacto(Agenda* agenda, int posicion){
    if(agenda -> cantidad_de_contactos > 1){
        mostrar_contactos(agenda);

        //mando el q quiero elimnar a la ult pos y lo intercambio con ese
        swap(agenda, agenda -> cantidad_de_contactos - 1, posicion);

        mostrar_contactos(agenda);

        Contacto** nuevo_vector_contactos = new Contacto*[agenda -> cantidad_de_contactos - 1];

        for(int i = 0; i < agenda -> cantidad_de_contactos - 1; i++){
            nuevo_vector_contactos[i] = agenda -> contactos[i];
        }
        //borro el contacto de la ult pos
        delete agenda -> contactos[agenda -> cantidad_de_contactos - 1];
        delete[] agenda -> contactos; 

        //observar q el de la ult pos se mueve a la pos del q elimine

        agenda -> contactos = nuevo_vector_contactos;
    }else{
        delete agenda -> contactos[agenda -> cantidad_de_contactos - 1];
        delete[] agenda -> contactos;
    }

    agenda -> cantidad_de_contactos--;
}

void swap(Agenda* agenda, int posicion1, int posicion2){
    Contacto* aux = agenda -> contactos[posicion1]; //cant_cont -1
    agenda -> contactos[posicion1] = agenda -> contactos[posicion2]; //el q quiero eliminar ->lo mando a ult pos
    agenda -> contactos[posicion2] = aux; //cant_cont -1
}
