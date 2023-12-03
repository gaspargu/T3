// experimento_2.cpp
#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado5.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"
#include <chrono>  
using namespace std;

int main() {
    // Número de puntos
    ull n = 1000000;
    // Archivo para guardar los tiempos
    FILE* times_det = fopen("times_det.txt", "a");
    // Archivo para guardar los tiempos
    FILE* times_random = fopen("times_random.txt", "a");
    float dist;

    for(int i = 1; i <= 100; i++) {
        // Generar n puntos aleatorios
        vector<Point> puntos_aleatorios = generarPuntosAleatorios(n);

        cout << "Iteracion: " << i << endl;
        
        cout << "Algoritmo determinístico: " << endl;
        auto start_det = chrono::high_resolution_clock::now();
        // Ejecutar algoritmo
        dist = divideAndConquer(puntos_aleatorios);
        auto end_det = chrono::high_resolution_clock::now();
        // Calculamos duracion de ejecuccion
        chrono::duration<double> duration_det = end_det - start_det;
        double duration_d_det = duration_det.count();
        //Guardamos el tiempo
        fprintf(times_det, "dist = %f ,duration = %f\n", dist, duration_d_det);

        cout << "Algoritmo aleatorizado: " << endl;
        auto start_random = chrono::high_resolution_clock::now();
        // Ejecutar algoritmo
        pair<float,float> dist_random = aleatorizado(puntos_aleatorios);
        auto end_random = chrono::high_resolution_clock::now();
        // Calculamos duracion de ejecuccion
        chrono::duration<double> duration_random = end_random - start_random;
        double duration_d_random = duration_random.count();
        //Guardamos el tiempo
        fprintf(times_random, "dist = %f ,duration = %f , selected_d = %f\n", dist_random.first, duration_d_random, dist_random.second);
    }
    // Cerramos el archivo
    fclose(times_det);
    fclose(times_random);
    return 0;
}
