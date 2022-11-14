#include <stdio.h>
#include <stdlib.h>

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
    for(int i = 0; i < len; i++) {
        buf[i] = 0;
    }
}

int main()
{
    FILE *fp;
    char delim = '\t';
    int len = 2048;
    char *buf = malloc(len * sizeof(char));
    int n, r, i = 0;
    int maxlines = 50;
    
    fp = fopen("dinosaur.dat", "r");
    
    n = readline(fp, buf, len);
    printf("read %d chars\n", n);
    
    // n != -1: returned -1 from readline (EOF)
    while((n != -1) && (i<maxlines))
    {
        r = redelim('\t', ';', buf, len);
        printf("changed %d delims: %s\n", r, buf);
        
        clearbuf(buf, len);
        n = readline(fp, buf, len);
        
        i++;
    }
    
    return 0; 
}
