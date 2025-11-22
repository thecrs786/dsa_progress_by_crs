// MAJORITY ELEMENT -> element which appears more than floor of n/2 times

#include<iostream>
#include<vector>
using namespace std;  

int MajorityElement(vector<int>nums){
    int size = nums.size();
    for(int val : nums){
        int freq =0;
        for(int el : nums){
            if (el == val){freq++;}
        }
        if (freq>(size/2)){return val;}
        freq =0; // reset count if current one ain't majority element
    }
        
    return -1; // returns -1 if no majority element found
    }
    


int main(){

vector<int> nums = {1,2,2,1,1};

int result = MajorityElement(nums);

if(result != -1){
    cout << "Majority Element : " << result << endl;
} else {
    cout << "No Majority Element Found!" << endl;
}

return 0;
}

