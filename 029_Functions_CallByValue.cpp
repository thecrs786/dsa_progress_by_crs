// CALL BY VALUE

#include<iostream>
using namespace std;  

int incby5(int n){
    n+=5;
    return n;  // function creates a copy and then operates with it
              //  real values inside of main function remains unchanged
}

int main(){

int a = 5;

cout<<incby5(a)<<endl;

cout<<a;  // value is same as before calling function


return 0;
}