#include "stdio.h"
#include "./function.c"
#include "./../util/define.h"
#include "./student_tag.h"
#include "./person_tag.h"

void menu()
{
    printf("\n\n\n-------------------MENU-------------------\n");
    printf("\n(1) Display students’ details\n");
    printf("\n(2) Search for a student’s mark\n");
    printf("\n(3) Find the details of student with the largest average\n");
    printf("\n(4) Find the details of failed students\n");
    printf("\n(5) Add new student to the record\n");
    printf("\n(6) Quit program\n\n");
}



void choose_menu(int menu)
{

    switch (menu)
    {
    case MENU_1:
        display();
        break;
    case MENU_2:
        search(1);
        break;
    case MENU_3:
        find_largest_average();
        break;
    case MENU_4:
        find_failed_students();
        break;
    case MENU_5:
    
        struct person_tag info = {"1","Sambo"};
        struct student_tag std = {.student_info = info};
        add_new(std);
        break;
    case MENU_6:
        quite();
        break;
    default:
        printf("not found!");
        break;
    }
}