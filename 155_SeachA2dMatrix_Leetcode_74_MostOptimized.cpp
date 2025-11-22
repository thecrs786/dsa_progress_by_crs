// ✅ QUESTION: Search a 2D Matrix (LeetCode)
// You're given a 2D matrix with the following properties:
// 1. Integers in each row are sorted from left to right.
// 2. The first integer of each row is greater than the last integer of the previous row.
//
// TASK: Given a `matrix` of integers and an integer `target`, return true if the target is found in the matrix, otherwise false.

// ✅ SOLUTION METHOD NAME: Binary Search on Flattened Matrix
// ✅ TIME COMPLEXITY: O(log(m * n)), where m = number of rows, n = number of columns
// ✅ SPACE COMPLEXITY: O(1) — constant extra space
// ✅ OPTIMALITY: This is the MOST OPTIMAL solution possible for this problem.
// ✅ LEETCODE STATUS: ✅ 100% ACCEPTED — No TLE or MLE risk, fully optimized.

// ✅ BOILERPLATE + FUNCTION:

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();                     // Get number of rows in the matrix
        int cols = matrix[0].size();                  // Get number of columns in the matrix

        int low = 0;                                  // Flattened start index (0th element)
        int high = rows * cols - 1;                   // Flattened end index (last element)

        while (low <= high) {
            int mid = low + (high - low) / 2;         // To prevent overflow, use this formula instead of (low+high)/2
            int row = mid / cols;                     // Convert 1D index to 2D row index
            int col = mid % cols;                     // Convert 1D index to 2D col index

            int midElement = matrix[row][col];        // Access the actual matrix element using the converted row and col

            if (midElement == target) return true;    // If we found the target, return true
            else if (midElement < target) low = mid + 1;  // If current element is less, discard left half
            else high = mid - 1;                          // If current element is more, discard right half
        }

        return false;  // If while loop ends, target doesn't exist in the matrix
    }
};

// ✅ FULL EXPLANATION (LIKE A BRUTAL COACH WOULD TEACH YOU):

/*
🔎 LOGIC IN DEPTH:

You're given a matrix that is SORTED in a very specific way:
- Each row is sorted from left to right.
- The first element of a row is always greater than the last element of the previous row.

That means the ENTIRE matrix can be **imagined** as a 1D sorted array of size (m * n), where:
    index 0        = matrix[0][0]
    index 1        = matrix[0][1]
    ...
    index (n-1)    = matrix[0][n-1]
    index (n)      = matrix[1][0]
    ...
    index (m*n-1)  = matrix[m-1][n-1]

So we use **Binary Search** like we do in a sorted array, BUT we convert the 1D mid index into 2D coordinates using:
    - `row = mid / cols` (integer division)
    - `col = mid % cols` (remainder)

Why does this work?
- Because each "virtual index" in the range [0 ... m*n - 1] maps exactly to a unique (row, col) in the matrix.

⬇️ WHY WE TOOK EACH STEP:
- `int rows = matrix.size();` → Get number of rows.
- `int cols = matrix[0].size();` → Get number of columns.
- `int low = 0, high = rows * cols - 1;` → We are binary searching in the 1D space of matrix.
- `int mid = low + (high - low) / 2;` → Safer mid calculation.
- `int row = mid / cols, col = mid % cols;` → Convert the mid index to 2D.
- `matrix[row][col] == target` → Found the target.
- If not found, we discard half of the search space just like in regular binary search.

🔥 No nested loops, no row-based scanning — **pure binary search on a virtually flattened 2D array**.

This is the **most efficient way** to solve this problem under given constraints.

*/

// ✅ EXAMPLE TEST CASE (FOR DEBUGGING, ANALYSIS & VISUAL UNDERSTANDING)



int main() {
    Solution sol;
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    int target = 3;

    if(sol.searchMatrix(matrix, target)) {
        cout << "Target " << target << " found in the matrix " << endl;
    } else {
        cout << "Target " << target << " not found in the matrix " << endl;
    }

    return 0;
}

/*
🧠 HOW THIS WORKS FOR ABOVE INPUT:

- Matrix:
    1   3   5   7
    10 11 16  20
    23 30 34  60

- Flattened version:
    Index 0 → 1
    Index 1 → 3   ← Target is here
    Index 2 → 5
    ...
    Index 11 → 60

- Binary Search Steps:
    low = 0, high = 11 → mid = 5 → matrix[1][1] = 11 → too big → high = 4
    low = 0, high = 4 → mid = 2 → matrix[0][2] = 5 → too big → high = 1
    low = 0, high = 1 → mid = 0 → matrix[0][0] = 1 → too small → low = 1
    low = 1, high = 1 → mid = 1 → matrix[0][1] = 3 → FOUND ✅

- Final Answer: true

*/

// 🔚 END OF BRUTAL, COMPLETE NOTES
