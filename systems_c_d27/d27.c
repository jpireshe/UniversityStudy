#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

#include "libdinos.h"
#include "libgeodist.h"

#define NUM_PROCESSES 4
#define MAXDINOS 20000

double calc_geodist(dino *d0, dino *d1)
{
    return geodist(d0->lat, d0->lng, d1->lat, d1->lng);
}

double calc_timedist(dino *d0, dino *d1)
{
    double t0 = (d0->maxma + d0->minma) / 2;
    double t1 = (d1->maxma + d1->minma) / 2;
    return fabs(t0 - t1);
}

void printdino(dino *d)
{
    printf("%f %f %f %f %d %s\n", d->lat, d->lng, d->maxma, d->minma, d->namelen, d->name);
}

/***** PROCESS WORKSPACE ******/
dino *dinos[30000];                                                             // globals
double nearest_dinos[MAXDINOS];   

typedef struct {                                                                                                                                 
    int dinoindex;
    double dist;    
} ret;

void processfunc(int dinoindex) {
    fflush(NULL);

    char *fn = malloc(128 * sizeof(char));                                      // create new file name
    sprintf(fn, "ret_%d.bin", getpid());

    FILE* fp = fopen(fn, "wb");                                                 // create new file

    double d = nearest_dino(dinos[dinoindex], dinos, MAXDINOS, &calc_geodist);  // get nearest dino, write it into new file
    fwrite(&dinoindex, sizeof(int), 1, fp);    
    fwrite(&d, sizeof(double), 1, fp);                  

    free(fn);                                                                   // free stuff
    fclose(fp);
}

/******************************/

int main() {
    int n = readdinos("dinosaur.dat", dinos), cpid, ppid = getpid(),j = 0, wpid; // variable declaration
    ret returned;

    while (j < MAXDINOS) {
        for(int i = 0; i < NUM_PROCESSES; i++) {                                // call fork to create children
            if (getpid() == ppid) {cpid = fork();}                                
            if (cpid == 0) {                                                    // make children call processfunc
                processfunc(j + i);
                return 0; 
            }
        }   

        for (int i = 0; i < NUM_PROCESSES; i++) {
            wpid = wait(NULL);

            char *fn = malloc(128 * sizeof(char));                              // open temp file
            sprintf(fn, "ret_%d.bin", wpid);                                    
            FILE* fp = fopen(fn, "rb");

            fread(&returned.dinoindex, sizeof(int), 1, fp);                     // read from file
            fread(&returned.dist, sizeof(double), 1, fp);

            nearest_dinos[returned.dinoindex] = returned.dist;                  // put into nearest dinos

            fclose(fp);
            remove(fn);
            free(fn);
        }
        
        j += NUM_PROCESSES;
    }
    
    for(int i = 0; i < MAXDINOS; i++) printf("%d\t%f\n", i, nearest_dinos[i]);  // print each nearest dino
    for(int i = 0; i < n; i++) {free(dinos[i]->name); free(dinos[i]);}
    return 0; 
}
