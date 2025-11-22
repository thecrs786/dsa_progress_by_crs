/*
────────────────────────────────────────────────────────────
📘 CONTEXT:
This guide covers 2D static arrays in C++. We fix the number
of columns to 3 throughout, because C++ requires the number
of columns to be known at compile-time when passing a 2D array 
to a function. All initialization methods, access patterns,
and usage techniques are explained with examples.

────────────────────────────────────────────────────────────
📘 2D STATIC ARRAY MASTERLIST (int matrix[R][3])
────────────────────────────────────────────────────────────
1. Initialization Methods:
   - Manual assignment
   - Inline brace-enclosed
   - Partial initialization
   - Zero-initialization

2. Accessing Elements:
   - matrix[i][j] → using row & column indices

3. Modification:
   - matrix[i][j] = val → overwrite any element

4. No direct insert/remove:
   - Static arrays have fixed size.
   - No push_back, erase, etc. like vector.

5. Traversal:
   - Nested loops → index-based only

6. Time Complexity:
   - Access: O(1)
   - Update: O(1)
   - Traversal: O(n × m)

7. Iterator Support:
   ❌ No iterators
   ✅ Only index-based access
────────────────────────────────────────────────────────────
*/

#include<iostream>
using namespace std;

// Function to print a 2D static array with 3 columns
void printArr(int matrix[][3], int rows, int columns){
    cout << "Matrix : \n";
    for(int i = 0; i < rows; i++){
        cout << "[ ";
        for(int j = 0; j < columns; j++){
            cout << matrix[i][j];
            if(j != columns - 1) cout << ", ";
        }
        cout << " ]\n";
    }
    cout << endl;
}

int main() {
    // ─────────────────────────────────────────────
    // ✅ Method 1: Manual assignment after declaration
    // ─────────────────────────────────────────────
    int matrix1[3][3];  // [rows][columns]

    matrix1[0][0] = 1;
    matrix1[0][1] = 2;
    matrix1[0][2] = 3;
    matrix1[1][0] = 4;
    matrix1[1][1] = 5;
    matrix1[1][2] = 6;
    matrix1[2][0] = 7;
    matrix1[2][1] = 8;
    matrix1[2][2] = 9;

    printArr(matrix1, 3, 3);

    // ─────────────────────────────────────────────
    // ✅ Method 2: Inline Initialization
    // ─────────────────────────────────────────────
    int matrix2[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };
    printArr(matrix2, 4, 3);

    // ─────────────────────────────────────────────
    // ✅ Method 3: Partial Initialization (rest = 0)
    // ─────────────────────────────────────────────
    int matrix3[3][3] = {
        {1, 2},     // 3rd element = 0
        {3},        // 2nd, 3rd = 0
        {4, 5, 6}
    };
    printArr(matrix3, 3, 3);

    // ─────────────────────────────────────────────
    // ✅ Method 4: Zero Initialization
    // ─────────────────────────────────────────────
    int matrix4[2][3] = {};  // All elements initialized to 0
    printArr(matrix4, 2, 3);

    // ─────────────────────────────────────────────
    // 🛠️ Access & Modify
    // ─────────────────────────────────────────────
    matrix2[0][0] = 100;    // Modify value at 0th row, 0th column
    int val = matrix2[3][2];  // Access value at 3rd row, 2nd column
    cout << "Value at [3][2]: " << val << "\n";
    printArr(matrix2, 4, 3);

    // ❌ No direct push_back, erase, insert like vector
    // ✅ Use loops to shift elements manually if needed

    return 0;
}
