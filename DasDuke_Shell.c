#include "DDS.h"
#include "colour.h"

int main() {
    char* string_command = NULL;

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
        string_command = readline("\n      ❯ ");
        if (string_command == NULL) {
            perror("Error: Readline failed. Exiting.");
            exit(EXIT_FAILURE);
        }

        if (*string_command != '\0') {
            add_history(string_command);

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

        free(string_command);
    }
    return 0;
}
