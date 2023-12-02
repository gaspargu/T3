#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado3.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"

using namespace std;

int main() {
    // Numero de puntos
    ull n = 10000;
    // Generar 100 puntos aleatorios
    vector<Point> puntos_aleatorios = generarPuntosAleatorios(n);
    cout << "Arreglo de " << n << " puntos aleatorios:" << endl;
    //printPointArray(puntos_aleatorios);

    // Algoritmo determinista
    unsigned t0 = clock();
    float determinista = divideAndConquer(puntos_aleatorios); 
    unsigned t1 = clock();
    double time_determinista = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Distancia minima determinista:"<< determinista << endl;
    cout << "Tiempo determinista: "<< time_determinista << endl;

    // Algoritmo aleatorizado
    unsigned t2 = clock();
    float aleatorio = aleatorizado(puntos_aleatorios, hashUniversal); 
    unsigned t3 = clock();
    double time_aleatorio = (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Distancia minima aleatorizado:"<< aleatorio << endl;
    cout << "Tiempo aleatorizado: " << time_aleatorio << endl;
    return 0;
}
