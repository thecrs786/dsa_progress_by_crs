// ✅ PROBLEM: Find the Duplicate Number (LeetCode - Array - Medium)
// 🧠 DESCRIPTION (SUMMARY):
// Given an array of integers `nums` containing n + 1 integers where each integer is in the range [1, n] inclusive,
// There is only one duplicate number, return this duplicate number.
// You must not modify the array (read-only), and you must use only constant extra space if going for most optimal.
// However, this version uses an unordered_set — optimized, but not most optimal in terms of space.

// 🔍 SOLUTION METHOD: Using HashSet / Unordered_Set
// ✔️ NAME: Hashing Approach using Unordered Set
// 🕒 TIME COMPLEXITY: O(n) — traverses the array once
// 🧠 SPACE COMPLEXITY: O(n) — in worst case, all elements inserted into the set
// ✅ WILL THIS GET ACCEPTED ON LEETCODE? YES — passes all test cases successfully, fast and memory efficient enough
// ⚠️ WILL IT CAUSE TLE (Time Limit Exceeded)? No — runs in linear time
// ⚠️ WILL IT CAUSE MLE (Memory Limit Exceeded)? No — space usage is acceptable for LeetCode limits
// ⚡ OPTIMALITY: This is an *optimized* solution, but not the *most optimal*.
// The most optimal solution is Floyd's Tortoise and Hare (Cycle Detection) which uses O(1) space.

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Step 1: Declare an unordered_set (hash set) to track seen elements
        unordered_set<int> m;

        // Step 2: Traverse the entire array
        for (int i = 0; i < nums.size(); i++) {
            // Step 3: Check if current number already exists in set
            if (m.find(nums[i]) != m.end()) {
                // If it exists, it means this is the duplicate — return it
                return nums[i];
            } else {
                // Otherwise, insert it into the set
                m.insert(nums[i]);
            }
        }

        // Step 4: Return default if no duplicate is found (should never reach here based on problem guarantees)
        return {};
    }
};

/*
🔍 LOGIC WALKTHROUGH:

- The core idea is that since all elements are in the range [1, n], and the array has n+1 elements,
  the pigeonhole principle guarantees that at least one number will be repeated.

- We use a HashSet (unordered_set) to remember which numbers we've already seen.

- For each number in the array:
    → If it's already in the set → that means it's the duplicate → return it immediately.
    → Otherwise → add it to the set.

- This logic is extremely clean and efficient because:
    → Lookup in unordered_set is O(1) average-case.
    → Inserting and checking happens in constant time.

⚠️ KEY INSIGHTS:

- This method is great for interviews or when constraints do NOT require constant space.
- You should remember that this solution is NOT usable when the array is read-only or if O(1) space is required.
- In that case, use Floyd's Cycle Detection algorithm (Tortoise & Hare).

📌 EDGE CASES HANDLED:

- Only one duplicate exists — this is guaranteed by the problem, so we don't need to handle multiple duplicates.
- No need to sort or modify the original array.

✅ ADVANTAGES:
- Very easy to implement and understand.
- Performs extremely well in real-world scenarios.

⚠️ LIMITATIONS:
- Uses O(n) extra space.
- Not acceptable if the constraint says: "You must use constant extra space."

*/


// 🧪 WORKING EXAMPLE
int main() {
    Solution sol;

    // Test case
    vector<int> nums = {3, 1, 3, 4, 2};  // 3 is the duplicate

    int duplicate = sol.findDuplicate(nums);
    cout << "Duplicate number is: " << duplicate << endl;

    return 0;
}

/*
🎯 OUTPUT ANALYSIS:

Input:
    nums = [3, 1, 3, 4, 2]

Step-by-step processing:
    i=0 → nums[i]=3 → not in set → insert 3
    i=1 → nums[i]=1 → not in set → insert 1
    i=2 → nums[i]=3 → already in set → return 3

Output:
    Duplicate number is: 3

✔️ CONFIRMED: Works correctly for valid test case.

📌 FINAL TAKEAWAY:
- Fast and optimized with hashing — use it when space isn’t a strict constraint.
- Understand this before learning the more complex cycle detection version.
*/
