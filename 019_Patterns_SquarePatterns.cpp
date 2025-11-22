// SQUARE PATTERNS

#include<iostream>
using namespace std;  

int main(){

int n=4;

for(int i=1;i<=n;i++){
    for(int j = 1;j<=n;j++){
        cout<<"*"<<" ";
    }
    cout<<"\n"; // cout<<endl;
}

// PRINT A B C D , 4 TIMES
cout<<"\n";


for(int i=1;i<=n;i++){
    for(int j = 0;j<n;j++){
        cout<<char(65+j)<<" ";
    }
    cout<<"\n";
}

cout<<"\n";

// print : [{1,2,3},{4,5,6},{7,8,9}]

n = 3;
int num=1;

for(int i=1;i<=n;i++){
    for(int j = 0;j<n;j++){

cout<<num<<" ";
num+=1;

    }
    cout<<"\n";
}

cout<<"\n";

// print : [{A,B,C},{D,E,F},{G,H,I}]

char ch ='A'; 

for(int i=1;i<=n;i++){
    for(int j = 0;j<n;j++){

cout<<ch<<" ";
ch+=1;    
}
cout<<"\n";
}


return 0;
}