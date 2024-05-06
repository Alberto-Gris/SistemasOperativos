#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>                                                             
#include <unistd.h>

void *proceso_1(void *s){  
   printf("soy un proceso delgado mejor conocido como Hilo o Thread\n");
   pthread_exit(NULL);
}

 
void *proceso_2(void *parametro){  //Define el proceso del hilo
   printf("Yo soy otro Hilo o Thread\n");
   char *ptr = (char *)parametro;
   printf("mi dato de entrada es %c\n", *ptr);
   pthread_t hilo_3;
   pthread_create(&hilo_3,NULL,proceso_2,&parametro);
   pthread_join(hilo_3,NULL);
   pthread_exit(NULL);
}


int main()
{
   char k = 'a';
   pthread_t hilo_1, hilo_2;
   pthread_create(&hilo_1, NULL, proceso_1, NULL); //Crea el hilo con el proceso asignado
   pthread_create(&hilo_2, NULL, proceso_2, (void *)&k);//Es como si se ejecutara al mismo tiempo los dos procesos
   pthread_join(hilo_1, NULL);
   pthread_join(hilo_2, NULL);
   printf("fin de main\n");
   return 0;
}

