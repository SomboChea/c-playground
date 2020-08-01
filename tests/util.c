#include "stdio.h"

void print(char *text) {
    printf(text);
}

void println(char *text) {
    newline();
    print(text);
}

void newline() {
    printf("\n");
}