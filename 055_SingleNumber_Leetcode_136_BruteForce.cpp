// SINGLE NUMBER PROBLEM

/* given a non-empty array of integers nums, every element appears 
twice except for one . find the single one.
*/

#include<iostream>
#include<vector>
using namespace std;  

int main(){

vector<int>vec={4,1,2,6,1,8,6,2,4};

for(int i=0;i<vec.size();i++){
    bool a = true;
    for(int j=0;j<vec.size();j++){
        if(i!=j && vec[i]==vec[j]){
            a=false;
            break;
        }
    }
    if(a==true){cout<< "Single Number : "<<vec[i]<<endl;}
}

// this will work even if there are  multiple single numbers

return 0;
}