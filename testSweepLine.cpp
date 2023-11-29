#include <cfloat>
#include "structs.h"
#include "sweepLine.cpp"


/* 
Compilar: g++ testSweepLine.c -o testSweepLine
Ejecutar:  ./testSweepLine
*/ 

int main() {
    // Crear un vector de tuplas de 2 doubles
    vector<Point> array = {
        {0.2,0.3},
        {0.4,0.1},
        {0.5,0.2},
        {0.5,0.4},
        {0.1,0.1}

    };

    // Llamar a la función con el vector de tuplas como parámetro
    double min_distance = sweepLine(array);

    cout << "Arreglo de puntos:" << endl;
    printPointArray(array);
    cout << "La distancia mínima usando sweep line es:" << min_distance << endl;
    sort(array.begin(),array.end());
    printPointArray(array);
    return 0;
}