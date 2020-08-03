#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUFFER_SIZE 128
#define MAX_NO_OF_UNITS 4
#define NAME_SIZE 20

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
    int marks[MAX_NO_OF_UNITS];
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

// file function
void read_file();

// util functions
int menu();
void print_welcome();
void print_student(STUDENT *student);
void release(STUDENT *data);
int find_min_in_array(int *array);
STUDENT *search_student_by_name_or_id(char search_key[NAME_SIZE]);
STUDENT *find_maximum_avg();
STUDENT *add_last_student(STUDENT *nodes, STUDENT *element);

// core functions
void display_students();
void search_student();
void find_maximum();
void find_failed();
void update_file();
void quite();

// Linked list functions
void add_student(char student_name[20], char student_id[10], char course_name[20], int no_of_units, int marks[MAX_NO_OF_UNITS]);
int count_elements(STUDENT *elements);
int count();

int main(void)
{
    // variable use for menu selected
    int selected;

    print_welcome();

    // init the read data from the file
    read_file();

    while (1)
    {
        selected = menu();

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
    read_file();

    STUDENT *student = head;

    if (student == NULL)
    {
        printf("\nNo student!\n");
        return;
    }

    print_student(student);
}

void print_student(STUDENT *student)
{
    int records_count = 0;
    printf("\n================ Student Details ================\n");
    while (student != NULL)
    {
        printf("\n");
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
        student = student->next;
        records_count++;
    }

    // output the records count
    printf("\nRecords: %d has been loaded successfully!\n", records_count);

    // clean up the memory
    // after output the data
    // because we don;t need it anymore after output
    release(student);
}

int menu()
{
    printf("\n(1) Display students’ details\n");
    printf("(2) Search for a student’s mark\n");
    printf("(3) Find the details of student with the largest average\n");
    printf("(4) Find the details of failed students\n");
    printf("(5) Add new student to the record\n");
    printf("(6) Quit program\n");

    int choosen;
    printf("\nEnter your option: ");
    scanf("%d", &choosen);
    return choosen;
}

void add_student(char student_name[20], char student_id[10], char course_name[20], int no_of_units, int marks[MAX_NO_OF_UNITS])
{
    STUDENT *temp, *iterator;
    temp = (struct student_tag *)malloc(sizeof(struct student_tag));
    PERSON info;
    memcpy(info.name, student_name, 20);
    memcpy(info.id, student_id, 10);

    COURSE course;
    memcpy(course.course_name, course_name, 20);
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

int count_elements(STUDENT *elements)
{
    int n = 1;
    STUDENT *temp;
    temp = elements;
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

int count()
{
    return count_elements(head);
}

void search_student()
{
    char search_key[NAME_SIZE];

    printf("Enter student name or id to search: ");
    scanf("%s", &search_key);

    STUDENT *found_student = search_student_by_name_or_id(search_key);
    if (found_student == NULL)
    {
        printf("\nNo student found!\n");
        return;
    }

    print_student(found_student);
}

STUDENT *search_student_by_name_or_id(char search_key[NAME_SIZE])
{
    // refresh data from file first
    read_file();

    STUDENT *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->student_info.name, search_key) == 0 || strcmp(temp->student_info.id, search_key) == 0)
        {
            printf("\nSearch found with key: %s\n", search_key);
            // set the temp next to null
            // and free up the memory
            temp->next = NULL;
            free(temp->next);

            // return the current temp
            // that found in current search
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

STUDENT *find_maximum_avg()
{
    // refresh data from file first
    read_file();

    STUDENT *temp = head, *max;
    max = temp->next;

    while (temp != NULL)
    {
        if (max == NULL)
        {
            return temp;
        }

        if (max->course_info.avg < temp->course_info.avg)
        {
            max = temp;
        }

        temp = temp->next;
    }

    // release the max next record
    // set max next element to NULL
    // because we use only one record
    release(max->next);
    max->next = NULL;

    return max;
}

int find_min_in_array(int *array)
{
    if (array == NULL)
    {
        return -1;
    }

    int min = array[0];
    size_t size = sizeof(array) / sizeof(array[0]);

    for (int i = 1; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

STUDENT *add_last_student(STUDENT *nodes, STUDENT *element)
{
    STUDENT *temp = nodes, *node;
    node = (struct student_tag *)malloc(sizeof(struct student_tag));
    node->student_info = element->student_info;
    node->course_info = element->course_info;
    node->next = NULL;

    if (nodes == NULL)
    {
        nodes = node;

        return nodes;
    }

    // store current as tempo
    // ref for nodes
    temp = nodes;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = node;

    return nodes;
}

// ISSUE: can't find all failed students
// It's just return one record back
STUDENT *find_failed_mark(int upper_mark)
{
    // refresh data from file first
    read_file();

    printf("Count elements: %d\n", count());

    STUDENT *temp = head, *failed_students = NULL;

    int count = count_elements(temp);
    printf("Temp count elements: %d", count);

    int run_count = 0;

    while (temp != NULL)
    {
        run_count++;

        int min = find_min_in_array(temp->course_info.marks);
        if (min < upper_mark)
        {
            printf("\nRun min: %d\n", min);
            failed_students = add_last_student(failed_students, temp);
        }

        temp = temp->next;
    }

    printf("\nRun count: %d", run_count);

    return failed_students;
}

void find_maximum()
{
    // refresh data from file first
    read_file();

    STUDENT *max_student = find_maximum_avg();
    if (max_student == NULL)
    {
        printf("\nNo maximum student found!\n");
        return;
    }

    printf("\nFind maximum avg was found with: %0.2f\n", max_student->course_info.avg);
    print_student(max_student);
}

void find_failed()
{
    int upper_mark = 50;
    STUDENT *failed_students = find_failed_mark(upper_mark);
    if (failed_students == NULL)
    {
        printf("\nNo failed student found!\n");
        return;
    }

    printf("\nFind the failed students that at least one mark less than %d\n", upper_mark);
    print_student(failed_students);
}

void update_file()
{
    FILE *file;
    file = fopen(FILE_STUDENT_DATA_PATH, "a");

    char name[20];
    char id[10];
    char course_name[20];
    int no_of_units;
    int marks[MAX_NO_OF_UNITS];

    printf("Enter student name: ");
    scanf("%s", &name);

    printf("Enter student id: ");
    scanf("%s", &id);

    printf("Enter course name: ");
    scanf("%s", &course_name);

again:
    printf("Enter no of units: ");
    scanf("%d", &no_of_units);

    if (no_of_units > MAX_NO_OF_UNITS && no_of_units <= 0)
    {
        printf("\nyou cannot input the units bigger than %d or less than 0\n", MAX_NO_OF_UNITS);
        getchar();
        goto again;
    }

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

    printf("\nRecord saved successfully!\n");

    // reload data into linked list again
    // read_file();

    // show back the all results
    display_students();
}

void read_file()
{
    // release nodes
    // we need to clean up the memory
    if (head != NULL)
    {
        STUDENT *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            free(temp);
        }
    }

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

        no_of_units = atoi(no);
        for (int j = 0; j < no_of_units; j++)
        {
            char mark[BUFFER_SIZE];

            fgets(mark, sizeof mark, file);
            sscanf(mark, "%d", &marks[j]);
        }

        // add into linked list
        add_student(student_name, student_id, course_name, no_of_units, marks);
    }

    fclose(file);
}

void quite()
{
    printf("\nGoodbye!");
    exit(EXIT_SUCCESS);
}

void release(STUDENT *data)
{
    if (data == NULL)
    {
        return;
    }

    // free the nodes
    // because it can be use in memory
    // we need to clear it first
    // before we re-initailize the new data
    STUDENT *temp;
    while (data != NULL)
    {
        temp = data;
        data = data->next;
        free(temp);
    }
}