#include<stdio.h>
#include"pathfunc.h"

int main(int argc, char *argv[])
{

    // file pointer
    FILE *fp;
    // loop variables
    int i = 0;
    // array of structs
    Point points[30];
    // file name string
    char filename[30];

    if(argc == 1) { // no file
        printf("Input file name: ");
        scanf("%s", filename);
        fp = fopen(filename, "r"); // connect to file
        if(!fp) { // check for existence
            printf("File not found. \n");
            return 1; 
        } 
        while(i<30) // read file
        {
           fscanf(fp, "%f %f", &points[i].x, &points[i].y); // get stuff
           if(feof(fp)) break;
           i++;
        }

        printmenu(i, points); // calculate and print stuff

    }
    else if(argc == 2) { // program runs here

        fp = fopen(argv[1], "r"); // connect to file
        if(!fp) { // check for existence
            printf("File not found. \n");
            return 1; 
        } 
        while(i<30) // read file
        {
           fscanf(fp, "%f %f", &points[i].x, &points[i].y); // get stuff
           if(feof(fp)) break;
           i++;
        }

        printmenu(i, points); // calculate and print stuff

    }

    else { // more than one file
        printf("You did not this program the right way. Sorry.\n");
        return 1;
    }

    return 0;
}