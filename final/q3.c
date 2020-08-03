#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define DEPOT_SIZE 10

struct Bus
{
    int BusID;
    int RouteID;
    time_t schedule;
} Depot[DEPOT_SIZE];

typedef enum
{
    true,
    false
} bool;

void createBuses();
void printBuses();
void scheduleBuses();
void alignupBuses();
void releaseBuses();
void emergency();

// utils variable
bool has_created = false;
bool has_scheduled = false;
bool has_aligned = false;
int top = -1;

// utils function
void clrscr();
void print_depot(struct Bus *depot);

time_t get_random_time();

void confirm_on_finish();
int quicksort_compare_func(const void *elem1, const void *elem2);
bool isEmpty();
int menu();

void remove_index_of_array(int index);

// Main Function
int main()
{
    while (1)
    {
        int selection = menu();
        clrscr();
        printf("You Select : %d", selection);
        printf("\n");

        switch (selection)
        {
        case 1:
            createBuses();
            break;
        case 2:
            printBuses();
            break;

        case 3:
            scheduleBuses();
            break;
        case 4:
            alignupBuses();
            break;

        case 5:
            releaseBuses();
            break;

        case 6:
            emergency();
            break;

        default:
            printf("You are enter incorrect option number");
        }

        confirm_on_finish();
    };

    return EXIT_SUCCESS;
}

int menu()
{
    fflush(stdout);

    clrscr();

    printf("\nQuestion 3 ");
    printf("\n=========================================");
    printf("\n");
    printf("\n1. Create Buses");
    printf("\n2. Print Buses");
    printf("\n3. Schedule Buses");
    printf("\n4. Align up Buses");
    printf("\n5. Release Buses");
    printf("\n6. Emergency Buses");

    int chosen;
    printf("\n\nEnter Your Selection : ");
    scanf("%d", &chosen);
    return chosen;
}

void createBuses()
{

    if (has_created == true)
    {
        printf("\nYou have created already...");
        return;
    }

    printf("\n\nStart Create Buses...");

    for (int i = 0; i < DEPOT_SIZE; i++)
    {
        top++;
        Depot[i].BusID = i + 1;
        Depot[i].RouteID = 1000 + (i + i);
        printf("\n - Starting Create Bus %d", i + 1);
    }

    has_created = true;

    printf("\nFinish Created Buses");
}

void printBuses()
{
    if (has_created == false)
    {
        printf("\nPlease Create Buses First!");
        return;
    }
    print_depot(Depot);
}

void scheduleBuses()
{
    if (has_created == false)
    {
        printf("\nPlease Create Buses First!");
        return;
    }

    printf("\nStart Scheduling Buses...\n\n");

    size_t currentLen = sizeof(Depot) / sizeof(Depot[0]);

    for (int i = 0; i < currentLen; i++)
    {
        printf("\n  - Start Random Schedule %d...", i);

        Depot[i].schedule = get_random_time();
    }

    printf("\n\nEnd Scheduling Buses...");

    has_scheduled = true;
}

void print_depot(struct Bus *depot)
{

    size_t currentLen = sizeof(Depot) / sizeof(*Depot);

    for (int i = 0; i < top; i++)
    {
        printf("Bus ID: %d\n", depot[i].BusID);
        printf("Route ID: %d\n", depot[i].RouteID);

        char *scheduleForShow = "";
        if (depot[i].schedule != 0)
        {
            scheduleForShow = ctime(&depot[i].schedule);
        }

        printf("Schdule Time : %s\n\n", scheduleForShow);
    }
}

void alignupBuses()
{
    if (has_scheduled == false)
    {
        printf("\n\nYou are not scheduling buses yet ...");
        return;
    }
    size_t currentLen = sizeof(Depot) / sizeof(Depot[0]);

    qsort(Depot, sizeof(Depot) / sizeof(*Depot), sizeof(*Depot), quicksort_compare_func);

    printf("\n\nFinish Align up Buses Schedule ... ");
    has_aligned = true;
}

void releaseBuses()
{
    if (has_aligned == false)
    {
        printf("\n\nYou are not align buses schedule yet ...");
        return;
    }

    int last_index = sizeof(Depot) / sizeof(*Depot) - 1;

    remove_index_of_array(last_index);

    printf("\n\nRelease Complete...\n\n");
}

void emergency()
{
    if (has_aligned == false)
    {
        printf("\n\nYou are not align buses schedule yet ...");
        return;
    }

    remove_index_of_array(0);

    printf("\n\nRelease Complete...\n\n");
}

void remove_index_of_array(int remove_index)
{

    int current_len = sizeof(Depot) / sizeof(*Depot);
    memmove(Depot + remove_index, Depot + remove_index + 1, (sizeof(Depot) - remove_index - 1) * sizeof(*Depot));
    top--;
}

time_t get_random_time()
{
    time_t currentTime;

    time(&currentTime);

    long currentTimeNumber = (long)localtime(&currentTime);

    // Random in next 5 hours
    long randomAddOnTime = rand() % (60 * 60 * 5);

    long additionTime = currentTimeNumber + randomAddOnTime;

    return additionTime;
}

void clrscr()
{
    system("clear");
}

void confirm_on_finish()
{

    printf("\n\nPress Enter to Back to Menu...");

    getchar();
    getchar();
}

bool isFull()
{
    return top == -1;
}

int quicksort_compare_func(const void *elem1, const void *elem2)
{
    struct Bus element1 = *((struct Bus *)elem1);
    struct Bus element2 = *((struct Bus *)elem2);
    if (element1.schedule > element2.schedule)
        return -1;
    if (element1.schedule < element2.schedule)
        return 1;
    return 0;
}