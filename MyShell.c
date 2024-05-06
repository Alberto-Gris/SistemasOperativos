#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char comando[100];

    printf("MyMiniShell> ");
    scanf("&s",comando);
    // Eliminamos el carácter de nueva línea agregado por fgets
    if (comando[strlen(comando) - 1] == '\n')
        comando[strlen(comando) - 1] = '\0';

    // Se separa el comando y sus argumentos
    char *argumentos[20]; // Suponemos que el comando tendrá como máximo 20 argumentos
    char *token = strtok(comando, " ");
    int i = 0;
    while (token != NULL) {
        argumentos[i++] = token;
        token = strtok(NULL, " ");
    }
    argumentos[i] = NULL;

    // Ejecutamos el comando utilizando execvp()
    execvp(argumentos[0], argumentos);

    // Si execvp() devuelve, hubo un error
    perror("Error al ejecutar el comando");
    return 1;
}