#include "littlelib.h"
int arraylen(int a[]) {
    int ret = 0;
    while(a[ret] != 0){
        ret++;
    }
    return ret;
}

int sumnums(int a[]) {
    int i = 0, sum = 0;
    while(a[i] != 0){
        sum += a[i];
        i++;
    }
    return sum;
}

int init_littlelib() {
    srand(1337);
}

void printarray(int a[]) {
    int i = 0;
    printf("{ ");
    while(a[i] != 0) {
        printf("%d ", a[i]);
        i++;
    }
    printf("}\n");
}

void shuffle(int *a, int len) {
    int temp, A, B;
    for(int i = 0; i < len; i++) {
        A = rand() % len;
        B = rand() % len;
        
        // swap values
        temp = *(A + a);
        *(A + a) = *(B + a);
        *(B + a) = temp;
    }

}