//crossword.c by joao henares
//cse20311.01 - nd 2022
//made as the biggest project in our labs up to this point - exercise of pointers and coding project in general
#include"crosswordfunc.h"

int main(int argc, char *argv[])
{
    //=============[DECLARING VARIABLES]================
        // list of words and pointer
        Word words[NUMWORDS];
        Word *wp;
        wp = &words[0];

        // filter bad words
        char word[BOARDSIZE];
        int proper;

        // count of words and its pointer
        int wordcount = 0;
        int *wcp;
        wcp = &wordcount;

        // loop control
        int i, minidx, j;

        // File pointer
        FILE *fp, *fwp; // file read pointer and file writing pointer

    //==========[PRINT MENU, GET USER INPUT]=============

        if(argc == 1) { // interactive
            printmenu();
            printf("Enter a list of words (input '.' to stop):\n");
            // while loop to get the inputs (STILL HAVE TO FILTER STUFF)
            while(wordcount < NUMWORDS)
            {
                getinput(wp, wcp);
                // break while if "." is input
                if (strcmp(wp->str, ".") == 0) break;

                wp = &words[wordcount];
            }
        }

        else if((argc == 2) || (argc == 3)) // files
        {
            printmenu();
            wordcount = 0;

            fp = fopen(argv[1], "r"); // connect to file

            if(!fp) { // check for existence
                printf("File not found. \n");
                return 1; 
            }

            while(wordcount < NUMWORDS) // read file
            {
                proper = 1; // set proper to 1. if it is not proper, return it to zero
                fscanf(fp, "%s", word);

                for(i = 0; i < strlen(word); i++)
                {
                    if (!isalpha(word[i]) && strcmp(word, ".") != 0) {
                        proper = 0;
                    }
                }

                if(strlen(word) == 1 || strlen(word) > 15) // another way to check for not proper
                {
                    proper = 0;
                }

                if(proper == 1) {
                    strcpy(words[wordcount].str, word);
                    wordcount++;
                }

                if (feof(fp)) break; // break in end
            
            }                     
        }

        else // more than three arguments
        {
            printf("Error: wrong use of executable\n");
            return 1;
        }

        // convert all of them to upper case and input size into word struct
        for (i = 0; i < wordcount; i++)
        {
            for(j = 0; j < strlen(words[i].str); j++)
            {
                words[i].str[j] = toupper(words[i].str[j]);
            }
            words[i].size = strlen(words[i].str);
        }

    //===========[PREPARE TO USE FUNCTIONS]===============

        // reset wp to use in qsort
        wp = &words[0];

        // rank words by size: qsort sorts the struct array itself
        // by using function structcompare (on stdlib.h library)
        qsort(wp, wordcount, sizeof(words[0]), structcompare); 

        // now reset it to use in printsolution
        wp = &words[wordcount-1];

        // prepare clues
        srand(time(0));
        char randomwords[NUMWORDS][BOARDSIZE];
        for(i = 0; i < wordcount; i++)
        {
            randomizeword(words[i].str, randomwords[i], strlen(words[i].str));
        }

    //=================[USE FUNCTIONS]=====================

    if(argc != 3) { // interative mode or file mode
        printsolution(wp, wordcount, words);
        wp = &words[0];
        printclues(wp, randomwords, wordcount);
    }
    else { // output to file
        fwp = fopen(argv[2], "w");
        printfilesolution(fwp, wp, wordcount, words);
        fileprintclues(fwp, words, randomwords, wordcount);
    }

    return 0;
}