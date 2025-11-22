// CALCULATE NcR bionomial coefficient for n & r

// NcR = n! / (r!)*((n-r)!)

#include<iostream>
using namespace std;  

int fact(int n){
    if(n==0 || n==1){return 1;}
    return n*fact(n-1);
}

int biocoeff(int n,int r){
        return fact(n) / (fact(r)*fact(n-r));
}

int main(){
int n,r;
cout<<"Enter N and R for NcR : ";
cin>>n>>r;
cout<<"Bionomial coeffient is : "<<biocoeff(n,r)<<endl;


return 0;
}