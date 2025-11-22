// 🔍 QUESTION:
// Perform a linear search in a 2D array to find a target element.
// If found, return its coordinates (row and column), else return (-1, -1).

// ⚠️ WARNING:
// This implementation assumes the number of columns in the 2D array is 3.
// This is REQUIRED because in C++, when passing a 2D array to a function,
// all dimensions except the first (i.e., the number of rows) must be known at compile time.
// So, 'int matrix[][3]' is valid, but 'int matrix[][]' is NOT ALLOWED.
// If you want dynamic column sizes, you'd have to use pointers or STL containers (like vector<vector<int>>).

#include <iostream>
using namespace std;

// 🔧 METHOD: Brute-force Linear Search
// ⏱️ Time Complexity: O(n * m) where n = rows and m = columns (3 in this case)
// 🧠 Space Complexity: O(1) – no extra space used
// ✅ This is the most basic and correct solution. Accepted on LeetCode for small to medium constraints.
// ❌ Will NOT cause TLE or MLE unless array size is extremely large (which is rare in basic problems)

// 📦 FUNCTION BOILERPLATE
pair<int, int> linearSearch2D(int matrix[][3], int rows, int target) {
    // Step 1: Traverse the matrix row by row
    for(int i = 0; i < rows; i++) {
        // Step 2: Traverse each column in current row
        for(int j = 0; j < 3; j++) {
            // Step 3: Compare each element with the target
            if(matrix[i][j] == target) {
                // Step 4: If found, return its position as a pair
                return {i, j};
            }
        }
    }
    // Step 5: If not found, return (-1, -1) as an invalid indicator
    return {-1, -1};
}

/*
🧠 LOGIC EXPLAINED:

We perform a brute-force linear search by visiting each element of the 2D array.
Since the matrix is statically sized with 3 columns, we can safely hardcode the second dimension in the function.

- Start from the top-left corner.
- Move left-to-right across columns, top-to-bottom across rows.
- Compare each cell to the target.
- If match is found, return its (row, column).
- If the entire matrix is traversed with no match, return (-1, -1).

No need for extra space or complex conditions. It's readable and works within acceptable time for small to medium sizes.
*/

// 🧪 EXAMPLE DRIVER CODE
int main() {
    int matrix[3][3] = {
        {1, 5, 9},
        {14, 20, 25},
        {30, 34, 43}
    };

    int target = 20;

    pair<int, int> result = linearSearch2D(matrix, 3, target);

    if(result.first != -1) {
        cout << "Target " << target << " found at position: (" << result.first << ", " << result.second << ")\n";
    } else {
        cout << "Target " << target << " not found in the matrix.\n";
    }

    return 0;
}
