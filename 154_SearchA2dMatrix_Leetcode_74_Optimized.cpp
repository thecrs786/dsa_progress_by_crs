/*
----------------------------------------------------------------------
QUESTION: Search a 2D Matrix (Leetcode #74)

You are given an m x n integer matrix `matrix` with the following two properties:
1. Each row is sorted in non-decreasing order.
2. The first integer of each row is greater than the last integer of the previous row.

Given an integer `target`, return true if `target` is in `matrix`, and false otherwise.
----------------------------------------------------------------------

SOLUTION NAME: Optimized Binary Search (Two-step binary search)

TIME COMPLEXITY: O(log m + log n)
    -> First binary search to find the correct row: O(log m)
    -> Second binary search on that row: O(log n)

SPACE COMPLEXITY: O(1)
    -> No extra space used apart from variables.

IS THIS THE MOST OPTIMAL SOLUTION?
✔️ YES — This is the most optimal approach for this problem given the constraints.

LEETCODE STATUS:
✔️ Will be accepted on Leetcode. No risk of TLE or MLE.

----------------------------------------------------------------------
*/

#include <iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        // Step 1: Initialize binary search on rows
        int strow = 0;
        int endrow = matrix.size() - 1;

        while (strow <= endrow) {
            int midrow = strow + (endrow - strow) / 2;

            // Step 2: Check if target lies within this row's range
            if (matrix[midrow][0] <= target && matrix[midrow].back() >= target) {
                
                // Step 3: Target must be in this row, apply binary search on the row
                int stcol = 0;
                int endcol = matrix[midrow].size() - 1;

                while (stcol <= endcol) {
                    int midcol = stcol + (endcol - stcol) / 2;

                    if (matrix[midrow][midcol] == target) {
                        return true; // found the target
                    } 
                    else if (matrix[midrow][midcol] > target) {
                        endcol = midcol - 1; // discard right half
                    } 
                    else {
                        stcol = midcol + 1; // discard left half
                    }
                }

                // Target not found in the selected row
                return false;
            }

            // Step 4: If target is less than first element of midrow, discard bottom half
            if (matrix[midrow][0] > target) {
                endrow = midrow - 1;
            }

            // Step 5: If target is greater than last element of midrow, discard top half
            if (matrix[midrow].back() < target) {
                strow = midrow + 1;
            }
        }

        // Target not found in any row
        return false;
    }
};

/*
----------------------------------------------------------------------
FULL LOGIC EXPLANATION:

Why two binary searches?

Since the entire matrix is sorted *row-wise* and each row’s first element is greater than
the last element of the previous row, we can treat the matrix like a 1D sorted list. But instead 
of flattening, we do:
1. Binary search on rows to find the row where the target can possibly exist.
2. Binary search inside that row to find the exact value.

Step-by-step:
- First binary search helps us narrow down to 1 row (using the fact that row ranges are sorted).
- Once we know the row could contain the target, we perform normal binary search on that row.
- If the value is found — return true.
- If not — return false.

This avoids scanning unnecessary rows and keeps both row and column searches efficient.
----------------------------------------------------------------------

EXAMPLE USAGE:
*/



int main() {
    Solution sol;
    
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target = 3;

    if (sol.searchMatrix(matrix, target)) {
        cout << "Target " << target << " found in matrix." << endl;
    } else {
        cout << "Target " << target << " NOT found in matrix." << endl;
    }

    return 0;
}

/*
----------------------------------------------------------------------
OUTPUT:
Target 3 found in matrix.
----------------------------------------------------------------------
*/
