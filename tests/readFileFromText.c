#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
    char *text;
    struct list *next;
};

typedef struct list LIST;

int main(void)
{
    FILE *file;
    char line[128];
    LIST *current, *head;

    head = current = NULL;
    file = fopen("./data/test.txt", "r");

    while (fgets(line, sizeof(line), file))
    {
        LIST *node = malloc(sizeof(LIST));
        node->text = strdup(line);
        node->next = NULL;

        if (head == NULL)
        {
            current = head = node;
        }
        else
        {
            current = current->next = node;
        }
    }

    // close the file
    fclose(file);

    for (current = head; current; current = current->next)
    {
        printf("%s", current->text);
    }

    return 0;
}