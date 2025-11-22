// Problem: LeetCode 84 – Largest Rectangle in Histogram
// Summary: Given an array 'heights' where each element represents the height of a histogram bar of width 1,
// find the area of the largest rectangle that can be formed within the histogram.
//
// Example 1:
// Input: heights = [2,1,5,6,2,3]
// Output: 10
// Explanation: The largest rectangle can be formed by using bars at indices 2 and 3 (heights 5 and 6).
// Width = 2, Height = 5 → Area = 2 * 5 = 10.
//
// Example 2:
// Input: heights = [2,4]
// Output: 4
// Explanation: Largest rectangle is the bar at index 1 alone.
//
// Edge Cases:
// - Single bar histogram → returns the bar’s own height.
// - All bars same → largest rectangle spans all bars.
// - Increasing or decreasing sequences → handled by expanding spans correctly.

// Approach:
// Brute Force Method → For each bar, expand to all possible rectangles including it and find the max area.
// This approach is simple to implement and understand but has high time complexity for large inputs.

// Solution Name: Brute Force (Nested Loop Expansion)
// Time Complexity: O(n^2) → For each of the n bars, it can expand to up to n bars on the right.
// Space Complexity: O(1) → Uses only variables, no extra space for stacks or other data structures.
// Optimality: ❌ Not optimal; works for small inputs but inefficient for larger datasets.
// Accepted by LeetCode? ✔ Will pass smaller test cases but ❌ cause TLE on larger inputs (>10^4 bars).

#include <iostream>
#include <vector>
#include <climits> // For INT_MIN
using namespace std;

class Solution {
public:
    // Function to find the largest rectangle area in the histogram.
    int largestRectangleArea(vector<int>& heights) {
        int maxarea = INT_MIN; // Initialize maximum area to the smallest possible value
        
        // Outer loop: start from each bar in the histogram
        for(int i = 0; i < heights.size(); i++) {
            int area = heights[i]; // Area considering only the single bar at index i
            int height = heights[i]; // Smallest height seen so far in the current span
            maxarea = max(maxarea, area); // Update max area if the single bar is the largest so far
            
            // Inner loop: expand the rectangle to include bars to the right of index i
            for(int j = i + 1; j < heights.size(); j++) {
                int width = j - i + 1; // Width of rectangle from index i to j inclusive
                height = min(height, heights[j]); // Update minimum height seen so far
                area = width * height; // Calculate area with current width and height
                maxarea = max(area, maxarea); // Update maximum area if current rectangle is larger
            }
        }
        
        return maxarea; // Return the largest area found across all spans
    }
};

// ✅ Main function with working example and output explanation
int main() {
    Solution solution;
    // Example histogram
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    // Calling the function and storing the result
    int result = solution.largestRectangleArea(heights);
    // Output the result
    cout << "Largest Rectangle Area: " << result << endl;
    // Expected Output: 10
    return 0;
}

/*
DETAILED EXPLANATION OF EACH STEP:

1. Initialization:
   - We start by setting maxarea to INT_MIN, ensuring that any valid area will be larger.
   - We iterate over each index 'i', treating it as the starting point of a rectangle.

2. Single Bar Rectangle:
   - For every 'i', we first calculate the area assuming the rectangle is just the single bar at 'i'.
   - This ensures that the smallest possible rectangle is always considered.

3. Expanding to Right:
   - We expand the rectangle to include every subsequent bar 'j' (where j > i).
   - At each step, we update the minimum height seen so far using `min(height, heights[j])`.
   - This ensures that the rectangle's height is always the smallest bar in the current span.

4. Area Calculation:
   - The width is computed as 'j - i + 1' because we include both the start and end bars.
   - We calculate the area as 'width * height'.

5. Updating maxarea:
   - We always compare the newly calculated area with the previously recorded maxarea.
   - This ensures we keep track of the largest rectangle encountered.

6. Final Return:
   - After all iterations, we return the maximum area found.

LOGIC BEHIND MINIMUM HEIGHT:
- The rectangle’s height cannot exceed the smallest bar in the chosen span.
- As we expand, including a new bar might reduce the rectangle’s height.
- Hence, tracking the minimum height is essential to accurately calculate the area.

EDGE CASE HANDLING:
✔ Single bar → returns its own height
✔ All bars same → rectangle spans the entire array
✔ Bars with increasing/decreasing heights → expansion logic accommodates these patterns

IMPORTANT DETAILS & KEY INSIGHTS:
- The problem is solved by brute force but not by recalculating the minimum at every step → we update incrementally.
- Correct width calculation (`j - i + 1`) is vital; missing this will give wrong answers.
- Even though brute force is inefficient, understanding this approach helps when transitioning to optimal solutions like using stacks.

⚠ NOTE:
- This solution will pass smaller test cases but fail on larger inputs (≥10^4 elements) because of its quadratic complexity.
- The optimal stack-based solution achieves O(n) and is recommended for production or interviews.
*/
