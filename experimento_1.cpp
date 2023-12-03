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
    

    for (ull n = 5000000; n <= 50000000; n += 5000000) {
        vector<Point> puntos_aleatorios = generarPuntosAleatorios(n);
        float dist;
        cout << "Cantidad de Puntos: " << n << endl;
        for(int i = 1; i <= 100; i++) {
            cout << "Iteracion: " << i << endl;
            auto start_radix = chrono::high_resolution_clock::now();
            cout << "Algoritmo determinístico: " << endl;
            auto start_det = chrono::high_resolution_clock::now();
            // Ejecutar algoritmo
            dist = divideAndConquer(puntos_aleatorios);
            auto end_det = chrono::high_resolution_clock::now();
            chrono::duration<double> duration_det = end_det - start_det;
            double duration_d_det = duration_det.count();
            //Guardamos el tiempo
            fprintf(times_det, "n = %llu ,dist = %f ,duration_d = %f\n", n, dist, duration_d_det);

            cout << "Algoritmo aleatorizado: " << endl;
            auto start_random = chrono::high_resolution_clock::now();
            // Ejecutar algoritmo
            pair<float,float> dist_random = aleatorizado(puntos_aleatorios);
            auto end_random = chrono::high_resolution_clock::now();
            // Calculamos duracion de ejecuccion
            chrono::duration<double> duration_random = end_random - start_random;
            double duration_d_random = duration_random.count();
            //Guardamos el tiempo
            fprintf(times_random, "n = %llu ,dist = %f ,duration = %f ,selected_d = %f\n", 
                    n, dist_random.first, duration_d_random, dist_random.second);
        }
    }

    
    

    
    
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
    float aleatorio = aleatorizado(puntos_aleatorios); 
    unsigned t3 = clock();
    double time_aleatorio = (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Distancia minima aleatorizado:"<< aleatorio << endl;
    cout << "Tiempo aleatorizado: " << time_aleatorio << endl;
    return 0;
}