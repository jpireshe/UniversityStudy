#include <stdio.h>
#include <stdlib.h>

#include "libdinos.h"

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

int redelim(char curdelim, char newdelim, char *buf, int len)
{
    int count = 0;

    for(int i = 0; i < len; i++) 
        if (buf[i] == curdelim) { 
            buf[i] = newdelim;
            count++;
        }
    
    return count;
}       

void clearbuf(char *buf, int len)
{
    for(int i = 0; i < len; i++)
        buf[i] = 0;
}

int split(char *buf, char **splits, char delim, int max, int len) {
    // iteration variables
    int i = 0, j = 0, k = 0;
    char *section = malloc(len * sizeof(char));
    char *opa;

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

    free(section);
    return j;
}