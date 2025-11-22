// method 2

// PAIR SUM -> return pair in sorted array with target sum

#include<iostream>
#include<vector>
using namespace std;  

vector<int> findPair(vector<int> nums , int target){
    vector<int> ans;
    int size=nums.size();
    for(int i =0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(nums[i]+nums[j]==target){
                ans.push_back(nums[i]);
                ans.push_back(nums[j]);
                return ans;
            }
        }
    }
    return {}; // if no pair is found
}

int main(){

vector<int> arr = {1,2,3,4,5,6,7,8,9};


vector<int> result1 = findPair(arr, 15);
    if (!result1.empty()) {
        cout << "Pair found: " << result1[0] << ", " << result1[1] << endl;
    } else {
        cout << "No such pair found for target 15" << endl;
    }

vector<int> result2 = findPair(arr, 11);
    if (!result2.empty()) {
        cout << "Pair found: " << result2[0] << ", " << result2[1] << endl;
    } else {
        cout << "No such pair found for target 11" << endl;
    }


return 0;
}