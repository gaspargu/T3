
// C++ program Miller-Rabin primality test
#include <bits/stdc++.h>
using namespace std;

// Entrega la posicion del bit mas significativo de un unsigned long long
ull logBase2(ull n) {
    ull res = n;
    if (res == 0) {
        return 0; // Logaritmo indefinido para 0
    }
    ull pos = -1;
    while (res) {
        res >>= 1;
        pos++;
    }
    return pos;
}

// Encuentra 1era potencia de 2 mayor al numero
ull pot2(ull n) {
    ull res = 1;
    while(res < n) {
        res <<= 1;
    }
    return res;
}

// Exponenciacion rapida
ull pot(ull a, ull n) {
    if (n == 0) return 1;
    ull x = pot(a, n/2);
    if ((n & 1) == 0) return x*x;
    return x*x*a;
} 

// Función para verificar si un número es primo usando el test de Miller-Rabin para numeros de 64 bits
// Por lo tanto solo necesitamos verificar los primeros 12 primos
bool millerrabin(ull n) {
    // Casos base
    if (n == 2 || n == 3) return true;
    if (n < 2 || (n & 1) == 0) return false;

    // Escribimos n - 1 como 2^s * d
    ull s = 0;
    ull d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    // Probamos a hacer 12 veces el test de Miller-Rabin
    //vector<ull> prime_numbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    vector<ull> prime_numbers = {2, 3, 5, 7, 11};
    for (int i = 0; i < 5; i++) {
        // Elegimos un primo a en el rango [2, 37]
        ull a = prime_numbers[i];
        // x = a^d % n
        ull x = 1;
        for (ull r = 0; r < d; r++) {
            x = (x * a) % n;
        }

        // Si x == 1 o x == n-1, n probablemente es primo
        if (x == 1 || x == n-1) continue;

        // Iteramos s veces
        bool probablemente_primo = false;
        for (ull r = 0; r < s; r++) {
            x = (x * x) % n;
            if (x == 1) return false;
            if (x == n-1) {
                probablemente_primo = true;
                break;
            }
        }
        if (probablemente_primo) continue;
        return false;
    }
    return true;
}




// Función para encontrar el siguiente primo después de n
ull nextPrime(ull n){
    // Si n es par, el siguiente primo es n + 1
    if ((n & 1) == 0) n++;
    // Si n es impar, el siguiente primo es n + 2
    else n += 2;
    // Iteramos hasta encontrar un primo iterando entre los impares
    while (!millerrabin(n)) n += 2;
    return n;
}

uint hashSimple(ull x, int m) {
    return ((3*x + 2) % 186391) % m;
}

// Función para usar familia de funciones hash universales
ull hashUniversal(ull key, ull a, ull b, ull p, ull m){
    return ((a * key + b) % p) % m;
}

ull hashFast(ull key, ull a, ull b, ull k, ull l) {
    return ((a * key + b) & k) >> l;
}