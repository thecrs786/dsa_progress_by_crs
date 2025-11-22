/*
==============================================================
✅ LeetCode Problem: Two Sum (Brute Force Approach)
==============================================================
🧠 Problem Summary:
- Given an array of integers `nums` and an integer `target`,
  return the indices of the two numbers such that they add up to `target`.

- Exactly one solution exists.
- Cannot use the same element twice.
- Return the answer in any order.

📌 Example:
Input: nums = [2, 7, 11, 15], target = 9
Output: [0, 1]   // Because nums[0] + nums[1] == 2 + 7 == 9

==============================================================
🛠️ Method: Brute Force Approach
==============================================================
We check every possible pair in the array using nested loops.

🕒 Time Complexity: O(n^2)
📦 Space Complexity: O(1) auxiliary space (excluding output)

🟡 Is this the most optimal solution? ❌ No.
✅ Will it be accepted on LeetCode? ✅ Yes, for small input sizes.
⚠️ Can it cause TLE? ⚠️ Yes, for large arrays (due to O(n²)).
🚫 Can it cause MLE? ❌ No, space usage is minimal.
==============================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Main function to solve the two sum problem using brute force
    vector<int> twoSum(vector<int>& nums, int target) {
        // Iterate through each element
        for (int i = 0; i < nums.size(); i++) {
            // Start from the next element to avoid using the same index twice
            for (int j = i + 1; j < nums.size(); j++) {
                // Check if the sum of nums[i] and nums[j] equals target
                if (nums[i] + nums[j] == target) {
                    // Return their indices in a vector
                    return {i, j};
                }
            }
        }
        // If no such pair is found, return an empty vector (problem guarantees one solution, so this won’t execute)
        return {};
    }
};

/*
==============================================================
📘 Full Logic Explanation (Brute Force Two Sum)
==============================================================
1. The outer loop picks the first number (let's call it nums[i]).
2. The inner loop picks the second number (nums[j]) for every j > i.
3. It checks if nums[i] + nums[j] == target.
   - If true, we immediately return their indices [i, j].
4. Since only one solution is guaranteed, we can `return` early.
5. We only return an empty vector {} if no such pair exists — though by the problem’s constraints, this should never happen.

🧠 Why is j = i + 1?
- To ensure we don’t use the same element twice.
- And to avoid repeating the same pair in reverse (like (2,3) and (3,2)).

🧠 Why do we return inside the loop?
- Once we find a valid pair, no need to check further. Only one solution exists.
==============================================================
*/

int main() {
    // Create an instance of Solution class
    Solution obj;

    // Working test case
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    // Call the twoSum function and store result
    vector<int> result = obj.twoSum(nums, target);

    // Print the result
    cout << "Indices: ";
    for (int index : result) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}

/*
==============================================================
🔍 Output Analysis:
For input: nums = [2, 7, 11, 15], target = 9
The pair is (2, 7), at indices [0, 1].
Output:
Indices: 0 1

📌 All edge cases like:
- Only two elements in array: [3,4], target=7 ✅
- Negative numbers: [-2, 4, 1], target=2 ✅
- Repeating elements: [3, 3], target=6 ✅
- Large values: [100000, 999999], target=1999999 ✅
Work fine with this logic.

🧠 Final Verdict:
- Brute force is simple and beginner-friendly.
- Inefficient for large inputs but gets accepted on LeetCode.
- Good as a starting point before learning optimized methods like hashing (unordered_map).
==============================================================
*/
