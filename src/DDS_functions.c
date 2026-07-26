#include "DDS.h"
#include "errno.h"

void errors_errno() {
    if (errno == EAGAIN) {
        printf("EAGAIN: Cannot create a new process in this instant, try again later.");
    } else if (errno == ENOMEM) {
        printf("ENOMEM: Not enough RAM memory on your device.");
    } else if (errno == ENOSYS) {
        printf("ENOSYS: Certain system calls may be blocked by a security profile configured by the system administrator.");
    }
}

void execute_pipe_command(char* args_left[], char* args_right[]) {
    int fildes[2];
    if (pipe(fildes) == -1) {
        perror("Pipe command failed");
        return;
    }

    pid_t random_pid_one = fork();
    if (random_pid_one == -1) {
        errors_errno();
        exit(EXIT_FAILURE);
    } else if (random_pid_one == 0) {
        // duplicate write part to STDOUT_FILENO
        dup2(fildes[1], STDOUT_FILENO);
        close(fildes[1]);
        close(fildes[0]);
        execvp(args_left[0], args_left);
        perror("args_left failed!");
        exit(EXIT_FAILURE);
    }

    pid_t random_pid_two = fork();
    if (random_pid_two == -1) {
        errors_errno();
        exit(EXIT_FAILURE);
    } else if (random_pid_two == 0) {
        // duplicate read part to STDIN_FILENO
        dup2(fildes[0], STDIN_FILENO);
        close(fildes[0]);
        close(fildes[1]);
        execvp(args_right[0], args_right);
        perror("args_right failed!");
        exit(EXIT_FAILURE);
    }

    close(fildes[1]);
    close(fildes[0]);
    wait(NULL);
    wait(NULL);
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