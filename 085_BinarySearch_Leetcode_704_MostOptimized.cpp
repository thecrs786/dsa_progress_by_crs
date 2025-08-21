// LeetCode 704: Binary Search
// Difficulty: Easy
// Topic: Arrays, Binary Search
// Language: C++
// Time Complexity: O(log n)
// Space Complexity: O(1)

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;                      // Start pointer at beginning of array
        int end = nums.size() - 1;          // End pointer at last index

        while (start <= end) {              // Continue as long as search window is valid

            // ✅ Optimized Mid Calculation to Prevent Overflow:
            // If start and end are both close to INT_MAX (2^31 - 1),
            // then (start + end) can overflow.
            // So we use: mid = start + (end - start) / 2;
            int mid = start + (end - start) / 2;

            if (nums[mid] == target) {
                return mid;                 // Found the target, return index
            } else if (target > nums[mid]) {
                start = mid + 1;            // Discard left half
            } else {
                end = mid - 1;              // Discard right half
            }
        }

        return -1;                          // Target not found
    }
};

int main() {
    Solution obj;

    // Example 1:
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    int result1 = obj.search(nums1, target1);

    // Output: 4 because nums1[4] == 9
    cout << "Index of " << target1 << " in Example 1: " << result1 << endl;

    // Example 2:
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    int result2 = obj.search(nums2, target2);

    // Output: -1 because 2 is not present in the array
    cout << "Index of " << target2 << " in Example 2: " << result2 << endl;

    return 0;
}

/*
🧠 Concept Summary:
- Binary Search is a powerful technique for searching in **sorted arrays**.
- At each iteration, we check the middle element:
    → If it’s the target, return the index.
    → If target is less, search in the left half.
    → If target is more, search in the right half.

🧮 Optimized Formula Used:
    int mid = start + (end - start) / 2;
    ✅ Prevents Integer Overflow:
        - If start = INT_MAX - 1 and end = INT_MAX
        - Then (start + end) would overflow the range of int
        - But (end - start) is small and safe to divide

📌 Key Properties:
- Time Complexity: O(log n) → cuts array in half each time
- Space Complexity: O(1) → uses constant extra space
- Works **only** on sorted arrays
- Returns index of target if found, else returns -1

📍 Why This Optimization Matters:
- Without this change, in rare edge cases with large arrays near int limits,
  your program might crash or give incorrect results.
- This is a **best practice** in interviews and professional code.

✅ Recommended Practice:
- Always use `start + (end - start) / 2` in binary search code.
*/
