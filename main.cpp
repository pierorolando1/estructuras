#include <iostream>
#include "estructuras.h"
#include "database.h"

using namespace std;

int main() {
    Cuidadano cuidadanos[100];
    Residuo residuos[1000];

    cout << "Que desea?     1 (añadir información)\t2 (obtener información) ";
    int opcion;
    cin >> opcion;

    cargar_cuidadanos(cuidadanos);

    if (opcion == 1) {
        cout << "Ingrese el id del cuidadano: ";
        int id;
        cin >> id;

        // Si el cuidadano no está registrado, se registra
        if (cuidadanos[id].id != id || cuidadanos[id].nombres == "") {
            cout << "El cuidadano no está registrado, se procederá a registrar" << endl;
            cout << "Ingrese los nombres del cuidadano: ";
            string nombres;
            cin >> nombres;

            cout << "Ingrese la dirección del cuidadano: ";
            string direccion;
            cin >> direccion;

            cuidadanos[id] = Cuidadano{id, nombres, direccion};
            anadir_cuidadano(cuidadanos[id]);
        } else {
            cout << "Registrando datos del cuidadano " << cuidadanos[id].nombres << endl;
        }

        cout << "Ingrese la cantidad de residuos: ";
        int cantidad_residuos;
        cin >> cantidad_residuos;

        for (int i = 0; i < cantidad_residuos; i++) {
            Residuo nuevo_residuo;
            cout << "Ingrese la cantidad de kg del residuo " << i << ": ";
            cin >> nuevo_residuo.cantidad_kg;
            cout << "Ingrese el tipo de residuo " << i << ": ";
            cin >> nuevo_residuo.tipo;
            cout << "Ingrese una descripción del residuo " << i << ": ";
            cin >> nuevo_residuo.descripcion;
            nuevo_residuo.uid = id;
            anadir_residuo(nuevo_residuo);
        }
    } else if (opcion == 2) {
        cout << "Ingrese el id del cuidadano: ";
        // cout << "El cuidadano " << cuidadanos[id].nombres << " con id " << id << " generó los siguientes residuos: " << endl;
        // for (int i = 0; i < 1000; i++) {
        //     if (residuos[i].uid == id) {
        //         cout << "Residuo " << i << ": " << residuos[i].cantidad_kg << " kg de tipo " << residuos[i].tipo << endl;
        //     }
        // }
    }
}
