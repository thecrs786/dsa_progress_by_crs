#include <bits/stdc++.h>
using namespace std;

/*
==================================================
🔹 Problem (LeetCode #560: Subarray Sum Equals K) P in Brief:
Given an integer array nums and an integer k,
return the total number of subarrays whose sum equals k.

This is LeetCode Problem 560: "Subarray Sum Equals K"

==================================================
🔹 Concept of Prefix Sum:
- A prefix sum at index j represents the sum of all elements 
  from index 0 to j.
- Using prefix sums, we can calculate the sum of any subarray
  nums[i...j] as:
        prefixSum[j] - prefixSum[i-1]    (for i > 0)
        prefixSum[j]                     (for i = 0)

So prefix sums give us a way to compute subarray sums quickly.

But here, instead of querying subarray sums directly,
we reverse the logic:
    - If at index j, prefixSum[j] = S,
      and we want a subarray sum = k,
      then we check if there was some earlier prefix sum
      (say prefixSum[x]) such that:
        S - prefixSum[x] = k
      ⟹ prefixSum[x] = S - k
    - This means: to find valid subarrays ending at j,
      we just need to check if (S - k) has appeared before.

==================================================
🔹 Method Used in This Solution:
- Compute full prefixSum array.
- Use an unordered_map<int,int> (hashmap) to track frequencies
  of prefix sums that have been seen.
- If prefixSum[j] == k, increment count (handles subarray from 0..j).
- Otherwise, check if (prefixSum[j] - k) exists in the map.
  - If yes, add its frequency to count (all those subarrays are valid).
  - If not, continue.
- Update map with current prefixSum[j].

==================================================
🔹 Time and Space Complexity:
- Time Complexity: O(n) 
  (we compute prefix sums in O(n) and traverse once with hashmap lookups O(1) average).
- Space Complexity: O(n) 
  (prefixSum array of size n + hashmap of prefix sums).

==================================================
🔹 Is this the Most Optimal?
- No. This works and will be ACCEPTED on LeetCode,
  but it is not the cleanest optimal solution.
- Optimal solution avoids storing prefixSum vector,
  using only a running sum (still O(n) time and space).
- However, this code will NOT cause TLE or MLE in constraints.
  It is safe and accepted.

==================================================
🔹 Key Insights:
- Subarray sums can be converted into prefix sum differences.
- Hashmap stores counts of prefix sums, 
  because multiple earlier indices may yield valid subarrays.
- Directly checking `prefixSum[j] == k` covers cases
  where subarray starts from index 0.
- Important: we add to map AFTER checking,
  to avoid counting the current prefix as part of itself.

==================================================
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefixSum(n,0);  // stores prefix sums
        unordered_map<int, int> m;   // frequency map of prefix sums
        int count = 0;               // total subarrays count

        // build prefix sum array
        prefixSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        // iterate over prefix sums
        for (int j = 0; j < n; j++) {
            // Case 1: subarray starts at index 0
            if (prefixSum[j] == k) {
                count++;
            }

            // Case 2: subarray starts somewhere after 0
            int val = prefixSum[j] - k;

            if (m.find(val) == m.end()) {
                // if (prefixSum[j]-k) not found, just record this prefixSum
                m[prefixSum[j]]++;
            } else {
                // if found, add frequency (all those subarrays are valid)
                count += m[val];
                // update frequency of this prefixSum for future
                m[prefixSum[j]]++;
            }
        }

        return count;
    }
};

/*
==================================================
🔹 Full Logic and Walkthrough:

1. Compute prefixSum array:
   prefixSum[i] = sum(nums[0..i]).
   This helps in quickly calculating any subarray sum.

2. Iterate over prefixSum:
   - If prefixSum[j] == k:
        subarray nums[0..j] has sum k, increment count.
   - Otherwise:
        check if (prefixSum[j]-k) exists in hashmap.
        If yes, that means there was an earlier prefix sum 
        whose difference with current prefixSum equals k.
        Add the frequency of (prefixSum[j]-k) to count.

3. Update hashmap:
   - Record the current prefixSum[j] to be used for future indices.
   - If it already exists, increment frequency.

==================================================
🔹 Example Dry Run:

nums = [1,2,3], k = 3

Step 1: prefixSum = [1,3,6]

Step 2: Traverse:
j=0:
  prefixSum[0] = 1, not equal to k.
  val = 1-3 = -2, not in map.
  Store prefixSum[0]=1 in map.
  map = {1:1}

j=1:
  prefixSum[1] = 3 == k, count=1
  val = 3-3 = 0, not in map.
  Store prefixSum[1]=3 in map.
  map = {1:1, 3:1}

j=2:
  prefixSum[2] = 6, not equal to k.
  val = 6-3 = 3, found in map with frequency=1.
  count += 1 → count=2
  Store prefixSum[2]=6 in map.
  map = {1:1, 3:1, 6:1}

Final Answer: count = 2
(Valid subarrays: [1,2], [3])

==================================================
🔹 Edge Cases to Note:
- Negative numbers in nums (prefix sum + hashmap still works).
- Large arrays up to 10^5 → O(n) solution is necessary.
- k = 0 (works fine with logic).
- Single element array.

==================================================
*/

int main() {
    // Working Example
    Solution sol;
    vector<int> nums = {1, 2, 3};
    int k = 3;
    int result = sol.subarraySum(nums, k);

    cout << "Number of subarrays with sum = " << k << " is: " << result << endl;
    // Expected Output: 2
    // Explanation:
    // Subarrays [1,2] and [3] both sum to 3.
    return 0;
}
