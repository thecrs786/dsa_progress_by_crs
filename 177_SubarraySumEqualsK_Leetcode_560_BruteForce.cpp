#include <bits/stdc++.h>
using namespace std;

/*
========================================
🔹 Problem (LeetCode #560: Subarray Sum Equals K)
----------------------------------------
Given an array of integers (can include positive, negative, and zero),
count the total number of continuous subarrays whose sum equals k.

Example:
Input: nums = [1, 1, 1], k = 2
Output: 2
Explanation:
- Subarray [1,1] (first two elements) has sum = 2
- Subarray [1,1] (last two elements) has sum = 2
So, total count = 2.

----------------------------------------
🔹 Method: Brute Force with Running Sum
----------------------------------------
We fix a starting point (i), then expand the subarray step by step (j)
and keep track of the sum. Whenever sum == k, we increase count.

----------------------------------------
🔹 Time & Space Complexity
----------------------------------------
- Time Complexity: O(n^2)
  (Because we check all possible subarrays starting from i to j)
- Space Complexity: O(1)
  (We only use a few variables, no extra data structures)

----------------------------------------
🔹 Optimality & Acceptance
----------------------------------------
✔️ This solution WILL get accepted on LeetCode for most inputs.
❌ However, it's NOT the most optimal solution:
   - For large inputs (n ~ 10^5), O(n^2) may cause Time Limit Exceeded (TLE).
   - Optimal solution uses prefix sums + hashmap → O(n).
But for learning purpose, this brute force is correct and works for small-medium cases.

----------------------------------------
🔹 Important Insight
----------------------------------------
- We do NOT break the inner loop early:
  Because even if sum surpasses k (when numbers are positive),
  future numbers could be negative and bring it back to k.
  Similarly, if we skipped (continue), we might miss valid subarrays.
So, we always check FULLY from i → n-1 for each i.
========================================
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();    // store array size
        int count = 0;          // will store total valid subarray counts

        // Outer loop → select the starting point of subarray
        for (int i = 0; i < n; i++) {
            int sum = 0;  // reset sum for each new subarray starting at i

            // Inner loop → expand subarray from i → j
            for (int j = i; j < n; j++) {
                sum += nums[j];   // add current element to running sum

                // If subarray sum equals k, increment count
                if (sum == k) {
                    count++;
                }
            }
            // Note: No break/continue here because:
            // - Negative numbers can adjust the sum later
            // - Skipping may miss valid subarrays
        }
        return count;  // return total count
    }
};

/*
========================================
🔹 Logic & Working Explanation
----------------------------------------
1. For each index `i`, we consider it as the starting point of subarray.
2. We keep a running sum `sum` which initially is 0.
3. Then, for each next index `j`, we keep adding nums[j] to sum.
4. Every time sum == k, we found one valid subarray → increment count.
5. Finally, after checking all i..j pairs, return total count.

Why No Break/Continue?
- If nums has negatives:
   Example: nums = [3, -1, -2, 3], k = 3
   At i=0:
      sum = 3 → valid
      sum = 2 → not valid (shouldn't break, because next element +1 can restore k)
      sum = 0 → not valid
      sum = 3 → valid again
So, breaking early would MISS the second valid subarray.

========================================
🔹 Example Walkthrough
----------------------------------------
nums = [1, 2, 3], k = 3

i=0:
  j=0: sum=1 → not valid
  j=1: sum=3 → valid (count=1)
  j=2: sum=6 → not valid
i=1:
  j=1: sum=2 → not valid
  j=2: sum=5 → not valid
i=2:
  j=2: sum=3 → valid (count=2)

Final Answer: 2
========================================
*/

// Driver function to test working
int main() {
    Solution sol;

    // Example 1
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "Example 1 Output: " << sol.subarraySum(nums1, k1) << endl;
    // Expected: 2

    // Example 2
    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    cout << "Example 2 Output: " << sol.subarraySum(nums2, k2) << endl;
    // Expected: 2

    // Example 3 (with negatives)
    vector<int> nums3 = {3, -1, -2, 3};
    int k3 = 3;
    cout << "Example 3 Output: " << sol.subarraySum(nums3, k3) << endl;
    // Expected: 2 → [3], [3,-1,-2,3]

    return 0;
}
