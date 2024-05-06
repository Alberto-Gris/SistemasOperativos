/*************************************************************************************************
 Problema de las carreras de personas hasta la barrera
 4 corredores empiezan corriendo hasta una barrera(meta), los primeros 3 que lleguen a la meta deberan 
 esperar ahí hasta que llegue el ultimo, despues de que llegue el ultimo podran continuar corriendo los demas
*************************************************************************************************/
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define corredores 4

sem_t semaforo;

int conta = 0;


void *mesa(void *p){
    sem_wait(&semaforo);    //Solo deja trabajar a 4 hilos al mismo tiempo, los demas se duermen    
    int x;
    while(1) ++x;

    sem_post(&semaforo);
    pthread_exit(NULL);
}

int main(){

    pthread_t hilo[corredores];

    sem_init(&semaforo,0,conta);
    

    printf("Fin hilo principal");
    return 0;
}