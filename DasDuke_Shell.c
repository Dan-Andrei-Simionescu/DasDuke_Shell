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

            int pipe_index = -1;
            for (int i = 0; i < nr_index; i++) {
                if (strcmp(args[i], "|") == 0) {
                    pipe_index = i;
                    break;
                }
            }
            if (pipe_index != -1) {
                args[pipe_index] = NULL;
                char **args_right = &(args[pipe_index + 1]);
                if (strcmp(args_right[0], "grep") == 0) {
                    for (int i = 0; args_right[i] != NULL; i++) {
                        int len = strlen(args_right[i]);
                        if (args_right[i][0] == '"' && args_right[i][len - 1] == '"') {
                            args_right[i][len - 1] = '\0';
                            args_right[i]++;
                        }
                    }
                }
                execute_pipe_command(args, args_right);
            } else if (strcmp(args[0], "cd") == 0) {
                char current_directory[MAX_wd_string_size];
                change_directory(current_directory, last_working_directory, args);
            } else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
                exit(0);
            } else if (strcmp(args[0], "clear") == 0) {
                system("clear");
            } else {
                execution_of_command(args);
            }
        }

        free(string_command);
    }
    return 0;
}
