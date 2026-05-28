#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAX_wd_string_size 1024
#define MAX_args_string_size 1024

void execute_pipe_command(char* args_left[], char* args_right[]);
void execution_of_command(char* args[MAX_args_string_size]);
void errors_errno();
void change_directory(char* current_directory, char* last_working_directory, char* args[MAX_args_string_size]);
int return_args(char* string_command, char** args);

void red(char* text);
void green(char* text);
void blue(char* text);
void yellow(char* text);
void cyan(char* text);
void magenta(char* text);
void white(char* text);
void black(char* text);