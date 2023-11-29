#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <iostream>
#include "structs.h"
using namespace std; 

// A utility function to find 
// minimum of two float values 
float min(float x, float y) 
{ 
    return (x < y)? x : y; 
} 

float xdist(float x1, float x2) {
    return (x1 - x2)*(x1 - x2);
}

bool esPar(int numero) {
    return (numero & 1) == 0;
}

float recursion(vector<Point> sorted) {
    int n = sorted.size(); 
    if (n == 2) {
        return distance(sorted[0],sorted[1]);
    }
    if (n<2) {
        return FLT_MAX;
    }

    float recta_divisora;
    vector<Point> leftHalf;
    vector<Point> rightHalf;


    if (esPar(n)) {
        recta_divisora = (sorted[n/2-1].x + sorted[n/2].x) / 2;
        leftHalf = vector<Point>(sorted.begin(), sorted.begin() + n/2);
        rightHalf = vector<Point>(sorted.begin() + n/2, sorted.end());
    } else {
        recta_divisora = sorted[n/2].x;
        leftHalf = vector<Point>(sorted.begin(), sorted.begin() + n/2);
        rightHalf = vector<Point>(sorted.begin() + n/2 + 1, sorted.end());
    }


    float dLmin = recursion(leftHalf);
    float dRmin = recursion(rightHalf);
    float dLRmin = min(dLmin,dRmin);

    vector<Point> pLeft;
    vector<Point> pRight;
    float xDistance;
    for (int i=leftHalf.size()-1; i>=0; i--) {
        xDistance = xdist(recta_divisora,leftHalf[i].x);
        if (xDistance < dLRmin) {
            pLeft.push_back(leftHalf[i]);
        } else {
            break;
        }
    }

    for (int i=0; i<rightHalf.size(); i++) {
        xDistance = xdist(recta_divisora,rightHalf[i].x);
        if (xDistance < dLRmin) {
            pRight.push_back(rightHalf[i]);
        } else {
            break;
        }
    }

    if (!esPar(n)) {
        pLeft.push_back(sorted[n/2]);
    }
    

    float dCmin = dLRmin; 
    for (int i=0; i<pLeft.size(); i++) {
        for (int j=0; j<pRight.size(); j++) {
            float new_distance = distance(pLeft[i],pRight[j]);
            dCmin = min(dCmin, new_distance);
        }
    }

    return dCmin;
}


float divideAndConquer(vector<Point> coordinates) {
    vector<Point> sorted = coordinates;
    sort(sorted.begin(), sorted.end());

    return recursion(sorted);
}

