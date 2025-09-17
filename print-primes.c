/*
 print-primes.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int column_counter = 0;

/*This function prints a number to the terminal. When the specified
 number of columns is reached, a new line is started.
 Inparameter: n (int), the number to print.
 Outparameter: none.
*/
void print_number(int n){
    printf("%10d ", n);
    column_counter++;
    if(column_counter == COLUMNS){
        printf("\n");
        column_counter = 0;
    }
}

/*This function checks if n is a prime number.
 It returns 1 if n is prime, and 0 otherwise.
 Inparameter: n (int), the number to check.
 Outparameter: result (int), 1 if n is prime, 0 otherwise.
*/
int is_prime(int n){
    int result = 1; // Assume n is prime.
    for (int i = 2; i < n; i++){ //If n is divisble by any number between 2 and n-1, it is not a prime.
        if (n % i == 0){
            result = 0; // n is not prime.
            break;
}
    }
    return result;
} 

/*This function prints all prime numbers less than n.
 Inparameter: n (int), the upper limit.
 Outparameter: none.
*/
void print_primes(int n){
    for(int i = 2; i < n; i++){ //Check all numbers from 2 up to n-1.
        if(is_prime(i)){
            print_number(i);
        }
    }
    printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_primes(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}

 
