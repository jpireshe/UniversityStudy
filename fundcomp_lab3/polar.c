#include<stdio.h>
#include<math.h>

// polar.c by Joao Henares - CSE 20311.01 - ND 2022
// Prompts user for x and y coordinates and finds and displays polar coordinates and quadrant
// made to understand better functions and math

int get_quadrant(double x, double y);
double get_radius(double x, double y);
double get_angle(double x, double y);
void show_info(int quadrant, double radius, double angle);

int main()
{
     // get user input
         double x=0, y=0;
          
          printf("Please input x coordinate: ");
          scanf("%lf", &x);

          printf("Please input y coordinate: ");
          scanf("%lf", &y);
     
     // use functions
     
          // quadrant:
          int quadrant;
          quadrant = get_quadrant(x,y);

          // radius:
          double radius;
          radius = get_radius(x,y);
          
          // angle
          double angle;
          angle = get_angle(x,y);

          show_info(quadrant, radius, angle);         

     return 0;
}

// functions:

int get_quadrant(double x, double y)
{
     int quadrant;
     
     // make an if - else if statement to find quadrant based on x and y. 
     // Also make a case for when x or y is zero, and then there is no quadrant.

     if((x == 0) || (y==0)){
          quadrant = 0;
     }
     else if ((x > 0) && (y > 0)){
          quadrant = 1;
     }
     else if ((x < 0) && (y > 0)){
          quadrant = 2;
     }
     else if ((x < 0) && (y < 0)){
          quadrant = 3;
     }
     else if ((x > 0) && (y < 0)){
          quadrant = 4;
     } 
         
     return quadrant;

}

double get_radius (double x, double y)
{    
     // use radius formula
     double radius;
     radius = sqrt(x*x + y*y);
     return radius;
}

double get_angle (double x, double y)
{    
     // use angle formula
     double angle;
     angle = 180/M_PI * atan2(y,x);
     return angle;
}

void show_info(int quadrant, double radius, double angle)
{
     // print everything
     if (quadrant ==0)
     printf("Quadrant: Not determined, Radius: %.2lf, Angle: %.2lf\n", radius, angle);

     else
     printf("Quadrant: %d, Radius: %.2lf, Angle: %.2lf\n", quadrant, radius, angle);

}
