/*
Problem Number: 42
Problem Name: Trapping Rain Water

Problem Brief:
Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9

Approach / Method: 
- Brute Force using precomputed left max (lmax) and right max (rmax) but computed via nested loops.
- For each bar, scan all previous bars to find lmax and all next bars to find rmax.

Time Complexity: O(n^2)
- Two nested loops for each bar → extremely inefficient.

Space Complexity: O(n)
- lmax and rmax arrays used.

Optimality: 
- Not optimal at all.
- Will fail for large inputs (n > 10^4).  

Accepted on LeetCode: No, it will fail for large test cases.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> lmax(n);
        vector<int> rmax(n);
        
        // Compute lmax for each index using nested loop (brute force)
        // lmax[i] = maximum height of bars from 0..i (left boundary)
        lmax[0] = height[0];
        for(int i = 1; i < n; i++){
            lmax[i] = height[i];
            for(int j = i-1; j >= 0; j--){
                lmax[i] = max(lmax[i], height[j]);
            }
        }

        // Compute rmax for each index using nested loop (brute force)
        // rmax[i] = maximum height of bars from i..n-1 (right boundary)
        rmax[n-1] = height[n-1];
        for(int i = n-2; i >= 0; i--){
            rmax[i] = height[i];
            for(int j = i+1; j < n; j++){
                rmax[i] = max(rmax[i], height[j]);
            }
        }

        // Calculate trapped water for each bar
        int maxarea = 0;
        for(int i = 0; i < n; i++){
            // Water at index i = min(lmax[i], rmax[i]) - height[i]
            // Guaranteed to be >= 0 because lmax[i] and rmax[i] >= height[i]
            maxarea += min(lmax[i], rmax[i]) - height[i];
        }

        return maxarea;
    }
};

/*
Logic and Detailed Explanation:

1. lmax[i] calculation:
   - For index i, scan all bars to the left (0..i) to find the highest bar.
   - This acts as the left boundary for trapped water at index i.
   - Nested loop approach → O(n^2) time.

2. rmax[i] calculation:
   - For index i, scan all bars to the right (i..n-1) to find the highest bar.
   - This acts as the right boundary for trapped water at index i.
   - Nested loop approach → O(n^2) time.

3. Trapped water at each index:
   - Water trapped = min(lmax[i], rmax[i]) - height[i]
   - Always >= 0 because min(lmax[i], rmax[i]) >= height[i]
   - Sum over all indices for total trapped water.

4. Why this approach is bad:
   - Time complexity O(n^2) → will TLE for large inputs (n ~ 10^4 or higher)
   - Space complexity is acceptable (O(n)), but runtime is unacceptably slow
   - Only useful for understanding the brute-force logic, not for submission.

5. Key iteration insights:
   - Each index checks all previous and all next bars to compute boundaries.
   - Water is bounded by the shorter of left and right max heights.

*/

int main(){
    Solution sol;

    // Example 1
    vector<int> height1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "Trapped water (brute force) Example 1: " << sol.trap(height1) << endl; // Expected: 6

    // Example 2
    vector<int> height2 = {4,2,0,3,2,5};
    cout << "Trapped water (brute force) Example 2: " << sol.trap(height2) << endl; // Expected: 9

    return 0;
}

/*
Key Insights, Warnings, and Similar Questions:

1. Water calculation:
   - currarea = min(lmax[i], rmax[i]) - height[i] ≥ 0, guaranteed
   - lmax and rmax act as boundaries

2. Edge Cases:
   - Empty array → 0 trapped water
   - Array size < 3 → cannot trap water → 0
   - Bars of equal height → no water trapped
   - Bars with 0 height at edges → handled correctly

3. Warnings:
   - This approach is extremely slow. Never use for n > 10^4
   - Only educational, for understanding the boundary logic

4. Similar Questions / Approaches:
   - Optimized DP: precompute lmax[i] and rmax[i] in O(n) time
   - Two-pointer approach: O(1) space, O(n) time
   - LeetCode 11: Container With Most Water
   - LeetCode 407: Trapping Rain Water 2D
*/
