#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

#include "libdinos.h"
#include "libgeodist.h"

#define MAX_THREADS 4
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

/**** THREAD WORKSPACE ****/

typedef struct {                                                                // thread argument struct
    int tn;                                                                     // thread number
    int dinoindex;
} threadarg;
double nearest_dinos[MAXDINOS];                                                 // globals 
dino *dinos[30000];

void* threadfcn(void* varg) {
    threadarg* args = (threadarg*) varg;                                        // cast void * into args context.
    nearest_dinos[args->dinoindex] = nearest_dino(dinos[args->dinoindex], dinos, MAXDINOS, &calc_geodist);
}

/**************************/

int main() {
    int n = readdinos("dinosaur.dat", dinos);

    threadarg targs[MAX_THREADS];                                               // Create array of thread args
    for(int i = 0; i < MAX_THREADS; i++) {                                      // Put parameters into them: 
        targs[i].tn = i;                                                        // thread number for debugging
    }

    pthread_t tid[MAX_THREADS];                                                 // thread ID structure
    int j = 0;

    while (j < MAXDINOS) {
        for(int i = 0; i < MAX_THREADS; i++) {                                  // create the threads themselves
            targs[i].dinoindex = j + i;
            pthread_create(&tid[i], NULL, threadfcn, (void*)&targs[i]);         // this is pretty much inspired by the class code;
        }                                                                       // i would like to understand it better (and why not process 5k dinos in each thread at once?)
        for(int i = 0; i < MAX_THREADS; i++) pthread_join(tid[i],NULL);         // join threads
        
        j += MAX_THREADS;
    }
    
    for(int i = 0; i < MAXDINOS; i++) printf("%d\t%f\n", i, nearest_dinos[i]);  // print each nearest dino
    for(int i = 0; i < n; i++) {free(dinos[i]->name); free(dinos[i]);}
    return 0; 
}
