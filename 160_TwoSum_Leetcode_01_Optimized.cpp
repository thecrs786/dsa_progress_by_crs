// ------------------------------------------------------------------------------------------------
// 📌 Problem: Two Sum (LeetCode #1)
// ✅ Given an array `nums` and an integer `target`, return indices of the two numbers such that
//    they add up to the target. You may assume that each input has exactly one solution.
//    You may not use the same element twice.
//
// 🎯 Goal: Return the indices of the two elements that sum to the given `target`
// ------------------------------------------------------------------------------------------------

// 🧠 Solution Name: Two Pointer on Sorted Copy
//
// 📊 Time Complexity:
//     - Sorting the array: O(n log n)
//     - Two Pointer Search: O(n)
//     - Finding indices in original array: O(n)
//     - Total: O(n log n)
//
// 🧠 Space Complexity:
//     - O(n): For creating a copy of the array and storing result
//
// ⚙️ Optimal?: No, the HashMap approach (O(n) time & O(n) space) is more optimal in terms of time.
// 🔒 LeetCode Accepted?: ✅ YES. Passes all test cases.
// 🚫 MLE/TLE?: ❌ No. Efficient enough unless array is huge and stricter time limits are enforced.
// ------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 🚀 Function: Returns indices of two elements in nums[] that sum to target.
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Step 1: Make a copy of the original nums to sort it (so we can use two-pointer technique)
        vector<int> x(nums);  // O(n) space

        // Step 2: Sort the copy
        sort(x.begin(), x.end()); // O(n log n)

        int st = 0, end = x.size() - 1;
        int a, b; // Will store the two values that sum to target

        // Step 3: Two pointer search for the two values that sum up to target
        while (st < end) {
            int sum = x[st] + x[end];

            if (sum == target) {
                // Found the two numbers
                a = x[st];
                b = x[end];
                break;
            }
            else if (sum > target) {
                // Too big, move right pointer left
                end--;
            }
            else {
                // Too small, move left pointer right
                st++;
            }
        }

        // Step 4: Find the indices of a and b in the original array
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == a || nums[i] == b) {
                ans.push_back(i);
            }
            if (ans.size() == 2) break;
        }

        return ans;
    }
};

// ------------------------------------------------------------------------------------------------
// 🧠 Logic Explanation:
//
// 1. We can't sort the original array directly because we need the *original indices*.
//    So we copy it and sort that instead.
//
// 2. After sorting, we use the two-pointer approach to find two numbers that sum to target.
//    - Start from both ends and move accordingly:
//       - If sum is less than target → increase left
//       - If sum is more than target → decrease right
//
// 3. Once found, we loop through the original array to find their original indices.
//    - We break as soon as we find both to avoid using the same index twice.
//
// 4. Return the result vector with the indices.
//
// 📌 This approach keeps logic clean and understandable, but is slightly slower due to sorting.
// ------------------------------------------------------------------------------------------------


// 🔍 WORKING EXAMPLE — Run this to test and analyze the output
int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    Solution obj;
    vector<int> result = obj.twoSum(nums, target);

    cout << "Indices of elements that sum to " << target << " are: ";
    for (int idx : result) {
        cout << idx << " ";
    }
    cout << endl;

    // 🔎 Output: Indices of elements that sum to 9 are: 0 1
    // 🔍 Explanation: nums[0] = 2, nums[1] = 7 → 2 + 7 = 9 ✅
}
