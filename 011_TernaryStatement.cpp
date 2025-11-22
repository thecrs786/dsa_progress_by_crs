// Ternary statement : condition? stt1 : stt2 ;

#include<iostream>
using namespace std;  

int main(){

int n = -10;

// cout<<(n>=0);  Output --> False -->0

// (1)

cout<<(n>=0? "positive" : "negative") << endl;

//(2)

string value;

n>=0? value = "Positive" : value ="Negative"; 

cout<<value<<endl;

// (3)

string val = n>=0? "Yes" : "No";

cout<<val<<endl;

return 0;
}