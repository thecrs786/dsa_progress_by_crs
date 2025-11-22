/*
    🔶 QUESTION: Maximum Row Sum in a 2D Array

    🧾 BRIEF:
    Given a 2D matrix of integers with fixed number of columns (say 3 for this example),
    find the row which has the maximum sum of its elements. Return both:
    → the index of that row
    → the sum of that row

    ⚠️ WARNING:
    Column size must be known at compile time when passing a 2D array like int arr[][3].
    This is a rule in C++ for static 2D arrays. Why?
    → Because the compiler needs to calculate the memory offset for `arr[i][j]` using:
       address = base + ((i * column_size) + j) * size_of_element
    If column size is unknown, it can’t compute this offset during compilation.

    🧠 METHOD NAME: Brute Force Row-Wise Traversal

    🕒 TIME COMPLEXITY: O(rows × columns)
    🧠 SPACE COMPLEXITY: O(1) → we only use constant extra variables

    ✅ MOST OPTIMAL: Yes, for static 2D arrays and row-sum problem.

*/

// 🔻 BOILERPLATE + SOLUTION FUNCTION
#include <iostream>
#include <climits>
using namespace std;

// FUNCTION: Finds row with maximum sum and returns pair (index, sum)
pair<int, int> maxRowSum(int arr[][3], int rows) {
    // maxSum → stores the maximum row sum found so far
    // rowIndex → stores the index of the row with maxSum
    int maxSum = INT_MIN;
    int rowIndex = -1;

    // Loop through each row
    for(int i = 0; i < rows; i++) {
        int rowSum = 0; // reset rowSum for each row

        // Calculate sum of current row
        for(int j = 0; j < 3; j++) {
            rowSum += arr[i][j];
        }

        // If this row's sum is greater than maxSum, update it
        if(rowSum > maxSum) {
            maxSum = rowSum;
            rowIndex = i;
        }
    }

    // Return both row index and max sum as a pair
    return {rowIndex, maxSum};
}

/*
    🔍 FUNCTION LOGIC EXPLAINED:

    Step 1: Initialize maxSum to INT_MIN so that even if all elements are negative,
            we still find the correct maximum sum.
    
    Step 2: Iterate through each row using outer loop `i`.
            For each row, initialize a variable `rowSum = 0`.

    Step 3: Use an inner loop `j` to go through each element in that row
            and add the values to `rowSum`.

    Step 4: After the inner loop finishes for that row, compare `rowSum` with `maxSum`.
            If `rowSum` is greater, update both `maxSum` and `rowIndex`.

    Step 5: After finishing all rows, return `{rowIndex, maxSum}`.

    This returns the row with the maximum sum and the value of that sum.
*/

/*
    🔁 HOW FUNCTION WORKS: Example Dry Run
    arr = {
        {1, 2, 3},      // sum = 6
        {4, 5, 6},      // sum = 15  <-- max
        {7, 8, 9}       // sum = 24  <-- final max
    }

    → Starts with INT_MIN, rowIndex = -1
    → Row 0: sum = 6 → maxSum updated → maxSum = 6, rowIndex = 0
    → Row 1: sum = 15 → maxSum updated → maxSum = 15, rowIndex = 1
    → Row 2: sum = 24 → maxSum updated → maxSum = 24, rowIndex = 2
    → Return → {2, 24}
*/

// 🔽 EXAMPLE USAGE
int main() {
    int arr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    pair<int, int> result = maxRowSum(arr, 3);

    cout << "Row with maximum sum is at index: " << result.first << endl;
    cout << "Maximum sum is: " << result.second << endl;

    return 0;
}

/*
    ✅ OUTPUT:
    Row with maximum sum is at index: 2
    Maximum sum is: 24
*/
