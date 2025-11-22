// =======================================
// for loops in C++
// General Syntax:
// for(initialisation; condition; updation){
//      work;
// }
// =======================================

#include<iostream>
#include<stdio.h>
using namespace std;  

int main(){

    // ===========================
    // Example 1: Simple Multiplication Table
    // ===========================
    int num;
    cout<< "Enter a number : ";
    cin>> num;

    // Standard for loop → only ONE variable (i)
    for(int i = 1; i <= 10; i++){
        printf("%d * %d = %d\n", num, i, num * i);
        // cout<< num << " * " << i << " = " << num*i;
    }


    // ===========================
    // Example 2: Two-variable for loop
    // ===========================
    // We can initialize, update, and check condition
    // for MORE THAN ONE variable at the same time.
    //
    // Syntax:
    // for(initialise1, initialise2; condition1 && condition2; update1, update2)
    // This is very useful in problems like two-pointer technique,
    // diagonal traversals, etc.

    cout << "\nTwo-variable for loop demo:\n";

    for(int i = 0, j = 9; i < 10 && j >= 0; i++, j--){
        cout << "i = " << i << ", j = " << j << "\n";
        // Here, i increases (0 → 9), while j decreases (9 → 0).
        // So, (i, j) pairs will look like:
        // (0,9), (1,8), (2,7), ... (9,0)
    }

    // Key Insight:
    // You can use this trick whenever you want to move
    // two pointers/variables in OPPOSITE or DIFFERENT directions.
    // - Example: i++ (left to right), j-- (right to left).
    // - Example: i--, j++ (move upwards-right on a matrix).

    return 0;
}

/*
==============================================
OUTPUT SAMPLE:
----------------------------------------------
Enter a number : 5
5 * 1 = 5
5 * 2 = 10
...
5 * 10 = 50

Two-variable for loop demo:
i = 0, j = 9
i = 1, j = 8
i = 2, j = 7
...
i = 9, j = 0
==============================================

✔ This is EXACTLY the style we used in N-Queens
  for diagonal checks:
  for(int i=row, j=column; i>=0 && j>=0; i--, j--)

==============================================
*/
