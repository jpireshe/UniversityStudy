#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <string.h>

#include "libdinos.h"
#include "libgeodist.h"

dino *dinos[30000];

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

void handle_sigusr1(int sig, siginfo_t* siginfo, void* context) {
    int dinonum;                                    // integer for the number we will read from dinonum
    FILE* fp = fopen("dinonum.bin", "rb");
    fread(&dinonum, sizeof(int), 1, fp);            // read it from dinonum.bin
    
    char ofn[30];                   
    sprintf(ofn, "dino_%d.bin", dinonum);

    save_dino(dinos[dinonum], ofn);                 // load it to file in save_dino
}

void handle_sigusr2(int sig, siginfo_t* siginfo, void* context) {
    int dinonum;                                    // integer for the number we will read from dinonum
    FILE* fp = fopen("dinonum.bin", "rb");          // file pointer to dinonum
    fread(&dinonum, sizeof(int), 1, fp);            // read it from dinonum.bin
    
    char ofn[30];                                   // filename of dino to be retrieved
    sprintf(ofn, "dino_%d.bin", dinonum);
    dino* d = malloc(sizeof(dino));                 // alloc a dino for the load function

    load_dino(d, ofn);
    free(dinos[dinonum]->name);                     // copy d dino to dinos[dinonum]
    dinos[dinonum]->namelen = d->namelen;
    dinos[dinonum]->name = strdup(d->name);
    dinos[dinonum]->lat = d->lat;
    dinos[dinonum]->lng = d->lng;
    dinos[dinonum]->maxma = d->maxma;
    dinos[dinonum]->minma = d->minma;

    free(d->name);                                  // finally, free the d dino
    free(d);        
}

int main()
{
    struct sigaction act1, act2;                    // two structs for 2 signalers
    act1.sa_sigaction = &handle_sigusr1;
    act1.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act1, NULL);
    
    act2.sa_sigaction = &handle_sigusr2;
    act2.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &act2, NULL);

    int n;
    
    n = readdinos("dinosaur.dat", dinos);

    while(1) {
        
    }

    for(int i = 0; i < n; i++) {free(dinos[i]->name); free(dinos[i]);}
    return 0; 
}
