#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
#include <climits>
#include <unordered_map>
#include "structs.h"

using namespace std;

// Retorna la distancia minima de n pares de puntos
// Paso 1 del algoritmo aleatorizado para obtener el d para el tamaño de las grillas
float comparacion_pares(vector<Point> points, int num_pairs) {
    float min_distance = numeric_limits<float>::max();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, points.size() - 1);
    
    for (int i = 0; i < num_pairs; i++) {
        int index1 = dist(gen);
        int index2 = dist(gen);
        // Nos aseguramos que los indices sean distintos
        while (index1 == index2) {
            index2 = dist(gen);
        }
        float new_distance = distance(points[index1], points[index2]);
        min_distance = min(min_distance, new_distance);
    }
    return min_distance;
}

// Generamos una grilla con cuadrados de lado d
// Paso 2 del algoritmo aleatorizado para obtener la grilla donde almacenaremos los puntos
new_HashTable create_grid(vector<Point> points, float d){
    // Calculamos el numero de filas y columnas de la grilla
    float grid_size = 1/d;
    // Calculamos el numero de filas y columnas de la grilla
    int num_rows = ceil(grid_size);
    int num_cols = ceil(grid_size);
    // Creamos la grilla
    vector<Square> squares;
    // Creamos los cuadrados de la grilla
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            // Calculamos el centro del cuadrado
            //Calculamos la llave del cuadrado
            uint32_t part1 = static_cast<uint32_t>(i);
            uint32_t part2 = static_cast<uint32_t>(j);
            ull key = (static_cast<ull>(part1) << 32) | part2;
            float x_center = (i + 0.5) * grid_size;
            float y_center = (j + 0.5) * grid_size;
            float x_max = x_center + d/2;
            Point center = {x_center, y_center};
            // Creamos el cuadrado
            Square square = {d, center, key};
            for (auto point = points.begin(); point != points.end();){
                if (PointInSquare(*point, square)){
                    square.points.push_back(*point);
                    //Borrar el punto de la lista de puntos
                    point = points.erase(point);
                }
                else if (point->x > x_max){
                    break;
                }
                else{
                    point++;
                }
            }
            //int z = hash(key);
            //APLICAR FUNCION DE HASH PARA LA LLAVE
            //Y BASADO EN ESO METER EL CUADRADO EN LA TABLA HASH
            //hash_table[z].push_back(square);
        }
    } 
    // Creamos la nueva tabla hash
    new_HashTable grid;
    return grid;
}

