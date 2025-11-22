// MULTIPLY 2 MATRICES

#include<iostream>
using namespace std;

void multiplyMatrix(int a[3][3], int b[3][3], int result[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            result[i][j] = 0;
            for(int k=0; k<3; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void printMatrix(int matrix[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int mat1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int mat2[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int result[3][3];

    multiplyMatrix(mat1, mat2, result);

    cout << "Result of multiplication:\n";
    printMatrix(result);

    return 0;
}
