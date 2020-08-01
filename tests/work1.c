#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct person_tag
{
    char name[20];
    char id[10];
};

struct course_tag
{
    char course_name[20];
    int no_of_units;
    int marks[4];
    float avg;
};

struct student_tag
{
    struct person_tag student_info;
    struct course_tag course_info;
    struct student_tag *next;
};

int main()
{
    int selected;
    struct person_tag person, person2 = {"Chea", "4567892"}, *personPtr;

    // strcpy style
    strcpy(person.id, "2345678");
    strcpy(person.name, "Sambo");

    personPtr = &person;

    printf("Hello, %s \n", person.name);
    printf("Hello, %s \n", person2.name);
    printf("Hello Ptr, %s \n", personPtr->name);

    // using linkedlist
    struct student_tag *first = NULL;
    struct student_tag *second = NULL;
    struct student_tag *third = NULL;

    first = (struct student_tage *)malloc(sizeof(struct student_tag *));

    struct course_tag c1 = {"Computer", 4, {1, 2, 3, 4}};
    struct person_tag p1 = {"Sambo", "121214"};
    first->course_info = c1;
    first->student_info = p1;
    first->next = second;

    printf("Student name: %s \n", first->student_info.name);
    printf("Student id: %s \n", first->student_info.id);
    printf("Course name: %s \n", first->course_info.course_name);
    printf("Course of units: %d", first->course_info.no_of_units);

    read_file("./../data/welcome.txt");
    
    display_menu();

    scanf("\nenter the option: ", selected);

    menu(selected);

    return 0;
}

void read_file(char *filename)
{
    // read the file here...
    FILE *file;
    char c;

    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("no file were found...!");
    }
    else
    {
        while ((c = getc(file)) != EOF)
        {
            printf("%c", c);
        }
    }
}

void menu(int menu)
{
    switch (menu)
    {
    case 1:
        printf("1. Student details...");
        break;

    default:
        printf("No menu found here...!");
        break;
    }
}


void display_menu() {
    printf("\n");
    read_file("./../note/section1.txt");
}