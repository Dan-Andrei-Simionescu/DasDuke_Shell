#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void execution_of_command(char* args[64]) {
    size_t random_pid = fork();

    if (random_pid == -1) {
        perror("Something went wrong when creating the child process.");
        exit(EXIT_FAILURE);
    } else if (random_pid == 0){
        // Child's Timeline (sees itself as 0)
        execvp(args[0], args);
        if (execvp(args[0], args) == -1) {
            perror("Invalid Command, stop all operations -> ");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent's Timeline (sees the child as a positive number)
        wait(NULL);
    }
}

int main() {
    char* string = NULL;
    size_t length = 0;
    ssize_t err_code;

    while (1) {
        printf("DasDuke_shell_prompt> ");
        err_code = getline(&string, &length, stdin);

        if (err_code == -1) {
            perror("Getline_Failed (Never Happens).");
            exit(EXIT_FAILURE);
        } else {
            char* string_cut = strtok(string, " \n\t");
            int index_str = 0;
            char *args[64];
            while (string_cut != NULL) {
                args[index_str] = string_cut;
                string_cut = strtok(NULL, " \n\t");
                index_str++;
            }
            args[index_str] = NULL;
            if (strcmp(args[0], "cd") == 0) {
                chdir(args[1]);
            } else {
                execution_of_command(args);
            }
        }
    }
    return 0;
}
