/*
Es para ver si el puerto serial este encendido o apagado
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
#include <sys/ioctl.h>
/*

*/

int main(void)
{
    int serial,fd;
    fd = open("/dev/ttys5",1);
    ioctl(fd,TIOCMGET,&serial);
    if (serial & TIOCM_DTR)
    {
        printf("Encendido\n");
    }else{
        printf("Apagado\n");
    }
    
    return 0;
}