#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <sys/types.h>

void *h1( void * ); 
void *retira(void *);

unsigned int k = 500;
int montoCuenta = 500;

pthread_mutex_t lock;

int main( )
{
    pthread_t hilo[10];
    int clientes[] = {1,2};
    pthread_mutex_init(&lock,NULL);
    for(int i = 0;i<2;i++)
        pthread_create(&hilo[i],NULL,retira,&clientes[i]);
    for (int i = 0; i < 2; i++)
        pthread_join(hilo[i],NULL);

    printf("SSALDO FINAL %d\n",montoCuenta);
   return 0;
}

void *retira(void *p){
    int i = *(int *)p;
    printf("Cliente entrante = %d\n", i);
    pthread_mutex_lock(&lock);
    if (montoCuenta >= 500)
    {
        //sleep(1);
        montoCuenta = montoCuenta -500;
        printf("El cliente %d hizo un retiro exitoso\n",i);
    }else{
        printf("El cliente %d no hizo un retiro exitoso\n",i);
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}