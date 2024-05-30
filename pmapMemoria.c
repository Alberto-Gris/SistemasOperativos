#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	char *addr,*file_name;
	int fd;
	char seekchar, newchar;
	struct stat statbuf;

	if (argc == 4)
	{
		file_name = argv[1];
		seekchar = *argv[2];
		newchar = *argv[3];
	}else{
		exit(1);
	}
	fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0600);
	fstat(fd, &statbuf);

	addr = mmap(NULL,statbuf.st_size,PROT_WRITE,MAP_SHARED,fd,0);
	
	

	return 0;
}