#include "stdio.h"
#include "stdlib.h"

struct person_tag {
    char name[20];
    char id[10];
};

struct course_tag {
    char course_name[20];
    int no_of_units;
    int marks[4];
    float avg;
};

void display_students(void);
void search_student(void);
void find_maximum(void);
void find_failed(void);
void update_file();
void read_file();
void quite();

int main(void) {
    printf("Welcome!");

    printf("Goodbye!");
}