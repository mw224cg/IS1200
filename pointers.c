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

1. Explain how you get the pointer addresses to the two char arrays (text1 and text2) and the
 counter variable (count) in function work().

 When initiallized (line 12,13) the variable 'text' points to the adress of the first char in the string.
 To get the adress of the counter variable the '&'-sign is used.

--> work(text1,text2,&counter) the parameters are pointers to the adresses containing the variables

2. What does it mean to increment a pointer? What is the difference between incrementing the
 pointer that points to the ASCII text string, and incrementing the pointer that points to the
 integer array? In what way is the assembler code and the C code different?

Incrementing a pointer (e.g text++) means that you move the pointer to the next element in the adress
it points to. Incrementing the ASCII text string (text1,text2) pointers means that the
pointer jumps 1 byte (size of char) whilst incrementing the integer array makes the pointer
jump 4 bytes (size of an int).

3. What is the difference between incrementing a pointer and incrementing a variable that a
 pointer points to? Explain how your code is incrementing the count variable.

Incrementing a pointer means to move where in the memory it points to,
incrementing a variable that a pointer points to means to change the value 
stored at the adress of the pointer. To increment the counter variable, it 
needs to be dereferenced: (*counter)++

4. Explain a statement in your code where you are dereferencing a pointer. What does this mean?
 Explain by comparing it with the corresponding assembler code. 

 Line 44: *list = *text; 

 The char (1byte) that 'text' points to gets moved to the int (4byte) that 'list' points to
 
 In assembler code:

 sb t0, 0(a0)  #Load 1 byte to t0 from  memory adress given in a0 (the first)
 sw t0, 0(a1)  #Store 4 bytes from t0 to the memory adress given in a1
*/
