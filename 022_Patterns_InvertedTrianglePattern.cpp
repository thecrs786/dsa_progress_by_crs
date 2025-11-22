// INVERTED TRIANGLE PATTERN

#include<iostream>
using namespace std;  

int main(){

/* PRINT
 1 1 1 1    SPACE = 0 : NUM = 4 = n-i   i=0=space
   2 2 2    SPACE = 1 : NUM = 3 = n-i   i=1=spaces
     3 3    SPACE = 2 : NUM = 2 = n-i   i=2=spaces
       4    SPACE = 3 : NUM = 1 = n-i   i=3=spaces

*/
int n= 4;

for(int i=0;i<n;i++){
    // SPACES
    for(int j =0;j<i;j++){
        cout<<" ";
    }
    for(int j =0;j<n-i;j++){
        cout<<i+1;     // NO SPACES BETWEEN NUMBERS
    }
    cout<<"\n";
}

cout<<"\n";

// IF SPACES BETWEEN NUMBERS

for(int i=0;i<n;i++){
    // SPACES
    for(int j =0;j<i;j++){
        cout<<" ";
    }
    for(int j =0;j<n-i;j++){
        cout<<i+1<<" ";     
    }
    cout<<"\n";
}

cout<<("\n");

/* PRINT
AAAA
 BBB
  CC
   D
*/
char ch ='A';

for(int i=0;i<n;i++){
    // SPACES
    for(int j =0;j<i;j++){
        cout<<" ";
    }
    for(int j =0;j<n-i;j++){
        cout<<ch<<"";     
    }
    ch++;
    cout<<"\n";
}
return 0;
}