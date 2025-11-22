// ✅ Question: LeetCode 74 - Search a 2D Matrix
// --------------------------------------------------
// You're given an `m x n` matrix where each row is sorted in ascending order,
// and the first integer of each row is greater than the last integer of the previous row.
// You are also given an integer `target`.
//
// You must return `true` if `target` exists in the matrix, else return `false`.

// 🔍 Approach: Brute-Force Linear Search
// -----------------------------------------
// 💡 Method: searchMatrix_bruteForce
// 📦 Time Complexity: O(n * m)       -> We check each element one by one.
// 📦 Space Complexity: O(1)          -> No extra space used.
// ⚠️ Optimal?: No, this is NOT the most optimal solution.
// 🟢 Will it be accepted on LeetCode?: YES, this will be accepted.
//     - LeetCode constraints are small enough for this brute-force to pass.
//     - But it's not suitable for large-scale data.
// --------------------------------------------------

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Brute-force solution to search for target in 2D matrix
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        // Step 1: Iterate through each row of the matrix
        for (int row = 0; row < matrix.size(); row++) {

            // Step 2: Iterate through each element of the current row
            for (int col = 0; col < matrix[row].size(); col++) {

                // Step 3: Compare current element with target
                if (matrix[row][col] == target) {
                    return true;  // Found the target, return true immediately
                }
            }
        }

        // Step 4: If loop completes without finding the target, return false
        return false;
    }
};

// 🧠 Full Logic Explanation (In Human Language):
// ---------------------------------------------
// 1. The matrix is a 2D vector, meaning we have multiple rows and columns.
// 2. Since it's sorted row-wise and the first element of each row is > last of the previous row,
//    the whole matrix behaves like a sorted 1D array flattened in a structured way.
// 3. However, in brute force, we ignore all that optimization and **simply check every element**.
// 4. We use two nested loops:
//    - Outer loop goes over each row.
//    - Inner loop goes over each column in the current row.
// 5. For each cell (i, j), we check if it matches the `target`.
//    - If it does, we return true.
//    - If after all elements no match is found, we return false.
//
// ✅ This approach always works but is inefficient for large inputs.

// 🔍 Example Input and Output Check:
int main() {
    Solution sol;

    // Sample matrix
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    // Example target
    int target1 = 3;
    int target2 = 13;

    // Call function and print result
    cout << "Searching for 3: " << (sol.searchMatrix(matrix, target1) ? "Found" : "Not Found") << endl;
    cout << "Searching for 13: " << (sol.searchMatrix(matrix, target2) ? "Found" : "Not Found") << endl;

    return 0;
}

/*
🧪 Sample Output:
---------------------
Searching for 3: Found
Searching for 13: Not Found

📝 Notes:
- Even though brute-force is not the best way to solve this, it's a **good baseline**.
- It guarantees correctness and helps understand the problem structure.
- But always aim to improve to `O(log(n*m))` using binary search for production-level use.
*/
