/*

Problem (LeetCode 37 - Sudoku Solver):
- Given a partially filled 9x9 Sudoku board, fill it such that:
  1. Each row contains digits 1-9 without repetition
  2. Each column contains digits 1-9 without repetition
  3. Each 3x3 subgrid contains digits 1-9 without repetition
- Empty cells are denoted by '.'
- Goal: Fill all empty cells to produce a valid Sudoku board

Method / Solution Name: Backtracking + Constraint Checking (issafe)

Time Complexity:
- Worst-case: O(9^m), where m = number of empty cells
- For each empty cell, we try 9 digits
- Each check of issafe takes O(9) row + O(9) column + O(9) grid = O(27) ≈ O(1) per cell

Space Complexity:
- O(1) extra space for board manipulation
- O(m) recursion stack space for m empty cells

Optimality:
- Works fine for standard 9x9 Sudoku
- Not the absolute fastest (could be optimized with row/col/box occupancy arrays)
- Accepted by LeetCode, will **not cause MLE or TLE**

Key Details / Insights:
1. issafe function checks if placing a digit is valid
2. Grid checking uses top-left corner formula: (row/3)*3, (col/3)*3
3. helper function returns bool to indicate whether a valid solution is found
4. Base case: row == 9 → entire board is filled correctly
5. Backtracking: Try digit, recurse, undo if fails
6. Using char '1'-'9' instead of int for board compatibility
7. Recursion moves left-to-right, top-to-bottom

*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    // Function: Check if a digit can be placed at board[row][col]
    bool issafe(vector<vector<char>> &board, int row, int col, char dig){
        int strow = (row / 3) * 3; // Starting row of 3x3 subgrid
        int stcol = (col / 3) * 3; // Starting column of 3x3 subgrid

        // Check the row and column
        for(int i = 0; i < 9; i++){
            if(board[row][i] == dig) return false;  // Same row
            if(board[i][col] == dig) return false;  // Same column
        }

        // Check the 3x3 subgrid
        for(int i = strow; i < strow + 3; i++){
            for(int j = stcol; j < stcol + 3; j++){
                if(board[i][j] == dig) return false;
            }
        }

        return true; // Digit is safe to place
    }

    // Backtracking helper function
    bool helper(vector<vector<char>> &board, int row, int col){
        // Base case: reached past last row → board is solved
        if(row == 9) return true;

        // Determine next cell (move left-to-right, top-to-bottom)
        int nextrow = row, nextcol = col + 1;
        if(nextcol == 9){ // If we reach end of row
            nextrow = row + 1;
            nextcol = 0;
        }

        if(board[row][col] == '.'){ // If cell is empty, try all digits
            for(char dig = '1'; dig <= '9'; dig++){
                if(issafe(board, row, col, dig)){ // Check if placing is valid
                    board[row][col] = dig; // Place digit
                    if(helper(board, nextrow, nextcol)) return true; // Recurse
                    board[row][col] = '.'; // Backtrack if solution fails
                }
            }
            return false; // No valid digit could be placed → backtrack
        }
        else return helper(board, nextrow, nextcol); // Filled cell → move to next

    }

    // Main function called to solve Sudoku
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0); // Start recursion from top-left
    }
};

// --------------------------- WORKING EXAMPLE ---------------------------
int main() {
    Solution sol;

    // Example Sudoku board ('.' denotes empty cells)
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    cout << "Original Sudoku Board:\n";
    for(auto &row : board){
        for(auto &cell : row) cout << cell << " ";
        cout << endl;
    }

    // Solve the board
    sol.solveSudoku(board);

    cout << "\nSolved Sudoku Board:\n";
    for(auto &row : board){
        for(auto &cell : row) cout << cell << " ";
        cout << endl;
    }

    return 0;
}

/*
------------------------- DETAILED LOGIC -------------------------

1. issafe function:
   - Checks if placing 'dig' at board[row][col] violates any Sudoku rules.
   - Row: scan all columns in current row
   - Column: scan all rows in current column
   - 3x3 grid: compute top-left of grid using (row/3)*3, (col/3)*3 and scan all 9 cells
   - Returns true if safe, false if any conflict found.

2. helper function:
   - Returns bool indicating if the board can be solved from current cell onwards.
   - Base case: row == 9 → entire board filled → return true
   - nextrow/nextcol: calculate next cell to process
   - If current cell is empty:
       - Try '1' to '9'
       - If issafe → place digit → recurse
       - If recursion returns false → undo placement (backtracking)
   - If current cell is filled:
       - Simply move to next cell
   - If no digit fits → return false (forces backtracking)

3. Backtracking:
   - Core idea: explore all possibilities
   - Place digit, recurse, undo if dead-end
   - Guarantees that eventually a valid board is found if solvable

4. Why bool return type for helper:
   - Allows early termination when solution found
   - Avoids unnecessary recursion after board is solved

5. Important insights:
   - Using char '1'-'9' aligns with input board
   - Base case is crucial for stopping recursion
   - 3x3 grid checking logic prevents writing 9 separate conditions
   - Backtracking ensures no solution path is permanently blocked

*/
