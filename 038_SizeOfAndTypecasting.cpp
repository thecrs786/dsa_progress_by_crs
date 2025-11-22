// DATA TYPE MODIFIERS -> Changing meaning of data types (altering capacity)

#include<iostream>
using namespace std;  

int main(){

// (1) long -> gives >= 4 bytes

cout<< sizeof(int)<<endl;
cout<< sizeof(long int)<<endl;
cout<< sizeof(long long int)<<endl; // can use long only upto twice

cout<< sizeof(float)<<endl;  // long float is invalid

cout<< sizeof(char)<<endl; // long char is also invalid

cout<< sizeof(double)<<endl;
cout<< sizeof(long double)<<endl; // long long double ain't valid

// long long is strictly for integers

// (2) short -> gives 2 bytes -> only for integers

cout<<sizeof(short int)<<endl;

// (3) signed and unsigned

// int is signed by default

// signed -> can store positive as well as negative numbers : -2,147,483,648 to 2,147,483,647

// unsigned int cannot store negative integers : 0 to 4,294,967,295

// in unsigned int, msb isn't used to store sign(+ or -) it is used to store data as sign is already positive

cout<<sizeof(unsigned int)<<endl;


return 0;
}