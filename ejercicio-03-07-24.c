/*
Escriba un programa con un proceso padre y un pŕoceso hijo,
Cuando el proceso hijo tarda mas de 10 segundos en terminar,
el proceso padre enviará la señal 9 a su proceso hijo.
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

int main()
{
    int *aleatorio;
    int hijillo;
    int pid = fork();
    if (pid > 0)
    {
        // for (int i = 0; i < 10; i++)
        //{

        printf("Chambeando.....\n");
        sleep(10);
        //}

        hijillo = waitpid(pid, aleatorio, WNOHANG);

        if (hijillo == 0)
        {
            printf("Ya muerete\n");
            kill(pid, 9);
        }
        if (hijillo == -1)
        {
            printf("No es necesario matar a mi hijo\n");
        }
    }
    else
    {
        sleep(15);
    }
    return 0;
}