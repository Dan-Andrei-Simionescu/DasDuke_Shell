#include "DDS.h"

void execution_of_command(char* args[MAX_args_string_size]) {
    ssize_t random_pid = fork();

    if (random_pid == -1) {
        perror("Something went wrong when creating the child process.");
        exit(EXIT_FAILURE);
    } else if (random_pid == 0){
        // Child's Timeline (sees itself as 0)
        if (execvp(args[0], args) == -1) {
            perror("Invalid Command, stop all operations");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent's Timeline (sees the child as a positive number)
        wait(NULL);
    }

    return;
}

void change_directory(char* current_directory, char* last_working_directory, char* args[MAX_args_string_size]) {
    getcwd(current_directory, MAX_wd_string_size);

    if (strcmp(args[1], "~") == 0) {
        char* home = getenv("HOME");
        chdir(home);
        strcpy(last_working_directory, current_directory);
    } else if (strcmp(args[1], "-") == 0) {
        if (strlen(last_working_directory) > 0) {
            chdir(last_working_directory);
            strcpy(last_working_directory, current_directory);
        }
    } else {
        chdir(args[1]);
        strcpy(last_working_directory, current_directory);
    }

    return;
}

int return_args(char* string_command, char** args) {
    char* string_cut = strtok(string_command, " \n\t");
    if (string_cut == NULL) {
        return 0;
    }
    int index_str = 0;

    while (string_cut != NULL) {
        args[index_str] = string_cut;
        string_cut = strtok(NULL, " \n\t");
        index_str++;
    }
    args[index_str] = '\0';

    return index_str;
}