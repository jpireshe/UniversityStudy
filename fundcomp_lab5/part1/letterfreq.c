// letterfreq.c by Joao Henares - ND 2022
// Made to understand better how to read and use files in general.

#include<stdio.h>
#include<ctype.h>
#define ALPHANUM 26 // Number of letters in the alphabet you are using
#define ALPHACONSTANT 97 // Offset on ASCII (a = 97 and i wanted to set 0 for a)

int main()
{
     // point to file (to be looked for)
     FILE *fp;

     // get file from user
     char infile[30];
     printf("Please enter file name: ");
     scanf("%s", infile);                    // scan file name

     // open user file
     fp = fopen(infile, "r");                // connect to file
     if (!fp) {
          printf("File not found. \n");
          return 1;                          //in case file is not found
     }

     // create alphabet array, number of letters and file read variables
     int letterfreq[ALPHANUM] = {0}, numberofletters = 0, numbertotal = 0;
     char ch, lowerval;

     // read file
     while(1) {
          ch = fgetc(fp);                    // get ch, which is the next character in the
                                             // file
                                   
          if (feof(fp)) break;               // break if the end of file is reached
          numbertotal++; // raise n of total characters
          if (isalpha(ch) != 0)              // checks for letter
           {
               numberofletters++;
               lowerval = tolower(ch);       // makes it in lowercase
               int letternum = lowerval - ALPHACONSTANT;  // throws character into
                                                          // letterfreq according to
                                                          // numerical value
               letterfreq[letternum]++;
           } 
     }
     
     // print stuff ---------------------------------------------------------------------
     
     // number of letters and total characters
     printf("\nGeneral summary for %s: \n", infile);
     printf("There were %d total characters.\nThere were %d letters\n", numbertotal, numberofletters); 
        
     // for loop to print stuff
     int i, ninline = 0;                     // control variables
     char a = 'a';                           // add 1 to that variable in the for loop to
                                             // make it go a: "" b: "" etc
     // letter counts            
     printf("Letter counts: \n");
     for (i = 0; i < ALPHANUM; i++)
     {
          if (ninline == 6)
          {
               ninline = 0;                  // control number of infos in the line
               printf("\n");
          }

          printf("%c: %4d  ",a,letterfreq[i]);
          a++;
          ninline++;    
     }
     printf("\n");
     
     // letter %
     printf("Letter percentages: \n");
     a = 'a';                                // reset variables
     ninline = 0;
     for (i=0; i< ALPHANUM; i++)
     {
               if(ninline == 6) {
                    ninline = 0;
                    printf("\n");
               }

          float freq = (float)letterfreq[i]/(float)numberofletters*100;  // get frequency on float
           
          printf("%c: %4.1f%% ",a, freq);
          a++;
          ninline++;
     }
     printf("\n");

     return 0;
}
