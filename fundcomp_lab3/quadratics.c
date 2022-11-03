// quadratics.c
// computes the roots of quadratic equation in a while loop using functions
// Joao Henares, CSE 20311.01 - ND 2022
// Made to understand better functions and while loops.

#include<stdio.h>
#include<math.h>

float calcRootOne(float a, float b, float c);
float calcRootTwo(float a, float b, float c);

int main()
{    
     float a = 1, b, c, x1, x2; // create variables
     printf("Quadratic equation calculator: ax^2 +bx + c = 0. Input a as 0 to quit.\n");
     
     while (a!=0) // while loop to repeat program
     {     
          printf("Please input a: "); // ask for inputs
          scanf("%f",&a);
               if (a == 0)
               {
                    break; // get out of loop
               }
          printf("Please input b: ");
          scanf("%f",&b);

          printf("Please input c: ");
          scanf("%f",&c);
          
          // check for inexistent roots:
          if(b*b >= 4*a*c)
          {
               x1 = calcRootOne(a,b,c); // calculate roots
               x2 = calcRootTwo(a,b,c);

               if (x1 != x2){ //check for same roots
                    printf("Root 1: %.2f\nRoot 2: %.2f\n",x1,x2);
               }
               else {
                    printf("Root: %.2f\n",x1);     
               }
          }
          else
          {
               printf("There is no root for this equation\n");
          }
     }

     printf("End of program.\n");

     return 0;
}

float calcRootOne(float a, float b, float c) // two functions to calculate roots using
                                             // bhaskara
{
     float x1;
     x1 = (-1*b + sqrt(b*b - 4*a*c))/(2*a);
     return x1;
}

float calcRootTwo(float a, float b, float c)
{
     float x2;
     x2 = (-1*b - sqrt(b*b - 4*a*c))/(2*a);
     return x2;
}


