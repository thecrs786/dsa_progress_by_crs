// 🟩 PROBLEM SUMMARY (LeetCode - Find the Duplicate Number):
// - You are given an array of integers `nums` containing n + 1 integers 
//   where each integer is in the range [1, n] inclusive.
// - There is only one repeated number in `nums`, but it could be repeated more than once.
// - You must return that **single repeated number**.
// - Your solution must not modify the array and should use **constant extra space** (optimal approach).
//
// 📌 Example:
// Input: nums = [3,1,3,4,2]
// Output: 3
//
// Constraints:
// - 1 <= n <= 10^5
// - nums.length == n + 1
// - nums[i] in the range [1, n]
// - Exactly one duplicate exists (could be repeated more than twice)
//
// 🧠 Solution Name: Brute-Force using Nested Loops
// ✅ Type: Brute Force
// ❌ Time: O(n^2) — NOT optimal
// ❌ Space: O(1)
// ❌ Not Accepted for Large Inputs — Will cause TLE (Time Limit Exceeded) on LeetCode
//
// 🚨 Why? Because for input size near 10^5, O(n^2) leads to ~10^10 comparisons (extremely slow).

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Outer loop iterates through each element
        for(int i = 0; i < nums.size(); i++) {

            // Inner loop checks rest of array for duplicate of nums[i]
            for(int j = i + 1; j < nums.size(); j++) {

                // If we find a match, that’s the duplicate
                if(nums[i] == nums[j]) {
                    return nums[i];
                }
            }
        }

        // If no duplicate is found (though problem guarantees there is one)
        return {};
    }
};

/*

🧠 FULL EXPLANATION:

We are brute-force comparing every element in the array with every other element after it.
The moment we find a match, we return that element because it’s the duplicate.

✔️ Step-by-step:
1. We loop from i = 0 to i = n-1.
2. For each i, we start an inner loop from j = i+1 to n.
3. For each pair (i,j), we check if nums[i] == nums[j].
4. If true, return nums[i] as it's the duplicate.
5. If we exit both loops without finding a duplicate (which shouldn't happen due to problem guarantees), we return an empty object `{}`.

🧪 WORKING EXAMPLE:

Input: nums = [3,1,3,4,2]

Iteration 1:
i = 0 (nums[i] = 3)
→ j = 1 (nums[j] = 1) → Not Equal
→ j = 2 (nums[j] = 3) → ✅ Match found → return 3

So the output will be: 3

🟡 TIME & SPACE ANALYSIS:

Time Complexity:
- Outer loop runs O(n) times.
- Inner loop runs O(n) in worst case.
→ Total = O(n^2)

Space Complexity:
- We use no extra data structures, so space = O(1)

📛 LIMITATIONS:

- ❌ Not optimal.
- ❌ Fails on large inputs (TLE on LeetCode for large n).
- ❌ Breaks the efficiency requirement of O(1) space and better than O(n^2) time.
- ❌ Not accepted by LeetCode when input size is high.

🧠 KEY INSIGHTS:

- This method is useful **only for small input sizes** (like n ≤ 1000).
- LeetCode expects a more optimal solution — e.g., using **Floyd's Tortoise and Hare Algorithm** (Cycle Detection, O(n) time, O(1) space) or Binary Search on Value Range.
- Even a hash map-based approach would be better than this, with O(n) time and O(n) space.
- This code will always find the first duplicate due to the guarantee in problem description.

*/

int main() {
    // 🔍 Example Test Case
    vector<int> nums = {3, 1, 3, 4, 2};

    Solution sol;
    int duplicate = sol.findDuplicate(nums);

    cout << "The duplicate number is: " << duplicate << endl;

    // 🔎 Expected Output: 3
    return 0;
}
