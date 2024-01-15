#include <iostream>
#include <fstream>

#include <queue>

using namespace std;

// cargar cola, leer cola.db de abajo hacia arriba
queue<string> cargar_cola() {
  queue<string> cola;
  ifstream fr("cola.db");
  string line;
  while (getline(fr, line)) {
    cola.push(line);
  }
  fr.close();
  return cola;
}

//añadir a la cola
void anadir_a_cola(queue<string>* cola, string descripcion) {
  cola->push(descripcion);

  ofstream fw("cola.db", std::ofstream::out | std::ofstream::app);
  //check if file was successfully opened for writing
  if (fw.is_open()) {
    fw << descripcion << "\n";
    fw.close();
  }
  else cout << "Problem with opening file";
}

string extraer_de_cola(queue<string>* cola) {
  ifstream fr("cola.db");
  ofstream fw("temp.db", std::ofstream::out | std::ofstream::app);
  string line;
  int i = 0;
  while (getline(fr, line)) {
    if (i != 0) {
      fw << line << "\n";
    }
    i++;
  }
  fr.close();
  fw.close();
  remove("cola.db");
  rename("temp.db", "cola.db");

  string descripcion = cola->front();
  cola->pop();
  return descripcion;
}


bool validar_cuidadano(int dni) {
  ifstream fr("cuidadanos.db");
  string line;
  while (getline(fr, line)) {
    int pos = line.find("|");
    int id = stoi(line.substr(0, pos));
    if (id == dni) {
      fr.close();
      return true;
    }
  }
  fr.close();
  return false;
}



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

void cargar_cuidadanos(Cuidadano cuidadanos[]) {
  ifstream fr("cuidadanos.db");
  string line;
  int i = 0;
  while (getline(fr, line)) {
    int pos = line.find("|");
    int id = stoi(line.substr(0, pos));
    cuidadanos[i].dni = id;
    line.erase(0, pos + 1);

    pos = line.find("|");
    cuidadanos[i].nombres = line.substr(0, pos);
    line.erase(0, pos + 1);

    cuidadanos[i].residuosGenerados = stof(line);
    i++;
  }
  fr.close();
}



void anadir_cuidadano(Cuidadano c) {
  ofstream fw("cuidadanos.db", std::ofstream::out | std::ofstream::app);
  //check if file was successfully opened for writing
  if (fw.is_open()) {
    fw << c.dni<< "|";
    fw << c.nombres << "|";
    fw << 0 << "\n";
    
    fw.close();
  }
  else cout << "Problem with opening file";
}


void crearHistorialResiduo(string descripcion, int tipo = 1 | 2 | 3 | 4) {
  ofstream fw("residuos.db", std::ofstream::out | std::ofstream::app);

  string id = createRandomHash(7);

  //check if id is unique
  ifstream fr("residuos.db");
  string line;
  while (getline(fr, line)) {
    int pos = line.find("|");
    string residuo_id = line.substr(0, pos);
    if (residuo_id == id) {
      id = createRandomHash(7);
    }
  }

  if (fw.is_open()) {
    fw << id << "|";
    fw << descripcion << "|";
    fw << tipo << "\n";

    fw.close();
  }


  else cout << "Problem with opening file";
}