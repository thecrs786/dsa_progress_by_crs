/*******************************************************
LeetCode Problem 240: Search a 2D Matrix II

 NOTE -> BRUTE FORCE APPROACH FOR THIS QUESTION IS SIMILAR TO THAT OF QUESTION 74
        SEARCH A 2D MATRIX


🔍 Question Summary:
Given an `m x n` matrix where each row is sorted in 
ascending order from left to right, and each column is 
sorted in ascending order from top to bottom, determine 
whether a target integer exists in the matrix.

🔧 Method Name: Row-wise Binary Search (Optimized but Not Most Optimal)

⏱️ Time Complexity:
- Best Case: O(log n) if found in the first row
- Worst Case: O(m * log n), where `m = number of rows`, `n = number of columns`
  (we run binary search for each row)

🧠 Space Complexity:
- O(1), no extra space used beyond variables

💡 Is it the Most Optimal? ❌
- No. There exists a better solution with O(m + n) using Staircase Search
  from top-right corner.

✅ Will it get Accepted by LeetCode? ✔️
- Yes, completely safe from TLE and MLE within given constraints

*******************************************************/



#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // Step 1: Loop through each row one by one
        for (int row = 0; row < matrix.size(); row++) {

            // ⚠️ OPTIMIZATION:
            // If the smallest element in this row is greater than the target,
            // then the entire row is too big → skip it.
            if (matrix[row][0] > target) continue;

            // If the largest element in this row is smaller than the target,
            // then the entire row is too small → skip it.
            if (matrix[row].back() < target) continue;

            // Step 2: Set binary search boundaries for current row
            int st = 0;
            int end = matrix[row].size() - 1;

            // Step 3: Perform Binary Search in the current row
            while (st <= end) {
                // Prevent integer overflow
                int mid = st + (end - st) / 2;

                // Step 4: Check if middle element is the target
                if (matrix[row][mid] == target) {
                    return true;  // Found the target
                }

                // Step 5: If middle element is greater than target,
                // search in the left half
                else if (matrix[row][mid] > target) {
                    end = mid - 1;
                }

                // Step 6: If middle element is less than target,
                // search in the right half
                else {
                    st = mid + 1;
                }
            }
            // If not found in this row, move to next row
        }

        // Step 7: Target not found in any row
        return false;
    }
};


/************************************************************
🧠 EXPLANATION OF THE LOGIC (Long, Raw, and Clear):

We are given a 2D matrix where:
1. Each row is sorted in ascending order
2. Each column is also sorted in ascending order

This means:
- All elements in a row go from small to large → allows binary search
- But across rows, there's no strict linear pattern → can't apply 1D binary search on entire matrix

So we use this approach:
- Go row-by-row and apply Binary Search in each row individually.
- Since each row is sorted, Binary Search will work.
- We avoid brute force (O(m * n)) by doing O(log n) per row

⚠️ OPTIMIZATION EXPLAINED:
Before doing binary search on any row, we do two checks:

1. If the first element of the row is **greater than the target**, then:
   - All elements in that row are also greater (because it’s sorted).
   - No point searching — skip that row entirely.
   - Saves O(log n) time that would have been wasted.

2. If the last element of the row is **less than the target**, then:
   - All elements in that row are also less.
   - No point searching — skip that row entirely.

This optimization makes the algorithm avoid completely unnecessary work.
In the worst case, it still stays O(m log n), but on many inputs this **reduces actual runtime significantly.**

This is an "optimized" approach — better than brute force,
but not the best. There exists a top-right to bottom-left
staircase search with O(m + n), which skips unnecessary rows/columns.

************************************************************/


/************************************************************
🔎 WORKING EXAMPLE TO TEST OUTPUT:

Matrix:
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

Target: 5 → should return true
Target: 20 → should return false

************************************************************/

int main() {
    Solution sol;

    vector<vector<int>> matrix = {
        {1,   4,  7, 11, 15},
        {2,   5,  8, 12, 19},
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    int target1 = 5;
    int target2 = 20;

    cout << "Searching for " << target1 << ": " << (sol.searchMatrix(matrix, target1) ? "Found" : "Not Found") << endl;
    cout << "Searching for " << target2 << ": " << (sol.searchMatrix(matrix, target2) ? "Found" : "Not Found") << endl;

    return 0;
}
