/*
 pointers.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

char* text1 = "This is a string."; //text1 is a pointer to first char in the string
char* text2 = "Yet another thing.";

int list1[20]; //20 * 4byte = 80
int list2[20];
int counter = 0; //4 bytes = word

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

/*This function copies the ASCII code for each value in text to
 list and updates the variable counter
 Inparameters:
 -char* text (pointer to a string)
 -int* list (pointer to an array)
 -int* counter (pointer to an int)
 */ 
void copycodes(const char* text, int* list, int* counter){
  while (*text != 0)
  {
    *list = *text; //Copy value pointed to in text to place in list
    text++;        //update pointers to next spot
    list++;
    (*counter)++;
  }
  
}
void work(void){
  copycodes(text1, list1, &counter); //& -> pekare till platsen i minnet för counter
  copycodes(text2, list2, &counter); 
}



int main(void){
 
    work();
    printf("\nlist1: ");
    printlist(list1);
    printf("\nlist2: ");
    printlist(list2);
    printf("\nCount = %d\n", counter);

    endian_proof((char*) &counter);
}

/*

'*': Dereferencer, *p gives value that p is pointing to
'&': Address to, &a returns address of a
*/