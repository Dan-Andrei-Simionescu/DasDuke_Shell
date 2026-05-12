#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_wd_string_size 1024

void execution_of_command(char* args[64]);
void change_directory(char* current_directory, char* last_working_directory, char* args[64]);
void return_args(char* string_command, char** args);

void red(char* text);
void green(char* text);
void blue(char* text);
void yellow(char* text);
void cyan(char* text);
void magenta(char* text);
void white(char* text);
void black(char* text);