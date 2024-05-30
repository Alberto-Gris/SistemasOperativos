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
    

    sigaction(SIGALRM,&act,NULL);
    alarm(1);
    while (1)
    {
        /* code */
    }
    
}