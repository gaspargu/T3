#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
#include <climits>
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

map<ull,vector<Point>> createGrid(vector<Point> points, float d) {
    map<ull,vector<Point>> grid;
    for (int i=0; i < points.size(); i++) {
        ull key = findKey(points[i], d);
        grid[key].push_back(points[i]);

        cout << "key: "<<key << endl;
    }
    cout << grid.size() <<endl;
    return grid;
}

vector<vector<ull>> createHashTable(vector<Point> points, float d, 
                                    int m, ull (*hashFunction)(ull,ull,ull,ull,ull), 
                                    ull a, ull b, ull p) { 
    vector<vector<ull>> hashTable(m);

    for (int i=0; i < points.size(); i++) {
        ull key = findKey(points[i], d);
        hashTable[hashFunction(key, a, b, p, m)].push_back(key);
    }

    return hashTable;
}

bool buscar(ull key, vector<vector<ull>> hashTable, 
            ull (*hashFunction)(ull,ull,ull,ull,ull), int m,
            ull a, ull b, ull p) {
    vector<ull> hashPosition = hashTable[hashFunction(key, a, b, p, m)];
    int n = hashPosition.size();
    for (int i=0; i<n; i++) {
        if (hashPosition[i]==key) {
            return true;
        }
    }
    return false;
}

float minDistance(Point p, ull key, map<ull,vector<Point>> grid, float start) {
    vector<Point> points = grid[key];
    for (int i=0; i < points.size(); i++) {
        if (p != points[i]) {
            float new_distance = distance(p, points[i]);
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
    
    map<ull,vector<Point>> grid = createGrid(points, d);
    vector<vector<ull>> hashTable = createHashTable(points, d, m, hashFunction,a,b,p);
    // Paso 3 del algoritmo
    for (int i=0; i < points.size(); i++) {
        //cout << i << endl;
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
        ull neighbour[] = {key,n1,n2,n3,n4,n5,n6,n7,n8};
        //cout << "encuentra vecinos" << endl;
        for (int j=0; j<9; j++) {
            if (buscar(neighbour[j],hashTable,hashFunction,m,a,b,p)) {
                min_distance = minDistance(points[i], neighbour[j], grid, min_distance);
            }
        }
    }

    return min_distance;
}




