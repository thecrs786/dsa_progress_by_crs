// DO -WHILE-LOOPS : do{work;}while(condition);

// runs atleast once

#include<iostream>
using namespace std;  

int main(){

do{cout<<"Hello World\n";}while(3>5); // ran once even if condition is false

int n = 9;
int i =1;
do{cout<<n<<" * "<<i<< " = "<<n*i<<endl;i++;}while(i<=10);

return 0;
}