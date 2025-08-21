#include <iostream>
#include <vector>
using namespace std;

/*
    ✅ QUESTION: LeetCode 704. Binary Search
    --------------------------------------------------
    📌 Problem Statement (in brief):
       - You are given a sorted array `nums` (in ascending order).
       - You need to search for a given `target` value in this array.
       - If `target` exists in the array, return its index.
       - If not, return -1.

    ⚡ Method/Approach:
       - Recursive Binary Search.

    🕒 Time Complexity: O(log n)
       - Each recursive step halves the search space.
    💾 Space Complexity: O(log n) 
       - Due to recursion stack calls.
       - If iterative version is used → O(1) space.

    🔑 Optimal or not?
       - YES. Binary search is the most optimal approach for sorted arrays.
       - Iterative version is slightly better in memory usage, but recursion is still acceptable.
       - LeetCode will accept this solution. ✅
       - No chance of TLE (O(log n) is very efficient).
       - No chance of MLE (recursion depth = log n, safe since n ≤ 10^4 for this problem).

    🔥 Key Insights:
       - `mid = st + (end - st)/2` is used instead of `(st+end)/2` to prevent integer overflow.
       - Base case `if(st > end) return -1;` ensures recursion stops.
       - Always shrink search space → either search left or right half.
       - Works only on **sorted arrays**.
*/


class Solution {
public:
    // Recursive binary search helper function
    int binarysearch(vector<int>& nums, int st, int end, int target) {
        if (st > end) return -1;  // ✅ Base case: target not found

        int mid = st + (end - st) / 2;  // ✅ Prevents overflow

        if (nums[mid] == target) {
            return mid;  // ✅ Found target at mid
        }
        else if (nums[mid] > target) {
            // ✅ Target must be in the left half
            return binarysearch(nums, st, mid - 1, target);
        }
        else {
            // ✅ Target must be in the right half
            return binarysearch(nums, mid + 1, end, target);
        }
    }

    // Public function called by user/LeetCode
    int search(vector<int>& nums, int target) {
        return binarysearch(nums, 0, nums.size() - 1, target);
    }
};


/*
    ⚡ Walkthrough of Logic (example):
    ---------------------------------
    Input: nums = [-10, -3, 0, 5, 9, 12], target = 9

    1. st = 0, end = 5, mid = 2 → nums[2] = 0
       - 0 < 9 → search right half.
    2. st = 3, end = 5, mid = 4 → nums[4] = 9
       - Found target at index 4 → return 4.

    Output: 4
    ---------------------------------
    Edge Case Examples:
    - nums = [1], target = 1 → mid = 0 → found → return 0.
    - nums = [1], target = 2 → base case triggers → return -1.
    - nums = [2,4,6,8,10], target = -5 → return -1.
*/


// ✅ Working Example with main()
int main() {
    Solution obj;
    vector<int> nums = {-10, -3, 0, 5, 9, 12};

    cout << "Example 1: target = 9 → Output: " 
         << obj.search(nums, 9) << endl;   // Expected 4

    cout << "Example 2: target = 2 → Output: " 
         << obj.search(nums, 2) << endl;   // Expected -1

    cout << "Example 3: target = -10 → Output: " 
         << obj.search(nums, -10) << endl; // Expected 0

    cout << "Example 4: target = 12 → Output: " 
         << obj.search(nums, 12) << endl;  // Expected 5

    return 0;
}

/*
    📌 Summary:
    - Binary search works by repeatedly halving the search space.
    - Recursive version is simple and elegant but uses O(log n) stack memory.
    - Iterative version is slightly more memory-efficient (O(1) space).
    - Both are acceptable and optimal in time complexity O(log n).
    - Always check base case `st > end` to avoid infinite recursion.
*/
