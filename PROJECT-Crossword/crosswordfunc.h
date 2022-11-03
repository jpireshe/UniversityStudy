#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

// define macros

#define NUMWORDS 20 // size of word array
#define BOARDSIZE 15
#define BOARDCENTER 7 // board size, center

// structs
typedef struct word_struct {
    char str[BOARDSIZE]; // its string
    int size; // size of the word
    int type; // 0 for horizontal, 1 for vertical
    int posx; // position in x
    int posy; // position in y
    int printed; // check if it has been printed
} Word;

// FUNCTIONS
void printmenu(); // print start menu
void getinput(Word *, int *); // fill vector
void printsolution(Word *, int, Word []); // print the solution part
void printpuzzleboard(char [BOARDSIZE][BOARDSIZE]); // print only the puzzle
int structcompare(const void *, const void *); // used by qsort, probably will not use it.
void horizontalwordfunc(Word *, Word *, int *, char [BOARDSIZE][BOARDSIZE]);
void verticalwordfunc(Word *, Word *, int *, char [BOARDSIZE][BOARDSIZE]);
void printfilesolution(FILE *, Word *, int, Word []); // print the solution part
void printfilepuzzleboard(FILE *, char [BOARDSIZE][BOARDSIZE]); // print only the puzzle
void randomizeword(char [], char [], int); // word randomizing algorithm
void printclues(Word *, char [NUMWORDS][BOARDSIZE], int); // print clues (normal and file version)
void fileprintclues(FILE *, Word [], char [NUMWORDS][BOARDSIZE], int);
