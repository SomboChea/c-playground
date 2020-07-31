#include "stdio.h"
#include "string.h"

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

    struct person_tag person, person2 = {"Chea", "4567892"}, *personPtr;

    // strcpy style
    strcpy(person.id, "2345678");
    strcpy(person.name, "Sambo");

    personPtr = &person;

    printf("Hello, %s \n", person.name);
    printf("Hello, %s \n", person2.name);
    printf("Hello Ptr, %s \n", personPtr->name);

    return 0;
}