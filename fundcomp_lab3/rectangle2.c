// rectangle2.c
// Joao Pires Henares - cse 20311.01 - ND 2022. Made to understand how to use functions.

// function prototypes go here

#include<stdio.h>

float find_perim(float len, float wid);

float find_area(float len,float wid);

void display(float perim, float area);

int main()
{

     float len, wid;
     float perim, area;

     printf("Enter the Rectangle's length and width: ");
     scanf("%f %f", &len, &wid);

     perim = find_perim(len, wid); // call the find_perim function
     area = find_area(len, wid);

   //  printf("perimeter: %.2f\narea: %.2f\n",perim,area);
     display(perim,area);

     return 0;

}

// function definitions here


float find_perim(float len,float wid)
{
     float perim;
        
     perim = 2 * len + 2 * wid;

     return perim;
}

float find_area(float len, float wid)
{
     float area;

     area = len * wid;

     return area;
}

void display(float perim, float area)
{
     printf("Perimeter: %.2f\nArea: %.2f\n",perim,area);
}
