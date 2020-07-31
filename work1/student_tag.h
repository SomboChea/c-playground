#include "./person_tag.h"
#include "./course_tag.h"

struct student_tag
{
    struct person_tag student_info;
    struct course_tag course_info;
    struct student_tag *next;
};
