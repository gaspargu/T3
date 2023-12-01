#include "structs.h"
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <iostream>
#include <random>
#include <utility>

using namespace std;

float distance(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return dx*dx + dy*dy;
}

vector<Point> generarPuntosAleatorios(int num_points) {
    // Configurar el generador de números aleatorios
    random_device rd;  // Obtener una semilla aleatoria del dispositivo
    mt19937 gen(rd()); // Generador Mersenne Twister

    // Distribuciones para las coordenadas x e y en el rango [0, 1)
    uniform_real_distribution<float> dist(0.0, 1.0);

    // Generar y almacenar puntos aleatorios en un vector
    vector<Point> puntos;
    for (int i = 0; i < num_points; ++i) {
        float x = dist(gen);
        float y = dist(gen);
        puntos.push_back({x, y});
    }
    // Retornar el vector de puntos
    return puntos;
}

ull concatenateBits(uint i, uint j) {
    uint32_t part1 = static_cast<uint32_t>(i);
    uint32_t part2 = static_cast<uint32_t>(j);
    ull res = (static_cast<ull>(part1) << 18) | part2;
    return res;
}

// Encuentra 
ull findKey(Point p, float d) {
    uint i = static_cast<uint>(p.x / d);
    uint j = static_cast<uint>(p.y / d);
    return concatenateBits(i,j);
}

void printPointArray(vector<Point> array) {
    cout << "[";
    for (ull i = 0; i < array.size(); i++) {
        cout << "(" << array[i].x << "," << array[i].y << ")" << " ";
    }
    cout << "]" << endl;
}
