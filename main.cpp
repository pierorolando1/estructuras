#include <iostream>
#include "estructuras.h"
#include "database.h"
#include <string>
#include <fstream>

using namespace std;
void clear_screen() {
    //execute different commands depending on the operating system
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


/*
xSN6lfK
*/

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
            cin.ignore();
            getline(cin, descripcion);

            anadir_a_cola(&cola, descripcion);

            cout << "Residuo agregado correctamente" << endl;
        }

    }
}


void mostrar_residuos_clasificados() {
    ifstream fr("residuos.db");
    string line;
    while (getline(fr, line)) {
        int pos = line.find("|");
        string id = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find("|");
        string descripcion = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find("|");
        string tipo = line.substr(0, pos);
        line = line.substr(pos + 1);

        cout << "ID: " << id << endl;
        cout << "Descripción: " << descripcion << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "---------------------" << endl;
    }
    fr.close();
}

void mostrar_historial_residuo(string residuo_id) {
    ifstream fr("historial.db");
    string line;

    while (getline(fr, line)) {
        int pos = line.find("|");
        string id = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find("|");
        string residuo_id_ = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find("|");
        string descripcion = line.substr(0, pos);
        line = line.substr(pos + 1);

        if (residuo_id_ == residuo_id) {
            cout << descripcion << "=>";
        }
    }
}

void insertar_historial_residuo(string residuo_id, string descripcion) {
    ofstream fw("historial.db", std::ofstream::out | std::ofstream::app);
    if (fw.is_open()) {
        fw << createRandomHash(8) << "|";
        fw << residuo_id << "|";
        fw << descripcion << "\n";

        fw.close();
    }
}


void adminDashboard() {

    queue<string> cola = cargar_cola();

    clear_screen();

    cout << "Bienvenido administrador" << endl;
    cout << "---------------------" << endl;
    cout << "Cantidad de residuos en cola: " << cola.size() << endl;
    cout << "1. Extraer residuo a clasificar de la cola" << endl;
    cout << "2. Mostrar residuos clasificados" << endl;
    cout << "3. Mostrar historial un residuo" << endl;
    cout << "4. Añadir a historial un residuo" << endl;
    cout << "5. Salir" << endl;
    cout << "Ingrese una opción: ";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        string descripcion = extraer_de_cola(&cola);

        cout << "Residuo extraido: " << descripcion << endl;

        // escoger entre 1, 2, 3 y 4 dependiendo del tipo de residuo
        cout << "Ingrese el tipo de residuo (1(plastico), 2(orgánicos), 3(papel), 4(otros)): ";
        int tipo;
        cin >> tipo;

        cout << "Ingrese la descripción del residuo (dejar en blanco si deseas que sea la misma): ";
        string descripcion_residuo;
        cin.ignore();
        getline(cin, descripcion_residuo);

        if (descripcion_residuo == "") {
            descripcion_residuo = descripcion;
        } 

        crearHistorialResiduo(descripcion_residuo, tipo);
    } else if (opcion == 2) {
        mostrar_residuos_clasificados();
    } else if (opcion == 3) {
        cout << "Ingrese el id del residuo: ";
        string residuo_id;
        cin >> residuo_id;

        mostrar_historial_residuo(residuo_id);
    } else if (opcion == 4) {
        cout << "Ingrese el id del residuo: ";
        string residuo_id;
        cin >> residuo_id;

        cout << "Ingrese la descripción del cambio: ";
        string descripcion;
        cin.ignore();
        getline(cin, descripcion);

        insertar_historial_residuo(residuo_id, descripcion);
    } else if (opcion == 5) {
        cout << "Saliendo..." << endl;
    } else {
        cout << "Opción inválida" << endl;
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
