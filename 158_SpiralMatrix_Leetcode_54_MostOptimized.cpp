// ✅ PROBLEM: Leetcode 54 - Spiral Matrix
// Given a 2D matrix, return all elements of the matrix in spiral order.

// ✅ SOLUTION NAME: Layer-by-Layer Spiral Traversal
// ✅ TIME COMPLEXITY: O(m * n) where m = number of rows, n = number of columns
// ✅ SPACE COMPLEXITY: O(1) extra (excluding output vector)
// ✅ OPTIMALITY: Yes. This is the most optimal approach — linear traversal
// ✅ STATUS: ✅ Accepted by LeetCode. No TLE. No MLE. Handles all edge cases
// ✅ EDGE CASE SAFETY: All edge cases like single row, single column, odd rows, odd columns, 1x1 matrix, etc. are handled explicitly

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;

        // Step 1: Define the four boundaries
        int srow = 0;                     // starting row
        int scol = 0;                     // starting column
        int erow = matrix.size() - 1;     // ending row
        int ecol = matrix[0].size() - 1;  // ending column

        // Step 2: Spiral traversal until boundaries meet
        while (srow <= erow && scol <= ecol) {
            // → Traverse top row from left to right
            for (int j = scol; j <= ecol; j++) {
                ans.push_back(matrix[srow][j]);
            }
            // ✅ Top row is always present, so no special check needed here
            // After top row, move srow down
            srow++;

            // ↓ Traverse right column from top to bottom
            for (int i = srow; i <= erow; i++) {
                ans.push_back(matrix[i][ecol]);
            }
            // ✅ Right column is always valid after top row, no need to check here
            // After right col, move ecol left
            ecol--;

            // ← Traverse bottom row from right to left (only if multiple rows exist)
            if (srow <= erow) {
                for (int j = ecol; j >= scol; j--) {
                    ans.push_back(matrix[erow][j]);
                }
                // ✅ Checked: only process bottom row if it wasn’t already done in top row
                erow--;
            }

            // ↑ Traverse left column from bottom to top (only if multiple columns exist)
            if (scol <= ecol) {
                for (int i = erow; i >= srow; i--) {
                    ans.push_back(matrix[i][scol]);
                }
                // ✅ Checked: only process left column if it wasn’t already done in right col
                scol++;
            }
        }

        return ans;
    }
};

/*
🧠 FULL LOGIC EXPLANATION (BOOK STYLE):

We simulate the spiral traversal by maintaining 4 boundaries:
    - `srow` (starting row), `erow` (ending row)
    - `scol` (starting column), `ecol` (ending column)

The idea is to move in **four directions** in a loop:
    1. **Left to Right** across the top row
    2. **Top to Bottom** along the right column
    3. **Right to Left** across the bottom row
    4. **Bottom to Top** along the left column

After each full cycle, we **shrink the boundaries inward**:
    - Increment `srow` (since top row is traversed)
    - Decrement `ecol` (rightmost column done)
    - Decrement `erow` (bottom row done)
    - Increment `scol` (leftmost column done)

📌 Why do we check `if (srow <= erow)` and `if (scol <= ecol)` before bottom and left?
    Because in **odd dimension matrices**, when we reach the last layer, either:
    - Only **1 row** remains → We must skip bottom row and left column
    - Only **1 column** remains → We must skip bottom row and left column
    - If not checked, we will re-traverse already visited cells → duplicates

🚨 Without these checks, the loop would still run and revisit the same row/column,
resulting in extra or duplicated values in the output.

Examples of wrong behavior if we skip checks:
    - In a matrix like: [[1,2,3],[4,5,6],[7,8,9]], the middle element `5` would be added multiple times.

---
🧪 EDGE CASES & HOW WE HANDLED THEM:

✅ 1x1 matrix:
    [[1]] → Single element → Only top row is run, works fine.
    
✅ Single row matrix:
    [[1,2,3]] → Only top row, right column is skipped, no issue since `srow > erow` after one loop.

✅ Single column matrix:
    [[1],[2],[3]] → Top row + right column works, bottom and left are skipped safely by boundary checks.

✅ Odd number of rows/columns:
    e.g. 3x3 matrix → Middle element will be handled only once as top row shrinks inward correctly.

✅ Even number of rows/columns:
    e.g. 4x4 → All loops go evenly, works fine.

✅ Rectangular matrix (more rows than columns or vice versa):
    e.g. 3x4 or 4x2 — no issue. Boundaries adjust properly, checks stop re-processing.

⛔ What can go wrong:
    - ❌ If boundary checks are missing before bottom/left traversal → duplicates
    - ❌ If the loop doesn't check `srow <= erow` and `scol <= ecol` → index out of bounds
---

🔁 WORKING EXAMPLE TO TEST AND VISUALIZE OUTPUT:
*/


int main() {
    Solution obj;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> res = obj.spiralOrder(matrix);
    
    cout << "Spiral Traversal: ";
    for (int val : res) {
        cout << val << " ";
    }
    return 0;
}
/*
Expected Output:
Spiral Traversal: 1 2 3 6 9 8 7 4 5

---

🔥 FINAL NOTES:
- You can think of the matrix as layered "onion rings", and we peel one layer at a time.
- We protect each layer by bounding it using the 4 variables: srow, erow, scol, ecol.
- Every check and update exists **for a reason** — especially the `if`s around bottom and left traversal.
- This is a textbook example of "simulate traversal by shrinking boundaries".

*/

