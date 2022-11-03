// menucalc.c by Joao Henares - CSE 20311.01 - ND 2022
// Text calculator - add, subtract, multiply, divide
// made to use functions

#include<stdio.h>

// FUNCTIONS

void result(double c); // prints the result
void numbera(); // prompt user to input 1st number in operation
void numberb(); // prompt user to input 2nd number in operation
double getnumbers(); // gets the user's input

// OPERATION FUNCTIONS
double add(double a, double b);
double sub(double a, double b);
double mult(double a, double b);
double div(double a, double b);

int main()
{    
     // print name of program and create menu control variable
     printf("Text menu-driven basic calculator\n");    
     int menuOption = 1;
     
     // get number variables to be used in other functions
     double a,b,c;

     // while loop to keep inside program
     while (menuOption != 0) 
     {
          // print menu
          printf("0) Quit\n1) +\n2) -\n3) *\n4) /\nInput: ");
          scanf("%d", &menuOption); 

          // understand user input
          switch(menuOption){
               case 0: // quit
                    printf("Bye!\n");
                    break;
               case 1: // adition
                    numbera();                  
                    a = getnumbers();
                    numberb();
                    b = getnumbers();
                    c = add(a,b);    
                    result(c);
           
                    break;

               case 2: // subtraction
                    numbera();                  
                    a = getnumbers();
                    numberb();
                    b = getnumbers();
                    c = sub(a,b);    
                    result(c);

                    break;

               case 3: // multiplication
                    numbera();                  
                    a = getnumbers();
                    numberb();
                    b = getnumbers();
                    c = mult(a,b);    
                    result(c);

                    break;

               case 4: // division
                    numbera();                  
                    a = getnumbers();
                    numberb();
                    b = getnumbers();

                    // check for division with 0
                    if (b != 0)
                    {
                         c = div(a,b);    
                         result(c);

                    }
                    else
                         printf("Can't divide by 0.\n");

                    break;

               default:
                    printf("Not a valid option.\n");
          }
     }

     return 0;        
}

double getnumbers()
{
     double n;
     scanf("%lf",&n);
     return n;
}

void numbera()
{
     printf("Input 1st number: ");                  
}

void numberb()
{
     printf("Input 2nd number: ");
}

void result(double c)
{
     printf("The result is: %.2lf\n",c);
}

double add(double a, double b)
{
          return a+b;
}
double sub(double a, double b)
{
          return a-b;
}
double mult(double a, double b)
{
          return a*b;
}
double div(double a, double b)
{
          return a/b;
}
