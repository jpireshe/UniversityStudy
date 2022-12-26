#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libdinos.h"
#include <math.h>
#include <limits.h>

// need to clean these
void save_dino(dino *d, char *ofn)
{
    FILE* fp = fopen(ofn, "wb");                                    // file to be opened
    fwrite(&d->lat, sizeof(double), 1, fp);                         // write dinodata to the file
    fwrite(&d->lng, sizeof(double), 1, fp);
    fwrite(&d->minma, sizeof(double), 1, fp);
    fwrite(&d->maxma, sizeof(double), 1, fp);
    fwrite(&d->namelen, sizeof(int), 1, fp);
    fwrite(d->name, d->namelen, 1, fp);                             // i used namelen because to write we don't need
    fclose(fp);                                                     // to solve the same bug as in load_dino
}

void load_dino(dino *d, char *ifn)
{
    FILE* fp = fopen(ifn, "rb");                                    // open file
    fread(&d->lat, sizeof(double), 1, fp);
    fread(&d->lng, sizeof(double), 1, fp);
    fread(&d->minma, sizeof(double), 1, fp);
    fread(&d->maxma, sizeof(double), 1, fp);
    fread(&d->namelen, sizeof(int), 1, fp);                         // read stuff
    d->name = (char *)malloc((d->namelen + 1)*sizeof(char));        // why + 1? Because we NEED to put the last '/0' to finish the string
    fread(d->name, d->namelen, 1, fp);                              // read still in namelen
    d->name[d->namelen] = 0;                                        // but we have to terminate the string for all of it to work

    fclose(fp);
}

int readline(FILE *fp, char *buf, int len)
{
    char c = fgetc(fp);
    int i = 0;
    
    while((c != '\n') && (i < len - 1))
    {
        buf[i] = c;
        
        c = fgetc(fp);
        i++;

        if (c == EOF){
            buf[i] = '\0';
            i = -1;
            break; 
        }
    }
    if(i >= 0) {buf[i] = 0;}
    
    return i;
}

int split(char *buf, char **splits, char delim, int max, int len) {
    int i = 0, j = 0, k = 0;                                            // You have to build your own string!
    splits[j] = malloc(len*sizeof(char));

    while (buf[i] != 0 && i < len) {
        if(buf[i] != delim) {
            splits[j][k] = buf[i];
            k++;
        }
        else {
            splits[j][k] = 0;
            j++;
            splits[j] = malloc(len*sizeof(char));
            k = 0;
        }  
        i++;
    }

    splits[j][k] = 0;

    return j;
}

int readdinos(char *fn, dino **dinos) {
    FILE* fp = fopen(fn, "r");
    int n = 0, len = 2048, r, max = 50, ns, expected = 27;
    char* buf = malloc(len * sizeof(char));

    r = readline(fp, buf, len);
    
    while(r != -1) {
        char* splits[max];
        r = readline(fp, buf, len);
        ns = split(buf, splits, '\t', max, len);
        if(ns == expected) {
            dinos[n] = (dino*) malloc(sizeof(dino));
            dinos[n]->lat = strtod(splits[19], NULL);
            dinos[n]->lng = strtod(splits[18], NULL);
            dinos[n]->maxma = strtod(splits[15], NULL);
            dinos[n]->minma = strtod(splits[16], NULL);
            dinos[n]->namelen = strlen(splits[5]);
            dinos[n]->name = strdup(splits[5]);
            n++;
        }
        for(int i = 0; i < ns + 1; i++) free(splits[i]);             // NS + 1!!! (makes sense LOL)
    }

    free(buf);
    fclose(fp);
    return n;
}

double nearest_dino(dino *d0, dino **dinos, int numdinos, double(*f)(dino *, dino *)) {
    double d = INT_MAX;                                             // distance variable initialized to max
    //int cpy = 0;                                                    // index to memcpy to d1

    for(int i = 0; i < numdinos; i++)                               // iterate the dinos
        if (((*f)(d0, dinos[i]) < d) && ((*f)(d0, dinos[i]) > 0)) { // if our func is smaller than the current one and not 0
            d = (*f)(d0, dinos[i]);                                 // update distance
            //cpy = i;                                                // update index
        }

    //memcpy(d1, dinos[cpy], sizeof(dino));                           // finally, copy to memory the info of the dino you want 

    return d;                                                       // return distance
}