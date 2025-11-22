/*
Problem: LeetCode 84 - Largest Rectangle in Histogram

Given an array of integers 'heights' representing the histogram's bar heights 
where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Examples:
1) heights = [2,1,5,6,2,3]
   Output: 10
   Explanation: The largest rectangle has height 2 and width 5-3+1 = 2*5 = 10

2) heights = [2,4]
   Output: 4
   Explanation: The largest rectangle is the second bar itself.

Approach/Method: Stack-based Nearest Smaller to Left and Right (Single Stack Optimization)
Time Complexity: O(n)
Space Complexity: O(n)
Optimality: ✅ Most optimal stack-based solution
Accepted in LeetCode? ✅ Yes, no TLE or MLE
Key insights:
    - Use a single stack to compute nearest smaller indices for left and right.
    - Width = rightBoundary - leftBoundary - 1 accounts for index shift.
    - Assign -1 to left when no smaller element exists.
    - Assign n to right when no smaller element exists.
    - Handles all edge cases naturally.
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> leftNearestSmaller(n);   // Stores index of nearest smaller bar to the left
        vector<int> rightNearestSmaller(n);  // Stores index of nearest smaller bar to the right

        stack<int> s;  // Stack to calculate left and right nearest smaller indices

        // -----------------------------
        // Compute left nearest smaller
        // -----------------------------
        for(int i = 0; i < n; i++){
            // Pop all indices from stack whose heights >= current height
            // These cannot be nearest smaller for the current bar
            while(!s.empty() && heights[s.top()] >= heights[i]){
                s.pop();
            }

            // If stack is empty → no smaller bar on the left → assign -1
            // This means rectangle can extend to index 0
            if(s.empty()){
                leftNearestSmaller[i] = -1;
            }
            else {
                // Stack top now contains index of nearest smaller bar
                leftNearestSmaller[i] = s.top();
            }

            // Push current index onto stack for future bars
            s.push(i);
        }

        // Clear stack to reuse it for right nearest smaller
        while(!s.empty()) s.pop();

        // ------------------------------
        // Compute right nearest smaller
        // ------------------------------
        for(int i = n-1; i >= 0; i--){
            // Pop all indices from stack whose heights >= current height
            while(!s.empty() && heights[s.top()] >= heights[i]){
                s.pop();
            }

            // If stack is empty → no smaller bar on the right → assign n
            // This means rectangle can extend to index n-1
            if(s.empty()){
                rightNearestSmaller[i] = n;
            }
            else {
                // Stack top now contains index of nearest smaller bar
                rightNearestSmaller[i] = s.top();
            }

            // Push current index onto stack for future bars
            s.push(i);
        }

        // ------------------------------
        // Compute max rectangle area
        // ------------------------------
        int maxarea = 0;
        for(int i = 0; i < n; i++){
            // Width calculation:
            // rightNearestSmaller[i] is first smaller bar on the right (exclusive)
            // leftNearestSmaller[i] is first smaller bar on the left (exclusive)
            // Subtract 1 to account for both boundaries being smaller bars
            int width = rightNearestSmaller[i] - leftNearestSmaller[i] - 1;

            // Area = height of current bar * width of rectangle
            int area = heights[i] * width;

            // Update maximum area found
            maxarea = max(maxarea, area);
        }

        return maxarea;
    }
};

// --------------------------------------
// Main function to test the solution
// --------------------------------------
int main() {
    Solution solution;

    // Example 1
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "Largest Rectangle Area for [2,1,5,6,2,3]: " 
         << solution.largestRectangleArea(heights1) << endl; // Expected: 10

    // Example 2
    vector<int> heights2 = {2, 4};
    cout << "Largest Rectangle Area for [2,4]: " 
         << solution.largestRectangleArea(heights2) << endl; // Expected: 4

    // Example 3 (Edge case: increasing heights)
    vector<int> heights3 = {1, 2, 3, 4, 5};
    cout << "Largest Rectangle Area for [1,2,3,4,5]: " 
         << solution.largestRectangleArea(heights3) << endl; // Expected: 9 (3*3)

    // Example 4 (Edge case: single bar)
    vector<int> heights4 = {7};
    cout << "Largest Rectangle Area for [7]: " 
         << solution.largestRectangleArea(heights4) << endl; // Expected: 7

    return 0;
}

/*
--------------------------------------
Full Logic Explanation:
--------------------------------------

1) Nearest Smaller to Left (NSL):
   - Maintain a stack to store indices of bars.
   - Pop all bars >= current bar because they cannot be NSL.
   - If stack is empty → no smaller bar exists → assign -1
   - Else → top of stack is the index of nearest smaller bar.
   - Index shift: rectangle starts **one index after** leftNearestSmaller[i].

2) Nearest Smaller to Right (NSR):
   - Traverse from right to left using same logic.
   - Pop all bars >= current bar.
   - If stack empty → no smaller bar exists → assign n
   - Else → top of stack is the index of nearest smaller bar.
   - Index shift: rectangle ends **one index before** rightNearestSmaller[i].

3) Width formula:
   - width = rightNearestSmaller[i] - leftNearestSmaller[i] - 1
   - Handles the "shift" caused by exclusive boundaries.

4) Area calculation:
   - area = heights[i] * width
   - Update maxarea for each bar.

5) Edge cases handled:
   - Single bar → area = bar height
   - Increasing or decreasing sequences → NSL and NSR handle correctly
   - Equal heights → entire array considered as rectangle

6) How popping works:
   - Bars popped are taller/equal → cannot be NSL/NSR for current bar
   - After popping, top of stack gives the nearest smaller index
   - If stack empty → no smaller bar → assign -1 (left) or n (right)

7) Key Insights:
   - Single stack reuse reduces memory slightly
   - Index shift handled elegantly using r-l-1 formula
   - O(n) time and O(n) space is optimal for this problem
   - Works for all edge cases naturally

Time Complexity: O(n)
Space Complexity: O(n)
Optimality: ✅ Most optimal for histogram rectangle problem
LeetCode Acceptance: ✅ Yes, passes all tests
*/

