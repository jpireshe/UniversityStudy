#include"crosswordfunc.h"

void printmenu() {
    printf("Anagram Crossword Puzzle Generator\n----------------------------------\n");
}

void getinput(Word *wp, int *wcp) {
    char word[15]; // initial word input
    int proper = 0, foundnum = 0, i; // evaluate what the user has input

    scanf("%s", word);
    getchar(); // not to mess file i/o

    for(i = 0; i < strlen(word); i++)
    {
        if (!isalpha(word[i])) {
            foundnum = 1; // flag as wrong if it has any non-alphabetic algarisms
        }
    }

    if(strlen(word) == 0 || strlen(word) == 1 || strlen(word) > 15) {foundnum = 1;} // filter small or big inputs

    // Check if strcmp(word, ".") == 0, if yes, return function
    // return;

    if(foundnum == 0)
    {
        proper = 1;
    }
    else
    {
        if(strcmp(word, ".") == 0)
        {
            proper = 1; // to not print error if "." is input ( to end the loop )
        }
    }

    if(proper == 1)
    {
        strcpy(wp->str, word); // now put in word array
        wp++; // increase count
        // increase word count and pointer
        if(strcmp(word, ".") != 0) {
            *wcp = *wcp + 1;
        }
    }
    else
    {
        printf("Invalid word.\n"); // if after all it was a bad input just print it.
    }
}

void printsolution(Word *wp, int wordcount, Word words[]) {

    // declare variables
        int i, j, k, counter = wordcount, found = 0, *foundpointer, iterating = 0; // loop control
        Word *firstword, *lastword, tempword; // loop control struct pointers.
        firstword = wp; // to not lose the first word if i need it.
        foundpointer = &found; // points to found (will call in other functions)

        Word lostwords[19]; // put words that were not initially printed here (in case i try the extra credit)
        int lostcount = 0;

    // create empty board
        char board[BOARDSIZE][BOARDSIZE];
        for(i = 0; i < BOARDSIZE; i++)
        {
            for(j = 0; j < BOARDSIZE; j++)
            {
                board[i][j] = '.';
            }
        }
    
    // define the position of the words to be printed
        while(counter > 0)
        {
            lastword = wp;
            found = 0;
            lastword++;
            iterating = 0; 
            *foundpointer = 0;

            if(counter == wordcount) // BIGGEST WORD
            {
                // put biggest one into the board (Always horizontal)
                for(i = 0; i < strlen(wp->str); i++)
                {
                    board[BOARDCENTER][(BOARDSIZE-strlen(wp->str))/2+i] = wp->str[i];
                }
                wp->posx = (BOARDSIZE-strlen(wp->str))/2; // define pos x and y, flag it as printed and as horizontal.
                wp->posy = BOARDCENTER;
                wp->printed = 1;
                wp->type = 0;
            }

            else // 4TH WORD - NEW STANDARD (TRYING TO MAKE IT UNIVERSAL)
            {   
                while(iterating < wordcount - counter) // (while you still have words to iterate on)
                {
                    if(found == 1) // go to next word if the "found" flag is activated (to not print multiple times)
                    {
                        break;
                    }

                    if(lastword->printed == 1) // check if the word you are trying to print on has been printed
                    {

                        if(lastword->type == 0) // horizontal lastword 
                        {
                            horizontalwordfunc(wp, lastword, foundpointer, board);
                            if (found == 1) // FOUND LETTER IN COMMON (and it is in a valid position)
                            {
                                for(k = 0; k<strlen(wp->str); k++) // print
                                {
                                    board[wp->posy+k][wp->posx] = wp->str[k];
                                }
                                wp->printed = 1; // flag as printed and vertical
                                wp->type = 1;
                            }
                        }
                        else if(lastword->type == 1) // vertical lastword 
                        {
                            verticalwordfunc(wp, lastword, foundpointer, board);
                            if (found == 1)
                            {
                                for(k = 0; k<strlen(wp->str); k++)
                                {
                                    board[wp->posy][wp->posx + k] = wp->str[k];
                                }
                                wp->printed = 1; // flag printed and horizontal
                                wp->type = 0;
                            }
                        }
                    }

                    lastword++;
                    iterating++;

                    if(iterating == wordcount-counter && found == 0) // if after all you could not print it
                    {
                        printf("Could not print word '%s'\n", wp->str);
                        wp->printed = 0; // flag to not be iterated on while loop.
                    }
                }
            }

            counter--;
            wp--;
        }

        // print the board
        printf("\nSolution: \n");
        // print top part
        printf(" ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            printf("-");
        }
        printf("\n");

        // print middle
        for(i = 0; i < BOARDSIZE; i++)
        {   
            printf("|");
            for(j = 0; j < BOARDSIZE; j++)
            {
                printf("%c",board[i][j]);
            }
            printf("|\n");
        }

        // print end
        printf(" ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            printf("-");
        }
        printf("\n");

        printpuzzleboard(board);
}

