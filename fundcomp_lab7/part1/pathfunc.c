#include<stdio.h>
#include"pathfunc.h"

void printmenu(int i, Point points[]) {
    printf("There are %d points:\n  x   |   y \n------+--------\n", i+1); // header
    int j;
    float sum = 0; // sum distances on for loop

    for(j = 0; j <= i; j++)
    {
        printf("%5.1f | %5.1f \n", points[j].x, points[j].y); // print data
        if(j>0) {
        sum = sum + sqrt(pow((points[j].x - points[j-1].x), 2) + pow((points[j].y - points[j-1].y), 2)); } // do sum
    }

    printf("The path distance through them is %.2f\n", sum); // print sum

}