// ✅ Leetcode Problem (Matrix Search) — [e.g. Leetcode 240: Search a 2D Matrix II]
// 🔍 Question Summary:
// You're given a 2D matrix `matrix` of integers where each row is sorted in ascending order (left to right),
// and each column is also sorted in ascending order (top to bottom).
// Your task is to determine whether a given target integer exists in this matrix.

// ✅ Method Used: Staircase Search (Optimized Approach)

/* NOTE -> This approach will work for Search A 2D Matrix (74) as well
           BUT the time complexity is O(m+n) here
           and the solution we used there has time complexity is O(log(m*n))
           which is better. That's why this method is not recommended for that question
*/
// 🔧 Time Complexity: O(m + n) → where m is number of rows, n is number of columns
// 🔧 Space Complexity: O(1) → constant extra space
// 🧠 Most Optimal? Yes, this is the most optimized approach possible for this kind of matrix.
// ✅ Will it get accepted by LeetCode? Yes, it’s efficient and passes all constraints. No TLE or MLE issues.

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = 0;                           // Start from the first row
        int column = matrix[0].size() - 1;     // Start from the last column (top-right corner)

        // Traverse while staying inside the matrix bounds
        while (row < matrix.size() && column >= 0) {

            int mid = matrix[row][column];     // current element being considered

            // 🎯 If we found the target, return true
            if (mid == target) {
                return true;
            }

            // 🔽 If current element is greater than the target, move left
            else if (mid > target) {
                column--; // We eliminate the current column since all elements below in this column are larger
            }

            // ➡️ If current element is less than the target, move down
            else {
                row++; // We eliminate the current row since all elements to the right in this row are larger
            }
        }

        // ❌ If loop ends, target not found
        return false;
    }
};

/*
=============================
🔍 Explanation and Full Logic:
=============================

💡 Matrix Properties:
---------------------
1. Each **row** is sorted from left to right.
2. Each **column** is sorted from top to bottom.

That means:
- For any cell matrix[i][j]:
  - All values to the **right** are larger → matrix[i][j+1] > matrix[i][j]
  - All values **below** are larger → matrix[i+1][j] > matrix[i][j]

💡 So we pick our starting point very strategically: either **top-right** or **bottom-left**.

Why?
- At **top-right**:
  - If value is **greater** than target → move **left**
  - If value is **less** than target → move **down**

Alternative starting point (also valid):
- We could have started at **bottom-left** (`matrix[matrix.size()-1][0]`)
  - If value > target → move **up**
  - If value < target → move **right**
  - But both give same complexity and traversal logic.

🚶 Traversal Logic (from top-right):
------------------------------------
- Initialize: row = 0, column = last index (matrix[0].size() - 1)
- Loop while row is in bounds and column is in bounds
  - Compare `matrix[row][column]` with target:
    - If equal → return true
    - If greater → go left (column--)
    - If less → go down (row++)

💡 Edge Case Handling:
----------------------
- Even if we reach the **last row**, and start moving left (column--), it’s valid.
- Even if we reach the **first column**, and start moving down (row++), it’s valid.
- The loop will automatically break if:
  - `row == matrix.size()` → we're out of rows
  - `column < 0` → we're out of columns
  So no segmentation fault, and bounds are safe.

📌 Important:
-------------
- This is **not brute-force**. We're not scanning every cell. Instead, at every step:
  - We **eliminate an entire row or column**, hence reducing the search space drastically.

📌 Why Not Binary Search on Each Row?
- That would be `O(m log n)` → good but **not better** than `O(m + n)`
- This method is **faster when both dimensions are large**.

=======================================
🔁 Example Run (Dry Run with Output)
=======================================

Let's test the function with a real example:

Matrix:
[
  [1,  4,  7, 11, 15],
  [2,  5,  8, 12, 19],
  [3,  6,  9, 16, 22],
  [10,13, 14,17, 24],
  [18,21, 23,26, 30]
]

Target = 5

→ Start at matrix[0][4] = 15
→ 15 > 5 → move left → column = 3
→ matrix[0][3] = 11 > 5 → move left → column = 2
→ matrix[0][2] = 7 > 5 → move left → column = 1
→ matrix[0][1] = 4 < 5 → move down → row = 1
→ matrix[1][1] = 5 == target ✅

=======================================
🧪 Demo Code to Test It
=======================================
*/

int main() {
    Solution s;
    vector<vector<int>> matrix = {
        {1,  4,  7, 11, 15},
        {2,  5,  8, 12, 19},
        {3,  6,  9, 16, 22},
        {10,13, 14,17, 24},
        {18,21, 23,26, 30}
    };

    int target = 5;
    cout << (s.searchMatrix(matrix, target) ? "Target Found " : "Target Not Found ❌") << endl;

    return 0;
}

/*
🧾 Output:
Target Found ✅
*/

