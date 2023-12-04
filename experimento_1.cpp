// experimento_1.cpp
#include <iostream>
#include <vector>
#include "structs.h"
#include "aleatorizado5.cpp"
#include "sweepLine.cpp"
#include "divideAndConquer.cpp"
#include <chrono>  
using namespace std;

int main() {

    // Archivo para guardar los tiempos
    FILE* times_det = fopen("times_det_exp1.txt", "a");
    // Archivo para guardar los tiempos
    FILE* times_random = fopen("times_random_exp1.txt", "a");
    
    FILE* times_mersenne = fopen("times_mersenne_exp1.txt", "a");

    FILE* times_fast = fopen("times_fast_exp1.txt", "a");

    for (ull n = 500000; n <= 5000000; n += 500000) {
        vector<Point> puntos_aleatorios = generarPuntosAleatorios(n);
        float dist;
        cout << "Cantidad de Puntos: " << n << endl;
        for(int i = 1; i <= 100; i++) {
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
            fprintf(times_det, "n = %llu, dist = %e ,duration = %e\n", n, dist, duration_d_det);

            cout << "Algoritmo aleatorizado: " << endl;
            auto start_random = chrono::high_resolution_clock::now();
            // Ejecutar algoritmo
            pair<float,float> dist_random = aleatorizado(puntos_aleatorios);
            auto end_random = chrono::high_resolution_clock::now();
            // Calculamos duracion de ejecuccion
            chrono::duration<double> duration_random = end_random - start_random;
            double duration_d_random = duration_random.count();
            //Guardamos el tiempo
            fprintf(times_random, "n = %llu ,dist = %e ,duration = %e ,selected_d = %e\n", 
                    n, dist_random.first, duration_d_random, dist_random.second);

            cout << "Algoritmo aleatorizado Mersenne: " << endl;
            auto start_random_m = chrono::high_resolution_clock::now();
            // Ejecutar algoritmo
            pair<float,float> dist_random_mersenne = aleatorizado_mersenne(puntos_aleatorios);
            auto end_random_m = chrono::high_resolution_clock::now();
            // Calculamos duracion de ejecuccion
            chrono::duration<double> duration_random_m = end_random_m - start_random_m;
            double duration_d_random_m = duration_random.count();
            //Guardamos el tiempo
            fprintf(times_mersenne, "n = %llu ,dist = %e ,duration = %e ,selected_d = %e\n", 
                    n, dist_random_mersenne.first, duration_d_random_m, dist_random_mersenne.second);

            cout << "Algoritmo aleatorizado Fast: " << endl;
            auto start_random_f = chrono::high_resolution_clock::now();
            // Ejecutar algoritmo
            pair<float,float> dist_random_f = aleatorizado_fast2(puntos_aleatorios);
            auto end_random_f = chrono::high_resolution_clock::now();
            // Calculamos duracion de ejecuccion
            chrono::duration<double> duration_random_f = end_random_f - start_random_f;
            double duration_d_random_f = duration_random_f.count();
            //Guardamos el tiempo
            fprintf(times_fast, "n = %llu ,dist = %e ,duration = %e ,selected_d = %e\n", 
                    n, dist_random_f.first, duration_d_random_f, dist_random_f.second);
        }
    }
    // Cerramos el archivo
    fclose(times_det);
    fclose(times_random);
    fclose(times_mersenne);
    fclose(times_fast);
    return 0;
}