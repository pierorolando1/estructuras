#include <iostream>
#include <fstream>

#include <queue>


using namespace std;

string createRandomHash(int length) {
    string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string newstr;
    int pos;
    while (newstr.size() != length) {
        pos = ((rand() % (str.size() - 1)));
        newstr += str.substr(pos, 1);
    }
    return newstr;
}

struct Cuidadano {
    int dni;
    string nombres;
    float residuosGenerados = 0;
};

// Cambio en el historial del registro de residuos
struct ResiduoCambio {
    string id;
    string residuo_id;
    string descripcion;
    ResiduoCambio* prev;
    ResiduoCambio* next;
};

struct Residuo {
    string id;
    string descripcion;
    int tipo; // 1 => plastico, 2 => orgánicos, 3 => papel, 4 => otros
    ResiduoCambio* cambioMasAntiguo;
    ResiduoCambio* cambioMasReciente;

    void mostrarHistorial() {
        ResiduoCambio* temp = cambioMasAntiguo;
        while (temp != NULL) {
            cout << temp->descripcion << "->";
            temp = temp->next;
        }
    }

    void insertarAlFinal(ResiduoCambio* nuevo) {
        if (cambioMasAntiguo == NULL) {
            cambioMasAntiguo = nuevo;
            cambioMasReciente = nuevo;
        } else {
            cambioMasReciente->next = nuevo;
            nuevo->prev = cambioMasReciente;
            cambioMasReciente = nuevo;
        }
    }

    void insertarCambio(string descripcion) {
        ResiduoCambio* nuevo = new ResiduoCambio;
        nuevo->id = createRandomHash(7);
        nuevo->residuo_id = id;
        nuevo->descripcion = descripcion;
        nuevo->prev = NULL;
        nuevo->next = NULL;

        if (cambioMasAntiguo == NULL) {
            cambioMasAntiguo = nuevo;
            cambioMasReciente = nuevo;
        } else {
            cambioMasReciente->next = nuevo;
            nuevo->prev = cambioMasReciente;
            cambioMasReciente = nuevo;
        }

        ofstream fw("historial.db", std::ofstream::out | std::ofstream::app);
        if (fw.is_open()) {
            fw << nuevo->id << "|";
            fw << nuevo->residuo_id << "|";
            fw << descripcion << "\n";

            fw.close();
        }
    }

    void insertarAntesDe(string descripcion, string residuo_id) {
        ResiduoCambio* nuevo = new ResiduoCambio;
        nuevo->id = createRandomHash(7);
        nuevo->residuo_id = residuo_id;
        nuevo->descripcion = descripcion;
        nuevo->prev = NULL;
        nuevo->next = NULL;

        ResiduoCambio* temp = cambioMasAntiguo;
        while (temp != NULL) {
            if (temp->residuo_id == residuo_id) {
                if (temp->prev == NULL) {
                    nuevo->next = temp;
                    temp->prev = nuevo;
                    cambioMasAntiguo = nuevo;
                } else {
                    nuevo->next = temp;
                    nuevo->prev = temp->prev;
                    temp->prev->next = nuevo;
                    temp->prev = nuevo;
                }
                break;
            }
            temp = temp->next;
        }
    }

};

// get length of residuos
int getLengthResiduos() {
    ifstream fr("residuos.db");
    string line;
    int i = 0;
    while (getline(fr, line)) {
        i++;
    }
    fr.close();
    return i;
}

vector<Residuo> obtenerResiduos() {
    ifstream fr("residuos.db");
    string line;
    int i = 0;
    vector<Residuo> residuos;
    while (getline(fr, line)) {
        int pos = line.find("|");
        string id = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        string descripcion = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        string tipo = line.substr(0, pos);
        line.erase(0, pos + 1);

        Residuo nuevo;
        nuevo.id = id;
        nuevo.descripcion = descripcion;
        nuevo.tipo = stoi(tipo);
        nuevo.cambioMasAntiguo = NULL;
        nuevo.cambioMasReciente = NULL;
        residuos.push_back(nuevo);

        // obtener historial de cambios
        ifstream fr2("historial.db");
        string line2;
        while (getline(fr2, line2)) {
            int pos2 = line2.find("|");
            string id = line2.substr(0, pos2);
            line2.erase(0, pos2 + 1);

            pos2 = line2.find("|");
            string residuo_id = line2.substr(0, pos2);
            line2.erase(0, pos2 + 1);

            pos2 = line2.find("|");
            string descripcion = line2.substr(0, pos2);
            line2.erase(0, pos2 + 1);

            if (residuo_id == nuevo.id) {
                ResiduoCambio* nuevoCambio = new ResiduoCambio;
                nuevoCambio->id = id;
                nuevoCambio->residuo_id = residuo_id;
                nuevoCambio->descripcion = descripcion;
                nuevoCambio->prev = NULL;
                nuevoCambio->next = NULL;
                nuevo.insertarAlFinal(nuevoCambio);
            } 
        }

        i++;
    }
    fr.close();

    return residuos;
}
