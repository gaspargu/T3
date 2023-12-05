# Ejecutando Experimento 1 y Experimento 2

Experimentos realizados para medir los tiempos de ejecución de un algoritmo aleatorizado vs uno determinista, para el problema *Closest Pair of Points*. El experimento 1 ejecuta el algoritmo 100 veces para el mismo arreglo de puntos aleatorios en el rango [0,1)x[0,1) y el experimento 2 se ejecutan los algoritmos en arreglos aleatorios.

## Prerrequisitos
- Asegúrate de tener `g++` instalado en tu sistema.

## Funciones que se van a ejecutar
En el siguiente orden se van a ejecutar las siguientes funciones para los experimentos:
1. `generarPuntosAleatorios(int num_points)`
2. `divideAndConquer(vector<Point> puntos_aleatorios)`
3. `aleatorizado(vector<Point> puntos_aleatorios)`
4. `aleatorizado_mersenne(vector<Point> puntos_aleatorios)`
5. `aleatorizado_fast2(vector<Point> puntos_aleatorios)`

## Compilación
Para compilar `experimento_1.cpp`, ejecuta el siguiente comando en tu terminal:

```sh
g++ experimento_1.cpp structs.cpp -o exp1

```

Para ejecutar el experimento se usa el siguiente comando:

```sh
./exp1
```


Para compilar `experimento_2.cpp`, ejecuta el siguiente comando en tu terminal:

```sh
g++ experimento_2.cpp structs.cpp -o exp2

```
Para ejecutar el experimento 2 se usa el siguiente comando:
```sh
./exp2
```