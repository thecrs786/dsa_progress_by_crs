// MOORE'S VOTING ALGORITHM

#include<iostream>
#include<vector>
using namespace std;

int MajorityElement(vector<int> nums) {
    int candidate = nums[0];
    int count = 1;

    // Phase 1: Find a candidate
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] == candidate) {
            count++;
        } else {
            count--;
        }

        if(count == 0) {
            candidate = nums[i];
            count = 1;
        }
    }

    // Phase 2: Verify the candidate
    count = 0;
    for(int num : nums) {
        if(num == candidate) {
            count++;
        }
    }

    if(count > nums.size() / 2) {
        return candidate;
    }

    return -1; // No majority element
}

int main() {
    vector<int> nums = {1,2,2,1,1};

    int result = MajorityElement(nums);

    if(result != -1){
        cout << "Majority Element : " << result << endl;
    } else {
        cout << "No Majority Element Found!" << endl;
    }

    return 0;
}
