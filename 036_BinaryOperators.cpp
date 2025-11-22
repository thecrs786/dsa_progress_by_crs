/* BITWISE OPERATORS

(1) bitwise & (and)
(2) bitwise | (or)
(3) bitwise ~ (not)
(4) bitwise xor (^) (exclusive or)
(5) bitwise <<  (left shift)  
(6) bitwise >>  (right shift)

& -> 0 & 0 = 0 : 0 & 1 = 0 : 1 & 1 = 1
   
    only 1 & 1 = 1 , rest all & gives 0

| -> 0 | 0 = 0  :  0 | 1 = 1  :  1 | 1 = 1

    only 0 | 0 = 1 , rest all | gives 1

^ -> if bits same --> 0 : if bits different --> 1 . 

<< , >> -> shifts each bit in binary left and right and the empty space if filled with 0

*/ 

#include<iostream>
using namespace std;  

int main(){

int a = 4;
int b = 8;

cout<<(a&b)<<endl; // 4 = 100 , 8 = 1000 ,(4 digits) so, 4 = 0100
             // now 0100 & 1000 = 0 -> 0

cout<<(a|b)<<endl;  // 0100 | 1000 = 1100 in binary = 12 in decimal

cout<<(0^0)<<endl;
cout<<(0^1)<<endl;
cout<<(1^1)<<endl;

cout<<(4^8)<<endl; // 0100 ^ 1000 = 1100  --> 12 in decimal

cout<<(4<<2)<<endl;// 100 --> 1000 (sifted twice left) = 16
  
cout<<(4>>2)<<endl; // 100 -> 1 = 1
cout<<(8>>2)<<endl; // 1000 -> 10 = 2

return 0;
}