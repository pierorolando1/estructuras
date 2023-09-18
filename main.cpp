#include <iostream>
#include "estructuras.h"
#include "database.h"

using namespace std;

void clear_screen() {
    //execute different commands depending on the operating system
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int cuidadanos_count = numero_cuidadanos();
    int residuos_count = numero_residuos();

    Cuidadano cuidadanos[cuidadanos_count + 10];
    Residuo residuos[residuos_count + 10];

    cout << "Que desea?\t1 (añadir información)\t2 (obtener información) ";
    int opcion;
    cin >> opcion;

    cargar_cuidadanos(cuidadanos);

    if (opcion == 1) {
        cout << "Ingrese el id del cuidadano: ";
        int id;
        cin >> id;

        bool cuidadano_registrado = false;

        // Si el cuidadano no está registrado, se registra
        for (int j = 0; j < cuidadanos_count; j++) {
            if (cuidadanos[j].id == id) {
                cuidadano_registrado = true;
                cout << "Registrando datos del cuidadano " << cuidadanos[j].nombres << endl;
                break;
            }
        }

        if (!cuidadano_registrado) {
            cout << "El cuidadano no está registrado, se procederá a registrar" << endl;
            cout << "Ingrese los nombres del cuidadano: ";
            string nombres;
            // read the entire line, including spaces, and store it in nombres
            getline(cin >> ws, nombres, '\n');

            cout << "Ingrese la dirección del cuidadano: ";
            string direccion;
            getline(cin >> ws, direccion, '\n');

            //cuidadanos[id] = Cuidadano{id, nombres, direccion};
            anadir_cuidadano(Cuidadano{id, nombres, direccion});
        } else {
        }

        cout << "Ingrese la cantidad de residuos: ";
        int cantidad_residuos;
        cin >> cantidad_residuos;

        for (int i = 0; i < cantidad_residuos; i++) {
            Residuo nuevo_residuo;
            cout << "Ingrese la cantidad de kg del residuo " << i+1 << ": ";
            cin >> nuevo_residuo.cantidad_kg;
            cout << "Ingrese el tipo de residuo (1)Plastico (2)Organico (3)Papel (4)Otro: ";
            cin >> nuevo_residuo.tipo;
            cout << "Ingrese una descripción del residuo " << i+1 << ": ";
            cin >> nuevo_residuo.descripcion;
            nuevo_residuo.uid = id;
            anadir_residuo(nuevo_residuo);
        }
    } else if (opcion == 2) {
        cargar_residuos(residuos);

        clear_screen();
        cout << endl;        
        cout << "\tQue desea?" << endl;
        cout << "\t1 (obtener información de un cuidadano)" << endl;
        cout << "\t2 (obtener información de los residuos)" << endl;
        cout << "\t3 (obtener que cuidadano generó más residuos)" << endl;
        cout << "\t4 (Salir)" << endl;

        cout << "Ingrese la opción: ";
        int o;
        cin >> o;

        switch (o) {
            case 1: {
                cout << "Ingrese el id del cuidadano: ";
                int id;
                cin >> id;
                bool cuidadano_registrado = false;

                for(int i = 0; i < cuidadanos_count; i++) {
                    if (cuidadanos[i].id == id) {
                        cout << "Información del cuidadano " << cuidadanos[i].nombres << endl;
                        cout << "Dirección: " << cuidadanos[i].direccion << endl;
                        float suma_kg = 0;
                        for (int j = 0; j < residuos_count; j++) {
                            if (residuos[j].uid == id) {
                                suma_kg += residuos[j].cantidad_kg;
                            }
                        }
                        cout << "\tCantidad de residuos generados: " << suma_kg << " kg" << endl;
                        cuidadano_registrado = true;
                        break;
                    }
                }

                if (!cuidadano_registrado) {
                    cout << "El cuidadano no está registrado" << endl;
                }

                break;
            }
            case 2: {
                cout << "Información de los residuos" << endl;
                // total de residuos generados, porcentaje de cada tipo
                int total_residuos = 0;
                int residuos_plastico = 0;
                int residuos_organicos = 0;
                int residuos_papel = 0;
                int residuos_otros = 0;
                for (int i = 0; i < residuos_count; i++) {
                    if (residuos[i].uid != 0) {
                        total_residuos += residuos[i].cantidad_kg;
                        switch (residuos[i].tipo) {
                            case 1: {
                                residuos_plastico += residuos[i].cantidad_kg;
                                break;
                            }
                            case 2: {
                                residuos_organicos += residuos[i].cantidad_kg;
                                break;
                            }
                            case 3: {
                                residuos_papel += residuos[i].cantidad_kg;
                                break;
                            }
                            case 4: {
                                residuos_otros += residuos[i].cantidad_kg;
                                break;
                            }
                        }
                    }
                }
                cout << "\tTotal de residuos generados: " << total_residuos << " kg" << endl;
                cout << "\tPorcentaje de residuos plásticos: " << (residuos_plastico*100)/total_residuos << "%" << endl;
                cout << "\tPorcentaje de residuos orgánicos: " << (residuos_organicos*100)/total_residuos << "%" << endl;
                cout << "\tPorcentaje de residuos papel: " << (residuos_papel*100)/total_residuos << "%" << endl;
                cout << "\tPorcentaje de residuos otros: " << (residuos_otros*100)/total_residuos << "%" << endl;
                break;
            }
            case 3: {
                int cuidadano_mas_residuos = 0;
                int cantidad_residuos_kg = 0;
                for (int i = 0; i < cuidadanos_count; i++) {
                    int cantidad_residuos_cuidadano = 0;
                    for (int j = 0; j < residuos_count; j++) {
                        if (residuos[j].uid == cuidadanos[i].id) {
                            cantidad_residuos_cuidadano += residuos[j].cantidad_kg;
                        }
                    }
                    if (cantidad_residuos_cuidadano > cantidad_residuos_kg) {
                        cantidad_residuos_kg = cantidad_residuos_cuidadano;
                        cuidadano_mas_residuos = i;
                    }
                }
                cout << "El cuidadano que generó más residuos es " << cuidadanos[cuidadano_mas_residuos].nombres << " con " << cantidad_residuos_kg << " kg" << endl;
                break;
            }
        }
    }
}
