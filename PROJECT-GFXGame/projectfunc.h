// NUGHI, by Joao Henares
// ND 2022 - CSE 20311.01
// Mini final project - made to synthesize coursework
// tip: if you open this in vscode it should be easy to read all comments.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

typedef struct ship_struct {
    int posx;                       // position in x
    int posy;                       // position in y
    int alive;                      // check if ship is alive
    int v;                          // velocity
    int powerup;                    // 0 for double velocity, 1 for rapid fire, 100 for nothing
} Ship;

typedef struct powerup {
    int posx;                       // position in x
    int posy;                       // position in y
    int active;                     // check if powerup is active (0 for not active, 1 for spawn, 2 for active)
    int v;                          // velocity
    int type;                       // 0 for double velocity, 1 for rapid fire
    int inuse;                      // check if power up is being currently used
} Powerup;

typedef struct laser_struct {
    int posx;                       // position in x
    int posy;                       // position in y
    int active;                     // check if ship is active
    int velocity;                   // the velocity
    int to;                         // time since it was shot
    int current;                    // current laser position
    int delay;                      // laser time delay to be shot again
    int ready;                      // flag for when the laser is ready to be used
} Laser;

typedef struct enemy_struct {
    int posx;                       // position in x
    int posy;                       // position in y
    int alive;                      // check if ship is alive
    int v;                          // velocity
    int limit;                      // limit to y pos (special enemy)
    int initialposy;                // initial y pos (special enemy)
} Enemy;


// MENU
void printmenu(int, int);                                                                                              // prints the menu of the game
void reset(Ship *up, int *sp, int numenemies, Enemy *ep, Laser *lp, int *ghs, Powerup *dvp, Powerup *rfp, Enemy *sep); // reset stuff in menu
void gethighscores(int highscores[]);                                                                                  // get high score data from files 
void showhs(int highscores[], int, int, int);                                                                          // shows the high scores
void checkforhighscores(int score, int highscores[], int n, int *);                                                    // checks if your score is one of the high scores
void gameover(int x, int y, int score, int *ghs);                                                                      // shows game over

// GAMEPLAY PRINTS
void printship(Ship, int *);                                                                                           // prints the ship sprite
void square(int, int, int);                                                                                            // prints a square
void rotatepolygon(int, int, int *, int);                                                                              // prints a rotating polygon
void printbackground(int, int, int, int, Ship*, int);                                                                  // prints the background (and some info)

//LASER
void shootlaser(Laser *, int, int, int);                                                                               // sets the laser shot
void shotprocess(Laser *, int, int);                                                                                   // process where the laser shot is
void lasercol(Laser *, Enemy *, int, Enemy [], int *);                                                                 // checks for collision between laser and enemy

// ENEMIES
void printenemies(int, int, Enemy *, int, Enemy [], int *);                                                            // prints the enemy according to their position and moves them
void checkcollision(Ship *, Enemy *, int);                                                                             // checks for a collision between ship and enemy.
void printspecialenemy(int xwindow, int ywindow, Enemy *sep, int *tp, int score);                                      // prints and moves the special enemy
void speciallasercol(Laser *lp, Enemy *sep, int *sp);                                                                  // detects collision between laser and special enemy

// POWER UPS
void rolldice(Powerup *p, int n, int, int);                                                                            // rolls a 100 side dice and spawns a power up
void spawnpowerup(Powerup *p, int xwindow, int ywindow, int *tp);                                                      // spawns and processes the powerup
void powerupcol(Powerup *dvp, Ship *up, int r, int *adp, int *pwdp);                                                   // checks for collision (powerup and user)
