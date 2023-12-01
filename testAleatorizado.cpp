#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado3.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"

using namespace std;

int main() {
    // Generar 100 puntos aleatorios
    vector<Point> puntos_aleatorios = generarPuntosAleatorios(100000);
    cout << "Arreglo de puntos aleatorios:" << endl;
    //printPointArray(puntos_aleatorios);
    float min_dc = divideAndConquer(puntos_aleatorios); 
    cout << "Distancia minima determinista:"<< min_dc << endl;
    cout << "Distancia minima aleatorizado:"<< aleatorizado(puntos_aleatorios, hashUniversal) << endl;

    return 0;
}
