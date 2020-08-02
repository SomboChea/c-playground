#include <stdlib.h>
#include <stdio.h>

struct book
{
    char *title;
    char *author;
    char *isbn;
    struct book *next;
};

typedef struct book BOOK;

FILE *file;
BOOK *head;

void add_book(char *title, char *author, char *isbn);
void display();
int count();
void save_book_data(struct book *selection);

int main()
{
    head = NULL;
    add_book("My Third Book", "Zero 1", "000-000-111");
    add_book("My Fouth Book", "1 Zero", "111-000-000");
    add_book("My Fouth Book", "1 Zero", "111-000-000");

    int i;
    file = fopen("./data/books.txt", "a+");

    if (file == NULL)
    {
        printf("Error: addressbook.dat could not be opened.\n");
        return EXIT_FAILURE;
    }

    char title[20];
    char author[20];
    char isbn[20];

    while (!feof(file))
    {
        fgets(title, 20, file);
        fgets(author, 20, file);
        fgets(isbn, 20, file);

        // Removes newline characters from the ends of the names
        i = 0;

        while (title[i] != '\n')
        {
            i++;
        }

        title[i] = '\0';

        i = 0;

        while (author[i] != '\n')
        {
            i++;
        }

        author[i] = '\0';

        // Adds the entry from the strings with the file data in them
        add_book(title, author, isbn);
    }

    // close the file
    fclose(file);

    // display();

    int countEntries = count();
    printf("There are %d entries\n", countEntries);

    return EXIT_SUCCESS;
}

void add_book(char *title, char *author, char *isbn)
{
    struct book *tempNode, *iterator;
    tempNode = (struct book *)malloc(sizeof(struct book));
    tempNode->title = title;
    tempNode->author = author;
    tempNode->isbn = isbn;
    iterator = head;

    if (head == NULL)
    {
        head = tempNode;
        head->next = NULL;
    }
    else
    {
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
        }
        tempNode->next = NULL;
        iterator->next = tempNode;
    }
}

int count()
{
    int n = 1;
    BOOK *temp;
    temp = head;
    if (head == NULL) {
        return 0;
    }

    while (temp->next != NULL)
    {
        n++;
        temp = temp->next;
    }

    return n;
}