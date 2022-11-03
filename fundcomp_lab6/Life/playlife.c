// playlife.c by Joao Henares
// CSE 20311.01 - ND 2022
// Made to practice C and understand modular compiling

#include<stdio.h>
#include"lifefunc.h"
#include <unistd.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
    // board and size of board
    int board[40][40] = {0};
    int boardmirror[40][40] = {0};
    int nrows = sizeof(board)/sizeof(board[0]);
    int ncols = sizeof(board[0])/sizeof(board[0][0]);

    // user inputs
    char userchoice = 'z';
    int userrow, usercol;

    // files
    FILE *fp;
    char p;

    if (argc == 1) { // interactive mode

        // game title and instructions
        printf("Life: interactive game\nInput a to add a new cell\nInput r to remove a cell\n");
        printf("Input n to advance to the next iteration by applying game rules\nInput p to play the program nonstop (CTRL+C to quit)\nInput q or CTRL+C to quit\n");

        // while loop to keep user inside program
        while(userchoice != 'q') {

            // prompt user to input choice
            printf("Choice: ");
            scanf(" %c", &userchoice);

            // process user input
            if (userchoice == 'a') { // add
                printf("Coordinates: ");
                scanf(" %d %d", &userrow, &usercol);
                board[userrow-1][usercol-1] = 1;
                printboard(board, nrows, ncols);
            }
            else if (userchoice == 'r') { // remove
                printf("Coordinates: ");
                scanf(" %d %d", &userrow, &usercol);
                board[userrow-1][usercol-1] = 0;
                printboard(board, nrows, ncols);
            }
            else if (userchoice == 'n') { // next iteration
                applyrules(board, nrows, ncols, boardmirror);
                printboard(board, nrows, ncols);
            }
            else if (userchoice == 'p') { // play
                while(1) {
                applyrules(board, nrows, ncols, boardmirror);
                printboard(board, nrows, ncols);
                sleep(1); // I USED SLEEP BECAUSE USLEEP DID NOT SEEM TO WORK
                }
            }
        }

    }

    else if (argc == 2) { // batch mode
        //getchar();
        fp = fopen(argv[1], "r"); // connect to file
        if(!fp) { // check for existence
            printf("File not found. \n");
            return 1; 
        }

        while(1) // read file
        {
            // fgets(ch, 8,fp); // get line on txt
            p = fgetc(fp);
            if (feof(fp)) break; // break in end
            if(p == 'a') // adding mode
            {
                fscanf(fp,"%d", &userrow); // get user row and col
                fscanf(fp,"%d", &usercol);
                board[userrow][usercol] = 1; // put into board
                fgetc(fp); // eliminates spaces
            }
            else if(p == 'p') // play 
            {
                 while(1) {
                printboard(board, nrows, ncols);
                applyrules(board, nrows, ncols, boardmirror); 
                sleep(1); // I USED SLEEP BECAUSE USLEEP DID NOT SEEM TO WORK
                }
            } 
            else {
                printf("There is something wrong with this file\n"); // just to debug stuff
            }
        }
    }

    else { // error
        printf("Error: put at most one argument other than ./playlife.\n");
        return 1;
    }

    return 0;
}