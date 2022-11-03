// NUGHI, by Joao Henares
// ND 2022 - CSE 20311.01
// Mini final project - made to synthesize coursework

// tip: if you open this in vscode it should be easy to read all comments.

#include "projectfunc.h"

int main()
{
    //=====================[VARIABLES]======================

    srand(time(0));
    int xwindow = 900, ywindow = 700;                                   // window
    char c = '0';                                                       // user interactions
    int showmenu = 957;                                                 // menu control
    int score = 0, *sp = &score;                                        // score of the game
    int r = 20;                                                         // circle sprite radius

    Ship usership = {150, 350, 1, 4, 100};                              // our ship of the game!
    Ship *up = &usership;

    int time = 0, *tp;                                                  // time and its pointer (animation)
    tp = &time;

    // laser struct
    Laser userlaser;                                                    // what the ship shoots and its pointer
    Laser *lp;
    lp = &userlaser;
    userlaser.active = 0;
    userlaser.current = 0;
    userlaser.delay = 2000;
    userlaser.ready = 1;
    userlaser.velocity = 5;

    // power up - double velocity
    Powerup doublev, *dvp = &doublev;                                   // when you use it, it speeds you up (used to double)
    doublev.active = 0;                                                 // speed, but got too strong (check parameters in header)
    doublev.v = 2;
    doublev.type = 0;
    doublev.inuse = 0;
    int powerupdelay = 0, *pwdp = &powerupdelay, activatedelay = 0, *adp = &activatedelay; // those are used in the activation of powerups

    // power up - rapid fire
    Powerup rapidfire, *rfp = &rapidfire;                                // this one makes you fire faster (check parameters in header)
    rapidfire.active = 0;
    rapidfire.v = 2;
    rapidfire.type = 1;
    rapidfire.inuse = 0;

    // ENEMIES
    Enemy enemies[6], *ep;                                               // vector of enemy structs
    int numenemies = sizeof(enemies)/sizeof(Enemy), i;
    ep = enemies;

    Enemy specialenemy, *sep = &specialenemy;                            // special enemy who moves up and down

    // high score
    int check = 0, gothighscore, *ghs = &gothighscore;                   // highscore computer (saves across sections)
    int highscores[5], nhs = 5;

    //=======================[FILES]========================

    gethighscores(highscores);                                           // gets high scores from file

    //===================[CREATE WINDOW]====================

    gfx_open(xwindow, ywindow, "NUGHI The Game");

    //====================[WINDOW LOOP]====================

    while(1)
    {
        //====================[MENU]=====================

        if(showmenu == 957)          
        {
            printmenu(xwindow, ywindow);                                // shows menu

            ep = enemies;
            reset(up, sp, numenemies, ep, lp, ghs, dvp, rfp, sep);      // resets a lot of parameters in the post game over
            ep = enemies;                                               // so you can play again

            check = 0;                                                  // powerup variables (not thrown into functions)
            activatedelay = 0;                                          // because that would create even more pointers
            powerupdelay = 0;
        }

        //==========[USER INPUT COLLECTION]================

        if(gfx_event_waiting())                                         
        {
            c = gfx_wait();
            if(c != 'h')
            {
                showmenu = 0;
            }
            else
            {
                showmenu = 1;                                           // special case to see highscores (which also pauses game)
            }
        }
        
        //=============[PROCESS INPUTS]====================

        // print the action part if not in menu and not in pause or high score screen
        if(showmenu == 0 && c != 'p')
        {
            if(usership.alive == 1)                                            // gameplay loop
            {
                printship(usership, tp);                                       // print ourselves

                printbackground(xwindow, ywindow, userlaser.ready, score, up, powerupdelay); // print background info

                // print enemies
                ep = enemies;
                printenemies(xwindow, ywindow, ep, numenemies, enemies, tp);    // moves and puts enemies in screen
                printspecialenemy(xwindow, ywindow, sep, tp, score);

                // NUGHI movement
                if(c == 'w')
                {
                    usership.posy -= usership.v;
                    c = '0';
                }
                else if( c == 's')
                {
                    usership.posy += usership.v;
                    c = '0';
                }
                else if( c == 'd')
                {
                    usership.posx += usership.v;
                    c = '0';
                }
                else if( c == 'a')
                {
                    usership.posx -= usership.v;
                    c = '0';                                                    // put c = '0' so you only walk once
                }
                
                // shooting
                else if((int)c == 32)                                           // space bar
                {
                    shootlaser(lp, usership.posx, usership.posy, *tp);
                    c = '0';                                                    // so you shoot once
                }

                if(userlaser.active == 1)                                       // user hit space bar and laser is
                {                                                               // within existing bounds

                    shotprocess(lp, xwindow, *tp);                              // move laser, checks if it is out of bounds

                    // detect collision of laser with enemy
                    ep = enemies;
                    lasercol(lp, ep, numenemies, enemies, sp);                  // checks for collision of laser and enemy
                    speciallasercol(lp, sep, sp);
                }

                //=========[POWER UP SECTION]==========

                // double velocity
                if(doublev.active == 0)                                         // double v little token does not exist
                {
                    rolldice(dvp, 20, xwindow, ywindow);                        // tries to make it exist by rolling a dice
                }
                else if(doublev.active == 1)                                    // dice rolled and it exists
                {
                    spawnpowerup(dvp, xwindow, ywindow, tp);                    // makes it move
                    powerupcol(dvp, up, r, adp, pwdp);                          // checks for collision with user
                }

                // rapid fire
                if(rapidfire.active == 0)                                       // same as with double v
                {
                    rolldice(rfp, 30, xwindow, ywindow);
                }
                else if(rapidfire.active == 1)
                {
                    spawnpowerup(rfp, xwindow, ywindow, tp);
                    powerupcol(rfp, up, r, adp, pwdp);
                }

                // processing powerup
                if(usership.powerup == 0 && dvp->inuse == 1)                    // collision with double velocity was successful
                {   
                    if(rfp->inuse != 0)                                         // turns off the other powerups
                    {
                        rfp->inuse = 0;
                        rfp->posx = 0;
                    }
                    userlaser.delay = 2000;

                    usership.v = 6;                                             // turns on the double velocity powerup
                    if(activatedelay == 1)                                      // if we are making use of the delay
                    {                                                           // then expand its counter
                        powerupdelay++;
                    }
                    else                                                        // turn powerup off.
                    {
                        usership.powerup = 100;
                        dvp->inuse = 0;
                    }
                    if(powerupdelay == 2000)                                    // when counter reaches delay limit
                    {
                        activatedelay = 0;                                      // turn everything off and reset loop
                        powerupdelay = 0;
                        doublev.active = 0;
                    }
                }
                else if(usership.powerup == 1 && rfp->inuse == 1)               // same as in double velocity
                {
                    if(dvp->inuse != 0)
                    {
                        dvp->inuse = 0;
                        dvp->posx = 0;
                    }
                    usership.v = 4;

                    userlaser.delay = 500;
                    if(activatedelay == 1)
                    {
                        powerupdelay++;
                    }
                    else
                    {
                        usership.powerup = 100;
                        rfp->inuse = 0;
                    }
                    if(powerupdelay == 2000)
                    {
                        activatedelay = 0;
                        powerupdelay = 0;
                        rapidfire.active = 0;
                    }
                }
                else {usership.v = 4; userlaser.delay = 2000; activatedelay = 0;}

                // ways of losing the game
                if(usership.posx - r >= xwindow || usership.posx + r <= 0 || usership.posy + r <= 0 || usership.posy - r >= ywindow)
                {                                                                        // out of bounds
                    usership.alive = 0;
                }
                else
                {
                    ep = enemies;
                    checkcollision(up, ep, numenemies);                                  // check for collision; if we find a collision we lose the game.
                    checkspecialcol(up, sep);
                }

                score++;                                                                 // at the end of each loop we get 1 of score for being alive.
            }
            else                                                                         // print game over
            {
                gameover(xwindow, ywindow, score, ghs);
                if(check == 0)                                                           // counter reset at the beggining 
                                                                                         //of each game (check only once for 
                                                                                         //high score)
                {
                    checkforhighscores(score, highscores, nhs, ghs);
                    check = 1;
                }
                if(c == 'r')                                                             // reset game in gameover screen
                {
                    showmenu = 957;
                    usership.alive = 1;
                }
            }
        }
        else if(showmenu == 1)                                                          // high score menu
        {
            showhs(highscores, xwindow, ywindow, nhs);
        }
        else if(c == 'p' && showmenu != 957)                                            // pause menu
        {
            gfx_color(255,0,255);
            gfx_text(xwindow/2 - 30, ywindow/2, "Game Paused");
            gfx_text(xwindow/2 - 50, ywindow/2 + 20, "Press any key to continue");
        }

        if((int)c == 27) break;                                                         // get out of game with esc key

        //=============[FLUSH, SLEEP AND CLEAR]=============
        gfx_flush();
        usleep(6000);
        gfx_clear();
        time++;
    }

    return 0;
}