#include<stdio.h>
#include"usastatesfunc.h"

void printmenu(int *up){
    int choice;
    printf("Input 1 to list all data\n"); 
    printf("Input 2 to list a state's info based on abbreviation\n"); 
    printf("Input 3 to list a state's info based on name\n"); 
    printf("Input 4 to list a state's capital based on its abbreviation\n"); 
    printf("Input 5 to list a state's capital based on its name\n"); 
    printf("Input 6 to list states who joined a given year\n");
    printf("Input 7 to list states who joined each year\n"); 
    printf("Input 8 to quit\nOption: ");
    scanf("%d", &*up);
    getchar();
}

void listalldata(State states[], int size)
{
    int i;
    for(i=0; i<size;i++) // iterate states and print info
    {
        printf("Abbreviation: %s; Name: %s; Capital: %s; Year: %d\n", states[i].abb, states[i].name, states[i].capital, states[i].year);
    }
    printf("\n");
}

void option2(State states[], int size)
{
    char abb[3];
    printf("State abbreviation: ");
    scanf("%s", abb); // get state abbreviation
    getchar();
    int i, hasfound = 0;
    for(i=0; i<size;i++) // get state from array
    {
        if(strcasecmp(abb, states[i].abb) == 0) { // print it 
        printf("Abbreviation: %s; Name: %s; Capital: %s; Year: %d\n", states[i].abb, states[i].name, states[i].capital, states[i].year);
        hasfound = 1;
        }
    }
    if(hasfound == 0)
    {
        printf("State not found.\n");
    }
    printf("\n");
}

void option3(State states[], int size)
{
    char name[30], namewithoutnewline[30]; // had to create two name variables
    printf("State name: ");                // because i was having a problem with
    fgets(name, 29, stdin);                // the \n from fgets
                                           // so I eliminated it
    strcpy(namewithoutnewline, strtok(name, "\n"));
    int i, hasfound = 0;
    for(i=0; i<size;i++) // get state from array
    {
        if(strcasecmp(namewithoutnewline, states[i].name) == 0) { // print it
            printf("Abbreviation: %s; Name: %s; Capital: %s; Year: %d\n", states[i].abb, states[i].name, states[i].capital, states[i].year);
            hasfound = 1;
        }
    }
    if(hasfound == 0)
    {
        printf("State not found.\n");
    }
    printf("\n");
}

void option4(State states[], int size)
{
    char abb[3];
    printf("State abbreviation: ");
    scanf("%s", abb); // get state abbreviation
    getchar();
    int i, hasfound = 0;
    for(i=0; i<size;i++) // get state from array
    {
        if(strcasecmp(abb, states[i].abb) == 0) { // print it 
        printf("Capital: %s\n", states[i].capital);
        hasfound = 1;
        }
    }
    if(hasfound == 0)
    {
        printf("State not found.\n");
    }
    printf("\n");
}

void option5(State states[], int size)
{
    char name[30], namewithoutnewline[30]; // had to create two name variables
    printf("State name: ");                // because i was having a problem with
    fgets(name, 29, stdin);                // the \n from fgets
                                           // so I eliminated it
    strcpy(namewithoutnewline, strtok(name, "\n"));
    int i, hasfound = 0;
    for(i=0; i<size;i++) // get state from array
    {
        if(strcasecmp(namewithoutnewline, states[i].name) == 0) { // print it
            printf("Capital: %s\n", states[i].capital);
            hasfound = 1;
        }
    }
    if(hasfound == 0)
    {
        printf("State not found.\n");
    }
    printf("\n");
}

void option6(State states[], int size)
{
    int year;
    printf("Year: ");
    scanf("%d", &year); // get year
    getchar();
    int i, hasfound = 0; // hasfound controls what happens in multiple outputs
    for(i=0; i<size;i++) // get state from array
    {
        if (hasfound == 1) {
            if(year == states[i].year) { // print it 
                printf("%s ", states[i].name);
            }
        }
        else
        {
            if(year == states[i].year) { // print it 
                printf("States: %s ", states[i].name);
                hasfound = 1;
            }
        }
    }
    if(hasfound == 0)
    {
        printf("There are no states for this year.\n");
    }
    printf("\n");
}

void option7(State states[], int size)
{
    int i;
    int j;
    int iprinted; // iprinted controls what happens in multiple outputs
    for(i=0; i<2100;i++) // go from year to year
    {
        iprinted = 0;
        for(j=0; j<size;j++) // go from state to state
        {
            if(iprinted == 0)
            {
                if(states[j].year == i)
                {
                    iprinted = 1;
                    printf("%d: ", i);
                }
            }
            if(iprinted == 1)
            {
                if(states[j].year == i)
                {
                    printf("%s, ", states[j].name);
                }
            }
        }
        if (iprinted == 1)
        {
            printf("\n");
        }
    }
    printf("\n");
}