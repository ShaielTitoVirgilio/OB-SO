#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sM1_M2, sF1_FN, sF1_TD, sQG_TD, sQG_MIN, sM2_RR, sM2_FN, sM2_MF, sFN_RR, sFN_IN, sFN_PR, sFN_MIN, sRR_SR, sTD_MF, sMIN_PR, sMIN_CB, sPR_CB, sPR_IN, sPR_SN, sMF_SR, sSR_SN;

void* M1 (void* arg) {
    printf("Materia: Matematicas 1\nCantidad previas: 0\nMaterias previas: \n---------------------------------------------------------------------------------------\n");
    sem_post(&sM1_M2);
}

void* IN (void* arg) {
    sem_wait(&sFN_IN);
    sem_wait(&sPR_IN);
    printf("Materia: Instrumentacion Nuclear\nCantidad previas: 2\nMaterias previas: Proteccion Radiologica,Fisica Nuclear\n---------------------------------------------------------------------------------------\n");
    pthread_exit(NULL);
}


void* F1 (void* arg) {
    //
     printf("Materia: Fisica 1\nCantidad previas: 0\nMaterias previas: \n---------------------------------------------------------------------------------------\n");
    sem_post(&sF1_FN);
    sem_post(&sF1_TD);
}

void* QG (void* arg) {
     printf("Materia: Quimica General\nCantidad previas: 0\nMaterias previas: \n---------------------------------------------------------------------------------------\n");
    sem_post(&sQG_TD);
    sem_post(&sQG_MIN);
    pthread_exit(NULL);
}


void* TD (void* arg) {
    sem_wait(&sF1_TD);
    sem_wait(&sQG_TD);
    printf("Materia: Termodinamica\nCantidad previas: 2\nMaterias previas: Fisica 1, Quimica General\n---------------------------------------------------------------------------------------\n");
    //
    sem_post(&sTD_MF);
}

void* M2 (void* arg) {
    sem_wait(&sM1_M2);
    printf("Materia: Matematicas 2\nCantidad previas: 1\nMaterias previas: Matematicas 1\n---------------------------------------------------------------------------------------\n");
    sem_post(&sM2_RR);
    sem_post(&sM2_FN);
    sem_post(&sM2_MF);
    pthread_exit(NULL);
}


void* FN (void* arg) {
    sem_wait(&sM2_FN);
    sem_wait(&sF1_FN);
    printf("Materia: Fisica Nuclear\nCantidad previas: 2\nMaterias previas: Matematicas 2, Fisica 1\n---------------------------------------------------------------------------------------\n");
    //
    sem_post(&sFN_RR);
    sem_post(&sFN_IN);
    sem_post(&sFN_PR);
    sem_post(&sFN_MIN);
}

void* MF (void* arg) {
    sem_wait(&sM2_MF);
    sem_wait(&sTD_MF);
    printf("Materia: Mecanica de fluidos\nCantidad previas: 2\nMaterias previas: Matematicas 2, Termodinamica\n---------------------------------------------------------------------------------------\n");
    sem_post(&sMF_SR);
    pthread_exit(NULL);
}


void* MIN (void* arg) {
    sem_wait(&sQG_MIN);
    sem_wait(&sFN_MIN);
    printf("Materia: Materiales en Ingenieria Nuclear\nCantidad previas: 2\nMaterias previas: Quimica General, Fisica Nuclear\n---------------------------------------------------------------------------------------\n");
    //
    sem_post(&sMIN_PR);
    sem_post(&sMIN_CB);
}
void* RR (void* arg) {
    sem_wait(&sM2_RR);
    sem_wait(&sFN_RR);
    printf("Materia: Reactividad de Reactores\nCantidad previas: 2\nMaterias previas: Matematicas 2, Fisica Nuclear\n---------------------------------------------------------------------------------------\n");
    sem_post(&sRR_SR);
    pthread_exit(NULL);
}

void* PR (void* arg) {
    sem_wait(&sFN_PR);
    sem_wait(&sMIN_PR);
    printf("Materia: Proteccion Radiologica\nCantidad previas: 2\nMaterias previas: Materiales en Ingenieria Nuclear, Fisica Nuclear\n---------------------------------------------------------------------------------------\n");
    sem_post(&sPR_CB);
    sem_post(&sPR_IN);
    sem_post(&sPR_SN);

}

void* SR (void* arg) {
    sem_wait(&sRR_SR);
    sem_wait(&sMF_SR);
        printf("Materia: Sistemas de Reactores\nCantidad previas: 2\nMaterias previas: Mecanica de fluidos, Reactividad de Reactores\n---------------------------------------------------------------------------------------\n");
    sem_post(&sSR_SN);
    pthread_exit(NULL);
}


