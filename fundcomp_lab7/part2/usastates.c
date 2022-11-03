//usastates.c by joao henares
//cse20311.01 - nd 2022
//made to understand better structs and pointers

#include<stdio.h>
#include"usastatesfunc.h"
#define LINEMAX 80

int main(int argc, char *argv[]) {
    // ==========[VARIABLE DECLARATIONS]============

    FILE *fp; // file pointer
    int i = 0, j; // loop variables
    State states[100]; // states array
    int size = sizeof(states)/(2*sizeof(states[0])); // size of the array
    char filename[30]; // user file name
    char line[LINEMAX]; // get line
    int userinput = 0, *up; // user menu input and its pointer
    up = &userinput;

    // ================[RUNNING]=====================

    if (argc == 1) // executable run without any files
    {
        // ======[GETTING FILE DATA]================
        printf("Input file name: "); // get file name
        scanf("%s", filename);

        fp = fopen(filename, "r"); // connect to file
        if(!fp) { // check for existence
            printf("File not found. \n");
            return 1; 
        } 

        while(1) // store data into array
        {
            fgets(line, LINEMAX, fp);
            if(feof(fp)) break;

            strcpy(states[i].abb, strtok(line,",")); // use strtok to get the words
            strcpy(states[i].name, strtok(NULL,","));
            strcpy(states[i].capital, strtok(NULL,","));
            states[i].year = atoi(strtok(NULL,"\n"));
            i++;
        }
        // ===========================================
    }

    else if (argc == 2) // filename at execution
    {
        //=========[GETTING FILE DATA]================
        fp = fopen(argv[1], "r"); // connect to file
        if(!fp) { // check for existence
            printf("File not found. \n");
            return 1; 
        } 
        while(1) // store data into array
        {
            fgets(line, LINEMAX, fp);
            if(feof(fp)) break;

            strcpy(states[i].abb, strtok(line,",")); // use strtok to get the words
            strcpy(states[i].name, strtok(NULL,","));
            strcpy(states[i].capital, strtok(NULL,","));
            states[i].year = atoi(strtok(NULL,"\n"));
            i++;
        }
        //============================================
    }

    else // more than 1 filename
    {
        printf("Sorry. This is not the way to use this program.\n");
        return 1;
    }

    //========================[USER MENU]===================================
    printf("Welcome to usastates.c!\n");
    while(userinput != 8) { // menu lock
        printmenu(up);
        
        // ============[PROCESS USER INPUT]===================
        switch(userinput)
        {
            case 1:
                listalldata(states, size);
                break;
            case 2:
                option2(states, size);
                break;
            case 3:
                option3(states, size);
                break;
            case 4:
                option4(states, size);
                break;
            case 5:
                option5(states, size);
                break;
            case 6:
                option6(states,size);
                break;
            case 7:
                option7(states,size);
                break;
            case 8:
                break;
            default:
                printf("Not a valid option\n");
        }
    }
    

    return 0;
}