void printpuzzleboard(char board[BOARDSIZE][BOARDSIZE]) { // prints the puzzle board
    int i, j;
    printf("Crossword Puzzle:\n");
    // print top part
        printf(" ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            printf("-");
        }
        printf("\n");

        // print middle
        for(i = 0; i < BOARDSIZE; i++)
        {   
            printf("|");
            for(j = 0; j < BOARDSIZE; j++)
            {
                if(board[i][j] == '.')
                {
                    printf("#");
                }
                else printf(" ");
            }
            printf("|\n");
        }

        // print end
        printf(" ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            printf("-");
        }
        printf("\n");
}

int structcompare(const void * wpsort1, const void * wpsort2) // used by qsort only.
{
    Word *p1 = (Word *)wpsort1;
    Word *p2 = (Word *)wpsort2;

    return strlen(p1->str) - strlen(p2->str);
}

void horizontalwordfunc(Word *wp, Word *lastword, int *foundpointer, char board[BOARDSIZE][BOARDSIZE]) // last word horizontal
{
    int i = 0, j = 0, k, found = 0;
    for(i = 0; i<strlen(lastword->str); i++) // cycle the word that has been printed
                        {
                            for(j = 0; j<strlen(wp->str); j++) // cycle the word you want to print
                            {   
                                if(wp->str[j] == lastword->str[i]) // found same letter
                                {
                                    found  = 1; // flag to check whether to print

                                    wp->posx = lastword->posx + i; // define the position to print on
                                    wp->posy = lastword->posy - j;

                                    for(k = 0; k < strlen(wp->str); k++) // iterate items in the side of our string (check for validity)
                                    {
                                        if(board[wp->posy + k][wp->posx + 1] != '.' && wp->posy + k != lastword->posy)
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy + k][wp->posx - 1] != '.' && wp->posy + k != lastword->posy)
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy + k][wp->posx] != '.' && board[wp->posy + k][wp->posx] != wp->str[k] && wp->posy+k != lastword->posy)
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy -1][wp->posx] != '.')
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy + strlen(wp->str)][wp->posx] != '.')
                                        {
                                            found = 0;
                                        }
                                        // out of bounds
                                        else if(wp->posy + strlen(wp->str) > BOARDSIZE) found = 0; //("down")
                                        else if(wp->posy < 0) found = 0; //("up")
                                        // cannot go out of bounds to left and right (in this function)
                                    }

                                    break;
                                }
                                if(found == 1)
                                {
                                    break;
                                }
                            }
                            
                            if(found == 1) // return to the other function whether it found a common letter and is in a legal position.
                            {
                                    *foundpointer = 1;
                                    break;
                            }
                        }             
}

