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

struct student_tag {
    struct person_tag student_info;
    struct course_tag course_info;
    struct student_tag *next;
};

// core functions
void display_students();
void search_student();
void find_maximum();
void find_failed();
void update_file();
void read_file();
void quite();

// util functions
void display_menu();

int main(void) {
    printf("Welcome!");

    printf("Goodbye!");
}

void display_menu() {
    printf("(1) Display students’ details\n");
    printf("(2) Search for a student’s mark\n");
    printf("(3) Find the details of student with the largest average\n");
    printf("(4) Find the details of failed students\n");
    printf("(5) Add new student to the record\n");
    printf("(6) Quit program\n");
}