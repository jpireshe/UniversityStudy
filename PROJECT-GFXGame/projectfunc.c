// NUGHI, by Joao Henares.
// ND 2022 - CSE 20311.01
// Mini final project - made to synthesize coursework
// tip: if you open this in vscode it should be easy to read all comments.

#include "projectfunc.h"

void rolldice(Powerup *p, int n, int xwindow, int ywindow)
{
    int i = rand()%200+1;                                       // create a random num from 1 to 200
    if(i == n)                                                  // 1/200 chance
    {
        p->active = 1;                                          // make whatever powerup is in this function active
        p->posx = xwindow + 100;                                // define start position
        p->posy = rand()%(ywindow-40) + 40;                     // define random y position
    }
}

void spawnpowerup(Powerup *p, int xwindow, int ywindow, int *tp)
{
    p->posx -= p->v;                                            // move powerup
    if(p->inuse == 0)                                           // if p is not in action, player did not get it
    {
        if(p->type == 0)                                        // spawn powerup sprite (one for each case)
        {
            gfx_color(0,255,255);
            gfx_circle(p->posx, p->posy, 10);
            gfx_text(p->posx - 2, p->posy + 5, "V");
        }
        else if(p->type == 1) 
        {
            gfx_color(255,111,0);
            gfx_circle(p->posx, p->posy, 10);
            gfx_text(p->posx - 2, p->posy + 5, "F");
        }
    }
    if(p->posx <= 0)                                             // turn the sprite off if its position is less than 0
    {
        p->active = 0;
    }
}

void showhs(int highscores[], int x, int y, int n)
{
    gfx_color(255,0,255);
    gfx_text(x/2 - 30, y/2, "HIGH SCORES:");

    char scores[10];
    int i;

    for(i = 0; i < n; i++)
    {
        sprintf(scores, "%d", highscores[i]);                   // put the highscores in scores string
        gfx_text(x/2 -30, y/2 + 20*(i+1), scores);
    }
}

void reset(Ship *up, int *sp, int numenemies, Enemy *ep, Laser *lp, int *ghs, Powerup *dvp, Powerup *rfp, Enemy *sep)
{
    int i;                                                      // all of this is to reset the game when we die.

    // ship
    up->posx = 150;
    up->posy = 350;
    up->powerup = 100;

    // score
    *sp = 0;
    *ghs = 0;

    // enemies
    for(i = 0; i < numenemies; i++)
    {
        ep->alive = 0;
        ep++;
    }
    sep->alive = 0;
    sep->posx = 1000;

    // powerups
    dvp->active = 0;
    dvp->inuse = 0;

    rfp->inuse = 0;
    rfp->active = 0;

    // laser
    lp->current = 8000;
    lp->active = 0;
    lp->ready = 1;
}

void checkforhighscores(int score, int highscores[], int n, int *ghs)
{
    int i, j, k;
    FILE *fp = fopen("highscore.txt", "r+");

    for(i = 0; i < n; i++)                                      // check if the score you got is bigger than any score of the top 5
    {
        if(score >= highscores[i])                              // if it is
        {
            if(i == 0)                                          // flag 1 for highest score, 2 for top 5
            {
                *ghs = 1;
            }
            else
            {
                *ghs = 2;
            }
            for(j = 0; j < n - i; j++)                          // go through the rest of the elements
            {
                highscores[n-j] = highscores[n-j-1];            // bring everyone down by one element
            }
            highscores[i] = score;                              // put the highscore you got in its position
            for(k = 0; k < n; k++)
            {
                fprintf(fp, "%d\n", highscores[k]);             // save it in file
            }

            break;
        }
    }
}

void gethighscores(int highscores[])                
{
    FILE *hp, *hnp;
    int i = 0;
    hp = fopen("highscore.txt", "r+");                          // basic score reading into an array.
    while(1)
    {
        if(feof(hp)) break;
        fscanf(hp, "%d", &highscores[i]);
        i++;
    }
}

