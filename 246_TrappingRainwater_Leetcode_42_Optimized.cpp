/*
Problem Number: 42
Problem Name: Trapping Rain Water

Problem Brief:
Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: Water is trapped between the bars, totaling 6 units.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9

Approach / Method: 
- Dynamic Programming using precomputed left max (lmax) and right max (rmax) arrays.

Time Complexity: O(n) 
- We traverse the array three times: to fill lmax, rmax, and calculate trapped water.

Space Complexity: O(n) 
- Extra space used for lmax and rmax arrays.

Optimality: 
- This is an optimized DP approach but not the absolute best.
- The absolute optimal solution uses two pointers with O(1) extra space.

Accepted on LeetCode: Yes, within constraints (n <= 2*10^4)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> lmax(n);
        vector<int> rmax(n);
        
        // Step 1: Compute left max array
        lmax[0] = height[0]; // The maximum height to the left of first bar is itself
        for(int i = 1; i < n; i++){
            // lmax[i] stores the tallest bar from index 0 to i
            lmax[i] = max(lmax[i-1], height[i]);
        }

        // Step 2: Compute right max array
        rmax[n-1] = height[n-1]; // The maximum height to the right of last bar is itself
        for(int i = n-2; i >= 0; i--){
            // rmax[i] stores the tallest bar from index i to n-1
            rmax[i] = max(rmax[i+1], height[i]);
        }

        // Step 3: Calculate trapped water
        int maxarea = 0;
        for(int i = 0; i < n; i++){
            // Water trapped at index i is min(left_max, right_max) - height[i]
            // This is guaranteed to be >= 0 because lmax[i] and rmax[i] >= height[i]
            maxarea += min(lmax[i], rmax[i]) - height[i];
        }

        return maxarea;
    }
};

/*
Logic and Detailed Explanation:

1. Finding lmax:
   - For each index i, lmax[i] is the tallest bar from the start to i.
   - This guarantees that we know the maximum possible water level on the left side for index i.

2. Finding rmax:
   - For each index i, rmax[i] is the tallest bar from i to the end.
   - Guarantees maximum possible water level on the right side.

3. Calculating water:
   - At each index, water trapped = min(lmax[i], rmax[i]) - height[i]
   - The min ensures that water doesn't overflow beyond the shorter side.
   - Guaranteed to be >=0 because lmax[i] and rmax[i] are always >= height[i].

4. Iteration Explanation:
   - First loop: fill lmax[i] in O(n)
   - Second loop: fill rmax[i] in O(n)
   - Third loop: calculate trapped water in O(n)
   - Each element is processed only once in each loop, leading to O(n) time.

5. Example walkthrough (height = [0,1,0,2,1,0,1,3,2,1,2,1]):
   - lmax = [0,1,1,2,2,2,2,3,3,3,3,3]
   - rmax = [3,3,3,3,3,3,3,3,2,2,2,1]
   - Water at each index = min(lmax[i], rmax[i]) - height[i]
   - Total water = 6

*/

int main(){
    Solution sol;
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};

    int result = sol.trap(height);
    cout << "Trapped water: " << result << endl; // Expected output: 6

    return 0;
}

/*
Key Insights, Warnings, and Similar Questions:

1. lmax[i] and rmax[i] guarantee that min(lmax[i], rmax[i]) is always >= height[i]
   - No negative water is possible using this approach.

2. Edge Cases:
   - Empty array or array size < 3 → no water trapped
   - All bars of same height → water = 0
   - Bars with height 0 at edges → handled correctly

3. Warnings:
   - Never initialize lmax[0] or rmax[n-1] to 0. Always use the actual height.
   - Avoid brute force O(n^2) approach; it will TLE for large n.

4. Similar Questions and Approaches:
   - LeetCode 11: Container With Most Water → two-pointer approach
   - LeetCode 407: Trapping Rain Water II (2D version)
   - Approach: Two pointers for O(1) space optimization, using left_max and right_max while traversing from both ends.
*/
