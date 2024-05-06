#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define CLIENTES 7
#define LUGARES_EN_LA_MESA 4

sem_t semaforo;

unsigned int x = 0;

void *mesa(void *p){
    sem_wait(&semaforo);    //Solo deja trabajar a 4 hilos al mismo tiempo, los demas se duermen    
    while(1) ++x;

    sem_post(&semaforo);
    pthread_exit(NULL);
}

int main(){
    int k;
    pthread_t hilo[CLIENTES];

    sem_init(&semaforo,0,LUGARES_EN_LA_MESA);

    for (k = 0; k < CLIENTES; k++)
    {
        pthread_create(&hilo[k],NULL,mesa,NULL);
        //pthread_join(hilo[k],NULL);
    }
    for (k = 0; k < CLIENTES; k++)
    {
        pthread_join(hilo[k],NULL);
    }
    sem_destroy(&semaforo);

    printf("Fin hilo principal");
    return 0;
}