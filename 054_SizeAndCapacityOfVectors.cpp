// when we're pushbacking an element in a vector which is full, it's capacity gets doubled

#include<iostream>
#include<vector>
using namespace std;  

// vec.capacity() -> returns capacity of the vector

int main(){

vector<int>vec; // empty vector

cout<<"Size : " <<vec.size()<<", Capacity : "<<vec.capacity()<<endl;  // size = 0 = capacity


vec.push_back(1);

cout<<"Size : " <<vec.size()<<", Capacity : "<<vec.capacity()<<endl; // size and capacity increased by 1

vec.push_back(2);

cout<<"Size : " <<vec.size()<<", Capacity : "<<vec.capacity()<<endl; // size increased by one but capacity got doubled

vec.push_back(3);

cout<<"Size : " <<vec.size()<<", Capacity : "<<vec.capacity()<<endl;  // size increased by one but capacity got doubled

vec.push_back(4);

cout<<"Size : " <<vec.size()<<", Capacity : "<<vec.capacity()<<endl;  // size = capacity

vec.push_back(5);

cout<<"Size : " <<vec.size()<<", Capacity : "<<vec.capacity()<<endl;  // size increased by one but capacity doubled


return 0;
}