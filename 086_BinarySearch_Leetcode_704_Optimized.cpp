// LeetCode 704: Binary Search (Recursive Approach)
// Difficulty: Easy
// Topic: Binary Search, Divide & Conquer
// Language: C++
// Time Complexity: O(log n)
// Space Complexity: O(log n) due to recursion call stack

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Recursive binary search function
    int binarySearch(vector<int>& nums, int target, int start, int end) {
        if (start > end) {
            return -1; // Base case: invalid window means target not found
        }

        // ✅ Optimized mid calculation to prevent integer overflow
        int mid = start + (end - start) / 2;

        if (nums[mid] == target) {
            return mid; // Found the target
        } else if (target < nums[mid]) {
            return binarySearch(nums, target, start, mid - 1); // Search left half
        } else {
            return binarySearch(nums, target, mid + 1, end);   // Search right half
        }
    }

    // Public interface function
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size() - 1);
    }
};

int main() {
    Solution obj;

    // Example 1
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    int result1 = obj.search(nums1, target1);
    // Output: 4 → because nums1[4] == 9
    cout << "Index of " << target1 << " in Example 1: " << result1 << endl;

    // Example 2
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    int result2 = obj.search(nums2, target2);
    // Output: -1 → because 2 is not present
    cout << "Index of " << target2 << " in Example 2: " << result2 << endl;

    return 0;
}

/*
🧠 Concept Summary:
- Binary Search divides the array in half each step.
- Works only on sorted arrays.
- Recursion allows dividing the array by calling itself on subarrays.

📍 Recursive Flow:
    - Base Case: start > end → target not found.
    - Compute mid using optimized formula:
        mid = start + (end - start) / 2
    - If nums[mid] == target → return mid
    - Else search left or right half using recursive call

🧮 Optimized Mid Calculation:
    mid = start + (end - start) / 2;
    ✅ Prevents integer overflow:
       If start and end are large (close to INT_MAX), their sum might overflow.
       Subtracting then dividing is always safe.

📌 Time and Space Complexity:
- Time: O(log n) → Each call halves the array
- Space: O(log n) → Due to recursion call stack (each function call takes stack space)

📊 Iterative vs Recursive:

| Feature             | Iterative             | Recursive              |
|---------------------|------------------------|--------------------------|
| Time Complexity     | O(log n)               | O(log n)                 |
| Space Complexity    | O(1)                   | O(log n)                 |
| Stack Usage         | None                   | Uses system call stack   |
| Performance         | Slightly faster        | Slightly slower          |
| Code Simplicity     | More control/flexible  | More elegant/concise     |

✅ When to Use Recursion:
- For problems that are naturally recursive (trees, backtracking, etc.)
- For elegance or academic clarity
- Not recommended if memory/stack depth is critical

⚠️ When Not to Use Recursion:
- In tight loops or large datasets where stack overflow can occur
- When absolute performance or space efficiency is needed
*/
