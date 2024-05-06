#include <stdio.h>
#include <fcntl.h>

int main(){
    int fd=open("arch.txt",O_WRONLY | O_CREAT, O_TRUNC,0600);
    int h=100;
    write(fd, &h,sizeof(h));
    close(fd);
    return 0;
}