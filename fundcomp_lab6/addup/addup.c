//addup.c
//

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
     int n1, n2, sum;

     if (argc == 1) {
          printf("Enter two integers: ");
          scanf("%d %d", &n1, &n2);
     }
     else if (argc == 2) {
          printf("incorrect usage: too few arguments\n");
          return 1;
     }
     else if (argc == 3) {
          n1 = atoi(argv[1]);
          n2 = atoi(argv[2]);
     }
     else {
          printf("incorrect usage: too many arguments\n");
          return 2;
     }

     printf("Sum: %d\n", n1+n2);

     return 0;
}
