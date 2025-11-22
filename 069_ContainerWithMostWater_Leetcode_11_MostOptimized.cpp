// LeetCode Problem 11: Container With Most Water
// Optimized Two-Pointer Approach
// Time Complexity: O(n)
// Space Complexity: O(1)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // Initialize two pointers: one at the beginning, one at the end
        int leftptr = 0;
        int rightptr = height.size() - 1;

        int maxarea = 0; // This will store the maximum area found

        // Loop until the two pointers meet
        while (rightptr > leftptr) {
            // Height is determined by the shorter of the two lines
            int ht = min(height[leftptr], height[rightptr]);

            // Width is the distance between the two lines
            int width = rightptr - leftptr;

            // Calculate the current area
            int area = ht * width;

            // Update max area if current area is greater
            maxarea = max(area, maxarea);

            // Move the pointer pointing to the shorter line inward
            // Why? Because only the shorter line is limiting the area
            if (height[leftptr] < height[rightptr]) {
                leftptr++;
            } else {
                rightptr--;
            }
        }

        return maxarea;
    }
};

// 🔎 Example:
// Input: height = [1,8,6,2,5,4,8,3,7]
// Output: 49
// Explanation:
// The maximum area is formed between height[1] = 8 and height[8] = 7
// Area = min(8,7) * (8 - 1) = 7 * 7 = 49

int main() {
    Solution sol;
    vector<int> height = {1,8,6,2,5,4,8,3,7};

    cout << "Maximum Water Area: " << sol.maxArea(height) << endl;
    return 0;
}