void* IIN (void* arg) {
    //NADA
    printf("Materia: Introduccion a la Ingenieria Nuclear\nCantidad previas: 0\nMaterias previas: \n---------------------------------------------------------------------------------------\n");
}

void* CB (void* arg) {
    sem_wait(&sMIN_CB);
    sem_wait(&sPR_CB);
        printf("Materia: Calculo de Blindajes\nCantidad previas: 2\nMaterias previas: Materiales en Ingenieria Nuclear, Proteccion Radiologica\n---------------------------------------------------------------------------------------\n");

    pthread_exit(NULL);
}

void* SN (void* arg) {
    sem_wait(&sSR_SN);
        printf("Materia: Seguridad Nuclear\nCantidad previas: 2\nMaterias previas: Sistemas de Reactores, Proteccion Radiologica\n---------------------------------------------------------------------------------------\n");
    sem_post(&sPR_SN);
    pthread_exit(NULL);
}


int main() {
    // Initialize semaphores
    sem_init(&sM1_M2, 0, 0);
    sem_init(&sF1_FN, 0, 0);
    sem_init(&sF1_TD, 0, 0);
    sem_init(&sQG_TD, 0, 0);
    sem_init(&sQG_MIN, 0, 0);
    sem_init(&sM2_RR, 0, 0);
    sem_init(&sM2_FN, 0, 0);
    sem_init(&sM2_MF, 0, 0);
    sem_init(&sFN_RR, 0, 0);
    sem_init(&sFN_IN, 0, 0);
    sem_init(&sFN_PR, 0, 0);
    sem_init(&sFN_MIN, 0, 0);
    sem_init(&sRR_SR, 0, 0);
    sem_init(&sTD_MF, 0, 0);
    sem_init(&sMIN_PR, 0, 0);
    sem_init(&sMIN_CB, 0, 0);
    sem_init(&sPR_CB, 0, 0);
    sem_init(&sPR_IN, 0, 0);
    sem_init(&sPR_SN, 0, 0);
    sem_init(&sMF_SR, 0, 0);
    sem_init(&sSR_SN, 0, 0); 

    pthread_t  tM1, tIN, tF1, tQG, tTD, tM2, tFN, tMF, tMIN, tRR, tPR, tSR, tIIN, tCB, tSN;
    pthread_attr_t attr; 
    pthread_attr_init(&attr);

    pthread_create(&tM1, &attr, M1, NULL);
    pthread_create(&tIN, &attr, IN, NULL);
    pthread_create(&tF1, &attr, F1, NULL);
    pthread_create(&tQG, &attr, QG, NULL); 
    pthread_create(&tTD, &attr, TD, NULL);
    pthread_create(&tM2, &attr, M2, NULL);
    pthread_create(&tFN, &attr, FN, NULL);
    pthread_create(&tMF, &attr, MF, NULL);
    pthread_create(&tMIN, &attr, MIN, NULL);
    pthread_create(&tRR, &attr, RR, NULL);  
    pthread_create(&tPR, &attr, PR, NULL);
    pthread_create(&tSR, &attr, SR, NULL);
    pthread_create(&tIIN, &attr, IIN, NULL);
    pthread_create(&tCB, &attr, CB, NULL);
    pthread_create(&tSN, &attr, SN, NULL);

    pthread_join(tM1, NULL);
    pthread_join(tIN, NULL);    
    pthread_join(tF1, NULL);
    pthread_join(tQG, NULL);
    pthread_join(tTD, NULL);
    pthread_join(tM2, NULL);
    pthread_join(tFN, NULL);
    pthread_join(tMF, NULL);
    pthread_join(tMIN, NULL);
    pthread_join(tRR, NULL);
    pthread_join(tPR, NULL);
    pthread_join(tSR, NULL);
    pthread_join(tIIN, NULL);
    pthread_join(tCB, NULL);
    pthread_join(tSN, NULL);
    
    sem_destroy(&sM1_M2);
    sem_destroy(&sF1_FN);
    sem_destroy(&sF1_TD);
    sem_destroy(&sQG_TD);
    sem_destroy(&sQG_MIN);
    sem_destroy(&sM2_RR);
    sem_destroy(&sM2_FN);
    sem_destroy(&sM2_MF);
    sem_destroy(&sFN_RR);
    sem_destroy(&sFN_IN);
    sem_destroy(&sFN_PR);
    sem_destroy(&sFN_MIN);
    sem_destroy(&sRR_SR);
    sem_destroy(&sTD_MF);
    sem_destroy(&sMIN_PR);
    sem_destroy(&sMIN_CB);
    sem_destroy(&sPR_CB);
    sem_destroy(&sPR_IN);
    sem_destroy(&sPR_SN);
    sem_destroy(&sMF_SR);
    sem_destroy(&sSR_SN);
  
    return 0;
}
