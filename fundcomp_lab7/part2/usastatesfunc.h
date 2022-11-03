#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<strings.h>

// DECLARATION OF STRUCTS
typedef struct State_struct {
    char abb[5];
    char name[30];
    char capital[30];
    int year;
} State;

void printmenu(int *);

// functions user selects
void listalldata(State [], int);
void option2(State [], int);
void option3(State [], int);
void option4(State [], int);
void option5(State [], int);
void option6(State [], int);
void option7(State [], int);