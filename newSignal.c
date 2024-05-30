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
    sigprocmask(SIG_SETMASK, &mask, NULL);
    /*Se termina la configuracion del bloqueo*/

    sigaction(SIGALRM,&act,NULL);
    alarm(1);
    while (1)
    {
        /* code */
    }
    
}