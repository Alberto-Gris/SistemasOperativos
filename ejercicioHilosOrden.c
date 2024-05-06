/*
Ejercicio que debe de ejecutar tres hilos de forma ordenada, haciendo uso de candados
*/

#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

void *imprime1(void *);
void *imprime2(void *);
void *imprime3(void *);
pthread_mutex_t lock;

#define LUGARES_EN_LA_MESA 4

sem_t semaforo;

int main( )
{
    pthread_t hilo[40];
    sem_init(&semaforo,0,LUGARES_EN_LA_MESA);

    pthread_create(&hilo[0],NULL,imprime1,NULL);
    pthread_create(&hilo[1],NULL,imprime2,NULL);
    pthread_create(&hilo[2],NULL,imprime3,NULL);
    pthread_join(hilo[0],NULL);
    pthread_join(hilo[1],NULL);
    pthread_join(hilo[2],NULL);

    sem_destroy(&semaforo);
    return 0;
}

void *imprime1(void *p){
    printf("Soy el numero 1\n");
    
    pthread_exit(NULL);
}

void *imprime2(void *p){
    printf("Soy el numero 2\n");
    
    pthread_exit(NULL);
}

void *imprime3(void *p){
    printf("Soy el numero 3\n");
    
    pthread_exit(NULL);
}