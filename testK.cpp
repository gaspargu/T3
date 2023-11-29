#include "aleatorizado.cpp"

/* 
Test que busca cuantificar cual es el orden del tamaño de la grilla 
Compilar: g++ testK.cpp structs.cpp -o testK
Ejecutar: g++ ./testK 

El valor obtenido fue k = 174761, teniendo la grilla k x k cuadrados
*/

int main() {
    // Generar 100 puntos aleatorios
    vector<Point> puntos = generarPuntosAleatorios(50000000);
    // Imprimir los puntos generados
    int max = 0;
    for (int i=0; i<100; i++) {
        cout << i << endl;
        float min = comparacion_pares(puntos, 50000000);
        uint k = ceil(1/sqrt(min));
        if (k > max) {
            max = k;
        }
    }
    cout << max << endl;
    return 0;
}
