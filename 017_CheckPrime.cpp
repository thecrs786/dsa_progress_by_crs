// CHECK WHWTHER A NUMBER IS PRIME OR NOT

#include<iostream>
using namespace std;  

int main(){

int num;
cout<<"Enter number : ";
cin>> num;

bool isPrime = true;

for(int i = 2;i*i<=num;i++){
    if(num%i==0){
        isPrime=false;
        break;
    }
}
// if(isPrime==true){cout<<"Prime";}else{cout<<"Not Prime";}

string answer;

answer = isPrime==1? "Prime" : "Not Prime";

// isPrime == 1? answer = "Prime" : answer = "Not Prime"; 

cout<<answer<<endl;

return 0;
}