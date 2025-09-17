/* main.c

   This file written 2015 by F Lundevall, David Broman and Artur Podobas

   Latest update 2024-07-27 by Artur Podobas

   For copyright and licensing, see file COPYING */

extern void print(const char*);
extern void print_dec(unsigned int);
extern void print_hex32 ( unsigned int x);

void handle_interrupt(void) {}

/* 
 * Skriver ut en variabel av typen int (32 bitar).
 * str  = etikett (t.ex. "AM1: gv")
 * ptr  = adressen till variabeln
 * Utskrift: etikett, adress och värdet på variabeln.
 */
void print_word (const char *str, void *ptr)
{
  print(str);
  print(" : address=");
  print_hex32((unsigned int) ptr);
  print(" : value=");
  print_dec(*((unsigned int*)ptr));
  print("\n");
}

/* 
 * Samma som print_word, men för en byte (unsigned char).
 * Används för att se individuella bytes i minnet.
 */
void print_byte (const char *str, char *ptr)
{
  print(str);
  print(" : address=");
  print_hex32((unsigned int) ptr);
  print(" : value=");
  print_dec(*((unsigned char*)ptr));
  print("\n");
}



int gv; /* Global variable. */
int in = 3; /* Global variable, initialized to 3. */

/* 
 * Funktion som tar en parameter, ökar den,
 * skriver ut parametern och uppdaterar globala gv.
 */
void fun(int param)
{
  param++;
  print_word( "AF1: param", &param );
  gv = param; /* Change the value of a global variable. */
}

/* This is the main function */
int main()
{
  /* Local variables. */
  int m;
  int * p;  //pointer to int
  char cs[ 9 ] = "Bonjour!";
  char * cp = cs; //cp points to &cs[0]
                                                                                                                                                                                             
  /* Do some calculation. */                                                                                                                                                                
  gv = 4;                                                                                                                                                                                    
  m = gv + in;  //m = 4 + 3 = 7
  
  /* Check the addresses and values of some variables and stuff */                                                                                                                           
  print_word( "AM1: gv", &gv );                                                                                                                                                                
  print_word( "AM2: in", &in );
  print_word( "AM3: fun", &fun );
  print_word( "AM4: main", &main );

  p = &m;   //set pointer p to adress of m

  /* Check p and m */
  print_word( "AM5: p", &p );   //print value of p (adress to m)
  print_word( "AM6: m", &m );   //print value of m (7)

  /* Change *p */

  *p = *p + 1;    //dereference p and add 1 -> m = 8

  /* Check p and m */
  print_word( "AM7: p", &p );   
  print_word( "AM8: m", &m );

  p = (int*)cp;   //p points to address of cp (cs[0]) but reads 4 bytes (sizeof int)

  print_word( "AM9: p", &p ); //prints value at adress p in dec = adress of cs[0] = 0x00100A48 = 1051208

  //Prints address and value of cs[0-3]

  print_byte( "AM10: cs[0]", &cs[0] );  
  print_byte( "AM11: cs[1]", &cs[1] );
  print_byte( "AM12: cs[2]", &cs[2] );
  print_byte( "AM13: cs[3]", &cs[3] );

  *p = 0x1234abcd; //p points to cs[0] as an int (4byte), dereference p change value of cs[0]
                   // 

  print_byte( "AM14: cs[0]", &cs[0] ); //=205 = CD
  print_byte( "AM15: cs[1]", &cs[1] ); // = 171 = AB
  print_byte( "AM16: cs[2]", &cs[2] ); // = 52 = 34
  print_byte( "AM17: cs[3]", &cs[3] ); // = 18 = 12

  fun(m); //m = 8 -> 9, gv = 9

  /* Re-check the addresses and values of m and gv */
  print_word( "AM18: m", &m );
  print_word( "AM19: gv", &gv );

}

/*
--> Starting console.
================================================
===== RISC-V Boot-Up Process Now Complete ======
================================================
AM1: gv : address=0x000008E8 : value=4
AM2: in : address=0x000008E4 : value=3
AM3: fun : address=0x00000174 : value=1378195
AM4: main : address=0x00000288 : value=4244701459
AM5: p : address=0x00100A40 : value=1051196
AM6: m : address=0x00100A3C : value=7
AM7: p : address=0x00100A40 : value=1051196
AM8: m : address=0x00100A3C : value=8
AM9: p : address=0x00100A40 : value=1051208
AM10: cs[0] : address=0x00100A48 : value=66
AM11: cs[1] : address=0x00100A49 : value=111
AM12: cs[2] : address=0x00100A4A : value=110
AM13: cs[3] : address=0x00100A4B : value=106
AM14: cs[0] : address=0x00100A48 : value=205
AM15: cs[1] : address=0x00100A49 : value=171
AM16: cs[2] : address=0x00100A4A : value=52
AM17: cs[3] : address=0x00100A4B : value=18
AF1: param : address=0x00100A44 : value=9
AM18: m : address=0x00100A3C : value=8
AM19: gv : address=0x000008E8 : value=9
*/

/* QUESTIONS:

1.  Consider AM18, AM19, and AF1. Explain why gv ends up with the incremented value, but m
 does not

 m = lokal variabel i main
 fun(m); skapar en kopia av m till variabeln 'param' och ökar++ därefter ändras
 gv till 9 (gv = param). 'm' förblir oförändrad eftersom den endast skickar ett 
 invärde som parameter inte adressen.

AF1: param : address=0x00100A44 : value=9
AM18: m : address=0x00100A3C : value=8
AM19: gv : address=0x000008E8 : value=9

2. Pointer cp is a character pointer that points to a sequence of bytes.
What is the size of the cp pointer itself?

Storleken på en pekare är 32-bitar (i 64-bits arkitektur = 64 bitar)

3. Explain how a C string is laid out in memory. Why does the character string that cp
 points to have to be 9 bytes?

Eftersom strängen 'Bonjour!' = 8 st char + null terminator '0' = 9char
--> 'Bonjour!0x0'
Varje char är 1 byte/8bitar


Part 2:
1.  Which addresses are variables in and gv located at?

AM1: gv : address=0x000008E8 
AM2: in : address=0x000008E4 

2.  Variables p and m are not global variables. Where are they allocated? Which memory section
 is used for these variables? Why are the address numbers for p and m much larger than for in
 and gv?

 p, m är lokala variabler i main(), lokala variabler sparas på stacken.
 Skillnaden mot globala variablers adresser (som sparas i .data) är troligast för
 att stacken ligger i ett annat segment med högre addresstal

3. At print statement AM5, what is the address of pointer p, what is the value of pointer p, and
 what value is pointer p pointing to?

p = &m; //Set value of p to address of m
AM5: p : address=0x00100A40 : value=1051196 (0x00100A3C)
AM6: m : address=0x00100A3C : value=7

p pekar på värdet 7

4. At print statement AM7, what is the address of pointer p, what is the value of pointer p, and
 what value is pointer p pointing to?

AM7: p : address=0x00100A40 : value=1051196

p är samma som i fråga 3, den pekar fortfarande på m
dock har m ändrats genom att dereferera p genom:
*p = *p + 1;
så värdet p pekar på är 8

5. Consider AM14 to AM17. Is the RISC-V processor using big-endian or little-endian? Why?

RISC-V processorn är LE eftersom LSB sparas på lägsta adressen

 */
