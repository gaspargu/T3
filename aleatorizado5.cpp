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

pair<float,float> aleatorizado(vector<Point> points) {
    float d_square = comparacion_pares(points);
    float min_distance = d_square;
    float d = sqrt(d_square);
    ull grid_size = ceil(1/d);
    ull m = 2*points.size();
    ull max_key = concatenateBits(grid_size-1,grid_size-1);
    //ull p = 214696813;
    ull p = nextPrime(max_key);
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dist(1, p - 1);
    uniform_int_distribution<int> dist2(0, p - 1);
    ull a = dist(gen);
    ull b = dist(gen);
    
    vector<vector<Point>> hashTable(m);

    for (int i=0; i < points.size(); i++) {
        ull key = findKey(points[i], d);
        hashTable[((a * key + b) % p) % m].push_back(points[i]);
    }

    
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
            ull posHash = ((a * j + b) % p) % m;
            
            vector<Point> puntos = hashTable[posHash];
            for(int k=0; k<puntos.size(); k++) {
                float new_distance = distance(puntos[k], points[i]);
                if (new_distance > 0) {
                    min_distance = min(min_distance, new_distance);
                }
            } 
        } 
        
    }

    return make_pair(min_distance, d_square);
}


pair<float,float> aleatorizado_mersenne(vector<Point> points) {
    float d_square = comparacion_pares(points);
    float min_distance = d_square;
    float d = sqrt(d_square);
    ull grid_size = ceil(1/d);

    ull m = 2*points.size();
    ull max_key = concatenateBits(grid_size-1,grid_size-1);
    //ull p = 214696813;

    ull p =  mersennePrime(max_key);
    //cout << "PRIMO ELEGIDO: " << p << endl;
    ull k_m = log2(p + 1);
    //cout << "l "<< l <<" m "<< m << " p "<< p << endl;
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<ull> dist(1, p - 1);
    uniform_int_distribution<ull> dist2(0, p - 1);
    //cout << "ELIGIENDO A: " << endl;
    ull a = dist(gen);
    //cout << "ELIGIENDO B: " << endl;
    ull b = dist2(gen);
    vector<vector<Point>> hashTable(m);
    ull n = floor(log2(p+1));
    ull mask = ((1 << k_m) - 1);
    ull x, modp, key;

    for (int i=0; i < points.size(); i++) {
        
        key = findKey(points[i], d);

        x = (a * key + b);
      
        modp = (x & mask) + x >> k_m;
    
        if (modp >= (1 << k_m)) {
            modp -= (1 << k_m) - 1;
        }
        
        hashTable[modp % m].push_back(points[i]);
       
    }
    // Paso 3 del algoritmo
    uint mask2, row, column;
    ull n1, n2, n3, n4, n5, n6, n7, n8, posHash;
    vector<Point> puntos;
    float new_distance;

    for (int i=0; i < points.size(); i++) {
        key = findKey(points[i], d);
        mask2 = 262143;
        row = static_cast<uint>(key & mask2);
        column = static_cast<uint>(key >> 18);
        n1 = concatenateBits(column+1,row+1);
        n2 = concatenateBits(column+1,row);
        n3 = concatenateBits(column,row+1);
        n4 = concatenateBits(column-1,row-1);
        n5 = concatenateBits(column-1,row);
        n6 = concatenateBits(column,row-1);
        n7 = concatenateBits(column+1,row-1);
        n8 = concatenateBits(column-1,row+1);
       
        for (ull j : {key, n1, n2, n3, n4, n5, n6, n7, n8}) {
            x = (a * j + b);
            modp = (x & mask) + x >> k_m;  
            if (modp >= (1 << k_m)) {
                modp -= (1 << k_m) - 1;
            }
             
            puntos = hashTable[modp % m];
           
            for(int k=0; k<puntos.size(); k++) {
                new_distance = distance(puntos[k], points[i]);
                if (new_distance > 0) {
                    min_distance = min(min_distance, new_distance);
                }
            } 
        } 
        
    }

    return make_pair(min_distance, d_square);
}

pair<float,float> aleatorizado_fast2(vector<Point> points) {
    float d_square = comparacion_pares(points);
    float min_distance = d_square;
    float d = sqrt(d_square);
    ull grid_size = ceil(1/d);

    ull m = nextPot2(2*points.size());
    ull l = log2(m);

    ull max_key = concatenateBits(grid_size-1,grid_size-1);
    //ull p = 214696813;
    ull p =  mersennePrime(max_key);
    //cout << "PRIMO ELEGIDO f: " << p << endl;
    ull k_m = log2(p + 1);
    //cout << "l "<< l <<" m "<< m << " p "<< p << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ull> dist(1, p - 1);
    uniform_int_distribution<ull> dist2(0, p - 1);
    //cout << "ELIGIENDO A f: " << endl;
    ull a = dist(gen);
    //cout << "ELIGIENDO B f: " << endl;
    ull b = dist2(gen);
    
    vector<vector<Point>> hashTable(m);
    ull n = floor(log2(p+1));
    ull mask = ((1 << k_m) - 1);
    ull mask_l = ((1 << l) - 1);
    ull x, modp, key;
   
    for (int i=0; i < points.size(); i++) {
       
        key = findKey(points[i], d);

        x = (a * key + b);
      
        modp = (x & mask) + x >> k_m;
    
        if (modp >= (1 << k_m)) {
            modp -= (1 << k_m) - 1;
        }
        modp = modp &  mask_l;
        //cout << "modp "<< modp << " mask_l "<< mask_l << endl;
        hashTable[modp].push_back(points[i]);
       
    }

  
    // Paso 3 del algoritmo
    uint mask2, row, column;
    ull n1, n2, n3, n4, n5, n6, n7, n8, posHash;
    vector<Point> puntos;
    float new_distance;

    for (int i=0; i < points.size(); i++) {
        key = findKey(points[i], d);
        mask2 = 262143;
        row = static_cast<uint>(key & mask2);
        column = static_cast<uint>(key >> 18);
        n1 = concatenateBits(column+1,row+1);
        n2 = concatenateBits(column+1,row);
        n3 = concatenateBits(column,row+1);
        n4 = concatenateBits(column-1,row-1);
        n5 = concatenateBits(column-1,row);
        n6 = concatenateBits(column,row-1);
        n7 = concatenateBits(column+1,row-1);
        n8 = concatenateBits(column-1,row+1);
       
        for (ull j : {key, n1, n2, n3, n4, n5, n6, n7, n8}) {
            x = (a * j + b);
            modp = (x & mask) + x >> k_m;  
            if (modp >= (1 << k_m)) {
                modp -= (1 << k_m) - 1;
            }
            posHash = modp & mask_l;
            
            puntos = hashTable[posHash];
            
            for(int k=0; k<puntos.size(); k++) {
                new_distance = distance(puntos[k], points[i]);
                if (new_distance > 0) {
                    min_distance = min(min_distance, new_distance);
                }
            } 
        } 
        
    }
    return make_pair(min_distance, d_square);
}
