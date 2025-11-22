// TWO's COMPLIMENT

// MSB OF A binary tells whether itl's +ve or -ve : is msb = 0 --> +ve, if 1 --> -ve.
// MSB IS THE FIRST DIGIT OF BINARY

/*
as integer takes 4 bytes i.e 32 bits so

_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  these

32 bits are reserved in memory for easch integer.

if we store 45 --> 101101 , it will be stored as

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 1 .

BUT IF WE STORE A NEGATIVE INTEGER , IT WILL BE STORED DIFFERENTLY
*/

/* if a negative integer is given for ex : -10

step 1 --> convert number into binary : 10 --> 1010

step 2 : prefix it's msb  with a 0 (+ve) : 1010 --> 01010

 now we get two's compliment

step 3 : get 1's compliment i.e reverse 0's and 1's : 01010 --> 10101

step 4 add 1 (binary addition) : 10101 + 1 --> 10110 ((now msb is 1 ie -ve))

now 10110 is two's compliment

*/

// -10 = 10110 in binary msb is 1 ie -ve

// binary addtion : 0+0=0, 1+0 = 0+1 = 1, 1+1 = 0 and 1 carry over left side\

/* IF A BINARY FORM IS GIVEN AND WE KNOW THAT IT'S NEGATIVE

STEPS TO FIND THE NUMBER FROM BINARY

step 1 : get two's compliment of number 

 first reverse 0's and 1's i.e 1's compliment : 10110 --> 01001
 now add 1 (binary addition) : 01001 + 1 --> 01010

 step 2 : convert the calculated into decimal and add -ve sign to it --> 01010 = 10 --> -10



*/