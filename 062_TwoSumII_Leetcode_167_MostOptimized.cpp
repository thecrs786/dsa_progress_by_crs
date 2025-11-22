// METHOD 3 --> 2POINTER APPROACH  USING SORTED VECTOR TO GET ANS AS ELEMENTS ARE ARRANGED IN ASCENDING ORDER

#include<iostream>
#include<vector>
using namespace std;  

vector<int> findPair(vector<int> nums , int target){
    vector<int> ans;
    int size=nums.size();
   int i =0, j= size-1;

   while(i<j){
    int pairSum = nums[i] + nums[j];
    if(pairSum>target){j--;}
    else if(pairSum<target){i++;}
    else{
        ans.push_back(nums[i]);
        ans.push_back(nums[j]);
        return ans;
    }
   }
    return ans; // if no pair is found, returns empty vector
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
