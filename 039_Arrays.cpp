// ARRAYS

#include<iostream>
using namespace std;  

int main(){

int marks[5];

marks[0] = 90;
marks[1] = 80;
marks[2] = 70;
marks[3] = 80;
marks[4] = 90;

// or int marks[5] = {90,80,70,80,90};

cout<<marks[0]<<endl;

// 2D array

int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}}; // 3*3 matrix {{row 1},{row 2},{row 3}}

cout<<matrix[0][1]<<endl<<"\n\n";

cout << "   "<< "MATRIX"<<"\n\n";

for(int i = 0;i<3;i++){
    for(int j=0;j<3;j++){
        cout<<matrix[i][j]<<" ";
    }
    cout<<"\n";
}
cout<<"\n";
  
cout<<sizeof(matrix)<<endl; // 4*9 = 36 bytes
cout<<sizeof(matrix[0][2])<<endl; // 4 bytes

return 0;
}