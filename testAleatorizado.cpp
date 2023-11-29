#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"

using namespace std;

int main() {
    // Generar 100 puntos aleatorios
    vector<Point> puntos_aleatorios = generarPuntosAleatorios(6);
    cout << "Arreglo de puntos aleatorios:" << endl;
    printPointArray(puntos_aleatorios);
    cout << "Distancia minima determinista:"<< sweepLine(puntos_aleatorios) << endl;
    cout << "Distancia minima determinista d&c:"<< divideAndConquer(puntos_aleatorios) << endl;
    cout << "Distancia minima aleatorizado:"<< aleatorizado(puntos_aleatorios, hashSimple) << endl;
    vector<Point> puntos = {
        {0.3,0.1},
        {0.4,0.2},
        {0.5,0.4}, 
        {0.2,0.5},
        {0.2,0.9},
        {0.7,0.7},
        {0.9,0.2},
        {0.9,0.4}
    };

    vector<Point> puntos2 = {
        {0.684993,0.12022},
        {0.672714,0.574516},
        {0.837729,0.0366184}, 
        {0.773612,0.219248}
    };

    cout << "Arreglo de puntos elegidos:" << endl;
    printPointArray(puntos2);
    cout << "Distancia minima determinista:"<< sweepLine(puntos2) << endl;
    float min = aleatorizado(puntos2, hashSimple);
    cout << "Distancia minima aleatorizado:"<< min << endl;
    divideAndConquer(puntos2);

    return 0;
}