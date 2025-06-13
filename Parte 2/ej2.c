#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sM1_M2, sF1_FN, sF1_TD, sQG_TD, sQG_MIN, sM2_RR, sM2_FN, sM2_MF, sFN_RR, sFN_IN, sFN_PR, sFN_MIN, sRR_SR, sTD_MF, sMIN_PR, sMIN_CB, sPR_CB, sPR_IN, sPR_SN, sMF_SR, sSR_SN;

void* M1 (void* arg) {
    sem_post(&sM1_M2);
    return NULL;
}

void* IN (void* arg) {
    sem_wait(&sFN_IN);
    sem_wait(&sPR_IN);
    pthread_exit(NULL);
    return NULL;
}


void* F1 (void* arg) {
    //
    sem_post(&sF1_FN);
    sem_post(&sF1_TD);
    return NULL;
}

void* QG (void* arg) {
    sem_pos(&sQG_TD);
    sem_pos(&sQG_MIN);
    pthread_exit(NULL);
    return NULL;
}


void* TD (void* arg) {
    sem_wait(&sF1_TD);
    sem_wait(&sQG_TD);
    //
    sem_post(&sTD_MF);
    return NULL;
}

void* M2 (void* arg) {
    sem_wait(&sM1_M2);
    sem_pos(&sM2_RR);
    sem_pos(&sM2_FN);
    sem_pos(&sM2_MF);
    pthread_exit(NULL);
    return NULL;
}


void* FN (void* arg) {
    sem_wait(&sM2_FN);
    sem_wait(&sF1_FN);
    //
    sem_post(&sFN_RR);
    sem_post(&sFN_IN);
    sem_post(&sFN_PR);
    sem_post(&sFN_MIN);
    return NULL;
}

void* MF (void* arg) {
    sem_wait(&sM2_MF);
    sem_wait(&sTD_MF);
    sem_pos(&sMF_SR);
    pthread_exit(NULL);
    return NULL;
}


void* MIN (void* arg) {
    sem_wait(&sQG_MIN);
    sem_wait(&sFN_MIN);
    //
    sem_post(&sMIN_PR);
    sem_post(&sMIN_CB);
    return NULL
}
void* RR (void* arg) {
    sem_wait(&sM2_RR);
    sem_wait(&sFN_RR);
    sem_pos(&sRR_SR);
    pthread_exit(NULL);
    return NULL;
}

void* PR (void* arg) {
    sem_wait(&sFN_PR);
    sem_wait(&sMIN_PR);
    //
    sem_post(&sPR_CB);
    sem_post(&sPR_IN);
    sem_post(&sPR_SN);

    return NULL
}

void* SR (void* arg) {
    sem_wait(&sRR_SR);
    sem_wait(&sMF_SR);
    sem_pos(&sSR_SN);
    pthread_exit(NULL);
    return NULL;
}


void* IIN (void* arg) {
    //NADA
    return NULL;
}

void* CB (void* arg) {
    sem_wait(&sMIN_CB);
    sem_wait(&sPR_CB);
    pthread_exit(NULL);
    return NULL;
}

void* SN (void* arg) {
    sem_wait(&sSR_SN);
    sem_pos(&sPR_SN);
    pthread_exit(NULL);
    return NULL;
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
    sem_init(&sSR_SN, 0, 1); // Initial value for SR_SN is set to allow SN to run first

    pthread_t  tM1, tIN, tF1, tQG, tTD, tM2, tFN, tMF, tMIN, tRR, tPR, tSR, tINU, tCB, tSN;
    pthread_attr_t attr;//Declara una variable llamada attr de tipo pthread_attr_t, que representa los atributos de un hilo en la biblioteca pthread. Esta estructura permite configurar ciertas características de los hilos, como si serán desvinculados (detached) o no, el tamaño de su pila de ejecución, entre otras.
    pthread_attr_init(&attr);//Esta función inicializa attr con valores por defecto. Los valores predeterminados son: 1-Los hilos estarán en estado no-desvinculado, lo cual significa que podrás usar pthread_join() para esperar a que el hilo termine. 2- Se usa el tamaño de pila por defecto del sistem

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
    pthread_create(&tINU, &attr, INU, NULL);
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
    pthread_join(tINU, NULL);
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
