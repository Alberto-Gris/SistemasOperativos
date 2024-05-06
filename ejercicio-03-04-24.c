#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#define global 10000

int a[global],b[global],c[global],d[global];
void calculoProductoAB();
void calculoProductoCD();

void *h1( void * ); 
void *h2( void * ); 

unsigned int k = 100;

int main( )
{
   clock_t start = clock();
   pthread_t hilo_1, hilo_2;
   srand(time(NULL));
   for (int i = 0; i < global; i++)
   {
    
    a[i]=rand() % 30;
    b[i]=rand() % 30;
    c[i]=rand() % 30;
    d[i]=rand() % 30;
   }
   calculoProductoAB();
   calculoProductoCD();
   //pthread_create( &hilo_1, NULL, h1, NULL );
   //pthread_create( &hilo_2, NULL, h2, NULL );
   //pthread_join( hilo_1, NULL );    //Detiene el proceso de main, esperando a que termine el hilo 1
   //pthread_join( hilo_2, NULL );    //Detiene el proceso de main, esperando a que termine el hilo 2
   clock_t end = clock();
   printf("Tiempo transcurrido: %f", (double)(end - start)/CLOCKS_PER_SEC);
   return 0;                        //Si se termina el proceso principal MAIN, los hilos que haya ejecutado se mueren
}

void calculoProductoAB(){
    int sumatoria=0;
    for (int i = 0; i < global; i++)
    {
        sumatoria = sumatoria + a[i] * b[i];
    }
    printf("El producto punto es: %d\n",sumatoria);
}

void calculoProductoCD(){
    int sumatoria=0;
    for (int i = 0; i < global; i++)
    {
        sumatoria = sumatoria + c[i] * d[i];
    }
    printf("El producto punto es: %d\n",sumatoria);
}

void *h1( void *s ){  
   printf("%d, %d\n", getpid(), gettid( ) );//Obtiene el identificador del proceso( getpid() ) y el segundo dato es el id del HILO( (gettid()) )
    int sumatoria=0;
    for (int i = 0; i < global; i++)
    {
        sumatoria = sumatoria + a[i] * b[i];
    }
    printf("El producto punto es: %d\n",sumatoria);
   pthread_exit( NULL );
}

 
void *h2( void *parametro ){  
   printf("%d, %d\n", getpid(), gettid( ) );
    int sumatoria=0;
    for (int i = 0; i < global; i++)
    {
        sumatoria = sumatoria + c[i] * d[i];
    }
    printf("El producto punto es: %d\n",sumatoria);
   pthread_exit( NULL );
}