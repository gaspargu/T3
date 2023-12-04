// testAleatorizado.cpp
#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado5.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"

using namespace std;

// g++ testAleatorizado.cpp structs.cpp -o test
// ./test

int main() {
    // Numero de puntos
    ull n = 500000;
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
    pair<float, float> aleatorio_m = aleatorizado_mersenne(puntos_aleatorios); 
    unsigned t3 = clock();
    double time_mersenne = (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Distancia minima aleatorizado mersenne:"<< aleatorio_m.first << endl;
    cout << "Tiempo aleatorizado mersenne: " << time_mersenne << endl;

    // Algoritmo aleatorizado
    unsigned t4 = clock();
    pair<float, float> aleatorio = aleatorizado(puntos_aleatorios); 
    unsigned t5 = clock();
    double time_aleatorio = (double(t5-t4)/CLOCKS_PER_SEC);
    cout << "Distancia minima aleatorizado:"<< aleatorio.first << endl;
    cout << "Tiempo aleatorizado: " << time_aleatorio << endl;

    // Algoritmo aleatorizado
    unsigned t6 = clock();
    pair<float, float> aleatorio_fast = aleatorizado_fast2(puntos_aleatorios); 
    unsigned t7 = clock();
    double time_aleatorio_fast = (double(t7-t6)/CLOCKS_PER_SEC);
    cout << "Distancia minima aleatorizado fast:"<< aleatorio_fast.first << endl;
    cout << "Tiempo aleatorizado: " << time_aleatorio_fast << endl;

    return 0;
}
