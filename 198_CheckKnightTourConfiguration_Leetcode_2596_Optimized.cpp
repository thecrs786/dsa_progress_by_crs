/************************************************************

* CHECK KNIGHT TOUR CONFIGURATION - LEETCODE 2596
* Recursive Backtracking Approach (Explicit Knight Moves)

* Problem Summary:
 * Given an n x n grid representing a knight's tour, 
 * check whether the knight can move from cell 0 to cell n*n-1 
 * visiting each number exactly once following standard knight moves.
 * The first cell must contain 0, and the last cell n*n-1.
 * 
 * Method Name: Recursive Backtracking (Explicit Knight Moves)
 * 
 * Time Complexity: O(8^(n*n)) in worst case, as each cell may explore 8 moves recursively.
 * Space Complexity: O(n*n) for recursion stack in worst case.
 * 
 * Note:
 * - This is not the most optimal solution (deterministic O(n^2) exists),
 *   but this is acceptable for small n (LeetCode test cases).
 * - It uses backtracking and recursion to explore all valid knight moves.
 ************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Recursive helper: follow all knight moves, fail if out-of-bounds or wrong target
    bool helper(vector<vector<int>> &grid, int row, int col, int target, int n) {

        // if(target == n*n) return true; // check after the last cell

        // Fail fast if out-of-bounds OR cell does not contain expected target
        if(row < 0 || row >= n || col < 0 || col >= n || grid[row][col] != target) return false;

        // Base case: reached last cell successfully
        if(target == (n*n)-1) return true; // checking on the last cell

        // Store each recursive call in a separate variable for clarity
        bool ans1 = helper(grid, row + 2, col + 1, target + 1, n);
        bool ans2 = helper(grid, row + 2, col - 1, target + 1, n);
        bool ans3 = helper(grid, row - 2, col + 1, target + 1, n);
        bool ans4 = helper(grid, row - 2, col - 1, target + 1, n);
        bool ans5 = helper(grid, row + 1, col + 2, target + 1, n);
        bool ans6 = helper(grid, row + 1, col - 2, target + 1, n);
        bool ans7 = helper(grid, row - 1, col + 2, target + 1, n);
        bool ans8 = helper(grid, row - 1, col - 2, target + 1, n);

        // Return true if any move leads to a valid path
        return ans1 || ans2 || ans3 || ans4 || ans5 || ans6 || ans7 || ans8;
    }

    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();

        // First cell must be 0
        if(grid[0][0] != 0) return false;

        // Start recursion from step 0, looking for step 1 next
        return helper(grid, 0, 0, 0, n);
    }
};

/************************************************************
 * Logic Explanation:
 * 1. Start from top-left cell (0,0), which must contain 0.
 * 2. At each recursion step:
 *    - If the current cell is invalid (out-of-bounds or wrong number), fail fast.
 *    - If the target number is the last number (n*n-1), success! Return true.
 *    - Else, try all 8 knight moves recursively, each with target + 1.
 * 3. Return true if any of the recursive calls returns true, else false.
 * 
 * Important Details / Key Insights:
 * - Explicitly storing recursive calls in ans1..ans8 helps debugging.
 * - The order of checks is crucial: first fail-fast, then check base case.
 * - Recursion ensures backtracking: if a path fails, it tries other moves.
 * - This solution is simple and clear, but for large n it is slow.
 * - Optimal solution would check the knight path deterministically (O(n^2)).
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
 * - checkValidGrid calls helper starting from (0,0), target = 0.
 * - helper checks if grid[0][0] == 0 → passes.
 * - Then recursively explores all knight moves, incrementing target.
 * - Each recursive call returns true if a valid path exists from that point.
 * - When target reaches n*n-1, recursion returns true up the stack.
 * - If no moves lead to success, returns false.
 ************************************************************/
