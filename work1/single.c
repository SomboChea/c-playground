#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE 128

const char *FILE_STUDENT_DATA_PATH = "./data/students.test.txt";

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
void add_student(char student_name[20], char student_id[10], char course_name[20], int no_of_units, int marks[4]);
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

    while (1)
    {
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
}

void print_welcome()
{
    printf("Welcome!\n");
}

void display_students()
{
    printf("\n");

    read_student_to_data();

    STUDENT *student;

    student = head;

    if (student == NULL)
    {
        printf("No student!");
        return;
    }

    print_student(student);

    while (student->next != NULL)
    {
        student = student->next;
        print_student(student);
    }
}

void print_student(STUDENT *student)
{
    printf("Student Name: %s\n", student->student_info.name);
    printf("Student ID: %s\n", student->student_info.id);
    printf("Course Name: %s\n", student->course_info.course_name);
    printf("No of units: %d\n", student->course_info.no_of_units);

    printf("Marks: [ ");
    for (int i = 0; i < student->course_info.no_of_units; i++)
    {
        printf("%d ", student->course_info.marks[i]);
    }
    printf("]\n");
    printf("Avg: %.2f\n", student->course_info.avg);
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

void add_student(char student_name[20], char student_id[10], char course_name[20], int no_of_units, int marks[4])
{
    STUDENT *temp, *iterator;
    temp = (struct student_tag *)malloc(sizeof(struct student_tag));
    PERSON info;
    strncpy(info.name, student_name, 20);
    strncpy(info.id, student_id, 10);

    COURSE course;
    strncpy(course.course_name, course_name, 20);
    course.no_of_units = no_of_units;
    // memcpy(course.marks, marks);

    float sum = 0;
    for (int i = 0; i < no_of_units; i++)
    {
        course.marks[i] = marks[i];
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

    char student_name[20];
    char student_id[10];
    char course_name[20];
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

        // printf("Student Name: %s\n", student_name);
        // printf("Student ID: %s\n", student_id);
        // printf("Course Name: %s\n", course_name);
        // printf("No of units: %s", no);

        no_of_units = atoi(no);
        for (int j = 0; j < no_of_units; j++)
        {
            char mark[BUFFER_SIZE];

            fgets(mark, sizeof mark, file);
            sscanf(mark, "%d", &marks[j]);
        }

        // printf("Marks: [ ");
        // for (int x = 0; x < no_of_units; x++)
        // {
        //     printf("%d ", marks[x]);
        // }
        // printf("]\n\n");

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

    char name[20];
    char id[10];
    char course_name[20];
    int no_of_units;
    int marks[4];

    printf("Enter student name: ");
    scanf("%s", &name);

    printf("Enter student id: ");
    scanf("%s", &id);

    printf("Enter course name: ");
    scanf("%s", &course_name);

    printf("Enter no of units: ");
    scanf("%d", &no_of_units);

    for (int i = 0; i < no_of_units; i++)
    {
        printf("Enter mark[%d]: ", i + 1);
        scanf("%d", &marks[i]);
    }

    if (count() > 0)
    {
        fputs("\n", file);
    }

    fputs(name, file);
    fputs("\n", file);
    fputs(id, file);
    fputs("\n", file);
    fputs(course_name, file);
    fputs("\n", file);
    fprintf(file, "%d", no_of_units);

    for (int i = 0; i < no_of_units; i++)
    {
        fputs("\n", file);
        fprintf(file, "%d", marks[i]);
    }

    fclose(file);

    printf("\nSaved");
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