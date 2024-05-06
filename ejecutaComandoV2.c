#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
        
        printf("myshell>");
        char cadena_de_caracteres[100];
        scanf("%s", cadena_de_caracteres);
        
        execlp("ls", "ls" ,"-lh",NULL);
    return 0;
}