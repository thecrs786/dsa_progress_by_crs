#include<iostream>
using namespace std;  

int main(){

/* PRINT
1
1 2
1 2 3
1 2 3 4
*/

int n = 4;

for(int i=0;i<n;i++){
    for(int j=1;j<=i+1;j++){
        cout<<j<<" ";
    }
   cout<<"\n";
}

cout<<"\n";

/* PRINT
1
2 1
3 2 1
4 3 2 1

*/

n = 4;

for(int i = 0;i<n;i++){
    for(int j=i+1;j>0;j--){
        cout<<j<<" ";
    }
    cout<<"\n";

}

cout<<"\n";

/* PRINT FLOYD'S TRIANGLE
1
2 3 
4 5 6
7 8 9 10
*/

int num = 1;
for(int i =0;i<n;i++){
    for(int j = 0;j<i+1;j++){
        cout<<num<<" ";
        num++;
    }
    cout<<"\n";
}

cout<<"\n";

/* PRINT
A
B C
D E F
G H I J
*/

n=4;

char ch='A';

for(int i = 0;i<n;i++){
    for(int j =0;j<i+1;j++){
        cout<<ch<<" ";
        ch++;
    }
    cout<<"\n";
}

return 0;
}
