// METHOD 2-> USE OF SORTING

#include<iostream>
#include<vector>
#include<algorithm> // include this for sort

using namespace std;

int MajorityElement(vector<int>nums){
    int size = nums.size();
    
    sort(nums.begin(), nums.end());

    int freq = 1, ans = nums[0];
    for(int i = 1; i < size; i++){
        if(nums[i] == nums[i - 1]){
            freq++;
        } else {
            freq = 1;
            ans = nums[i];
        }

        if(freq > size / 2){
            return ans;
        }
    }

    return ans;// if only one element is present theabove code doesn't help, so return the only element i.e ans = nums[0].
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
