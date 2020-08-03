#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STUDENT_ID_SIZE 10
#define CHAR_INT '0'

struct studentID
{
    int value;
    struct studentID *next;
};

typedef struct studentID STUDENTID;
typedef STUDENTID *STUDENTIDPtr;

int main()
{

    const char student_id[] = "1001245345";

    // 1. creation nodes
    size_t student_id_len = sizeof(student_id) / sizeof(student_id[0]) - 1;

    STUDENTIDPtr student_ptr_1 = (STUDENTIDPtr)malloc(sizeof(STUDENTID));
    STUDENTIDPtr student_ptr_2 = (STUDENTIDPtr)malloc(sizeof(STUDENTID));
    STUDENTIDPtr student_ptr_3 = (STUDENTIDPtr)malloc(sizeof(STUDENTID));
    STUDENTIDPtr student_ptr_4 = (STUDENTIDPtr)malloc(sizeof(STUDENTID));
    STUDENTIDPtr student_ptr_5 = (STUDENTIDPtr)malloc(sizeof(STUDENTID));

    student_ptr_1->next = student_ptr_2;
    student_ptr_2->next = student_ptr_3;
    student_ptr_3->next = student_ptr_4;
    student_ptr_4->next = student_ptr_5;
    student_ptr_5->next = NULL;

    // 2. fill the node's values
    STUDENTIDPtr temp = student_ptr_1;
    int last_len = 5;
    while (temp != NULL)
    {
        temp->value = student_id[student_id_len - last_len] - CHAR_INT;
        temp = temp->next;
        last_len--;
    }

    // 3. removes dup
    STUDENTIDPtr temp1, temp2, duplicate;
    temp1 = student_ptr_1;

    while (temp1 != NULL && temp1->next != NULL)
    {
        temp2 = temp1;

        while (temp2->next != NULL)
        {
            if (temp1->value == temp2->next->value)
            {
                duplicate = temp2->next;
                temp2->next = temp2->next->next;
                free(duplicate);
            }
            else
                temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    // output the result
    while (student_ptr_1 != NULL)
    {
        printf("%d ", student_ptr_1->value);
        student_ptr_1 = student_ptr_1->next;
    }

    printf("\n");

    return EXIT_SUCCESS;
}
