//SUM OF ALL ODD NUMBERS FROM 1 TO n
#include<iostream>
using namespace std;  

int main(){

int num;
cout<<"Enter a number : ";
cin>> num;

int sum = 0;
for(int i =1;i<=num;i++){
    if(num==500){break;}  // get out of loop
    sum += i;
}

cout<< sum;

return 0;
}