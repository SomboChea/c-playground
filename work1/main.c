#include "stdio.h"
#include "stdlib.h"
#include "./../util/constants.h"
#include "./../util/utils.c"
#include "./menu.c"

int main()
{
    printf("\nInitializing program...\n");
    clrscr();

    char c;
    FILE *file;

    // check the file has load or not
    // if not load correctly or file not, it must be exit the program
    if ((file = fopen(WELCOME_FILE_DATA, "r")) == NULL)
    {
        printf("Cannot open file!\n");
        exit(1);
    }

    // read the file into output screen
    // if it's not meet the end of file it will run till the end of data
    while ((c = getc(file)) != EOF)
    {
        printf("%c", c);
    }

    // close the welcome file
    fclose(file);

    // show menu
    menu();

}