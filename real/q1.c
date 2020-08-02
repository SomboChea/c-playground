#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE 128

const char *FILE_STUDENT_DATA_PATH = "./students.txt";

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
} * head;

// typedef for declared to use as data type
typedef struct person_tag PERSON;
typedef struct course_tag COURSE;
typedef struct student_tag STUDENT;

// core functions
void display_students();
void search_student();
void find_maximum();
void find_failed();
void update_file();
void read_file();
void quite();

// Linked list functions
void add_student(char *student_name, char *student_id, char *course_name, int no_of_units, int *marks);
int count();

// util functions
void display_menu();
void read_student_to_data();
void print_welcome();

int main(void)
{
    // variable use for menu selected
    int selected;

    print_welcome();

    display_menu();

    printf("Enter your option: ");
    scanf("%d", &selected);

    switch (selected)
    {
    case 1:
        display_students();
        break;
    case 2:
        search_student();
        break;
    case 3:
        find_maximum();
        break;
    case 4:
        find_failed();
        break;
    case 5:
        update_file();
        break;
    case 6:
        quite();
        break;
    default:
        printf("cannot find your option!");
        break;
    }
}

void print_welcome()
{
    printf("Welcome!\n");
}

void display_students()
{
    read_student_to_data();
}

void display_menu()
{
    printf("\n(1) Display students’ details\n");
    printf("(2) Search for a student’s mark\n");
    printf("(3) Find the details of student with the largest average\n");
    printf("(4) Find the details of failed students\n");
    printf("(5) Add new student to the record\n");
    printf("(6) Quit program\n\n");
}

void add_student(char *student_name, char *student_id, char *course_name, int no_of_units, int *marks)
{
    STUDENT *temp, *iterator;
    temp = (struct student_tag *)malloc(sizeof(struct student_tag));
    PERSON info = {student_name, student_id};
    COURSE course = {course_name, no_of_units, marks};
    int sum = 0;
    for (int i = 0; i < no_of_units; i++)
    {
        sum += marks[i];
    }
    course.avg = sum / no_of_units;
    temp->student_info = info;
    temp->course_info = course;
    // reference in head
    iterator = head;

    if (head == NULL)
    {
        head = temp;
        head->next = NULL;
    }
    else
    {
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
        }
        temp->next = NULL;
        iterator->next = temp;
    }
}

void read_student_to_data()
{
    // init head to null
    head = NULL;

    FILE *file;
    file = fopen(FILE_STUDENT_DATA_PATH, "r");

    if (file == NULL)
    {
        printf("cannot read file: %s", FILE_STUDENT_DATA_PATH);
        exit(EXIT_FAILURE);
    }

    char student_name[BUFFER_SIZE];
    char student_id[BUFFER_SIZE];
    char course_name[BUFFER_SIZE];
    int no_of_units;
    int marks[4];

    int i;
    while (!feof(file))
    {
        char no[BUFFER_SIZE];

        fgets(student_name, sizeof student_name, file);
        fgets(student_id, sizeof student_id, file);
        fgets(course_name, sizeof course_name, file);
        fgets(no, sizeof no, file);

        i = 0;
        while (student_name[i] != '\n')
        {
            i++;
        }

        student_name[i] = '\0';

        i = 0;
        while (student_id[i] != '\n')
        {
            i++;
        }

        student_id[i] = '\0';

        i = 0;
        while (course_name[i] != '\n')
        {
            i++;
        }

        course_name[i] = '\0';

        printf("Student Name: %s\n", student_name);
        printf("Student ID: %s\n", student_id);
        printf("Course Name: %s\n", course_name);
        printf("No of units: %s", no);

        no_of_units = atoi(no);
        for (int j = 0; j < no_of_units; j++)
        {
            char d[BUFFER_SIZE];

            fgets(d, sizeof d, file);
            sscanf(d, "%d", &marks[j]);
        }

        printf("Marks: [ ");
        for (int x = 0; x < no_of_units; x++)
        {
            printf("%d ", marks[x]);
        }
        printf("]\n\n");

        // add into linked list
        add_student(student_name, student_id, course_name, no_of_units, marks);
    }

    fclose(file);
}

int count()
{
    int n = 1;
    STUDENT *temp;
    temp = head;
    if (head == NULL)
    {
        return 0;
    }

    while (temp->next != NULL)
    {
        n++;
        temp = temp->next;
    }

    return n;
}

void search_student()
{
    printf("\nNot implement yet!");
}

void find_maximum()
{
    printf("\nNot implement yet!");
}

void find_failed()
{
    printf("\nNot implement yet!");
}

void update_file()
{
    FILE *file;
    file = fopen(FILE_STUDENT_DATA_PATH, "a");
    printf("\nNot implement yet!");
}

void read_file()
{
    printf("\nNot implement yet!");
}

void quite()
{
    printf("\nGoodbye!");
    exit(EXIT_SUCCESS);
}