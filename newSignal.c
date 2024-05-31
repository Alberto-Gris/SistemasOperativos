#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void tratar_alarma(){
    static int c;
    printf("Alrma activada = %d\n",c++);
    alarm(1);
}

int main(void ){
    struct sigaction act;
    sigset_t mask;

    act.sa_handler = tratar_alarma;

    act.sa_restorer=NULL;
    act.sa_flags =0;

    /*Inicia la configuracion de bloqueo de la señal 2 SIGINT*/
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);/*Ya no responde el control + c*/
    sigaddset(&mask,SIGTSTP);/*Ya no responde el control + z*/
    sigprocmask(SIG_SETMASK, &mask, NULL);
    /*Se termina la configuracion del bloqueo*/

    sigaction(SIGALRM,&act,NULL);
    alarm(1);
    char str[100];
    int i=0;
    while (1)
    {
        if (i==10)
        {
            printf("Activado el ctrl+c\n");
            sigemptyset(&mask);/*En esta parte del codigo volvemos a reactivar las señales de CTRL + C y Z*/
            sigdelset(&mask,SIGINT);
            sigdelset(&mask,SIGTSTP);
            sigprocmask(SIG_SETMASK, &mask, NULL);
        }
        sleep(1);
        i++;
        //printf("Introduce una cadena: ");
        //fgets(str,50,stdin);
        //printf("%s",str);
    }
    
}