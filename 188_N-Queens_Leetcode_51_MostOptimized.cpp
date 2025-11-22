#include <bits/stdc++.h>
using namespace std;

/*
============================
    LEETCODE 51 - N Queens
============================

📌 PROBLEM (in short):
------------------------
- Place N queens on an N×N chessboard such that:
  1. No two queens attack each other.
  2. Queens attack in:
     → Same column
     → Same row
     → Both diagonals
- Return all distinct board configurations where this is possible.

--------------------------------
💡 OBSERVATIONS:
--------------------------------
1. At most 1 queen per row → so we only place one queen in each row.
2. This changes problem from "fill the whole board" → to "for each row, try columns".
   (Hence, we only iterate columns inside each row).
3. Backtracking is natural because:
   - We make a choice → place queen
   - Recurse to next row
   - If it fails, undo (backtrack) → try next column.

--------------------------------
🚩 Our Approach (Backtracking)
--------------------------------
- Use recursion to place queens row by row.
- For each row, try all columns [0..n-1].
- Before placing at (row, col), check safety with `isSafe`.
- If safe → place 'Q', recurse.
- If not safe → skip column.
- Once all rows filled → push board as a solution.

--------------------------------
KEY POINT: Why not check full row or below rows?
- Row check unnecessary → we place only 1 queen per row.
- Below rows unnecessary → they’re empty during construction (we haven’t reached them yet).
- Only need: same column above + two diagonals above.

--------------------------------
TIME COMPLEXITY:
- Worst case O(N!) (same as permutations), since each queen reduces available choices.
- Safety check costs O(N) per attempt.
- Overall: O(N! * N) (acceptable for N ≤ 9 on LeetCode).

SPACE COMPLEXITY:
- O(N^2) for board + O(N) recursion depth.
- Manageable and accepted.

✅ This solution is optimal for standard backtracking.
✅ It will be accepted by LeetCode (no MLE/TLE).

*/


class Solution {
public:

    // =========================
    // SAFETY CHECK FUNCTION
    // =========================
    bool isSafe(vector<string> &board, int row, int column, int sizeOfBoard) {
        // 1. Check column (above rows only)
        for (int i = 0; i < row; i++) {
            if (board[i][column] == 'Q') return false;
        }

        // 2. Check left diagonal (↖)
        for (int i = row, j = column; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // 3. Check right diagonal (↗)
        for (int i = row, j = column; i >= 0 && j < sizeOfBoard; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        return true;
    }

    // =========================
    // BACKTRACK FUNCTION
    // =========================
    void nQueens(vector<string> &board,
                 vector<vector<string>> &ans,
                 int row, int sizeOfBoard) {

        // Base Case: All rows filled → valid solution found
        if (row == sizeOfBoard) {
            ans.push_back(board);
            return;
        }

        // Try placing queen in every column of current row
        for (int j = 0; j < sizeOfBoard; j++) {
            if (isSafe(board, row, j, sizeOfBoard)) {
                // Place queen
                board[row][j] = 'Q';

                // Recurse for next row
                nQueens(board, ans, row + 1, sizeOfBoard);

                // Backtrack (remove queen, restore '.')
                board[row][j] = '.';
            }
        }
    }

    // =========================
    // DRIVER FUNCTION
    // =========================
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.')); // initialize board
        vector<vector<string>> ans;
        nQueens(board, ans, 0, n);
        return ans;
    }
};


/*
=============================================
🔎 HOW isSafe() WORKS
=============================================
Suppose we want to place a queen at (row, col).

1. Vertical Check:
   - Look at all rows ABOVE this row in the same column.
   - If any queen found, placement invalid.

2. Left Diagonal Check (↖):
   - Move upwards-left (row--, col--).
   - If any queen found, placement invalid.

3. Right Diagonal Check (↗):
   - Move upwards-right (row--, col++).
   - If any queen found, placement invalid.

⚠ Why not check:
- Same row? → We never place >1 queen per row.
- Below rows? → They are empty; recursion hasn't placed queens there yet.

*/


/*
=============================================
⚡ DRY RUN (N=4 Example)
=============================================
Row 0 → try col 0..3
- Place at (0,0) → recurse row 1
Row 1 → try col 0..3
- col0 blocked (same column)
- col1 blocked (↖ diagonal)
- col2 safe → place (1,2)
...
Eventually either find solution or backtrack (undo queen, try next column).

Backtracking tree explores ALL valid placements.

=============================================
*/


// =========================
// MAIN FUNCTION (example)
// =========================
int main() {
    Solution sol;
    int n = 4;
    vector<vector<string>> solutions = sol.solveNQueens(n);

    cout << "Total solutions for N=" << n << " → " << solutions.size() << "\n";
    for (auto &board : solutions) {
        for (auto &row : board) {
            cout << row << "\n";
        }
        cout << "-----------------\n";
    }

    return 0;
}

/*
=============================================
KEY TAKEAWAYS:
=============================================
✔️ Backtracking = try → recurse → undo.
✔️ isSafe checks only columns & diagonals above current row.
✔️ We reduced problem complexity by row-wise queen placement.
✔️ Base case is when row == n (all queens placed).
✔️ This is the classic backtracking template.
=============================================
*/

