#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

//Codigo que detecta las señales de dormir y despertar

void captura_control_c(){
    printf("El usuario me quiere mimir\n");
}

void captura_iniciar_denuevo(){
    printf("El usuario me quiere despertar :(\n");
}

int main(){
    signal(SIGTSTP,captura_control_c);//Detecta la señal de teclado y ejecuta una funcion
    //signal(SIGCONT,captura_iniciar_denuevo);//Detecta la señal de teclado y ejecuta una funcion
    while (1)
    {
        /* code */
    }
    
	return 0;
}