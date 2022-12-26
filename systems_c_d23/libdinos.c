#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libdinos.h"
#include <math.h>
#include <limits.h>

int readline(FILE *fp, char *buf, int len)
{
    char c = fgetc(fp);
    int i = 0;
    
    while((c != '\n') && (i < len))
    {
        buf[i] = c;
        
        c = fgetc(fp);
        i++;

        if (c == EOF){
            i = -1;
            break; 
        }
    }
    
    return i;
}

int split(char *buf, char **splits, char delim, int max, int len) {
    // iteration variables
    int i = 0, j = 0, k = 0;
    char *section = malloc(len * sizeof(char));

    while ((buf[i] != 0) && (i < len)) {
        // throw in section
        if (buf[i] != delim) {
            section[k] = buf[i];
            k++;
        }
        // throw in splits, begin again
        else {
            splits[j] = section;
            // do not need to clearbuf section
            section = malloc(len * sizeof(char));
            // increase count. return k to 0.
            j++;
            k = 0;
        }
        // increase stuff to iterate
        i++;
    }
    return j;
}

int readdinos(char *fn, dino **dinos) {
    int n = 0;                                          // return variable
    FILE* fp = fopen(fn, "r");                          // file pointer

    int len = 2048;                                     // len of buffer
    char* buf = (char*) malloc(len * sizeof(char));     // where we will readline
    
    int max = 50;                                       // max size of splits               
    int expected = 27;                                  // expected size of splits
    char** splits=(char **)malloc(max * sizeof(char *));// splits double pointer
    int ns;                                             // number of splits return

    int r = 0;                                          // number of chars read in readline
    r = readline(fp, buf, len);                         // these two gotta walk together: realloc of buf and readline
    buf = (char*) malloc(len * sizeof(char));           /* however, i ask myself how to do this without having to reallocate buf */

    char* u;                                            // to use in strtod

    while(r != -1) {                                    // action will happen here: we will read lines of program!
        r = readline(fp, buf, len);                     // read line
        ns = split(buf, splits, '\t', max, len);        // split line
        if (ns == expected) {                           // checking for correct line
            dinos[n] = (dino *)malloc(sizeof(dino));    // in this case, we will put stuff into dinos[number of dinos read]->data read
            dinos[n]->lat = strtod(splits[19],   &u);   
            dinos[n]->lng = strtod(splits[18],   &u); 
            dinos[n]->maxma = strtod(splits[15], &u); 
            dinos[n]->minma = strtod(splits[16], &u); 
            dinos[n]->namelen = strlen(splits[5]);
            dinos[n]->name = splits[5];
            n++;                                        // increase count of read lines
        }
        splits=(char **)malloc(max * sizeof(char *));   // make splits go somewhere else
        buf = (char*) malloc(len * sizeof(char));       // make buf point somewhere else
    }

    return n;
}

void freedinos(dino **dinos, int n) {
    for(int i = 0; i < n; i++) {
        free(dinos[i]->name);
        free(dinos[i]);
    }
}

double nearest_dino(dino *d0, dino *d1, dino **dinos, int numdinos, double(*f)(dino *, dino *)) {
    double d = INT_MAX;                                             // distance variable initialized to max
    int cpy = 0;                                                    // index to memcpy to d1

    for(int i = 0; i < numdinos; i++)                               // iterate the dinos
        if (((*f)(d0, dinos[i]) < d) && ((*f)(d0, dinos[i]) > 0)) { // if our func is smaller than the current one and not 0
            d = (*f)(d0, dinos[i]);                                 // update distance
            cpy = i;                                                // update index
        }

    memcpy(d1, dinos[cpy], sizeof(dino));                           // finally, copy to memory the info of the dino you want 

    return d;                                                       // return distance
}

