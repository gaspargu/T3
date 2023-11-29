#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>

using namespace std;
typedef unsigned long long ull;
typedef unsigned int uint;

// Estructuras

struct Point {
    float x, y;
    // Necesario para que set pueda comparar puntos
    bool operator<(const Point& otro) const {
        return x < otro.x || (x == otro.x && y < otro.y);
    }

    // Operador de igualdad
    bool operator==(const Point& otro) const {
        return x == otro.x && y == otro.y;
    }

    // Operador de desigualdad
    bool operator!=(const Point& otro) const {
        return !(*this == otro);
    }
};


// Funciones
float distance(Point p1, Point p2);
ull concatenateBits(uint i, uint j);
ull findKey(Point p, float d);
void printPointArray(vector<Point> array);
vector<Point> generarPuntosAleatorios(int num_points);

#endif // STRUCTS_H