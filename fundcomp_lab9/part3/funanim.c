// funanim.c by joao henares - ND 2022 - CSE 20311.01
// made to work with graphics - animation with rotation and user interaction

#include "funanimfunc.h"

int main()
{
    // global variables for the program
    const int xsize = 800, ysize = 600; // window
    char c = '0'; // user input
    
    // mouse stuff
    int xc, yc;

    // rotating polygons
    int xr, yr;
    int posx, posy;

    // rotatepoint
    int i, *ip;
    ip = &i;

    // random colors (textfunc)
    srand(time(0));
    int green = rand()%255+1;
    int red = rand()%255+1;
    int blue = rand()%255+1;
    int vred = rand()%10+1;
    int vgreen = rand()%10+1;
    int vblue = rand()%10+1;

    // create display
    gfx_open(xsize, ysize, "Part 3");

    while(1)
    {
        // get mouse position
        xc = gfx_xpos();
        yc = gfx_ypos();

        if(c != 'c') {
            // rotating circle and point wherever you click
            rotatepoint(ip);

            // rotating square wherever you click
            rotatesquare(ip);

            // increase i to animate
            i++;

            //text
            textfunc(red, green, blue);
            red += vred;
            blue += vblue;
            green += vgreen;
            if(red >= 255 || red <= 0) {vred = -1 * vred;}
            if(blue >= 255 || blue <= 0) {vblue = -1 * vblue;}
            if(green >= 255 || green <= 0) {green = -1 * green;}

            //rotating text
            rotatetext(ip);

            // rotating polygons - pentagon rotates around itself and around some radius
            xr = 50 * cos(M_PI/180 * i);
            yr = 50 * sin(M_PI/180 * i);
            posx = xr + 500;
            posy = yr + 500;
            polygon(ip, 5, posx, posy);
        }

        // user interaction
        if(gfx_event_waiting())
        {
            c = gfx_wait();
        }
        if(c == 27) break;
        else if(c == 'c') gfx_clear();

        // flush and clear
        gfx_flush();
        usleep(5000);
        gfx_clear();
    }

    return 0;
}