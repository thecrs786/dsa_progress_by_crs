// BINARY operators requires two operators

/*
(1) increment (++) : a = a+1 or a++ or a+=1 ---> post increment

++a --> pre increment -->first increment then use

(2) decrement (--) : a = a-1 or a-- or a-=1  --> post decrement

--a --> first decrement then use --> pre decrement

*/

#include<iostream>
using namespace std;  

int main(){

int a = 3;

// INCREMENT

cout<< "Increment\n";

cout<< "a = " << a << endl;

a=a+1;
cout<< "a = " << a << endl;

a++;
cout<< "a = " << a << endl;

a+=1;
cout<< "a = " << a << endl;

// DECREMENT

cout<<"\nDECREMENT\n";

a=a-1;
cout<< "a = " << a << endl;

a--;
cout<< "a = " << a << endl;

a-=1;
cout<< "a = " << a << endl;


return 0;
}