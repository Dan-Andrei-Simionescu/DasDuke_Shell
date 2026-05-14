#include "DDS.h"
#include "errno.h"

void errors_errno() {
    if (errno == EAGAIN) {
        perror("EAGAIN: Cannot create a new process in this instant, try again later.");
    } else if (errno == ENOMEM) {
        perror("ENOMEM: Not enough RAM memory on your device.");
    } else if (errno == ENOSYS) {
        perror("ENOSYS: Certain system calls may be blocked by a security profile configured by the system administrator.");
    }
}

void execution_of_command(char* args[MAX_args_string_size]) {
    pid_t random_pid = fork();

    if (random_pid == -1) {
        errors_errno();
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

    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        char* home = getenv("HOME");
        chdir(home);
        strcpy(last_working_directory, current_directory);
    } else if (strcmp(args[1], "-") == 0) {
        if (strlen(last_working_directory) > 0) {
            chdir(last_working_directory);
            strcpy(last_working_directory, current_directory);
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("No such file or directory.");
        } else {
            strcpy(last_working_directory, current_directory);
        }
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