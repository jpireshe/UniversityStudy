#include<stdio.h>

int main()
{
     
     // Mortgage Calculator by Joao Henares (jpireshe). Calculates Mortgage.
     // CSE 20311-01, Assignment: lab 2. Purpose: format output on console,
     // extend linux skills and gain experience in solving conditional and
     // iterative problems.
     
     // ask for user input
     float principal, interestRate, desiredPayment;

     // check also for invalid numeric input
     printf("Please enter principal / initial amount: ");
     scanf("%f", &principal);
     while (principal < 0){
          printf("Principal can not be less than 0. Input again: ");
          scanf("%f", &principal);
     }
     
     // interest rate: check for invalid numeric input
     printf("Please enter interest rate: ");
     scanf("%f", &interestRate);
     while (interestRate < 0){
          printf("Interest rate can not be less than 0. Input again: ");
          scanf("%f", &interestRate);
     }
     
     // do the same with desired payment
     printf("Please enter desired monthly payment: ");
     scanf("%f", &desiredPayment);
     while (desiredPayment < 0){
          printf("Desired Payment can not be less than 0. Input again: ");
          scanf("%f", &desiredPayment);
     }
     
     // monthly interest to help calculate values on table
     float monthlyInterest;
     monthlyInterest = interestRate / 12;

     // calculation of interest based on monthly interest and payment, fint
     float fint = monthlyInterest * principal;

     // nmonths: number of months
     int nmonths = 0;

     // total payment over the years
     float totalpay = 0;

     // while loop to calculate parameters and create outputs
     // header first:
     printf("Month:     Payment:     Interest:     Balance:\n");
     while (principal > 0){
          
          // break statement for when principal becomes less than one cent
          if (principal < 0.01)
                  break;
          // break statement for if fint > desired payment (which would create an infinite
          // loop)

          if (fint > desiredPayment){
          system("clear");
          printf("That payment is lower than the interest. It does not work.\n");
          break;
          }
          
          // month:
          nmonths = nmonths + 1;
          printf("%6d      ",nmonths);

          // payment: 
          if (desiredPayment >= principal){
               fint = monthlyInterest * principal;
               desiredPayment = principal + fint;
          }
          printf("$%6.2f      ", desiredPayment);
          totalpay += desiredPayment;

          // interest
          fint = monthlyInterest * principal;
          printf("$%6.2f      ", fint);
          
          // principal
          principal = principal - desiredPayment + fint;     
          printf("$%6.2f\n",principal);

     }
          // finally, get number of years and months.
          int nyears, nymon; // (number of year-months)
          nyears = nmonths / 12;
          nymon = nmonths % 12;
                    
          printf("\nYou paid a total of $%.2f over %d years and %d months\n",totalpay, nyears, nymon);

     return 0;

}
