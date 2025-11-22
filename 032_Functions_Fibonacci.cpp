// WAF TO CALCULATE FIBONACCI

#include<iostream>
using namespace std;  

// USING RECURSION

int fibRec(int n){
    if(n==0){return 0;}
    else if(n==1){return 1;}
    else{return fibRec(n-1)+fibRec(n-2);}
}

// USING LOOP

int fibLoop(int n){
    int a=0,b=1,next;
    for(int i=0;i<n;i++){
        next = a+b;
        a=b;
        b=next;
    }
    return a;

}

int main(){

int n;

cout<<"Enter n : ";
cin>>n;

cout<< "Fibonacci by recursion : "<<fibRec(n)<<endl;
cout<< "Fibonacci by loop : "<<fibLoop(n)<<endl;

return 0;
}