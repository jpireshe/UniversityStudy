#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// your code here (define the dino struct)
typedef struct dino {
    double lat;
    double lng;
    char* name;
} dino;

void save_dino(dino *d, char *ofn)
{
    FILE* fp = fopen(ofn, "wb");
    fwrite(&d->lat, sizeof(double), 1, fp);
    fwrite(&d->lng, sizeof(double), 1, fp);
    // SAVE LEN
    int len = strlen(d->name);
    fwrite(&len, sizeof(int), 1, fp);
    fwrite(d->name, strlen(d->name), 1, fp);

    fclose(fp);
}

void load_dino(dino *d, char *ifn)
{
    FILE* fp = fopen(ifn, "rb");
    fread(&d->lat, sizeof(double), 1, fp);
    fread(&d->lng, sizeof(double), 1, fp);
    int len;
    fread(&len, sizeof(int), 1, fp);
    // YOU HAVE TO ALLOCATE YOUR STRINGS: 
    d->name = (char *)malloc(len*sizeof(char));
    fread(d->name, len, 1, fp);

    fclose(fp);
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;
    
    char *fn = argv[1];
    
    // create a dino struct and give it the following values:
    // latitude = 51.083332
    // longitude = -1.166667
    // name = "Aves indet."
    // do NOT hardcode the string length, get it with strlen() instead
    dino d0;
    d0.lat = 51.083332;
    d0.lng = -1.166667;
    d0.name = "Aves indet.";

    // call save_dino() and save d0 to the given filename (fn)
    save_dino(&d0, fn);

    dino d1;
    load_dino(&d1, fn);
    // call load_dino() and load the file you just saved into d1 (NOT d0)
    printf("d1.lat %f\n", d1.lat);
    printf("d1.lng %f\n", d1.lng);
    printf("d1.name %s\n", d1.name);
    
    return 0;
}
