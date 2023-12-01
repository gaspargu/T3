
// C++ program Miller-Rabin primality test
#include <bits/stdc++.h>
using namespace std;
 
// Utility function to do modular exponentiation.
// It returns (x^y) % p
int power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
 
// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that  d*2 = n-1
// for some r >= 1
bool millerTest(int d, int n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);
 
    // Compute a^d % n
    int x = power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 
    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
 
    // Return composite
    return false;
}
 
// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
 
    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
 
    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
         if (!millerTest(d, n))
              return false;
 
    return true;
}

// Función para verificar si un número es primo usando el test de Miller-Rabin para numeros de 64 bits
// Por lo tanto solo necesitamos verificar los primeros 12 primos
bool millerrabin(ull n) {
    // Casos base
    if (n == 2 || n == 3) return true;
    if (n < 2 || n%2 == 0) return false;

    // Escribimos n - 1 como 2^s * d
    ull s = 0;
    ull d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    // Probamos a hacer 12 veces el test de Miller-Rabin
    vector<ull> prime_numbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; i++) {
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
    if (n % 2 == 0) n++;
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