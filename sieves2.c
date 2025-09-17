
#include <stdlib.h> 
#include <stdio.h>

#define COLUMNS 6
int column_counter = 0;


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

/*
This function prints all prime numbers less than n using the Sieve of Eratosthenes algorithm.
This function allocates the data on the stack.
Inparameter: n (int), the upper limit.
Outparameter: none.
*/
void print_sieves(int n){
    if (n < 2) {
        return; // No primes less than 2.
    }

    char *composites = malloc(n * sizeof(char)); // Array on heap: 1 byte * n
    if(n>1) composites[1] = 1;

    for (int i = 2; i < n; i++) {
        composites[i] = 0;
    }
    //mark all composites = 1
    for(int j = 2; j * j < n; j++) {
        if(composites[j] == 0){
            for(int multiple = j*j; multiple < n; multiple += j) {
                composites[multiple] = 1;
            }
        }
    }

    //print all primes
    for(int i = 2; i < n; i++) {
        if(composites[i] == 0) {
            print_number(i);
        }
    }

    free(composites);


}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_sieves(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}