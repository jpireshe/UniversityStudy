#include "symbolfunc.h"

void trianglefunc(int size)
{
    gfx_color(0,255,0);
    polyfunc(size, 3);
}

void squarefunc(int size)
{
    gfx_color(0,0,255);
    gfx_line(gfx_xpos()-size, gfx_ypos()-size, gfx_xpos()+size, gfx_ypos()-size); // upper line
    gfx_line(gfx_xpos()-size, gfx_ypos()+size, gfx_xpos()+size, gfx_ypos()+size); // below
    gfx_line(gfx_xpos()-size, gfx_ypos()-size, gfx_xpos()-size, gfx_ypos()+size); // left
    gfx_line(gfx_xpos()+size, gfx_ypos()-size, gfx_xpos()+size, gfx_ypos()+size); // right
}

void circlefunc(int size)
{
    gfx_color(255,255,255);
    gfx_circle(gfx_xpos(), gfx_ypos(), size);
}

void polyfunc(int size, int n)
{
    if(n != 3) {
        gfx_color(255,0,255);
    }

    int i;
    int x1, x2, y1, y2;

    for(i = 0; i < n; i++)
    {
        x1 = gfx_xpos() + size * cos(360/n * M_PI/180 * i);
        x2 = gfx_xpos() + size * cos(360/n * M_PI/180 * (i+1));
        y1 = gfx_ypos() + size * sin(360/n * M_PI/180 * i);
        y2 = gfx_ypos() + size * sin(360/n * M_PI/180 * (i+1)); 
        gfx_line(x1,y1,x2,y2);
    }
}