void lasercol(Laser *lp, Enemy *ep, int n, Enemy enemies[], int *sp)
{
    int i;

    for(i = 0; i < n; i++)                                                                      // go through each enemy
    {
        if((lp->current >= enemies[i].posx - 40) && (lp->current <= enemies[i].posx + 20))      // if we have a collision between them (x axis)
        {
            if((lp->posy >= enemies[i].posy - 23) && (lp->posy <= enemies[i].posy + 23))        // (y axis)
            {
                enemies[i].alive = 0;                                                           // kill/reset enemy
                enemies[i].posx = 1000;                                                         
                *sp = *sp + 100;                                                                // increase score in 100
            }
        }
    }
}

void speciallasercol(Laser *lp, Enemy *sep, int *sp)
{
    int i;
    if((lp->current >= sep->posx - 40) && (lp->current <= sep->posx + 20))                     // if we have a collision between them (x axis)
    {
        if((lp->posy >= sep->posy - 23) && (lp->posy <= sep->posy + 23))                       // (y axis)
        {
            sep->alive = 0;                                                                    // kill/reset enemy                                                     
            *sp = *sp + 300;                                                                   // increase score in 100
        }
    }
}

void checkcollision(Ship *up, Enemy *ep, int n)                                                
{
    int i, j, r = 20, point1x, point2x, point1y, point2y;
    for(i = 0; i < n; i++)
    {
        if((up->posx <= ep->posx + 2*r) && (up->posx >= ep->posx - 2*r) && (up->posy <= ep->posy + 2*r) && (up->posy >= ep->posy - 2*r))
        { // SAME RECTANGULAR AREA
            for(j = 0; j < 360; j++) // check for circular area within certain error margin in each degree
            {
                point1x = up->posx + r*cos(M_PI/180*j);
                point2x = ep->posx + r*cos(M_PI/180*j + M_PI);
                point1y = up->posy + r*sin(M_PI/180*j);
                point2y = ep->posy + r*sin(M_PI/180*j + M_PI);

                if((point1x >= point2x - 1) && (point1x <= point2x + 1) && (point1y >= point2y - 1) && (point1y <= point2y + 1))
                {
                    up->alive = 0;   // you die in this collision
                }
            }
        }
        ep++;
    }
}

void checkspecialcol(Ship *up, Enemy *sep)
{
    int j, point1x, point1y, point2x, point2y;
    int r = 20;

    if((up->posx <= sep->posx + 2*r) && (up->posx >= sep->posx - 2*r) && (up->posy <= sep->posy + 2*r) && (up->posy >= sep->posy - 2*r))
    { // SAME RECTANGULAR AREA
        for(j = 0; j < 360; j++) // check for circular area within certain error margin in each degree
        {
            point1x = up->posx + r*cos(M_PI/180*j);
            point2x = sep->posx + r*cos(M_PI/180*j + M_PI);
            point1y = up->posy + r*sin(M_PI/180*j);
            point2y = sep->posy + r*sin(M_PI/180*j + M_PI);

            if((point1x >= point2x - 1) && (point1x <= point2x + 1) && (point1y >= point2y - 1) && (point1y <= point2y + 1))
            {
                up->alive = 0;   // you die in this collision
            }
        }
    }
}

void powerupcol(Powerup *p, Ship *up, int r, int *adp, int *pwdp)
{
    int j, r2 = 10;
    int point1x, point1y, point2x,point2y;

    if((up->posx <= p->posx + r + 10) && (up->posx >= p->posx - r - 10) && (up->posy <= p->posy + r + 10) && (up->posy >= p->posy - r - 10))
        { // SAME RECTANGULAR AREA (same method as checkcollision())
            for(j = 0; j < 360; j++)
            {
                point1x = up->posx + r*cos(M_PI/180*j);
                point2x = p->posx + r2*cos(M_PI/180*j + M_PI);
                point1y = up->posy + r*sin(M_PI/180*j);
                point2y = p->posy + r2*sin(M_PI/180*j + M_PI);

                if((point1x >= point2x - 1) && (point1x <= point2x + 1) && (point1y >= point2y - 1) && (point1y <= point2y + 1))
                {
                   if(p->type == 0)                                 // more speed
                   { 
                      up->powerup = 0;
                   }
                   else if(p->type == 1)                            // rapid fire
                   {
                       up->powerup = 1;
                   }
                   *adp = 1;                                        // powerup processing variables (in main())
                   p->inuse = 1;
                   *pwdp = 0;
                }
            }
        }
}

