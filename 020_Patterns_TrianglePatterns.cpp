// TRIANGLE PATTERNS

#include<iostream>
using namespace std;  

int main(){


/* PRINT

*
* *
* * *
* * * *

*/

int n=20;

for(int i = 0;i<n;i++){
    for(int j=0;j<(i+1);j++){
        cout<<"* ";
    }
    cout<<"\n";
}

/*
PRINT

1
22
333
4444

*/

cout<<"\n";

n=4;

for(int i = 0;i<n;i++){
    for(int j=0;j<(i+1);j++){ // inner loop runs i+1 times
        cout<<(i+1)<< " ";
    }
    cout<<"\n";
}

cout<<"\n";

/* OR
n=4;
int num = 4;
for(int i = 0;i<n;i++){
    for(int j=0;j<(i+1);j++){ // inner loop runs i+1 times
        cout<<num<< " ";
    }
    cout<<"\n";
}
num++;
cout<<"\n";

*/

/*
PRINT

A
B B
C C C
D D D D
E E E E E

*/

n=5;
char ch ='A';
for(int i = 0;i<n;i++){
    for(int j=0;j<(i+1);j++){ // inner loop runs i+1 times
        cout<<ch<< " ";
    }
    ch++;
    cout<<"\n";
}
cout<<"\n";


return 0;
}


