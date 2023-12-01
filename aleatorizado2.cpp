#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
#include <climits>
#include <ctime>
#include <unordered_map>
#include "structs.h"
#include "funcionesHash.cpp"


using namespace std;

// Retorna la distancia minima cuadrada de n pares de puntos
// Paso 1 del algoritmo aleatorizado para obtener el d para el tamaño de las grillas
float comparacion_pares(vector<Point> points) {
    float min_distance = numeric_limits<float>::max();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, points.size() - 1);
    
    for (int i = 0; i < points.size(); i++) {
        int index1 = dist(gen);
        int index2 = dist(gen);
        // Nos aseguramos que los indices sean distintos
        if (index1 == index2) {
            index2 = (index1 + 1) % (points.size()-1);
        }
        float new_distance = distance(points[index1], points[index2]);
        min_distance = min(min_distance, new_distance);
    }
    return min_distance;
}

vector<vector<Point>> createHashTable(vector<Point> points, float d, 
                                    int m, ull (*hashFunction)(ull,ull,ull,ull,ull), 
                                    ull a, ull b, ull p) { 
    vector<vector<Point>> hashTable(m);

    for (int i=0; i < points.size(); i++) {
        ull key = findKey(points[i], d);
        hashTable[hashFunction(key, a, b, p, m)].push_back(points[i]);
    }

    return hashTable;
}

float minDistance(Point point, ull posHash, vector<vector<Point>> hashTable, 
                     float start) {
    const vector<Point>& points = hashTable[posHash];
    
    for (const auto& otherPoint : points) {
        //cout << "j=" << i << endl;
        float new_distance = distance(point, otherPoint);
        if (new_distance > 0) {
            start = min(start, new_distance);
        }
    } 
    
    return start;
}



float aleatorizado(vector<Point> points, ull (*hashFunction)(ull,ull,ull,ull,ull)) {
    float d_square = comparacion_pares(points);
    float min_distance = d_square;
    float d = sqrt(d_square);
    ull grid_size = ceil(1/d);
    ull m = grid_size*grid_size;
    
    ull max_key = concatenateBits(grid_size-1,grid_size-1);
    ull p = nextPrime(max_key);
    // Creamos a y b para la familia de funciones hash
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, p - 1);
    uniform_int_distribution<int> dist2(0, p - 1);
    ull a = dist(gen);
    ull b = dist(gen);
    
    vector<vector<Point>> hashTable = createHashTable(points, d, m, hashFunction,a,b,p);
    // Paso 3 del algoritmo
    for (int i=0; i < points.size(); i++) {
        ull key = findKey(points[i], d);
        uint mask = 262143;
        uint row = static_cast<uint>(key & mask);
        uint column = static_cast<uint>(key >> 18);
        ull n1 = concatenateBits(column+1,row+1);
        ull n2 = concatenateBits(column+1,row);
        ull n3 = concatenateBits(column,row+1);
        ull n4 = concatenateBits(column-1,row-1);
        ull n5 = concatenateBits(column-1,row);
        ull n6 = concatenateBits(column,row-1);
        ull n7 = concatenateBits(column+1,row-1);
        ull n8 = concatenateBits(column-1,row+1);
        
        for (ull j : {key, n1, n2, n3, n4, n5, n6, n7, n8}) {
            ull posHash = hashFunction(j,a,b,p,m);
            unsigned t0 = clock();
            min_distance = minDistance(points[i], posHash, hashTable, min_distance);
            unsigned t1 = clock();
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            cout << "tiempo:" << time << endl;
        }
        
        
    }

    return min_distance;
}