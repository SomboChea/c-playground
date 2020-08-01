#include "stdio.h"
#include "stdlib.h"

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;
void add_first(int);
void add_last(int);
void traverse();
void remove_first();
void remove_last();
int count = 0;
void display_menu();

int main(void) {
    printf("Welcome!\n");

    int selected, data;

    while (1) {
        if (count == 100) {
            exit(EXIT_SUCCESS);
        }

        // show menu
        display_menu();
    }

    printf("\nGoodbye!");
    return 0;
}

void display_menu() {

    printf("1. Add first element\n");
    printf("2. Add last element\n");
    printf("3. Traverse element\n");
    printf("4. Remove first element\n");
    printf("5. Remove last element\n");

}

void add_first(int element) {
    // init node
    struct node *node;

    // allocate the node for linkedlist
    node = (struct node*)malloc(sizeof(struct node));

    // add the data into node
    node->data = element;

    // count the nodes, that added into data
    count++;

    // check the head, if null put the data into it
    if (head == NULL) {
        // replace the node into head
        head = node;

        // set the next of head into null
        head->next = NULL;

        // return or end this process
        return;
    }

    node->next = head;
    head = node;
}