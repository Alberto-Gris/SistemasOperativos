
#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>
#include <sys/types.h>



void *h1( void * ); 
void *h2( void * ); 
void *h3( void * );
void *h4( void * );

unsigned int k = 100;


int main( )
{

   pthread_t hilo_1, hilo_2, hilo_3, hilo_4;
   pthread_create( &hilo_1, NULL, h1, NULL );
   pthread_create( &hilo_2, NULL, h1, NULL );
   pthread_create( &hilo_3, NULL, h1, NULL );
   pthread_create( &hilo_4, NULL, h1, NULL );
   pthread_join( hilo_1, NULL );    //Detiene el proceso de main, esperando a que termine el hilo 1
   pthread_join( hilo_2, NULL );    //Detiene el proceso de main, esperando a que termine el hilo 2
   pthread_join( hilo_3, NULL );    //Asi con todos
   pthread_join( hilo_4, NULL );
   printf( "fin de main\n" );
   return 0;                        //Si se termina el proceso principal MAIN, los hilos que haya ejecutado se mueren
}

void *h1( void *s ){  
   printf("%d, %d\n", getpid(), gettid( ) );//Obtiene el identificador del proceso( getpid() ) y el segundo dato es el id del HILO( (gettid()) )
   while( 1 )
       k++;

   pthread_exit( NULL );
}

 
void *h2( void *parametro ){  
   printf("%d, %d\n", getpid(), gettid( ) );
   while( 1 )
       k--;

   pthread_exit( NULL );
}

 
void *h3( void *parametro ){  
   printf("%d, %d\n", getpid(), gettid( ) );
   while( 1 ){
       //sleep( 1 );
       k--;
   }

   pthread_exit( NULL );
}


void *h4( void *parametro ){  
   printf("%d, %d\n", getpid(), gettid( ) );
   while( 1 )
       k--;

   pthread_exit( NULL );
}

