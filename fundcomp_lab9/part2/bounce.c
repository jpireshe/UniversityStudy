// symbol.c by joao henares - ND 2022 - CSE 20311.01
// made to work with graphics - animation

#include "bouncefunc.h"

int main() {

    // variables
    srand(time(0)); // create random stuff
    const int xsize = 800, ysize = 600; // window
    char c; // user input
    int xc = 400, yc = 300, vx = 4, vy = 4, r = 25; // circle data and velocity
    int randomvalue;

    // create display
    gfx_open(xsize, ysize, "Part 2");

    while(1)
    {
        // create moving ball
        xc += vx;
        yc += vy;
        gfx_circle(xc, yc, r);
        
        // collision
        if(xc + r >= xsize || xc <= r)
        {
            vx = 0 - vx;
        }
        if(yc + r >= ysize || yc <= r)
        {
            vy = 0 - vy;
        }

        // user event
        if(gfx_event_waiting()) // user has input stuff
        {
            c = gfx_wait();
            if((int)c == 1) // left click
            {
                xc = gfx_xpos();
                yc = gfx_ypos();

                randomvalue = rand()%2;

                if(randomvalue == 0) {
                    vx = rand()%10+1;
                    vy = rand()%10+1;
                }
                else {
                    vx = -1 * (rand()%10+1);
                    vy = -1 * (rand()%10+1);
                }
            }
        }

        // flush, sleep and clear
        gfx_flush();
        usleep(50000);
        gfx_clear();
        if (c == 27) break;
    }

    return 0;
}