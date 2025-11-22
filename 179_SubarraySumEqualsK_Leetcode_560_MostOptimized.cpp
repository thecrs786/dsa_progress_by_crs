/************************************************************
 * Problem : SUBARRAY SUM EQUALS K (560)
 * ----------------
 * Given an integer array 'nums' and an integer 'k', count
 * the total number of continuous subarrays whose sum equals 'k'.
 * 
 * Example:
 * nums = [1,1,1], k = 2
 * Output: 2
 * Explanation: The subarrays [1,1] at indices (0,1) and (1,2)
 * both sum to 2.
 * 
 * Method / Approach:
 * ------------------
 * Prefix Sum with Hash Map (unordered_map) to store frequency
 * of previous prefix sums.
 * 
 * Key Idea:
 * For each index i, let prefix = sum of nums[0..i]. If there
 * exists a prefix sum 'prefix-k' seen before, it means the subarray
 * between that previous occurrence +1 to i sums to k. Increment count
 * by the number of occurrences of 'prefix-k'.
 * 
 * Time Complexity: O(n) — traverse array once, hashmap operations O(1) average
 * Space Complexity: O(n) — store prefix sums in unordered_map
 * Optimality: Yes, this is the most optimal solution for this approach
 * LeetCode Status: Accepted, no TLE or MLE
 ************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to count subarrays with sum equal to k
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        // unordered_map stores frequency of each prefix sum seen so far
        unordered_map<int, int> PS;

        int prefix = 0;   // Running prefix sum
        int count = 0;    // Total subarrays with sum k

        for (int i = 0; i < n; i++) {
            prefix += nums[i];     // Step 1: update running prefix sum

            int val = prefix - k;  // Step 2: check if there exists a prefix sum
                                    // that would make current subarray sum = k
            
            if (val == 0) // case when the prefix sum is equal to k.
                count++;           // Step 3: handle subarrays starting at index 0

            // Step 4: if val exists in map, add its occurrences to count
            if (PS.find(val) != PS.end()) {
                count += PS[val];
            }

            // Step 5: update current prefix sum frequency in map
            PS[prefix]++;
        }

        return count;
    }
};

/************************************************************
 * Detailed Explanation of Logic:
 * --------------------------------
 * 1. We maintain a running sum called 'prefix' as we traverse nums.
 * 2. For each prefix, the subarray sum from a previous index j+1 to current i
 *    is exactly k if prefix - k equals a previously seen prefix sum.
 * 3. We store all previous prefix sums in unordered_map along with their count.
 * 4. Whenever we see 'prefix - k' in the map, it means there are PS[prefix-k]
 *    subarrays ending at current index which sum to k. Add this to count.
 * 5. For subarrays starting at index 0 that sum to k, 'prefix - k' would be 0.
 *    Instead of using PS[0]=1 (canonical method), we manually check val==0
 *    and increment count. This is why the code works without PS[0]=1.
 * 
 * Why no vector for prefix sums:
 * - We don’t need to store all prefix sums in a vector.
 * - We only need the **count of occurrences** for each prefix sum to calculate subarrays.
 * - Using unordered_map allows O(1) average time lookup, no extra vector required.
 * 
 * PS[0] concept:
 * - In standard implementations, PS[0] = 1 allows handling subarrays starting
 *   at index 0 without a manual check. In your code, the manual 'if(val==0)'
 *   handles this case. Functionally equivalent.
 * - Using PS[0]=1 removes manual edge-case handling and makes code cleaner.
 * - Both approaches work, but your version mixes manual check with map, still correct.
 ************************************************************/

// Working example for testing and analyzing output
int main() {
    Solution sol;
    
    vector<int> nums = {1, 2, 3, 1, 2};
    int k = 3;
    
    int result = sol.subarraySum(nums, k);
    
    cout << "Number of subarrays with sum " << k << " is: " << result << endl;
    
    /************************************************************
     * Dry Run of Example:
     * nums = [1,2,3,1,2], k = 3
     * prefix sums: 1,3,6,7,9
     * Map updates:
     * i=0, prefix=1, val=-2, count remains 0, PS[1]=1
     * i=1, prefix=3, val=0, count++ -> count=1, PS[3]=1
     * i=2, prefix=6, val=3, count += PS[3]=1 -> count=2, PS[6]=1
     * i=3, prefix=7, val=4, not in map, PS[7]=1
     * i=4, prefix=9, val=6, count += PS[6]=1 -> count=3, PS[9]=1
     * Final count = 3
     ************************************************************/
    
    return 0;
}
