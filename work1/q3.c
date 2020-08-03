#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DEPOT_SIZE 10

struct Bus {
    int BusID;
    int RouteID;
    time_t schedule;
} Depot[DEPOT_SIZE];

void createBuses();
void printBuses();
void scheduleBuses();
void alignupBuses();
void releaseBuses();
void emergency();

int main() {

    return EXIT_SUCCESS;
}

void createBuses() {
    // do something
}