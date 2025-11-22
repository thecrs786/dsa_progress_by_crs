// vectors are dynamic in nature i.e their size ain't fixed

// vec.size() and vec.push_back()

#include<iostream>
#include<vector>  // must for vector access
using namespace std;  

int main(){

// vector<type>name;

// METHOD 1

vector<int>vec(3);

vec[0]=1; // must declare size first
vec[1]=3;
vec[2]=2;

cout<<vec.size()<<endl;

for(int i=0;i<vec.size();i++){cout<<vec[i]<<" ";}cout<<endl;

// NOTE :

for(int i=0;i<vec.size();i++){cout<<vec.at(i)<<" ";}cout<<endl; //throws exception if out of bounds


// METHOD 2

vector<int>vec1={1,2,3}; // OR vector<int>vec1{1,2,3}

for(int i=0;i<vec1.size();i++){cout<<vec1[i]<<" ";}cout<<endl;

// METHOD 3

vector<int>vec2;

vec2.push_back(1);  // to append
vec2.push_back(5);
vec2.push_back(8);

for(int i=0;i<vec2.size();i++){cout<<vec2[i]<<" ";}cout<<endl;

// METHOD 4

vector<int>vec3(3,0);  // size, element at every side

for(int i=0;i<vec3.size();i++){cout<<vec3[i]<<" ";}cout<<endl;

return 0;
}