void verticalwordfunc(Word *wp, Word *lastword, int *foundpointer, char board[BOARDSIZE][BOARDSIZE]) // last word vertical (similar to hor.)
{
    int i = 0, j = 0, k, found = 0;
    found = 0;
    for(i = 0; i<strlen(lastword->str); i++)
                        {
                            for(j = 0; j<strlen(wp->str); j++)
                            {   
                                if(wp->str[j] == lastword->str[i])
                                {
                                    found  = 1; // to know we have found the word
                                    wp->posx = lastword->posx - j; 
                                    wp->posy = lastword->posy + i;

                                    for(k = 0; k < strlen(wp->str); k++) // iterate items in the side of our string
                                    {
                                        if(board[wp->posy + 1][wp->posx + k] != '.' && wp->posx + k != lastword->posx) // word under
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy - 1][wp->posx + k] != '.' && wp->posx + k != lastword->posx) // word above
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy][wp->posx + k] != '.' && board[wp->posy][wp->posx +k] != wp->str[k] && wp->posx+k != lastword->posx) // word in middle
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy][wp->posx -1] != '.') // one to the left
                                        {
                                            found = 0;
                                        }
                                        else if(board[wp->posy][wp->posx + strlen(wp->str)] != '.') // one to the right
                                        {
                                            found = 0;
                                        }
                                        // out of bounds
                                        else if(wp->posx + strlen(wp->str) > BOARDSIZE) {
                                            found = 0; //("right")
                                        }
                                        else if(wp->posx < 0) { //("left")
                                            found = 0;
                                        }
                                    }

                                    break;
                                }
                                if(found == 1)
                                {
                                    break;
                                }
                            }
                            
                            if(found == 1)
                            {
                                    *foundpointer = 1;
                                    break;
                            }
                        }             
}

void printfilesolution(FILE *fwp, Word *wp, int wordcount, Word words[]) { // SAME AS PRINT SOLUTION BUT FILE VERSION

    // declare variables
        int i, j, k, counter = wordcount, found = 0, *foundpointer, iterating = 0; // loop control
        Word *firstword, *lastword, tempword; // loop control structs
        firstword = wp; // i dont want to lose wp
        foundpointer = &found;

        Word lostwords[19]; // put words that were not initially printed here
        int lostcount = 0;

    // create empty board
        char board[BOARDSIZE][BOARDSIZE];
        for(i = 0; i < BOARDSIZE; i++)
        {
            for(j = 0; j < BOARDSIZE; j++)
            {
                board[i][j] = '.';
            }
        }
    
    // define the position of the words to be printed
        while(counter > 0)
        {
            lastword = wp;
            found = 0;
            lastword++;
            iterating = 0; 
            *foundpointer = 0;

            if(counter == wordcount) // BIGGEST WORD
            {
                // put biggest one into the board (Always horizontal)
                for(i = 0; i < strlen(wp->str); i++)
                {
                    board[BOARDCENTER][(BOARDSIZE-strlen(wp->str))/2+i] = wp->str[i];
                }
                wp->posx = (BOARDSIZE-strlen(wp->str))/2; 
                wp->posy = BOARDCENTER;
                wp->printed = 1;
                wp->type = 0;
            }

            else // 4TH WORD - NEW STANDARD (TRYING TO MAKE IT UNIVERSAL)
            {   
                while(iterating < wordcount - counter)
                {
                    if(found == 1)
                    {
                        break;
                    }

                    if(lastword->printed == 1)
                    {

                        if(lastword->type == 0) // horizontal lastword
                        {
                            horizontalwordfunc(wp, lastword, foundpointer, board);
                            if (found == 1) // FOUND LETTER IN COMMON
                            {
                                for(k = 0; k<strlen(wp->str); k++)
                                {
                                    board[wp->posy+k][wp->posx] = wp->str[k];
                                }
                                wp->printed = 1;
                                wp->type = 1;
                            }
                        }
                        else if(lastword->type == 1)// vertical lastword 
                        {
                            verticalwordfunc(wp, lastword, foundpointer, board);
                            if (found == 1) // FOUND LETTER IN COMMON
                            {
                                for(k = 0; k<strlen(wp->str); k++)
                                {
                                    board[wp->posy][wp->posx + k] = wp->str[k];
                                }
                                wp->printed = 1;
                                wp->type = 0;
                            }
                        }
                    }

                    lastword++;
                    iterating++;

                    if(iterating == wordcount-counter && found == 0)
                    {
                        fprintf(fwp, "Could not print word '%s'\n", wp->str);
                        wp->printed = 0;
                    }
                }
            }

            counter--;
            wp--;
        }

        // print the board
        fprintf(fwp, "Solution: \n");
        // print top part
        fprintf(fwp, " ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            fprintf(fwp, "-");
        }
        fprintf(fwp, "\n");

        // print middle
        for(i = 0; i < BOARDSIZE; i++)
        {   
            fprintf(fwp, "|");
            for(j = 0; j < BOARDSIZE; j++)
            {
                fprintf(fwp, "%c",board[i][j]);
            }
            fprintf(fwp, "|\n");
        }

        // print end
        fprintf(fwp, " ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            fprintf(fwp, "-");
        }
        fprintf(fwp, "\n");

        printfilepuzzleboard(fwp, board);
}

