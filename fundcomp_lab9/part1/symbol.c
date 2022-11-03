// symbol.c by joao henares - ND 2022 - CSE 20311.01
// made to work with graphics - polygons

#include "symbolfunc.h"

int main()
{
    // variables
    const int xsize = 800, ysize = 600; // window
    char c; // user input
    int SIZE = 50; // size of things
    int size = SIZE/2; // because size would be the radius and SIZE the diameter.

    // Open a new window
    gfx_open(xsize, ysize, "Part 1");

    while(1)
    {
        // get user input
        c = gfx_wait();
        
        // do stuff
        if(c == 'c') // circle
        {
            circlefunc(size);
        }
        else if(c == 't' || c == '3') // triangle
        {
            trianglefunc(size);
        }
        else if((int) c == 1 || c == '4') // square
        {
            squarefunc(size);
        }
        else if(c == '5' || c == '6' || c == '7' || c == '8' || c == '9') // regular polygon
        {
            polyfunc(size, c - '0');
        }

        else if (c == 27) gfx_clear(); // clear

        // flush and break
        if(c=='q') break;
        gfx_flush();
    }

    return 0;
}