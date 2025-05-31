#include <stdio.h>
#include <pthread.h>


int array1[5] = {1, 2, 3, 4, 5};
int array2[5] = {1, 2, 3, 4, 5};
int resultados[5]; //guardamos resultados intermedios
int resueltadoFinal;


//Hilos 1,2 y 3: sumamos posiciones 1,2 y 3 de array1 y array2
void* sumar_elementos(void* arg) {
    int index = *(int*)arg;
    resultados[index] = array1[index] + array2[index];
    printf("Hilo %d: Suma %d + %d = %d\n", index+1, array1[index], array2[index], resultados[index]);
    return NULL;
}


//Hilo 4
void* multiplicar_elementos(void* arg) {
    int sumaHilos = resultados[0] + resultados[1] + resultados[2];
    printf("Hilo 4: Suma total = %d\n",  sumaHilos);
    resultados[3] = sumaHilos * array1[3] * array2[3];
    printf("Hilo 4: Multiplicación %d * %d * %d = %d\n", sumaHilos, array1[3], array2[3],  resultados[3]);
    return NULL;
}

 
//Hilo 5
void* sumar_final(void* arg) {
    resultados[4] = resultados[3] + array1[4] + array2[4];
    printf("Hilo 5: %d + %d + %d = %d\n", resultados[3], array1[4], array2[4], resultados[4]);
    printf("Resultado final: %d\n", resultados[4]);
    return NULL;
}

 
//Crea y espera hilos
int main() {
    pthread_t hilos[5];
    int indices[3] = {0, 1, 2};

    // Crear hilos 1, 2, 3
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, sumar_elementos, &indices[i]);
    }

    // Esperar hilos 1-3
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }
 
    // Crear y esperar hilo 4
    pthread_create(&hilos[3], NULL, multiplicar_elementos, NULL);
    pthread_join(hilos[3], NULL);

    // Crear y esperar hilo 5
    pthread_create(&hilos[4], NULL, sumar_final, NULL);
    pthread_join(hilos[4], NULL);
    return 0;
}

 

 