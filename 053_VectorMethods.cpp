// VECTOR FUNCTIONS

#include<iostream>
#include<vector> 
using namespace std;  

int main(){

/* (1) -> vec.size() : return size of the vector
   (2) -> vec.push_back(el) : appends the element at the end (icreases size)
   (3) -> vec.pop_back() : deletes last element in vector (reduces size)
   (4) -> vec.front() : returns the first element of the vector = vec[0]
   (5) -> vec.back() : return last element of the vector = vec[vec.size()-1]
   (6) -> vec.at(index) : returns value at the particular index = vec[index]
   (7) -> vec.empty() : returns true (1) if vector is empty , returns false (0) if not. 
*/

vector<int>vec={1,2,3};

cout<< "size : "<<vec.size()<<"\n";

vec.push_back(4);

for(int i : vec){cout<<i<< " ";}cout<<"\n";

vec.pop_back();

for(int i : vec){cout<<i<< " ";}cout<<endl;

cout<<vec.front()<<endl;
cout<<vec[0]<<endl;  // same as above 

cout<<vec.back()<<endl;
cout<<vec[vec.size()-1]<<endl;  // can also be used to access last element

cout<<vec.at(1)<<endl;
cout<<vec[1]<<endl; // same work



return 0;
}