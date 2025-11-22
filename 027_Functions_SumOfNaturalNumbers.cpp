// CALCULATE SUM OF NUMBERS FROM 1 TO N

#include<iostream>
using namespace std;  

int calcSum(int n){
    int sum=0;
    for(int i = 1;i<=n;i++){sum+=i;}
    return sum;
}

int main(){
int n;
cout<<"Enter n : ";
cin>>n;

cout<<calcSum(n);

return 0;
}