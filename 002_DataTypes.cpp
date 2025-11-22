// VARIABLES

/*
DATA TYPES (Primitive) :

int -> integers : 4 bytes

char-> characters and symbols : 1 bytes

float-> numbers with decimal points : 4 bytes

bool-> true, false (true -> 1 & false -> 0) : 1 byte

double-> Long integers, numbers : 8 bytes

*/
#include<iostream>
using namespace std;  

int main(){

int age = 21;  // declaring and assigning value to an integer type variable

cout << age << endl;

cout<< "Name = " << "Hamid\n" << "Age = " << age << endl;

cout <<"Size Of Integer : "<<sizeof(age) << endl;  // getting size of variable

cout << false << endl; // --> 0
cout << true << endl; // --> 1

return 0;
}
