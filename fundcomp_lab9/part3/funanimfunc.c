#include "funanimfunc.h"

void rotatepoint(int *i)
{
    int x1, x2, y1, y2, size = 25;

    // spawn little point
    gfx_color(255,0,0);
    x1 = gfx_xpos() + size * cos(M_PI/180 * *i);
    x2 = gfx_xpos() + size * cos(M_PI/180 * (*i+size));
    y1 = gfx_ypos() + size * sin(M_PI/180 * *i);
    y2 = gfx_ypos() + size * sin(M_PI/180 * (*i+size)); 
    gfx_line(x1,y1,x2,y2);

    // spawn circle
    gfx_color(0,0,255);
    gfx_circle(x1,y1,2*size);
}

void rotatesquare(int *i)
{
    int x1, x2, y1, y2, x3, y3, x4, y4, size = 25;

    gfx_color(0,255,0);

    x1 = gfx_xpos() + size * cos(M_PI/180 * *i);
    x2 = gfx_xpos() + size * -1 * sin(M_PI/180 * *i);
    x3 = gfx_xpos() + size * -1 * cos(M_PI/180 * *i);
    x4 = gfx_xpos() + size * sin(M_PI/180 * *i);

    y1 = gfx_ypos() + size * sin(M_PI/180 * *i);
    y2 = gfx_ypos() + size * cos(M_PI/180 * *i); 
    y3 = gfx_ypos() + size * -1 * sin(M_PI/180 * *i); 
    y4 = gfx_ypos() + size * -1 * cos(M_PI/180 * *i);
    
    gfx_line(x1,y1,x2,y2);
    gfx_line(x2,y2, x3, y3);
    gfx_line(x3,y3,x4,y4);
    gfx_line(x4,y4, x1,y1);
}

void textfunc(int red, int green, int blue)
{
    gfx_color(red,green,blue);
    gfx_text(350, 300, "press c to clear the screen");
}

void rotatetext(int *i)
{
    int size = 25; // radius of rotation
    gfx_color(255,150,255);
    gfx_text(100 + size * cos(M_PI/180 * *i), 200 + size * sin(M_PI/180 * *i), "this text is not rotating");
    gfx_text(90 + size * cos(M_PI/180 * *i), 215 + size * sin(M_PI/180 * *i), "but the pentagon down there is");
    gfx_text(105 + size * cos(M_PI/180 * *i), 230 + size * sin(M_PI/180 * *i), "do you understand why?");

    gfx_color(102,235,186);
    gfx_text(40,400, "Click with the mouse somewhere");
}

void polygon(int *i, int n, int xc, int yc) 
{
    int size = 25, j, x1, x2, y1, y2;

    gfx_color(0,255,255);
    for(j = 0; j < n; j++)
    {
        x1 = xc + size * cos(M_PI/180 * *i + (j * 2 * M_PI/n));
        x2 = xc + size * cos(M_PI/180 * *i + ((j+1) * 2 * M_PI/n));
        y1 = yc + size * sin(M_PI/180 * *i + (j * 2 * M_PI/n));
        y2 = yc + size * sin(M_PI/180 * *i + ((j+1) * 2 * M_PI/n));
        gfx_line(x1, y1, x2, y2);
    }

}