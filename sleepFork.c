#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	int pid=fork();
	if(pid>0){
		wait(NULL);
		exit(1);
	}else{
		sleep(60);
		exit(1);
	}
}