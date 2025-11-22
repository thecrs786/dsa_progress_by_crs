// While loop , for loop, do while loop

#include<iostream>
using namespace std;  

int main(){

// WHILE LOOP  

int i = 1;

while(i<=10){
    cout<<i<<endl;
    i++;
}

cout<<"Value if i after loop ends : "<<i<< "\n";

// Table of n

int n;

cout<<"Enter n : ";
cin>> n;

int j = 1;
while(j<=10){
    //cout<< n << " * " << j << " = " << j*n << "\n";
    printf("%d * %d = %d\n",n,j,j*n);  // USING printf
    j++;

}

return 0;
}