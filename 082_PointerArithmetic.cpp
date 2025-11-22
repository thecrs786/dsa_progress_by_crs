// Pointer Arithmetic

#include<iostream>
using namespace std;

int main(){

    int a = 10;
    int* ptr = &a;
     
    cout<<ptr<<endl; // address of a;
    cout<<ptr+1<<endl; // address of memory which is 4th next to a
    cout<<ptr-1<<endl; // address of memory 4th previous to a

    // Because int takes 4 byte so ptr+1 will give address in context of integer
    // i.e 4 bytes next to adress of a
    // similarly ptr-1 will give address of memory 4 bytes previous to it

    // NOTE -> ptr + n or ptr - n gives an address offset based on the data type
    // i.e., it moves n * (size of data type) bytes forward or backward in memory
   
    /* 
   Example of pointer arithmetic based on data type size:

   int b = 10;
   int* p = &b;
   // Let's assume the address of b is 100
   // Since int is 4 bytes:
   // p++ results in address 104
   // p-- results in address 96

   char c = 's';
   char* q = &c;
   // Let's assume the address of c is 200
   // Since char is 1 byte:
   // q++ results in address 201
   // q-- results in address 199

   NOTE -> Pointer increment and decrement depend on the data type size.
           The pointer moves by (n × sizeof(data type)) bytes.
*/

    // ptr+3 -> incremented by 3 integers (12 bytes)


    // in hexadecimal --> 0, 1, 2, 3, ... ,9 , a, b,c, d, e, f is the order

    return 0;
}
