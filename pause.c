/*
Explique el funcionamiento de la funcion pause.
Muestre y explique un ejemplo de uso de esta función.
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

/*

*/
void signal_handler(int signal)
{
    printf("Signal %d caught\n", signal);
}

int main(void)
{
    struct sigaction act;
    int ret = 0;
    sigset_t mask;
    act.sa_restorer=NULL;
    act.sa_flags =0;

    act.sa_handler = signal_handler;
    sigaction(SIGCONT, &act, NULL);

    ret = pause();
    if (-1 == ret)
        printf("Process terminado con : %d\n",ret);
    return 0;
}