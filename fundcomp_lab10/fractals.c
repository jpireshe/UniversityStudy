// sierpmain.c
// ND 2022 - CSE 20311.01
// JOAO HENARES
// Made to understand the use of recursive functions.

#include "gfx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinkingsquares(int, int, int);
void drawsquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void squarespiral(int xc, int yc, double r, double angle);
void circless(int xc, int yc, int r);
void snowflake(int xc, int yc, int r);
void tree(int xc, int yc, int r, int angle);
void drawv(int xc, int yc, int r, int angle);
void fern(int x,int y,int l,int arg);
void smallcirclespiral(int xc, int yc, float r, int angle, float max);
void spiralofspirals(int xc, int yc, float r, int angle);

int main()
{
  int width = 1000, height = 1000, mrgn = 20;
  double t = 0, *tp;
  int k = 15, *kp;
  kp = &k;
  tp = &t;
  char c;
  double angle = 60, offset = 90;

  gfx_open(width, height, "Sierpinski's Triangle");

  while(1) {
    c = gfx_wait();
    gfx_clear();
    if (c == 'q') break;
    else if (c == '1') sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
    else if (c == '2') shrinkingsquares(width/2, height/2, 150);
    else if (c == '3') squarespiral(width/2,height/2,1, 0);
    else if (c == '4') {gfx_circle(width/2, height/2, 200); circless(width/2, height/2, 200);}
    else if (c == '5') snowflake(width/2,height/2,400);
    else if (c == '6') {gfx_line(width/2, height/1.1, width/2, height/2); tree(width/2,height/2,220, 60);}
    else if (c == '7') fern(width/2, height/1.3, 600, 0);
    else if (c == '8') spiralofspirals(width/2, height/2, 10, 0);
    else gfx_clear();
    gfx_flush();
    *tp = 0;
    *kp = 15;
    angle = 60;
  }
}

void spiralofspirals(int xc, int yc, float r, int angle)
{
  if(r<100) // base
  {
    smallcirclespiral(xc, yc, 1, angle, 0.6*r); // create a spiral
    spiralofspirals(xc + 8* r*cos(M_PI/180 * angle), yc + 8 * r*sin(M_PI/180 * angle), 1.12*r, angle + 45); // recursion
  }
}

void smallcirclespiral(int xc, int yc, float r, int angle, float max)
{
  gfx_circle(xc, yc, (int)r); // spawn circle at mosition

  if(r < max) // had to change this "max" so the spirals grow
  {
    smallcirclespiral(xc + 4* r*cos(M_PI/180 * angle), yc + 4 * r*sin(M_PI/180 * angle), 1.1*r, angle + 45, max); // recursive call
  }
}

void squarespiral(int xc, int yc, double r, double angle)
{
  int x1, y1, x2, y2, x3, y3, x4, y4;

  // define xs's position based on center and side
  x1 = xc - r;
  x2 = xc + r;
  x3 = x2;
  x4 = x1;

  // define the y positions
  y1 = yc - r;
  y2 = y1;
  y3 = yc + r;
  y4 = y3;

  drawsquare(x1,y1,x2,y2,x3,y3,x4,y4);
  
  if(r<500) // base
  {
    squarespiral(xc + 4*r * cos(M_PI/180 * angle), yc + 4*r * sin(M_PI/180 * angle), 1.15*r, angle + 45);
  }
}

void fern(int xc ,int yc, int r, int rotation)
{
  int xn, yn, i; // current points
  int ln, xnext, ynext; // next points
  int offset = 45; // between the ferns

  if(r>1) // base
  {
    xn = xc - r*sin(rotation*M_PI/180); // rotation is about the position of the ferns themselves
    yn = yc - r*cos(rotation*M_PI/180);
    gfx_line(xc,yc,xn,yn);
    ln = r/4;
    
    for(i = 0; i < 4 ;i++) // define the new positions
    {
      xnext = xc - i * ln * sin(rotation*M_PI/180) - ln * sin(rotation*M_PI/180);
      ynext = yc - i * ln * cos(rotation*M_PI/180) - ln * cos(rotation*M_PI/180);

      fern(xnext, ynext, r/4, rotation + offset);
      fern(xnext, ynext, r/4, rotation - offset);
    }
 }
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case. 
  if(abs(x2-x1) < 5) return;

  // Draw a triangle
  drawTriangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void circless(int xc, int yc, int r)
{
  int j = 0;

  if(r > 3) // base
  {
    for(j = 0; j < 6; j++) // 6 circles on each circke
    {
      gfx_circle(xc + r*cos(M_PI/3 * j), yc + r*sin(M_PI/3 * j), r/3);
      circless(xc + r*cos(M_PI/3 * j), yc + r*sin(M_PI/3 * j), r/3);
    }
  }
}

void tree(int xc, int yc, int r, int angle)
{
  
  // base case
  if(r < 2) return;
  // draw a y
  drawv(xc, yc, 0.7 * r, angle);

  // recursive call
  tree(xc + 0.7 * r * cos(M_PI/180 * (angle + 60)), yc - 0.7 * r * sin(M_PI/180 * (angle+60)), 0.7 * r, angle+45);
  tree(xc + 0.7 * r * cos(M_PI/180 * angle), yc - 0.7 * r * sin(M_PI/180 * angle), 0.7 * r, angle - 45);
  
}

void drawv(int xc, int yc, int r, int angle) // for void tree
{
  gfx_line(xc,yc,xc + r * cos(M_PI/180 * angle), yc - r * sin(M_PI/180 * angle));
  gfx_line(xc,yc,xc + r * cos(M_PI/180 * (angle + 60)), yc - r * sin(M_PI/180 * (angle+60)));
}

void snowflake(int xc, int yc, int r)
{
  int j = 0;

  if(r > 1) // base case
  {
    for(j = 0; j < 5; j++) // like the circles
    {
      gfx_line(xc, yc, xc + r*cos(2 * M_PI/5 * j), yc + r*sin(2 * M_PI/5 * j));
      snowflake(xc + 0.7*r *cos(2 * M_PI/5 * j), yc + 0.7*r *sin(2 * M_PI/5 * j), r/3);
    }
  }
}

void shrinkingsquares(int xc, int yc, int l) // square with side 2l
{
    int x1, y1, x2, y2, x3, y3, x4, y4;

    // define xs's position based on center and side
    x1 = xc - l;
    x2 = xc + l;
    x3 = x2;
    x4 = x1;

    // define the y positions
    y1 = yc - l;
    y2 = y1;
    y3 = yc + l;
    y4 = y3;

    drawsquare(x1,y1,x2,y2,x3,y3,x4,y4);

    if(l>1) // base
    {
        shrinkingsquares(x1,y1,l/2.1);
        shrinkingsquares(x2,y2,l/2.1);
        shrinkingsquares(x3,y3,l/2.1);
        shrinkingsquares(x4,y4,l/2.1);
    }
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

void drawsquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    gfx_line(x1,y1,x2,y2);
    gfx_line(x2,y2,x3,y3);
    gfx_line(x3,y3,x4,y4);
    gfx_line(x4,y4,x1,y1);
}