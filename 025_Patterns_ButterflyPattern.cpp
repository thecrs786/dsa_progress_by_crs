// BUTTERFLY PATTERN

#include<iostream>
using namespace std;  

int main(){

/* PRINT

*      *
**    **
***  ***
********
********
***  ***
**    **
*      * 

*/

int n=4;

//Upper part

for(int i=0; i<n; i++){

    for(int j=0;j<i+1;j++){
        cout<<"*";
    }

    for(int j=0; j<2*(n-i-1);j++){  // logic -> spaces are dcreasing so, role of -i, also even sspaces so 2*(n-i-something).
        cout<<" ";                  // follow first pattern, i=0, n=4, spaces = 6 -> 2n-2i = 8,-> 2n-2i-2 = 6 it worked for rest values of i 
    }                               // number of spaces = 2n-2i-2 = 2*(n-i-1)

    for(int j=0;j<i+1;j++){
        cout<<"*";
    }

    cout<<endl;
}

//Lower Part

for(int i=0; i<n; i++){

    for(int j=n-i;j>0;j--){
        cout<<"*";
    }

    if(i!=0){
        for(int j=0;j<2*i;j++){
            cout<<" ";
        }
    }
    
    for(int j=n-i;j>0;j--){
        cout<<"*";
    }

    cout<<endl;

}

return 0;
}