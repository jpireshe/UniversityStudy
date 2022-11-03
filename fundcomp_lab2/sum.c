//sum.c, by Joao Henares
// computes and displays the sum of squares of numbers 1 through 10
// and the sum of the square roots of numbers 1 through 10
// CSE 20311.01, LAB 2, made to understand better for loops

#include<stdio.h>
#include<math.h>

int main()
{

 // declare variables for loop and sums
 
 int i, squaresum=0;
 float rootsum=0;
 
 // for loop to compute sum
 
 for(i=1;i<=10;i++){
  squaresum = squaresum+ i*i;
  rootsum = rootsum + sqrt(i);     
 }

 // output sums
 
 printf("Square sum: %d\nRoot sum: %f\n", squaresum, rootsum);

}
