/*
LeetCode 36 — VALID SUDOKU (Notes + Working Example)

Problem (in brief):
Given a 9x9 Sudoku board (vector<vector<char>>) containing digits '1'..'9' and '.' for empty cells,
return true if the current board configuration is valid. "Valid" means:
  - Each row contains no duplicate digits (excluding '.')
  - Each column contains no duplicate digits
  - Each of the nine 3x3 sub-boxes contains no duplicate digits

Important: This problem only asks whether the *current* configuration is valid. It does NOT require
solving the Sudoku or determining if the board can be completed to a full solution.

---
Solution provided (the exact code below is the same as you gave):
- A recursive scan (helper) that visits every cell left-to-right, top-to-bottom.
- For every filled cell (not '.'), call issafe(board, row, col, board[row][col]) which verifies
  the cell doesn't conflict with any other filled cell in its row, column, or 3x3 box.
- If all filled cells are "safe", the helper reaches row==9 and returns true.

Name / Method: "Recursive validation" (a recursive grid traversal that uses local checks per cell).

Time complexity (detailed):
- Board is fixed 9x9. For general NxN board with sqrt(N) boxes per side (i.e., board size = N = n^2),
  issafe checks O(n) + O(n) + O(n) = O(n) per cell; there are N cells → O(N * n) = O(n^3).
- For classical 9x9 Sudoku this is constant-time in practice. Using N=9, each issafe does ~27 compares.
- In Big-O with board size as variable: O(N * sqrt(N)) or O(n^3) where n = 3 for 9x9. But practically O(1).

Space complexity:
- O(1) additional space (only recursion stack of depth up to 9, so O(n) stack in general). No heavy data
  structures are allocated.

Is this the most optimal solution for problem 36?
- Not strictly the fastest micro-optimized variant. A typical optimal approach for 36 uses three arrays
  (or bitmasks) to track seen digits per row/column/box in a single pass — that yields a clean one-pass
  O(1)-space check (still constant for 9x9). However, this recursive traversal with per-cell checks is
  fully acceptable, simple to reason about, and will be accepted on LeetCode. It will not cause TLE or MLE.

Will it be accepted by LeetCode (TLE / MLE concerns)?
- Yes. The algorithm performs a bounded number of operations (9x9 cells × ~27 checks) and uses trivial
  memory. It will not TLE or MLE.

---
Below is the exact solution code (unchanged), followed by:
 - detailed line-by-line comments explaining why each step exists,
 - an explanation of the issafe logic,
 - an explanation of the helper traversal and return types,
 - key sights and pitfalls,
 - and a small working main() with an example valid board and an invalid board.

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool issafe(vector<vector<char>> &board, int row, int col, char k) {
        int strow = (row / 3) * 3;
        int stcol = (col / 3) * 3;

        for (int i = 0; i < 9; i++) {
            if (i != row && board[i][col] == k) return false;   // check column (exclude current cell)
            if (i != col && board[row][i] == k) return false;   // check row (exclude current cell)
        }

        for (int i = strow; i < strow + 3; i++) {
            for (int j = stcol; j < stcol + 3; j++) {
                if ((i != row || j != col) && board[i][j] == k) return false; // check 3x3 box (exclude cell)
            }
        }
        return true;
    }

    bool helper(vector<vector<char>> &board, int row, int col) {
        if (row == 9) return true; // scanned all rows (0..8). If we reach row 9, everything checked.

        int nextrow = row, nextcol = col + 1;
        if (col == 8) {
            nextrow = row + 1;
            nextcol = 0;
        }

        if (board[row][col] == '.') {
            // empty cell: nothing to validate here; just continue to next cell
            return helper(board, nextrow, nextcol);
        } else {
           // filled cell: check whether this placement conflicts with other existing cells
           if( issafe(board, row, col, board[row][col])){
                  return helper(board, nextrow, nextcol);
           }
           else return false; // conflict detected — board is invalid
        }
    }

    bool isValidSudoku(vector<vector<char>> &board) {
        return helper(board, 0, 0);
    }
};

/*
Detailed explanation & reasoning (comments expanded):

1) issafe(board, row, col, k)
   - Purpose: Given a filled cell at (row, col) with character k ('1'..'9'), ensure no other cell
     in the same row, same column, or same 3x3 sub-box contains the same character k.
   - Why exclude the current cell itself? Because the board contains the character at (row,col) already;
     when scanning the row/col/box we must not treat the current cell as a duplicate of itself.
   - Implementation details:
     a) Compute the top-left corner of the 3x3 sub-box using integer division: (row/3)*3, (col/3)*3.
     b) Scan indices i = 0..8 and:
        - If any board[i][col] == k and i != row → duplicate in column → return false.
        - If any board[row][i] == k and i != col → duplicate in row → return false.
     c) Scan the 3x3 box (strow..strow+2, stcol..stcol+2) and if any other position equals k → false.
     d) If none matched, return true.

   - Complexity: constant bounded by the board size (9 checks for row, 9 for column, 9 for box).

2) helper(board, row, col)
   - Purpose: Visit every cell (row-major order). For each filled cell (non '.'), call issafe to verify
     there is no conflict. For empty cells, just skip them. If any cell reports a conflict, immediately
     return false. If the scan finishes (row==9), return true.
   - Why recursion? The code uses recursion simply to traverse cells and early-return on invalidity.
     This recursive structure is equivalent to a nested loop over rows and columns, but written recursively.
   - Row/column progression:
     - nextcol = (col+1) % 9 and nextrow increments when col==8. The code computes nextrow/nextcol
       so the recursive call always moves forward to the next cell.
   - Return semantics:
     - If any validation fails, return false. If we processed every cell without conflict, return true.

3) isValidSudoku(board)
   - Just kicks off the helper from (0,0).

Why this is correct for LeetCode 36 (and common pitfalls):
- Correctness: every filled cell is validated with respect to others. Because we exclude the cell itself
  during checks, we won't spuriously detect self-collisions.
- Pitfall: Don't try to "solve" the Sudoku here. Problem 36 requires only validation of current digits.
  If your code attempted to fill empty cells and see if some completion exists, that would be solving
  (LeetCode 37). Those are different problems.
- Another pitfall: forgetting to exclude the current cell while checking will always produce false negatives.
- Another pitfall: incorrect calculation of 3x3 sub-box start indices — always use (row/3)*3.

Key sights / takeaways (10/10 tips):
- For 9x9 Sudoku, bitmask or three boolean arrays for rows/cols/boxes is the most concise and efficient
  single-pass approach. But the recursive scan + issafe approach remains straightforward and readable.
- Always think whether the problem asks for current-state validation (36) or solving/completion (37).
- When checking a cell against its peers, be careful to exclude the cell itself.
- Use clear indices for 3x3 boxes: box_row = (row/3), top_row = box_row*3.
- For debugging, print board with coordinates; many errors come from off-by-one in next-cell logic.

Working example (main): constructs two boards — one valid and one invalid — and prints results.

*/

