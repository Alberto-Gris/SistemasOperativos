#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	char *s = "letrero a archivo\n";
	char *m = "letrero a pantalla\n";
	write( STDOUT_FILENO, m, strlen( m ));
	int fd = open( "arch.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);

// hacemos que STDOUT_FILENO describa al mismo archivo que describe fd
	dup2( fd, STDOUT_FILENO ); //Cambia la direccion del buffer, en el caso de las impresiones

// liberamos fd, ya no nos hace falta
	close( fd );
	write( STDOUT_FILENO, s, strlen( s ) );
	printf("bye bye\n");
	printf("Hola mundo soy una cadenita");
	return 0;
}