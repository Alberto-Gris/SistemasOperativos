#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int tuberia[ 2 ];
    
    int h1, h2;

    //pipe nos devuelve un descriptor de lectura y otro de escritura.
    //tuberia[0] es de lectura
    //tuberia[1] es de escritura
    pipe( tuberia );
    
    //generamos un proceso. Es el hijo1
    h1 = fork();

    if( h1 == 0 ){
        // este extremo de la tuberia no se utiliza
        // liberamos el descriptor de archivo correspondiente
        close( tuberia[ STDIN_FILENO ] ); 

        //dirigimos la salida estandar hacia la tuberia
        dup2(tuberia[ STDOUT_FILENO ], STDOUT_FILENO);

        //este descriptor ya no hace falta. Lo liberamos
        close( tuberia[ STDOUT_FILENO ] );

        //ejecutamos el comando ls con la salida direccionada 
        // a la tuberia
        execlp("ls", "ls", NULL );

        // este mensaje no deberia aparecer.
        printf("ls no se ejecuto\n");   //No se ejecuta por que muere el proceso hijo1, acaba el comando ls y se muere
    }
    
    //liberamos el descriptor de salida, ya que no se requiere.
    close( tuberia[ STDOUT_FILENO ] );      //Stdout siempre vale 1 y Stdin vale 0
    
    //generamos otro proceso. Es el hijo2
    h2 = fork();
    if( h2 == 0 ){

        //hacemos que el flujo de entrada provenga de la tuberia
        dup2( tuberia[ STDIN_FILENO ], STDIN_FILENO );

        // este descriptor ya no es necesario
        close( tuberia[ STDIN_FILENO ] );

        // ejecutamos el comando wc. Su flujo de
        // entrada proviene de la tuberia
        execlp("wc", "wc", NULL);

        // este letreo no debería aparecer.
        printf("wc no se ejectuo\n");   //Pasa lo mismo que con hijo1
    }

    // el proceso padre espera a que los
    // procesos hijos terminen su ejecución
    wait(NULL);     //Se ocupan para comprobar que sus dos hijos hayan muerto antes, una vez sus hijos acaben finaliza el proceso padre
    wait(NULL);     //El proceso padre es el primero en la cola de ejecucion
    printf("bye\n");
    return 0;
}