int main() {
    Solution sol;

    // Example 1: a standard valid Sudoku configuration snippet (from LeetCode examples)
    vector<string> rows_valid = {
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };

    vector<vector<char>> board_valid(9, vector<char>(9));
    for (int r = 0; r < 9; ++r) for (int c = 0; c < 9; ++c) board_valid[r][c] = rows_valid[r][c];

    bool res_valid = sol.isValidSudoku(board_valid);
    cout << "Valid board check -> " << (res_valid ? "true" : "false") << "\n"; // expected: true

    // Example 2: invalid board (duplicate '8' in first column)
    vector<string> rows_invalid = rows_valid;
    // Introduce a conflicting '8' in the first column (row 0, col 0 already '5', set row 2 col 0 to '5' too)
    rows_invalid[0] = "53..7...."; // unchanged
    rows_invalid[1] = "6..195..."; // unchanged
    // Put '5' at (2,0) instead of '.' causes duplicate '5' in column 0
    rows_invalid[2] = "598....6."; // changed '.' -> '5' at col 0 creating conflict with (0,0) being '5'

    vector<vector<char>> board_invalid(9, vector<char>(9));
    for (int r = 0; r < 9; ++r) for (int c = 0; c < 9; ++c) board_invalid[r][c] = rows_invalid[r][c];

    bool res_invalid = sol.isValidSudoku(board_invalid);
    cout << "Invalid board check -> " << (res_invalid ? "true" : "false") << "\n"; // expected: false

    return 0;
}
