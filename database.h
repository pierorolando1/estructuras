#include <iostream>
#include <fstream>

using namespace std;

int numero_cuidadanos() {
  ifstream fr("cuidadanos.db");
  string line;
  int i = 0;
  while (getline(fr, line)) {
    i++;
  }
  fr.close();
  return i;
}

int numero_residuos() {
  ifstream fr("residuos.db");
  string line;
  int i = 0;
  while (getline(fr, line)) {
    i++;
  }
  fr.close();
  return i;
}

void cargar_cuidadanos(Cuidadano cuidadanos[]) {
  ifstream fr("cuidadanos.db");
  string line;
  int i = 0;
  while (getline(fr, line)) {
    int pos = line.find("|");
    int id = stoi(line.substr(0, pos));
    cuidadanos[i].id = id;
    line.erase(0, pos + 1);

    pos = line.find("|");
    cuidadanos[i].nombres = line.substr(0, pos);
    line.erase(0, pos + 1);

    cuidadanos[i].direccion = line;
    i++;
  }
  fr.close();
}

void cargar_residuos(Residuo residuos[]) {
  ifstream fr("residuos.db");
  string line;
  int i = 0;
  while (getline(fr, line)) {
    int pos = line.find("|");
    int uid = stoi(line.substr(0, pos));
    residuos[i].uid = uid;
    line.erase(0, pos + 1);

    pos = line.find("|");
    residuos[i].cantidad_kg = stof(line.substr(0, pos));
    line.erase(0, pos + 1);

    pos = line.find("|");
    residuos[i].tipo = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);

    residuos[i].descripcion = line;
    i++;
  }
  fr.close();
}

void anadir_cuidadano(Cuidadano c) {
  ofstream fw("cuidadanos.db", std::ofstream::out | std::ofstream::app);
  //check if file was successfully opened for writing
  if (fw.is_open()) {
    fw << c.id << "|";
    fw << c.nombres << "|";
    fw << c.direccion << "\n";
    
    fw.close();
  }
  else cout << "Problem with opening file";
}

void anadir_residuo(Residuo residuo) {

  // get current dir
  ofstream fw("residuos.db", std::ofstream::out | std::ofstream::app);
  //check if file was successfully opened for writing
  if (fw.is_open()) {
    fw << residuo.uid << "|";
    fw << residuo.cantidad_kg << "|";
    fw << residuo.tipo << "|";
    fw << residuo.descripcion << "\n";
    
    fw.close();
  }
  else cout << "Problem with opening file";
}