void printfilepuzzleboard(FILE *fwp, char board[BOARDSIZE][BOARDSIZE]) {
    int i, j;
    fprintf(fwp, "Crossword Puzzle:\n");
    // print top part
        fprintf(fwp, " ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            fprintf(fwp, "-");
        }
        fprintf(fwp, "\n");

        // print middle
        for(i = 0; i < BOARDSIZE; i++)
        {   
            fprintf(fwp, "|");
            for(j = 0; j < BOARDSIZE; j++)
            {
                if(board[i][j] == '.')
                {
                    fprintf(fwp, "#");
                }
                else fprintf(fwp, " ");
            }
            fprintf(fwp, "|\n");
        }

        // print end
        fprintf(fwp, " ");
        for (i= 0; i < BOARDSIZE; i++)
        {
            fprintf(fwp, "-");
        }
        fprintf(fwp, "\n");
}

void randomizeword(char word[], char randomword[], int size) // make word random
{
    int i = 0, j = 0, randomvalue, count;
    count = 0;
    int worddetector[size];
    char newword[BOARDSIZE]; // we will randomize it and then copy it to randomword

    // fill worddetector with 1s and new word if A's
    for(i=0; i<size; i++)
    {
        worddetector[i] = 1;
        newword[i] = 'A';
    }
    
    while(count < size) // get random letters and make random word
    {
        randomvalue = rand()%size; // get a random value
        if(worddetector[randomvalue] == 1) // if it has not been occupied yet
        {
            worddetector[randomvalue] = 0; // flag it as occupied
            newword[count] = word[randomvalue]; // put it in there
            count++;
        }
    }

    if(size != 2) { // Created a special case for when size = 2 because i was getting a weird @ at the end of every 2 letter word.
        strcpy(randomword, newword); 
    }
    else {
        randomword[0] = newword[0];
        randomword[1] = newword[1];
    }
}

void printclues(Word *wp, char randomwords[NUMWORDS][BOARDSIZE], int wordcount) { // print the clues
    int i;

    printf("\nClues: \n\nLocation | Direction | Anagram\n");

    for(i = 0; i < wordcount; i++)
    {
        if(wp->printed == 1) {
        printf("%4d, %2d |", wp->posx, wp->posy);

        if(wp->type == 0) {printf(" Across    |");}
        else {printf(" Down      |");}

        printf(" %s\n", randomwords[i]);
        }
        wp++;
    }
}

void fileprintclues(FILE *fwp, Word words[], char randomwords[NUMWORDS][BOARDSIZE], int wordcount) { // printf clues file version
    int i;

    fprintf(fwp, "\nClues: \n\n");

    for(i = 0; i < wordcount; i++)
    {
        if(words[i].printed == 1) {
            fprintf(fwp, "%4d, %2d |", words[i].posx, words[i].posy);

            if(words[i].type == 0) {fprintf(fwp, " Across    |");}
            else {fprintf(fwp, " Down      |");}

            fprintf(fwp, " %s\n", randomwords[i]);
        }
    }
}
