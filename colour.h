#include "DDS.h"

void red(char* text) {
    printf("\033[0;31m");
    printf("%s\n", text);
    printf("\033[0m");
}

void green(char* text) {
    printf("\033[0;32m");
    printf("%s$ ", text);
    printf("\033[0m");
}

void blue(char* text) {
    printf("\033[0;34m");
    printf("%s", text);
    printf("\033[0m");
}

// Other colours to choose from
// (You'll have to modify yourself the colour of the prints inside main.c)
// (ex: You can modify the colour of the current directory path, or the DasDuke_shell_prompt message etc.)

void yellow(char* text) {
    printf("\033[0;33m");
    printf("%s", text);
    printf("\033[0m");
}

void cyan(char* text) {
    printf("\033[0;36m");
    printf("%s", text);
    printf("\033[0m");
}

void magenta(char* text) {
    printf("\033[0;35m");
    printf("%s", text);
    printf("\033[0m");
}

void white(char* text) {
    printf("\033[0;37m");
    printf("%s", text);
    printf("\033[0m");
}

void black(char* text) {
    printf("\033[0;30m");
    printf("%s", text);
    printf("\033[0m");
}
