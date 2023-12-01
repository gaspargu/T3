#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"

using namespace std;

int main() {
    // Generar 100 puntos aleatorios
    vector<Point> puntos_aleatorios = generarPuntosAleatorios(5000000);
    cout << "Arreglo de puntos aleatorios:" << endl;
    //printPointArray(puntos_aleatorios);
    //cout << "Distancia minima determinista:"<< sweepLine(puntos_aleatorios) << endl;
    float min_dc = divideAndConquer(puntos_aleatorios); 
    cout << "Distancia minima determinista d&c:"<< min_dc << endl;
    cout << "Distancia minima aleatorizado:"<< aleatorizado(puntos_aleatorios, hashUniversal) << endl;

    return 0;
}