#include<stdio.h>
#include<math.h>

int main()
{
     
     // graph. by Joao Henares. Creates a simple plot of a mathematical function. Made 
     // to understand C better. CSE 20311-01. LAB 2.

     // show function
     printf("Plot for function: y = abs(10*cos(x)), from x = 0 to x = 21. # stands for 1 in the graph.\n");

     // create loop variables and x and y to compute values
     int g, iy;
     float ix, y=0;

     // create max and min variables
     float xmax, xmin, ymax = 0, ymin = 2; // arbitrary values to make ymax and ymin
                                        // calculations possible from the first loop. 
                                        // I put 2 for ymin because ymin had to be
                                        // in the middle of the domain (in order to have
                                        // something lower than ymin and compute the real
                                        // ymin)
     
     // create header 

     printf("    X     Y  \n");

     // for loop to compute y

     for (ix = 0; ix <= 21.01; ix = ix + 0.2) {
          y = 10*cos(ix);
          // if statement to make y always positive
          if (y < 0){
               y = -1* y;
          }
          

          // print x and y
          //
          printf("%6.2f %6.2f ",ix, y);

          // create loop variable g (Graph)
          
          if (y - (int)y < 0.5){
               g = (int)y;       
          }
          else {
               g = (int)y + 1; 
          }
          
          // create base # for when y = 0
          printf("#");

          // create nested for loop to create graphic
          for (iy = 0; iy < g; iy++) {
               printf("#");
          
          }
          // jump line
          printf("\n");
          
          // find max
          if ((ymax - y) < 0){
           ymax = y;
           xmax = ix;       
          }
          // find min
          if ((ymin - y) > 0){
           ymin = y;
           xmin = ix;
          }
     }
          printf("The maximum of %.2f was at %.2f\n", ymax, xmax);
          printf("The minimum of %.2f was at %.2f\n", ymin, xmin);
      
          return 0;

}