void printmenu(int xwindow, int ywindow)                            // basic menu printing
{
    gfx_color(255,0,255);
    gfx_text(xwindow/2 - 60, ywindow/2, "NUGHI the game");
    gfx_text(xwindow/2 - 75, ywindow/2 + 20, "Click screen to start");
    gfx_text(xwindow/2 - 75, ywindow/2 + 40, "Press H for highscores");
}

void printenemies(int xwindow, int ywindow, Enemy *ep, int n, Enemy enemies[], int *tp)
{
    int done = 0, i, j, r = 20;
    Enemy *firstenemy = ep, *nextenemy = ep;
    nextenemy++;
    
    // make everyone get alive with an initial position
    for(i = 0; i < n; i++)
    {
        if(ep->alive == 0)
        {
            ep->posy = rand()%(ywindow-40) + 40; // random position
            ep->posx = xwindow + 100;
            ep->alive = 1;
        }
        if(ep->posx <= 0)
        {
            ep->alive = 0;                       // restart in final position
        }
        ep++;
    }

    // do not let enemies be printed in the same place
    // NOTE: since i am executing this for loop every frame of the game, locking it in a while loop
    // to not let the positions of the enemies be the same (never) seemed to be not only unpractical
    // but also to lag the game. Since this for loop always executes, eventually all circles get to a valid position
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if((i != j) && (enemies[i].posy >= enemies[j].posy - 40) && (enemies[i].posy <= enemies[j].posy + 40) && (enemies[i].posx >= enemies[j].posx - 40) && (enemies[i].posx <= enemies[j].posx + 40))
            {
                enemies[i].posy = rand()%(ywindow-40) + 40;
            }
        }
    }

    // make everyone move and print
    ep = firstenemy;
    for(i = 0; i < n; i++)
    {
        ep->posx -= 2;                                // change position
        gfx_color(0,0,255);                           // sprite creation
        gfx_circle(ep->posx, ep->posy, r);
        gfx_color(255,50,50);
        square(ep->posx + (r-5)*cos(M_PI/180 * *tp), ep->posy + (r-5)*sin(M_PI/180 * *tp), 5);
        square(ep->posx + (r-5)*cos(M_PI/180 * (*tp+180)), ep->posy + (r-5)*sin(M_PI/180 * (*tp+180)), 5);
        ep++;
    }
}

void printspecialenemy(int xwindow, int ywindow, Enemy *sep, int *tp, int score)
{
    int done = 0, i, j, r = 20;
    
    // make enemy alive with special position

    if(sep->alive == 0 && score > 1000)
    {
        sep->posy = rand()%(ywindow-240) + 121; // random position
        sep->posx = xwindow + 100;
        sep->alive = 1;
        sep->initialposy = sep->posy;
    }
    else if(sep->alive == 1) 
    {
        if(sep->posx <= 0)
        {
            sep->alive = 0;                       // restart in final position
        }

        // make enemy move and print
        sep->posx -= 2;                                // change position
        sep->posy = sep->initialposy + 100*sin(M_PI/180 * *tp);
        gfx_color(255,150,255);                           // sprite creation
        gfx_circle(sep->posx, sep->posy, r);
        gfx_color(255,255,0);
        square(sep->posx + (r-5)*cos(M_PI/180 * *tp), sep->posy + (r-5)*sin(M_PI/180 * *tp), 5);
        square(sep->posx + (r-5)*cos(M_PI/180 * (*tp+180)), sep->posy + (r-5)*sin(M_PI/180 * (*tp+180)), 5);
    }
}

void shootlaser(Laser *lp, int x, int y, int t)       // what happens when you shoot the laser
{
    if(lp->active == 0)
    {
        lp->posx = x;
        lp->posy = y;
        lp->active = 1;
        lp->to = t;                                   // initial "time"
        lp->ready = 0;                                
    }
}

