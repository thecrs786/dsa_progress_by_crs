// CALCULATE N FACTORIAL

#include<iostream>
using namespace std;  

// RECURSION

int factRec(int n){
    if(n ==0 || n==1){return 1;}
    return n*factRec(n-1);
}

// LOOP

int factLoop(int n){
    int fact =1;
    for(int i=1;i<=n;i++){fact *=i;}
    return fact;

}

int main(){

int n;

cout<<"Enter a number : ";
cin>>n;

cout<<"Factorial by recursion : "<<factRec(n)<<endl;

cout<<"Factorial by loop : "<<factLoop(n)<<endl;


return 0;
}