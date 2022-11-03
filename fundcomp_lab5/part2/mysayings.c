// sayings.c by Joao Henares - ND 2022
// CSE 20311.01
// Made to use files

#include<stdio.h>
#include<string.h>
#include<ctype.h>

void printmenu();

int main()
{
     // create file pointer and another for option 4
     FILE *fp, *fpfour;
     
     // get file name
     char filename[50];
     printf("Enter name of a startup file (max 50 characters): ");
     scanf("%s", filename);
     
     // open user file
     fp = fopen(filename, "r+");
     if(!fp) {
          printf("File not found.\n");
          return 1;
     }

     // read file content and store in char phrases
     char phrases[50][256];
     int phcount = 0;
     while(1) {
          fgets(phrases[phcount], 255, fp);
          if (feof(fp)) break;
          phcount++;            // counts number of sayings. MUST KEEP TRACK OF THIS!
     }
     
     // menu for user to use
     int userchoice = 0; // menu controller
     int i; // for loop counter
     char newfilename[50]; // name of file for option 4
     char word[50]; // word for option 3
     
     while (userchoice != 5) {
          printmenu();
          scanf("%d", &userchoice);
          getchar();

          if (userchoice == 1) {                 // show all sayings
               printf("\nShowing all sayings:\n"); // header
               i = 0;
               for(i = 0; i < phcount; i++) // for loop to number of phrases
               {
                    printf("-> ");
                    fputs(phrases[i], stdout); // print phrases
               }
               printf("\n");          
          }

          else if (userchoice == 2) {
               phcount++; // as there will now be one more phrase
               printf("Please enter saying (max 256 characters long): ");
               fgets(phrases[phcount-1],256,stdin); // get phrase in vector
          }

          else if (userchoice == 3) {
               printf("Please input word: "); // get word to be looked for
               scanf("%s", word);
               getchar();
               
               for (i = 0; i < phcount; i++) // iterate through 2d array of phrases
               {
                   if(strstr(phrases[i], word)) { // use strstr() to check if word is
                                                  // in the phrase
                         printf("-> ");
                         fputs(phrases[i], stdout);       // print
                   }
               }
          }
               
          else if (userchoice == 4) {
               printf("Please input new file name (max of 50 characters). Please include .txt as an extension: "); // get file name from user
               scanf("%s", newfilename);
               getchar(); // avoid \n problem

               fpfour = fopen(newfilename, "w+"); // open file with newfilename
               if (!fpfour) { // check for invalid file
                    printf("Invalid file.\n");
                    return 1;
               }
               
               for(i = 0; i < phcount; i++) // put every element of phrases vector into file
               {
                    fputs(phrases[i], fpfour);   // wrong: was using phcount instead of i
               }
          } 

          else if(userchoice == 5) {
                  return 0;
                  break;
          }
             
          else {
               printf("Not a valid option.\n");
          }
     }
     
     // close files
     fclose(fp);
     fclose(fpfour);
     return 0;
}

void printmenu() {
     printf("Tasks you can perform: \n   1: show all sayings.\n   2: enter a new saying.\n   3: list sayings that contain a given word. \n   4: save all sayings in a new text file. \n   5: quit. \nYour choice: ");
}



