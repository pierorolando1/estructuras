#include <iostream>
#include "estructuras.h"
#include "database.h"
#include <string>
using namespace std;
void clear_screen() {
    //execute different commands depending on the operating system
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cuidadanoDashboard(int dni) {
    queue<string> cola = cargar_cola();

    clear_screen();

    if(!validar_cuidadano(dni)) {
        cout << "El DNI ingresado no existe" << endl;
    } else {
        cout << "Bienvenido cuidadano" << endl;
        cout << "---------------------" << endl;
        cout << "1. Agregar residuos a la cola" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese una opción: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            
            string descripcion;

            cout << "Describa su residuo: ";
            cin >> descripcion;

            anadir_a_cola(&cola, descripcion);

            cout << "Residuo agregado correctamente" << endl;
        }


    }
}

void adminDashboard() {

    queue<string> cola = cargar_cola();

    clear_screen();

    cout << "Bienvenido administrador" << endl;
    cout << "---------------------" << endl;
    cout << "Cantidad de residuos en cola: " << cola.size() << endl;
    cout << "1. Extraer residuo a clasificar de la cola" << endl;
    cout << "2. Salir" << endl;
    cout << "Ingrese una opción: ";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        string descripcion = extraer_de_cola(&cola);

        cout << "Residuo extraido: " << descripcion << endl;

        // escoger entre 1, 2, 3 y 4 dependiendo del tipo de residuo
        cout << "Ingrese el tipo de residuo (1(plastico), 2(orgánicos), 3(papel), 4(otros)): " << endl;
        int tipo;
        cin >> tipo;

        cout << "Ingrese la descripción del residuo (dejar en blanco si deseas que sea la misma): " << endl;
        string descripcion_residuo;
        getline(cin, descripcion_residuo);

        if (descripcion_residuo == "") {
            descripcion_residuo = descripcion;
        } 

        crearHistorialResiduo(descripcion_residuo, tipo);
    }
}


void signIn() {
    cout << "¿Es usted administrador o cuidadano? (A/C): ";
    char tipo;
    cin >> tipo;

    if (tipo == 'C' || tipo == 'c') {
        cout << "Ingrese su DNI: ";
        string dni;
        cin >> dni;
        cuidadanoDashboard(stoi(dni));
    } else if (tipo == 'A' || tipo == 'a') {
        cout << "Ingrese la contraseña maestra: ";
        string password;
        cin >> password;

        if (password == "hola123") {
            adminDashboard();
        } else {
            cout << "Contraseña incorrecta" << endl;
        }
    } else {
        cout << "Opción inválida" << endl;
    }
}


int main() {

    clear_screen();

    signIn();



}
