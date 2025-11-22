#include<iostream>
#include<vector>
using namespace std;

/*
    ✅ TOPIC: 2D VECTORS IN C++

    A 2D vector in C++ is essentially a vector of vectors.
    It's dynamic, flexible, and easier to use than raw 2D arrays when the size is not fixed.

    🔍 USE CASES:
    - Useful in matrices, grids, graph adjacency lists, DP tables, etc.

    ----------------------------------------------
    🛠️ COMMON METHODS AND OPERATIONS WITH NOTES:
    ----------------------------------------------

    1. Initialization
        a. Empty:                      vector<vector<int>> v;
        b. Fixed size (NxM, default 0): vector<vector<int>> v(n, vector<int>(m));
        c. Fixed size with value:      vector<vector<int>> v(n, vector<int>(m, val));
        d. Init from raw array:        Use loops
        e. Init via initializer list:  vector<vector<int>> v = {{1,2}, {3,4}};

    2. Access:
        - v[i][j] → access element at i-th row and j-th column
        - O(1) time
        - Index-based

    3. Modify:
        - v[i][j] = x;
        - O(1) time
        - Index-based

    4. Push:
        - Add a row:                  v.push_back({1,2,3});         ✅ O(1)
        - Add an element to a row:    v[i].push_back(x);            ✅ O(1) amortized

    5. Pop:
        - Remove last row:            v.pop_back();                 ✅ O(1)
        - Remove last column in row:  v[i].pop_back();              ✅ O(1)

    6. Insert:
        - Insert row at pos:          v.insert(v.begin()+pos, row) ✅ O(N)
        - Insert col in row:          v[i].insert(v[i].begin()+j, x) ✅ O(M)

    7. Erase:
        - Erase row:                  v.erase(v.begin() + i);       ✅ O(N)
        - Erase column from row:      v[i].erase(v[i].begin() + j); ✅ O(M)

    8. Traversal:
        - Range-based for
        - Classic nested for loops
        - Iterators

    ----------------------------------------------
    📌 PERFORMANCE NOTE:
    - Index-based access is fast and direct
    - Insertion/removal (except at end) can be O(N)
    - Use carefully in nested structures

    ----------------------------------------------
    📌 ROWS AND COLUMNS SIZE IN 2D VECTORS:

    ✅ ROWS:
    - rows = v.size()
    - Because each row is a vector, v.size() gives number of rows

    ✅ COLUMNS (per row):
    - cols = v[i].size()
    - Each row can have different size (jagged vector), so column size must be fetched per row.

    ❗ DON'T use v[0].size() blindly unless you're 100% sure it's a perfect rectangle

    🔁 Example:
    vector<vector<int>> v = {
        {1, 2, 3},
        {4, 5},
        {6, 7, 8, 9}
    };

    - Total rows = v.size() = 3
    - v[0].size() = 3
    - v[1].size() = 2
    - v[2].size() = 4

    ✅ Best practice for nested traversal:
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
    }
    ----------------------------------------------
*/

int main() {
    // ----------------------------------------------
    // 1. Initialization Examples
    // ----------------------------------------------

    // a. Empty 2D vector
    vector<vector<int>> empty;

    // b. 3x4 matrix, all zeros
    vector<vector<int>> mat1(3, vector<int>(4));

    // c. 2x2 matrix, all filled with 7
    vector<vector<int>> mat2(2, vector<int>(2, 7));

    // d. From initializer list
    vector<vector<int>> mat3 = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // e. Row-wise construction using push_back
    vector<vector<int>> mat4;
    mat4.push_back({1, 2});
    mat4.push_back({3, 4, 5});

    // ----------------------------------------------
    // 2. Access & Modification
    // ----------------------------------------------
    mat3[0][1] = 20; // Access + modify
    cout << "mat3[0][1] = " << mat3[0][1] << endl;

    // ----------------------------------------------
    // 3. Add elements
    // ----------------------------------------------
    mat3.push_back({7, 8, 9});           // Add a new row
    mat3[1].push_back(99);              // Add to existing row

    // ----------------------------------------------
    // 4. Remove elements
    // ----------------------------------------------
    mat3.pop_back();                    // Remove last row
    mat3[1].pop_back();                 // Remove last element of row 1

    // ----------------------------------------------
    // 5. Insert and Erase
    // ----------------------------------------------
    vector<int> new_row = {100, 200, 300};
    mat3.insert(mat3.begin() + 1, new_row); // Insert new_row at index 1

    mat3.erase(mat3.begin() + 1);           // Remove the row we just added

    // ----------------------------------------------
    // 6. Traversal
    // ----------------------------------------------
    cout << "Matrix:\n";
    for (int i = 0; i < mat3.size(); i++) {
        for (int j = 0; j < mat3[i].size(); j++) {
            cout << mat3[i][j] << " ";
        }
        cout << endl;
    }

    // Alternate: Range-based
    cout << "\nRange-based for loop:\n";
    for (const auto& row : mat3) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
    ✅ SAMPLE OUTPUT:

    mat3[0][1] = 20

    Matrix:
    1 20 3
    4 5 6

    Range-based for loop:
    1 20 3
    4 5 6
*/
