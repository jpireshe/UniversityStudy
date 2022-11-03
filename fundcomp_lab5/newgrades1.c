#include <stdio.h>

float find_avg(int [], int);

int main()
{
     int grades[50], grd;
     int count = 0;
     FILE *fp;

     fp = fopen("grades.dat", "r");   // hard-coding the file name

     while (1) {
          fscanf(fp, "%d", &grd);   // read the next grade
          if(feof(fp)) break;       // end the loop if EOF reached
          grades[count] = grd;      // put the grade in the array
          count++;                  // increment the count
     }

     float avg = find_avg(grades, count); // GETS AVERAGE
     printf("there are %d grades\n", count); // USES COUNT VARIABLE FROM WHILE LOOP
     printf("their average is: %.2lf\n", avg); // PRINTS AVERAGE

     return 0;
}

float find_avg(int g[], int sz) // BASIC WAY TO FIND AVERAGE
{
     int g_sum = 0; // SUM VARIABLE

     int i;
     for (i = 0; i < sz; ++i) // ITERATES WHOLE ARRAY TO FIND SUM OF ALL GRADES
          g_sum = g_sum + g[i]; 

     return (float) g_sum / sz; // RETURNS SUM / SIZE (NUMBER OF GRADES) 
}

