// divideAndConquer.cpp
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <iostream>
#include <cfloat>
#include "structs.h"
using namespace std; 

// Obtiene el mínimo entre dos valores tipo float.
float min(float x, float y) { 
    return (x < y)? x : y; 
} 

// Obtiene el cuadrado de la distancia entre dos coordenadas.
float xdist(float x1, float x2) {
    return (x1 - x2)*(x1 - x2);
}

// Determina si un número entero es par.
bool esPar(int numero) {
    return (numero & 1) == 0;
}

/**
 * Función que utiliza "dividir para reinar" 
 * para encontrar la distancia mínima entre dos puntos de un conjunto de puntos.
*/
float recursion(vector<Point> sorted) {
    int n = sorted.size(); 
    // Caso base: Tamanho de conjuntos de puntos es 2
    if (n == 2) {
        // Se retorna distancia entre estos 2 puntos
        return distance(sorted[0],sorted[1]);
    }
    // Caso base: Tamanho de conjuntos de puntos es 1 o 0
    if (n<2) {
        // Se retorna infinito
        return FLT_MAX;
    }

    // Caso recursivo: se dividirá el conjunto en dos partes iguales con recta divisoria
    float recta_divisora;
    vector<Point> leftHalf;
    vector<Point> rightHalf;

    // Si el tamanho del conjunto es par
    if (esPar(n)) {
        // recta divisoria = promedio de coordenadas x de los dos puntos centrales 
        recta_divisora = (sorted[n/2-1].x + sorted[n/2].x) / 2;
        leftHalf = vector<Point>(sorted.begin(), sorted.begin() + n/2);
        rightHalf = vector<Point>(sorted.begin() + n/2, sorted.end());
    } else { // de lo contrario
        // recta divisoria = coordenada x del punto central
        recta_divisora = sorted[n/2].x;
        leftHalf = vector<Point>(sorted.begin(), sorted.begin() + n/2 +1);
        rightHalf = vector<Point>(sorted.begin() + n/2 + 1, sorted.end());
    }

    //cout << recta_divisora << endl;
    // Se llama recursivamente a la función, para el conjunto de la derecha e izquierda
    float dLmin = recursion(leftHalf);
    float dRmin = recursion(rightHalf);
    // Se obtiene el mínmo de las distancias obtenidas de la parte derecha e izquierday
    float dLRmin = min(dLmin,dRmin);

    // Paso Combinación de puntos:
    vector<Point> pLeft;
    vector<Point> pRight;
    float xDistance;
    // Se recorren puntos de la parte izquierda (de derecha a izquierda)
    for (int i=leftHalf.size()-1; i>=0; i--) {
        // Se calcula distancia de coordenada x de punto con recta divisoria
        xDistance = xdist(recta_divisora,leftHalf[i].x);
        // Si la distancia es menor a dLRmin
        if (xDistance < dLRmin) {
            
            // Se almacena punto 
            pLeft.push_back(leftHalf[i]);
        } else {
            break;
        }
    }
    // Se recorren puntos de la parte derecha (de izquierda a derecha)
    for (int i=0; i<rightHalf.size(); i++) {
        // Se calcula distancia de coordenada x de punto con recta divisoria
        xDistance = xdist(recta_divisora,rightHalf[i].x);
        // Si la distancia es menor a dLRmin
        if (xDistance < dLRmin) {
            // Se almacena punto 
            pRight.push_back(rightHalf[i]);
        } else {
            break;
        }
    }

    // cout << "Puntos left y right:" << endl;
    // printPointArray(leftHalf);
    // printPointArray(rightHalf);



    // if (!esPar(n)) {
    //     pLeft.push_back(sorted[n/2]);
    // }
    
    // Se compara la distancia entre los puntos más cercanos a al recta divisoria 
    float dCmin = dLRmin; 
    for (int i=0; i<pLeft.size(); i++) {
        for (int j=0; j<pRight.size(); j++) {
            float new_distance = distance(pLeft[i],pRight[j]);
            if (new_distance > 0) {
                //  Se actualiza distancia mínima
                dCmin = min(dCmin, new_distance);
            }
            
        }
    }
    // Se retorna distancia mínima
    return dCmin;
}

/**
 * Función que encuentra distancia mínima de par de puntos de un conjunto de puntos.
 * Ordena los puntos según coordenada x,
 * luego aplica "dividir para reinar".
*/
float divideAndConquer(vector<Point> coordinates) {
    vector<Point> sorted = coordinates;
    // Se ordenan puntos según coordenada x de manera creciente.
    sort(sorted.begin(), sorted.end());
    // Se llama a la función recursion
    return recursion(sorted);
}

