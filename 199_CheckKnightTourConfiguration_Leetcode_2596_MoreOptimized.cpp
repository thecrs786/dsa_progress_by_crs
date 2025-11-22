/************************************************************

* CHECK KNIGHT TOUR CONFIGURATION - LEETCODE 2596
* More Optimized Recursive Backtracking Approach

* Problem Summary:
 * Given an n x n grid representing a knight's tour, 
 * check whether the knight can move from cell 0 to cell n*n-1 
 * visiting each number exactly once following standard knight moves.
 * 
 * Method Name: Recursive Backtracking with Target Checking
 * 
 * Time Complexity: O(8^(n*n)) in worst case, as each cell can recursively explore up to 8 moves.
 * Space Complexity: O(n*n) for recursion stack.
 * 
 * Notes:
 * - This is NOT the most optimal solution (deterministic O(n^2) exists),
 *   but it is acceptable for small n in LeetCode.
 * - This solution uses recursion to explore all valid knight moves from each cell,
 *   checking that the next cell contains the expected target number.
 ************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Check if row or col is inside grid
    bool isValid(int n, int row, int col){
        return row >= 0 && row < n && col >= 0 && col < n;
    }

    // Recursive helper: check if from (row, col) we can reach target step
    bool helper(vector<vector<int>> &grid, int row, int col, int target, int n) {
        // Base case: all steps done
        if(target == n*n) return true;

        // All 8 possible knight moves
        int dr[8] = {2,2,-2,-2,1,1,-1,-1};
        int dc[8] = {1,-1,1,-1,2,-2,2,-2};

        for(int i = 0; i < 8; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            // Check if the move is inside bounds and matches the expected target
            if(isValid(n, newRow, newCol) && grid[newRow][newCol] == target) {
                // Recursively check the next step
                if(helper(grid, newRow, newCol, target + 1, n))
                    return true; // valid path found
            }
        }

        return false; // no valid move found from this cell
    }

    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();

        // First cell must be 0
        if(grid[0][0] != 0) return false;

        // Start recursion from step 0, looking for step 1 next
        return helper(grid, 0, 0, 1, n);
    }
};

/************************************************************
 * Function Logic Explained:
 * 
 * 1. checkValidGrid:
 *    - Ensures the first cell is 0.
 *    - Calls recursive helper to explore knight moves.
 *
 * 2. helper:
 *    - Base case: If target == n*n, all cells have been visited correctly.
 *    - Iterate over 8 possible knight moves (dr[i], dc[i]).
 *    - For each move, check:
 *        a) Is it inside grid bounds (using isValid)?
 *        b) Does it contain the expected target number?
 *    - If yes, recursively call helper with target+1.
 *    - If any recursive call returns true, the function returns true.
 *    - If no moves lead to success, return false.
 *
 * Key Points / Insights:
 * - Recursive backtracking ensures all paths are explored.
 * - Checking the target number prevents exploring invalid sequences.
 * - Using isValid prevents out-of-bounds access.
 * - This solution is simple, readable, and works for small grids.
 * - For large grids, it can be optimized to O(n^2) deterministically.
 ************************************************************/

// ---------------- Working Example ----------------

int main() {
    Solution sol;

    // Example 1: Valid 3x3 knight tour
    vector<vector<int>> grid1 = {
        {0, 7, 2},
        {3, 4, 5},
        {6, 1, 8}
    };
    cout << "Grid 1 valid? " << (sol.checkValidGrid(grid1) ? "Yes" : "No") << endl;

    // Example 2: Invalid 3x3 knight tour
    vector<vector<int>> grid2 = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };
    cout << "Grid 2 valid? " << (sol.checkValidGrid(grid2) ? "Yes" : "No") << endl;

    return 0;
}

/************************************************************
 * Working of the Function:
 * - checkValidGrid calls helper starting from (0,0), target = 1.
 * - helper explores all 8 knight moves.
 * - Recursion proceeds only if the next cell matches the expected target.
 * - Recursion continues until target reaches n*n, returning true if successful.
 * - If no valid path exists from any recursive branch, returns false.
 ************************************************************/
