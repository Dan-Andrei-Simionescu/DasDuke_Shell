#include "DDS.h"
#include "colour.h"

int main() {
    char* string_command = NULL;
    size_t length_command = 0;
    ssize_t err_code_command;

    char string_working_directory[MAX_wd_string_size];
    void* err_code_wd;
    char last_working_directory[MAX_wd_string_size] = "";

    printf("\n");
    red("Welcome to DasDuke Shell!");
    printf("\n");

    while (1) {
        err_code_wd = getcwd(string_working_directory, MAX_wd_string_size);
        
        blue("DasDuke_shell_prompt: ");
        if (err_code_wd != NULL) {
            green(string_working_directory);
        }
        printf("\n      ❯ ");

        err_code_command = getline(&string_command, &length_command, stdin);
        if (err_code_command == -1) {
            perror("Getline_Failed (Never Happens).");
            exit(EXIT_FAILURE);
        } else {
            char* args[MAX_args_string_size];
            int nr_index = return_args(string_command, args);
            if (nr_index == 0) {
                continue;
            }
            if (strcmp(args[0], "cd") == 0) {
                char current_directory[MAX_wd_string_size];
                change_directory(current_directory, last_working_directory, args);
            } else {
                execution_of_command(args);
            }
        }
    }
    return 0;
}
