// for each loop -> iterator store the value at the index ,instead of storing index

#include<iostream>
#include<vector>
using namespace std;  

int main(){

vector<int>vec(5,0);

for(int i : vec){  // type of iterator = type of vector
    cout<< i <<" ";
}

cout<<"\n\n";

vector<char>vec1={'a','b','c','d','e'};

for(char val : vec1){
    cout<<val<<" ";
}

cout<<"\n\n";

return 0;
}