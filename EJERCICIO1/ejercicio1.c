#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> //va?


int array1[5] = {1, 2, 3, 4, 5};
int array2[5] = {1, 2, 3, 4, 5};
int resultados[3]; // guardamos resultados intermedios
int resultadoHilo4;
int resueltadoFinal;

void sumar_elementos(void* arg) {
    int index = *(int*)arg;
    resultados[index] = array1[index] + array2[index];
    printf("Hilo %d: Suma %d + %d = %d\n", index + 1, array1[index], array2[index], resultados[index]);
    pthread_exit(NULL);
}
