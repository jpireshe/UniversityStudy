#include<stdio.h>

int main(){

     // multiplication table by joao henares
     // CSE 20311-01. LAB 2. Purpose: understand better for loops and formatting.
     // creates a table of multiplication as long as the user's input

     // declare variables and ask for input
     int x,y,ix,iy,iz;

     printf("Multiplication table\nPlease input size of x axis: ");
     scanf("%d",&x);
     printf("Please input size of y axis: ");
     scanf("%d",&y);

     // for loop to iterate through y axis of table

     for(iy = 1; iy <= y; iy++)
     {
          // do special initial case to create the first horizontal row
          // (the label of x axis of table)

          if(iy ==1)
          {
               printf("   ");
               for(iz=1;iz<=x;iz++)
               {
                    printf(" %4d ", iz);
               }
               printf("\n   ");
               for(iz = 1; iz<=x;iz++)
               {
                    printf("------");
               }
          }

          // print y coordinate of table 

          printf("\n%d |", iy);

          // nested loop to generate the numbers in table
          for(ix = 1; ix<=x;ix++)
          {
               printf(" %4d ",ix*(iy));
          }
     }
     
     printf("\n");
     return 0;
}
