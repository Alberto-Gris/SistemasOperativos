#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define tamaniomaximocomandos 100
#define maximosargumentos 10

int main() {
    char comando[tamaniomaximocomandos];
    char *args[maximosargumentos];
    char *token;
    int status;

    while (1) {
        printf("MiniShellDeRamon> ");
        fgets(comando, tamaniomaximocomandos, stdin);
        
        // Eliminar el carácter de nueva línea de la entrada
        if (comando[strlen(comando) - 1] == '\n')
            comando[strlen(comando) - 1] = '\0';

        // Separar el comando y los argumentos
        token = strtok(comando, " ");
        int i = 0;
        while (token != NULL && i < maximosargumentos - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Salir si el usuario escribe "exit"
        if (strcmp(args[0], "Fin") == 0)
            break;

        // Crear un proceso hijo para ejecutar el comando
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo
            execvp(args[0], args);
            // Si execvp() retorna, algo salió mal
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
        } else {
            // Proceso padre
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}