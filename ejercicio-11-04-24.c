/*
Ejercicio que simule un punto de venta automatizado de venta de boletas de autobuses 
*/

#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <sys/types.h>

void *retira(void *);

int asientos = 10;
int compra = 15;

pthread_mutex_t lock;

int main( )
{
    pthread_t hilo[40];
    int clientes[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    pthread_mutex_init(&lock,NULL);

    for(int i = 0; i<compra; i++)
        pthread_create(&hilo[i],NULL,retira,&clientes[i]);
    for (int i = 0; i < compra; i++)
        pthread_join(hilo[i],NULL);

    printf("Asientos restantes: %d\n",asientos);
    return 0;
}

void *retira(void *p){
    int i = *(int *)p;
    printf("Cliente entrante = %d\n", i);
    pthread_mutex_lock(&lock);
    if (asientos >= 1)
    {
        sleep(.5);
        asientos = asientos - 1;
        printf("El cliente %d hizo una compra exitosa\n",i);
    }else{
        printf("El cliente %d no hizo una compra exitosa\n",i);
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}