// --------------------------------------------------------------------------------------
// ✅ PROBLEM: Find the Missing and Repeated Numbers in a Grid (LeetCode style)
//
// You are given an n x n matrix called `grid` that contains all integers from 1 to n^2,
// except that one number is missing and one number is duplicated in its place.
//
// 🔍 GOAL:
// Return a vector of two integers:
// - First: the number that is repeated (appears twice)
// - Second: the number that is missing (doesn't appear at all)
//
// 🧠 KEY INSIGHT:
// Since we know the range is [1, n^2], the sum of all elements from 1 to n^2 should be:
//     expectedSum = n^2 * (n^2 + 1) / 2
// But due to one number being repeated and one missing:
//     actualSum = expectedSum - missing + repeated
// Thus,
//     missing = expectedSum - actualSum + repeated
//
// 🧮 METHOD NAME: Set + Math + Actual Sum Comparison
//
// 📊 TIME COMPLEXITY: O(n^2)  – We traverse all elements of the matrix once
// 🧠 SPACE COMPLEXITY: O(n^2) – In the worst case, we may insert n^2 distinct values into the set
//
// ✅ STATUS: Accepted by LeetCode for matrix size up to 250x250 (Max n^2 = 62500)
// ❌ WON’T cause TLE or MLE unless extreme constraints beyond n = 10^3 are introduced
//
// 💡 IS IT OPTIMAL?
// Yes, it’s a simple and effective approach, though further optimization is possible
// using XOR technique for constant space.
//
// --------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size(); // n x n matrix → total numbers = n^2
        unordered_set<int> m; // used to track seen numbers
        vector<int> ans; // result array
        int repeating, missing; // to store results
        int actualSum = 0; // sum of all elements in the matrix

        // Step 1: Traverse the entire matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = grid[i][j];

                // Step 2: Check for repetition using the set
                if (m.find(val) != m.end()) {
                    // If already exists, it's the repeating number
                    repeating = val;
                } else {
                    // Otherwise, insert into the set
                    m.insert(val);
                }

                // Step 3: Keep track of the total sum
                actualSum += val;
            }
        }

        // Step 4: Calculate the expected sum of all values from 1 to n^2
        int expectedSum = (n * n) * ((n * n) + 1) / 2;

        // Step 5: Derive the missing number using the formula
        missing = expectedSum - actualSum + repeating;

        // Step 6: Return result in [repeating, missing] format
        ans.push_back(repeating);
        ans.push_back(missing);
        return ans;
    }
};

// --------------------------------------------------------------------------------------
// 📌 FULL FUNCTION LOGIC AND EXPLANATION:
//
// Let’s say n = 3 → Matrix of 3x3 = 9 elements → valid values: [1, 2, 3, 4, 5, 6, 7, 8, 9]
// If number 7 is missing and number 2 is repeated instead, the matrix may contain:
//     1 2 3
//     4 2 6
//     5 8 9
//
// Actual sum = sum of all elements in matrix = 1+2+3+4+2+6+5+8+9 = 40
// Expected sum = 1+2+3+...+9 = 9×10/2 = 45
// Missing = expectedSum - actualSum + repeating = 45 - 40 + 2 = 7
//
// ➤ Step-by-step Execution:
//   - Use a set to keep track of elements we’ve already seen
//   - While traversing the matrix, if an element is already in the set, mark it as `repeating`
//   - At the same time, keep adding to `actualSum`
//   - At the end, calculate `expectedSum` using formula for first N natural numbers
//   - Find the missing number with:
//         missing = expectedSum - actualSum + repeating
//   - Return the pair [repeating, missing]
//
// 🔁 Edge Cases Handled:
//   - Works if the missing number is smallest (1) or largest (n^2)
//   - Repeating number can appear anywhere in the matrix
//   - Assumes exactly one missing and one repeated number
//
// --------------------------------------------------------------------------------------
// 🧪 WORKING EXAMPLE:

int main() {
    // Sample 3x3 matrix with repeated value 2 and missing value 7
    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 2, 6},
        {5, 8, 9}
    };

    Solution obj;
    vector<int> result = obj.findMissingAndRepeatedValues(grid);

    cout << "Repeated number: " << result[0] << endl;
    cout << "Missing number: " << result[1] << endl;

    // OUTPUT:
    // Repeated number: 2
    // Missing number: 7

    return 0;
}
