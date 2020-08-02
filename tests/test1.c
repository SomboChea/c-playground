#include "stdio.h"
#include "stdlib.h"

struct person {
    char name[20];
    int age;
};

struct student {
    int id;
    struct person info;
    struct student *next;
};

void add_first();
void add_last();
void remove_first();
void remove_last();
void show();
void quite();

int main() {

    printf("Goodbye!");
}