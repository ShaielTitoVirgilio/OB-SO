#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


//funciones esenciales(teorico)
//SISTEMA :
// read(), write(), printf()

//HILOS: 
//getpid(),fork()->crea un hilo nuevo ,wait(), getpid()

//PROCESOS: 
//getppid()->obtiene el id del procces padre, fork(), wait(), getpid()->obtiene el process id del proceso actual

int array1[5] = {1, 2, 3, 4, 5};
int array2[5] = {1, 2, 3, 4, 5};

void *hilo1() {
    int *resh1 = malloc(sizeof(int));
    *resh1 = array1[0] + array2[0];
    printf("Hilo 1: Suma %d + %d = %d\n", array1[0], array2[0], *resh1);
    pthread_exit((void *)resh1);
}

void *hilo2() {
    int *resh2 = malloc(sizeof(int));
    *resh2 = array1[1] + array2[1];
    printf("Hilo 2: Suma %d + %d = %d\n", array1[1], array2[1], *resh2);
    pthread_exit((void *)resh2);
}

void *hilo3() {
    int *resh3 = malloc(sizeof(int));
    *resh3 = array1[2] + array2[2];
    printf("Hilo 3: Suma %d + %d = %d\n", array1[2], array2[2], *resh3);
    pthread_exit((void *)resh3);
}

void *hilo4(void *arg) {
    int s = *((int *)arg);
    int *resh4 = malloc(sizeof(int));
    *resh4 = s * array1[3] * array2[3];
    printf("Hilo 4: Suma total = %d\n", s);
    printf("Hilo 4: Multiplicación %d * %d * %d = %d\n", s, array1[3], array2[3], *resh4);
    pthread_exit((void *)resh4);
}

void *hilo5(void *arg) {
    int n = *((int *)arg);
    int *resh5 = malloc(sizeof(int));
    *resh5 = n + array1[4] + array2[4];
    printf("Hilo 5: %d + %d + %d = %d\n", n, array1[4], array2[4], *resh5);
    pthread_exit((void *)resh5);
}

int main() {
    pthread_t h1, h2, h3, h4, h5;
    void *resh1, *resh2, *resh3, *resh4, *resh5;

    pthread_create(&h1, NULL, hilo1, NULL);
    pthread_create(&h2, NULL, hilo2, NULL);
    pthread_create(&h3, NULL, hilo3, NULL);

    pthread_join(h1, &resh1);
    pthread_join(h2, &resh2);
    pthread_join(h3, &resh3);

    int sumah123 = *((int *)resh1) + *((int *)resh2) + *((int *)resh3);
    free(resh1);
    free(resh2);
    free(resh3);

    pthread_create(&h4, NULL, hilo4, &sumah123);
    pthread_join(h4, &resh4);

    int resultado4 = *((int *)resh4);
    free(resh4);

    pthread_create(&h5, NULL, hilo5, &resultado4);
    pthread_join(h5, &resh5);

    printf("Resultado final: %d\n", *((int *)resh5));
    free(resh5);

    return 0;
}

