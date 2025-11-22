// CALCULATE SUM OF DIGITS OF A NUMBER

#include<iostream>
using namespace std;  

int sumofdigits(int n){
    int sum = 0;
    /* USING FOR LOOP

    /for(int i = 0;n>0;i++){
        sum+=(n%10);
        n/=10;
    } */

    // USING WHILE LOOP

    while(n>0){
        sum+=n%10;
        n/=10;}

    return sum;
}

int main(){
int n;
cout<< "enter a number : ";
cin>>n;
cout<<"Sum of digits : "<<sumofdigits(n);

return 0;
}