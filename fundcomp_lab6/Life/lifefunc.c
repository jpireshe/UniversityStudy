#include<stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include"lifefunc.h"

void printboard(int board[40][40], int nrows, int ncols) { // prints board

    system("clear"); // clear screen

    int irow, icol = 0; // iterate through board

    printf(" "); // these random printf are just to make the board look all nice

    for (icol = 0; icol < ncols; icol++)
        printf("-"); // print top side of board

    printf("\n"); // new line after top of board

    for (irow = 0; irow < nrows; irow++)
    {

        printf("|"); // left  side of board

        for(icol = 0; icol < ncols; icol++)
        {

            if (board[irow][icol] == 0)
                printf(" ");
            else   
                printf("x"); // oprint only what is alive
    
        }

        printf("|\n");   // right side of board     
    }

    printf(" ");
    for (icol = 0; icol < ncols; icol++)
        printf("-"); // bottom part of board
    printf("\n");
}

void applyrules(int board[40][40], int nrows, int ncols, int boardmirror[40][40]) {
    // make board 2 mirror of board 1 to apply rules
    int irow, icol;

    for (irow = 0; irow < nrows; irow++)
    {
        for(icol = 0; icol < ncols; icol++)
        {
            boardmirror[irow][icol] = board[irow][icol];
        }
    }

    // iterate through normal board and look at mirror board to apply rules
    for (irow = 0; irow < nrows; irow++)
    {
        for(icol = 0; icol < ncols; icol++)
        {
               if(irow == 0) // first column (1, x): special case
               {
                   if(icol == 0) // cell at (1,1) on table: special case
                   {
                       if(boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol+1] == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if (boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol+1] == 2) {} // do nothing
                       else
                       {
                           board[irow][icol] = 0; // underpopulation
                       }
                   }

                   else if (icol == 39) // cell at (1, 40) - no overpopulation
                   {
                       if(boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol - 1] + boardmirror[irow][icol-1] == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if (boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol - 1] + boardmirror[irow][icol-1] == 2) {} // do nothing
                       else
                       {
                           board[irow][icol] = 0; // underpopulation
                       }
                   }

                   else // cell at (1, 2-39)
                   {
                       if ((boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol - 1] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol + 1] + boardmirror[irow][icol -1]) == 3)
                       {
                           board[irow][icol] = 1; // getting alive by reproduction
                       }
                       else if ((boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol - 1] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol + 1] + boardmirror[irow][icol -1]) == 2)
                       { // stays alive or stays dead. no action needed 
                       }
                       else
                       {
                           board[irow][icol] = 0; // dies by overpopulation or underpopulation
                       }
                   }
               }
               else if(irow == 39) // cell at row 40
               {
                   if(icol == 0) // cel at (40,1)
                   {
                       if((boardmirror[irow][icol + 1] + boardmirror[irow - 1][icol] + boardmirror[irow - 1][icol + 1]) == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if((boardmirror[irow][icol + 1] + boardmirror[irow - 1][icol] + boardmirror[irow - 1][icol + 1]) == 2)
                       { //stays alive or dead
                       }
                       else
                       {
                           board[irow][icol] = 0; // dies due to over or underpopulation
                       }
                   }
                   else if (icol == 39) // cell at (40,40)
                   {
                       if((boardmirror[irow][icol - 1] + boardmirror[irow - 1][icol - 1] + boardmirror[irow - 1][icol]) == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if((boardmirror[irow][icol - 1] + boardmirror[irow - 1][icol - 1] + boardmirror[irow - 1][icol]) == 2)
                       { //stays alive or dead
                       }
                       else
                       {
                           board[irow][icol] = 0; // dies due to over or underpopulation
                       }
                   }
                   else // cell at rest of row 40
                   {

                   }
               }

               else { // cell at rows 2 - 39

                   if(icol == 0) // corners of non top/bottom parts - left part
                   {
                       if((boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol + 1] + boardmirror[irow - 1][icol] + boardmirror[irow - 1][icol + 1]) == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if((boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol + 1] + boardmirror[irow - 1][icol] + boardmirror[irow - 1][icol + 1]) == 2)
                       { //stays alive or dead
                       }
                       else
                       {
                           board[irow][icol] = 0; // dies due to over or underpopulation
                       }
                   }

                   else if (icol == 39) // corners of non top/ bottom parts - right part
                   {
                       if((boardmirror[irow + 1][icol - 1] + boardmirror[irow + 1][icol] + boardmirror[irow][icol - 1] + boardmirror[irow - 1][icol - 1] + boardmirror[irow - 1][icol]) == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if((boardmirror[irow + 1][icol - 1] + boardmirror[irow + 1][icol] + boardmirror[irow][icol - 1] + boardmirror[irow - 1][icol - 1] + boardmirror[irow - 1][icol]) == 2)
                       { //stays alive or dead
                       }
                       else
                       {
                           board[irow][icol] = 0; // dies due to over or underpopulation
                       }
                   }

                   else // not corners, all these have 8 cells around them
                   {
                       if((boardmirror[irow + 1][icol - 1] + boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol - 1] + boardmirror[irow][icol + 1] + boardmirror[irow - 1][icol - 1] + boardmirror[irow - 1][icol] + boardmirror[irow - 1][icol + 1]) == 3)
                       {
                           board[irow][icol] = 1; // reproduction
                       }
                       else if((boardmirror[irow + 1][icol - 1] + boardmirror[irow + 1][icol] + boardmirror[irow + 1][icol + 1] + boardmirror[irow][icol - 1] + boardmirror[irow][icol + 1] + boardmirror[irow - 1][icol - 1] + boardmirror[irow - 1][icol] + boardmirror[irow - 1][icol + 1]) == 2)
                       { //stays alive or dead
                       }
                       else
                       {
                           board[irow][icol] = 0; // dies due to over or underpopulation
                       }
                   }
               }  
        }
    }
}