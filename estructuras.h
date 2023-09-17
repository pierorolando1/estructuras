#include <iostream>
using namespace std;

struct Cuidadano {
    int id;
    string nombres;
    string direccion;
};

struct Residuo {
    float cantidad_kg;
    string descripcion;
    int tipo; // 1 => plastico, 2 => orgánicos, 3 => papel, 4 => otros
    int uid; // identificación de la persona que generó el residuo
};
