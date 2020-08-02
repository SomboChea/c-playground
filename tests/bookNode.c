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
void add_book_data();
void save_book_data(struct book *data);
void read_file_to_data();
void print_data(BOOK *data);

int main()
{
    head = NULL;

    int countEntries = count();
    printf("There are %d entries\n", countEntries);

    // add book data
    add_book_data();
    
    // display the books
    display();

    return EXIT_SUCCESS;
}

void add_book(char *title, char *author, char *isbn)
{
    struct book *temp, *iterator;
    temp = (struct book *)malloc(sizeof(struct book));
    temp->title = title;
    temp->author = author;
    temp->isbn = isbn;
    // ref
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

int count()
{
    int n = 1;
    BOOK *temp;
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

void add_book_data()
{
    add_book("My Third Book", "Zero 1", "000-000-111");
    add_book("My Fouth Book", "1 Zero", "111-000-000");
    add_book("My Fifth Book", "2 Zero", "222-000-000");

    int i;
    file = fopen("./data/books.txt", "a+");

    if (file == NULL)
    {
        printf("Error: addressbook.dat could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    BOOK *temp;
    temp = head;

    fputs(temp->title, file);
    fputs("\n", file);
    fputs(temp->author, file);
    fputs("\n", file);
    fputs(temp->isbn, file);

    while (temp->next != NULL)
    {
        temp = temp->next;
        fputs("\n", file);
        fputs(temp->title, file);
        fputs("\n", file);
        fputs(temp->author, file);
        fputs("\n", file);
        fputs(temp->isbn, file);
    }

    // close the file
    fclose(file);
}

void save_book_data(struct book *data)
{
    file = fopen("./data/books.txt", "a+");

    if (file == NULL)
    {
        printf("Error: addressbook.dat could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    BOOK *temp;
    temp = data;

    if (temp == NULL)
    {
        return;
    }

    fputs(temp->title, file);
    fputs(temp->author, file);
    fputs(temp->isbn, file);

    while (temp->next != NULL)
    {
        temp = temp->next;

        fputs(temp->title, file);
        fputs(temp->author, file);
        fputs(temp->isbn, file);
    }

    fflush(file);
    fclose(file);
}

void read_file_to_data()
{
    // clear head in linked list
    head = NULL;

    FILE *file;

    file = fopen("./data/books.txt", "r");

    if (file == NULL)
    {
        printf("cannot read file!");
        exit(EXIT_FAILURE);
    }

    char title[20];
    char author[20];
    char isbn[20];
    int i;

    while (!feof(file))
    {
        fgets(title, 20, file);
        fgets(author, 20, file);
        fgets(isbn, 20, file);

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

        add_book(title, author, isbn);
    }

    fclose(file);
}

void display()
{
    read_file_to_data();
    print_data(head);
}

void print_data(BOOK *book)
{
    BOOK *temp;
    temp = book;
    if (temp == NULL)
    {
        printf("book is empty!");
        return;
    }

    printf("Book title: %s\n", temp->title);
    printf("Book author: %s\n", temp->author);
    printf("Book isbn: %s", temp->isbn);

    while (temp->next != NULL)
    {
        temp = temp->next;
        printf("\nBook title: %s\n", temp->title);
        printf("Book title: %s\n", temp->title);
        printf("Book title: %s", temp->title);
    }
}