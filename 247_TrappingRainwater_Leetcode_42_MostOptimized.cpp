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
- Optimized Two-Pointer Approach
- We maintain two pointers, left and right, at the ends of the array.
- Keep track of maximum height encountered from left (lmax) and right (rmax).
- Move the pointer with smaller max height inward, calculating trapped water as we go.
- Eliminates the need for extra arrays for lmax and rmax.

Time Complexity: O(n)
- Single pass through the array, each element visited once.

Space Complexity: O(1)
- No extra arrays; only a few variables used.

Optimality: 
- This is the optimal approach for 1D Trapping Rain Water problem.

Accepted on LeetCode: Yes, will pass all test cases including large n (~10^5+).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int lmax=0, rmax=0, ans=0;         // Initialize left max, right max, and answer
        int l=0, r = height.size()-1;      // Pointers at the leftmost and rightmost bars

        while(l<r){                        // Continue until pointers meet
            lmax = max(lmax, height[l]);   // Update maximum height from left
            rmax = max(rmax, height[r]);   // Update maximum height from right

            if(lmax < rmax){                // The limiting boundary is the left side
                ans += lmax - height[l];   // Water trapped at index l = left max - current height
                l++;                        // Move left pointer inward
            }
            else{                           // The limiting boundary is the right side
                ans += rmax - height[r];   // Water trapped at index r = right max - current height
                r--;                        // Move right pointer inward
            }
        }
        return ans;                         // Return total trapped water
    }
};

/*
Logic and Detailed Explanation (Two-Pointer Approach):

1. Idea:
   - Water trapped at a position depends on the minimum of the highest bars on left and right.
   - Two-pointer method avoids storing entire lmax and rmax arrays by tracking only current max from both ends.

2. Why it works:
   - At each step, we move the pointer with smaller max because water trapped is limited by the shorter boundary.
   - For left < right:
       - If lmax < rmax, water trapped at left is guaranteed = lmax - height[l]
         (because there exists rmax >= lmax on right)
       - If lmax >= rmax, water trapped at right = rmax - height[r]
         (because there exists lmax >= rmax on left)
   - This ensures exact water height is calculated for each block without knowing all middle heights.

3. How the heights in the middle don’t cause issues:
   - The trapped water at a bar depends on the shorter boundary.
   - Moving inward ensures we never underestimate water because the limiting factor is always considered.
   - Every bar is processed exactly once; order guarantees correctness.

4. Steps:
   - Initialize left, right pointers and lmax, rmax, ans.
   - While l < r:
       - Update lmax = max(lmax, height[l])
       - Update rmax = max(rmax, height[r])
       - If lmax < rmax → trap water at left pointer → move left inward
       - Else → trap water at right pointer → move right inward
   - Return ans

5. Optimization:
   - Avoids O(n) extra space for lmax and rmax arrays
   - Linear O(n) time → much faster than O(n^2) brute force or O(n) DP with extra arrays

*/

int main(){
    Solution sol;

    // Example 1
    vector<int> height1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "Trapped water (two-pointer) Example 1: " << sol.trap(height1) << endl; // Expected: 6

    // Example 2
    vector<int> height2 = {4,2,0,3,2,5};
    cout << "Trapped water (two-pointer) Example 2: " << sol.trap(height2) << endl; // Expected: 9

    return 0;
}

/*
Key Insights, Warnings, and Similar Questions:

1. Key Insights:
   - Two-pointer approach calculates exact water height without storing lmax/rmax arrays.
   - Movement is always toward the center from the smaller boundary.
   - lmax and rmax represent maximum heights seen so far from each end.

2. Edge Cases:
   - Empty array → 0 trapped water
   - Array size < 3 → cannot trap water → 0
   - Bars of equal height → no water trapped
   - Bars with zero height at edges → handled correctly

3. Warnings:
   - Must use '<' comparison to decide which pointer to move, otherwise logic fails.
   - Ensure lmax and rmax are updated **before** calculating trapped water.

4. Similar Questions / Approaches:
   - DP approach with precomputed lmax/rmax arrays (O(n) time, O(n) space)
   - LeetCode 11 (Container With Most Water)
   - LeetCode 407 (Trapping Rain Water 2D)
   - Brute force O(n^2) approach is slow and impractical for large inputs
*/
