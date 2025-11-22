//Nested loops
#include<iostream>
using namespace std;  

int main(){
int rows;
int columns;

cout<<"Enter rows and columns : ";
cin>> rows >> columns;

for(int j = 1;j<=rows;j++){
for(int i=1;i<=columns;i++){cout<<"* ";}cout<<"\n";}

// 5 ROWS AND 10 COLUMNS

return 0;
}