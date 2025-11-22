// -----------------------------------------------------------------------------
// 🧠 LeetCode Problem: Two Sum
// 📌 Problem Summary:
// Given an array of integers (nums) and an integer target, return the indices 
// of the two numbers such that they add up to the target.
// You may assume that each input has exactly one solution, and you may not use 
// the same element twice. Return the answer in any order.
//
// 🧪 Example:
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
//
// 🛠️ Solution Method: Hash Map Lookup (Optimal - One-pass Hashing)
//
// ⏱️ Time Complexity: O(n)
//     - We traverse the array only once.
// 🧠 Space Complexity: O(n)
//     - In the worst case, we store all elements in the unordered_map.
//
// ✅ Accepted by LeetCode? YES
// 💯 Optimal? YES
// ❌ Any chance of TLE/MLE? NO (Only O(n) space and time - very safe)
//
// -----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Unordered map to store (value -> index)
        unordered_map<int,int> m;

        // Vector to store the answer (two indices)
        vector<int> ans;

        // Traverse through the array
        for(int i = 0; i < nums.size(); i++) {

            int first = nums[i];               // Current number
            int second = target - first;       // What number do we need to find?

            // Check if the 'second' is already in map
            if(m.find(second) != m.end()) {
                //m.find(value) returns an iterator to the element with key = value, if it exists.
                // if not found m.find() returns m.end() i.e is a special iterator that points one past the last element
                // If found, that means current number + previous = target
                // So push the indices of the pair and break
                ans.push_back(m[second]); // Index of the element we found before
                ans.push_back(i);         // Current index
                break; // We found the answer, break out
            }
            else {
                // If not found, store the current number and its index
                m[first] = i;
            }
        }

        return ans;
    }
};

// -----------------------------------------------------------------------------
// 📖 Function Logic Explanation:
//
// ✅ Step-by-step Working:
// - We need two numbers whose sum equals the given target.
// - For each number, we calculate what value would pair with it to reach the target.
// - If we’ve already seen that value before, we instantly have our answer.
// - Instead of checking every pair (O(n^2)), we use a hash map to store previous values.
//
// 🧠 Deep Internal Flow (Example: nums = [2, 7, 11, 15], target = 9):
// i = 0:
//     nums[i] = 2
//     second = 9 - 2 = 7
//     7 not in map → store 2:0 in map
// i = 1:
//     nums[i] = 7
//     second = 9 - 7 = 2
//     2 found in map → 2 was at index 0 → answer = [0, 1]
//
// 🧨 Edge Cases Handled:
// - Guaranteed only one solution → we can safely break once we find the pair.
// - We don’t add duplicates because we only insert into map if second is not found.
//
// -----------------------------------------------------------------------------

// 🧪 Working Example:


int main() {
    Solution obj;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = obj.twoSum(nums, target);

    cout << "Indices: ";
    for(int i : result) {
        cout << i << " ";
    }
    cout << endl;

    // Output should be: Indices: 0 1
    // Because nums[0] + nums[1] = 2 + 7 = 9
    return 0;
}

// -----------------------------------------------------------------------------
