#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int pid = fork();
    if( pid == 0 ){
        execlp("ls", "ls", NULL);
        printf("Que onda??");
    }
    else{
        wait( NULL );
        exit(0);
    }
    return 0;
}