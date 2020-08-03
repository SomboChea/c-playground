#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DEPOT_SIZE 10

struct Bus
{
    int BusID;
    int RouteID;
    time_t schedule;
} Depot[DEPOT_SIZE];

typedef enum { true, false } bool;

void createBuses();
void printBuses();
void scheduleBuses();
void alignupBuses();
void releaseBuses();
void emergency();

// utils variable
bool has_created = false;

// utils function
print_depot(struct Bus *depot);

int main()
{
    return EXIT_SUCCESS;
}

void createBuses()
{
    for (int i = 0; i < DEPOT_SIZE; i++)
    {
        Depot[i].BusID = i + 1;
        Depot[i].RouteID = 1000 + (i + i);
    }

    has_created = true;
}

print_depot(struct Bus *depot) {
    int size = sizeof(depot) / sizeof(depot[0]);

    printf("\n Depost size: %d", size);
    for (int i = 0; i < size; i++) {
        printf("Bus ID: %d\n", depot[i].BusID);
        printf("Route ID: %d\n", depot[i].RouteID);
    }
}