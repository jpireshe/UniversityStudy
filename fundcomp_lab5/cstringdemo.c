#include<stdio.h>
#include<string.h>

#define MAXLENGTH 30 // macro

int main()
{
     char states[][MAXLENGTH] = {"Indiana", "Michigan", "Ohio", "Illinois", "New York", "Texas"};
               // array of states

     int size = sizeof(states)/(sizeof(states[0])); // get size of vector; note that
                                                    // it is the division of the size of
                                                    // the entire array by the size of 
                                                    // maxlength (because the memory
                                                    // allocated is 31 in all cases)
     int i,j; // loop control

     printf("The states are:\n"); // listing states normally, iterates through loop
                                  // to show how each string is an array itself

     for (i=0; i< size; i++) {
          printf(" - %s\n", states[i]);
     }

     printf("Displaying states with a space between letters:\n"); // now with spaces
     for (i = 0; i< size; i++) { // does similar iteration to last time
          printf(" - ");
          for (j = 0; j < strlen(states[i]); j++) { // there is, however, a nested loop
                                                    // inside, which iterates through each
                                                    // character of the states' names.
                                                    // nice use of strlen here. I will use
                                                    // it.
               printf("%c ", states[i][j]); // prints character
          }
          printf("\n");
     }

     return 0;
}