void shotprocess(Laser *lp, int xwindow, int t)
{
    gfx_color(255,0,0);
    lp->current = lp->posx + lp->velocity * (t - lp->to);                   // define position based on initial time (x = x0 + v*deltat)
    gfx_line(lp->current , lp->posy, lp->current  + 20, lp->posy);          // laser sprite
    if(lp->delay == 2000) gfx_line(xwindow - 150, 130, xwindow - 150 + (lp->current)/60, 130);  // laser reload bars
    else gfx_line(xwindow - 150, 130, xwindow - 150 + (lp->current)/30, 130);                   // special case for rapid fire

    if(lp->current  >= xwindow + lp->delay)                                                     // if laser has waited enough time
    {
        lp->active = 0;                                                                         // recharge it
        lp->ready = 1;
    }
}

void printbackground(int xw, int yw, int laserready, int score, Ship *up, int powerupdelay)
{
    gfx_color(255,255,255);
    // instructions and score
    gfx_text(xw - 150, 50, "Hold WASD to move");
    gfx_text(xw - 150, 70, "Press SPACE to shoot");
    char scorestr[15];
    sprintf(scorestr, "Score: %d", score);
    gfx_text(xw - 150, 90, scorestr);
    gfx_text(xw - 150, 110, "Press P to pause");

    // variable dependent prints
    if(laserready == 1)
    {
        gfx_color(255,0,0);
        gfx_text(xw - 150, 130, "Laser ready!");
    }
    if(up->powerup == 0)
    {
        gfx_color(0,255,255);
        gfx_text(xw - 150, 150, "More speed!");
        gfx_line(xw - 150, 160, xw - 100 - powerupdelay/40, 160);
    }
    else if(up->powerup == 1)
    {
        gfx_color(255,111,0);
        gfx_text(xw - 150, 150, "Rapid fire!");
        gfx_line(xw - 150, 160, xw - 100 - powerupdelay/40, 160);
    }
}

void printship(Ship usership, int *tp)
{
    int i, j, r = 20, size = 8;

    if(usership.alive == 1)
    {
        // print the central circle
        gfx_color(255, 0,195);
        gfx_circle(usership.posx, usership.posy, r);

        // print the polygons that rotate around it
        if(usership.powerup == 0) gfx_color(0,255,255);
        else if(usership.powerup == 1) gfx_color(255,111,0);
        else gfx_color(0,255,0);

        for(j = 0; j < 4; j++)
        {
            rotatepolygon(usership.posx + (r-5)*cos(M_PI/180 * *tp + M_PI/2 * j), usership.posy + (r-5)*sin(M_PI/180 * *tp + M_PI/2 * j), tp, 8);
        }

        // text so you identify the ship
        gfx_text(usership.posx - 13, usership.posy - 28, "NUGHI");
    }
}

void square(int x, int y, int l)
{
    gfx_line(x-l, y-l, x+l, y-l);
    gfx_line(x+l, y-l, x+l, y+l);
    gfx_line(x+l, y+l, x-l, y+l);
    gfx_line(x-l, y+l, x-l, y-l);
}

void rotatepolygon(int xc, int yc, int *i, int size) 
{
    int j, x1, x2, y1, y2;

    for(j = 0; j < 5; j++)
    {
        x1 = xc + size * cos(M_PI/180 * *i + (j * 2 * M_PI/5));
        x2 = xc + size * cos(M_PI/180 * *i + ((j+1) * 2 * M_PI/5));
        y1 = yc + size * sin(M_PI/180 * *i + (j * 2 * M_PI/5));
        y2 = yc + size * sin(M_PI/180 * *i + ((j+1) * 2 * M_PI/5));
        gfx_line(x1, y1, x2, y2);
    }

}

void gameover(int x, int y, int score, int *ghs)
{
    gfx_color(255,0,255);
    gfx_text(x/2 - 30, y/2, "Game Over!");
    // score
    char scorestr[15];
    sprintf(scorestr, "Score: %d", score);
    gfx_text(x/2 - 30, y/2 + 20, scorestr);
    gfx_text(x/2-30, y/2 + 40, "Press R to restart");

    // print high score messages if you get it
    if(*ghs == 1)
    {
        gfx_text(x/2-30, y/2 + 60, "HIGH SCORE!");
    }
    else if(*ghs == 2)
    {
        gfx_text(x/2-30, y/2 + 60, "TOP 5 SCORES!");
    }
}