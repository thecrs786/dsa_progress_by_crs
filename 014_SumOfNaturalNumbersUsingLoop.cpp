// SUM OF NUMBERS FROM 1 TO 10
#include<iostream>
using namespace std;  

int main(){

int sum = 0;
int n;
cout<< "Enter a number : ";
cin>> n;

for(int i=1;i<=n;i++){
    sum = sum + i;
    //sum+=1;
}
cout<<sum<<endl;
return 0;
}