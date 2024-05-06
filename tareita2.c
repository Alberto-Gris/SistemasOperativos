#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 20
#define MAX_LENGTH 100

char *commands[MAX_COMMANDS];
char *args[MAX_ARGS];

void execute_command(char *command) {
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    execvp(args[0], args);
    perror("Error executing command");
    exit(EXIT_FAILURE);
}

void parse_command(char *command) {
    int i = 0;
    char *token = strtok(command, "|");
    while (token != NULL) {
        commands[i++] = token;
        token = strtok(NULL, "|");
    }
    commands[i] = NULL;
}

int main() {
    char input[MAX_LENGTH];
    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (strcmp(input, "") == 0)
            continue;

        // Check for 'cd' command
        if (strncmp(input, "cd", 2) == 0) {
            char *directory = input + 3; // Skip "cd " part
            if (chdir(directory) != 0) {
                perror("Error changing directory");
            }
            continue; // Skip parsing and execution
        }

        parse_command(input);

        int num_commands = 0;
        while (commands[num_commands] != NULL) {
            num_commands++;
        }

        if (num_commands == 1) {
            if (strstr(commands[0], ">") != NULL) {
                // Code for output redirection
            } else if (strstr(commands[0], "<") != NULL) {
                // Code for input redirection
            } else {
                execute_command(commands[0]);
            }
        } else {
            // Code for handling multiple commands
        }
    }
    return 0;
}
