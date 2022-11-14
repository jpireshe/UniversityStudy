#include <stdio.h> 

#include "littlelib.h"

void printprime()
{
    int n = randint(5,800);
    if (is_prime(n)) {
        printf("%d is prime\n", n);
        return;
    }
    printf("%d is not prime\n", n);
}

int main() 
{ 
    int i = 0;
  
    init_littlelib();
    
    for (i=0; i<10; i++)
        printprime();
    
    return 0; 
}
