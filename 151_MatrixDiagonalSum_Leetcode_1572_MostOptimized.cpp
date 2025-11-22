
/*
✅ QUESTION: 1572 Matrix Diagonal Sum

🎯 GOAL:
- Given an NxN square matrix, calculate the sum of both diagonals.
- If the matrix has odd dimensions, the center element belongs to both diagonals and
  must only be counted once.

⏱️ TIME COMPLEXITY: O(N)
💾 SPACE COMPLEXITY: O(1)
- Only one loop and a few int variables used.

🔍 OPTIMALITY:
- This is the most optimal approach possible for this problem.
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = mat.size();      // Size of the square matrix
        int totalSum = 0;        // Sum of both diagonals

        for (int i = 0; i < n; i++) {
            totalSum += mat[i][i];           // Primary diagonal
            totalSum += mat[i][n - 1 - i];   // Secondary diagonal
        }

        // If n is odd, subtract the center element once (it was counted twice)
        if (n % 2 == 1) {
            totalSum -= mat[n/2][n/2];
        }

        return totalSum;
    }
};

int main() {
    Solution sol;

    // Example 1: 3x3 matrix (odd size)
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Diagonal Sum of mat1 = " << sol.diagonalSum(mat1) << endl;
    // Step-by-step logic:
    // Primary diagonal: 1 + 5 + 9 = 15
    // Secondary diagonal: 3 + 5 + 7 = 15
    // Center element 5 counted twice → subtract once
    // Total sum = 15 + 15 - 5 = 25

    // Example 2: 4x4 matrix (even size)
    vector<vector<int>> mat2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10,11,12},
        {13,14,15,16}
    };
    cout << "Diagonal Sum of mat2 = " << sol.diagonalSum(mat2) << endl;
    // Step-by-step logic:
    // Primary diagonal: 1 + 6 + 11 + 16 = 34
    // Secondary diagonal: 4 + 7 + 10 + 13 = 34
    // Even-sized matrix → no center overlap
    // Total sum = 34 + 34 = 68

    return 0;
}

/*
=========================
LOGIC EXPLANATION (BRUTAL)
=========================
1. Loop from i = 0 to n-1
   - Primary diagonal element: mat[i][i]
   - Secondary diagonal element: mat[i][n-1-i]
2. Add both to totalSum in the same loop (O(N) time)
3. If n is odd, the center element mat[n/2][n/2] was counted twice, so subtract once
4. Return totalSum
5. Works for any NxN matrix, odd or even
6. Space Complexity: O(1) extra (only totalSum and n used)
7. Time Complexity: O(N) (single loop)
*/
