#include <iostream>
using namespace std;

/*
=========================
UNDERSTANDING RECURSION
=========================

1. Recursion is when a function calls itself to solve a smaller version of the same problem.
2. Every recursive function must have:
   - Base Case: Condition where recursion stops.
   - Recursive Case: Function calls itself with smaller input.
3. Call Stack:
   - Each function call is stored on the stack.
   - When a function finishes, it is popped from the stack.
4. Backtracking:
   - Happens when the function returns from a recursive call.
   - Allows you to undo previous actions and try alternatives (common in tree, maze, or combination problems).

Example problems solved recursively below:
1. Sum of first n natural numbers
2. Factorial of n
3. nth Fibonacci number
*/

// Function 1: Sum of first n natural numbers
int sumOfN(int n) {
    // Base case: if n is 0, sum is 0
    if (n == 0) return 0;
    
    // Recursive case: sum of n = n + sum of (n-1)
    return n + sumOfN(n - 1);
}

// Function 2: Factorial of n
int factorial(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n <= 1) return 1;

    // Recursive case: n! = n * (n-1)!
    return n * factorial(n - 1);
}

// Function 3: nth Fibonacci number
int fibonacci(int n) {
    // Base case: first two Fibonacci numbers
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Recursive case: F(n) = F(n-1) + F(n-2)
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // Demonstration of recursive functions

    int n;

    // 1. Sum of first n natural numbers
    n = 5;
    cout << "Sum of first " << n << " natural numbers: " << sumOfN(n) << endl;
    // Explanation: sumOfN(5) -> 5 + sumOfN(4) -> 5 + 4 + sumOfN(3) -> ... -> 0

    // 2. Factorial of n
    n = 5;
    cout << n << "! = " << factorial(n) << endl;
    // Explanation: factorial(5) -> 5*factorial(4) -> 5*4*factorial(3) -> ... -> 1

    // 3. nth Fibonacci number
    n = 6;
    cout << "Fibonacci term at position " << n << " is: " << fibonacci(n) << endl;
    // Explanation: fibonacci(6) -> fibonacci(5) + fibonacci(4) -> ... base cases return 0 or 1

    return 0;
}

/*
=========================
KEY POINTS
=========================

- Each recursive call is added to the call stack.
- Once base case is reached, the stack starts unwinding.
- Backtracking is visible when stack unwinds: functions resume from where they left.
- Recursive solutions are elegant but may be slower due to repeated calculations.
  - Example: naive Fibonacci has exponential time complexity O(2^n)
- Always ensure base case is reachable to prevent infinite recursion.
*/

/*
=========================
TIME & SPACE COMPLEXITY IN RECURSION
=========================

General rules:
1. Time Complexity (TC): Number of recursive calls * work done per call
2. Space Complexity (SC): Maximum depth of recursion (call stack) * space per call
3. Always consider:
   - Each function call uses O(1) extra space for variables and return address
   - Exponential recursion (like naive Fibonacci) can explode TC


// 1. Sum of first n natural numbers
int sumOfN(int n) {
    if (n == 0) return 0;       // Base case
    return n + sumOfN(n - 1);   // Recursive call
    // TC: O(n) → n calls, each does O(1) work (just addition)
    // SC: O(n) → recursion depth = n
}

// 2. Factorial of n
int factorial(int n) {
    if (n <= 1) return 1;       // Base case
    return n * factorial(n - 1);// Recursive call
    // TC: O(n) → n calls, each does O(1) multiplication
    // SC: O(n) → recursion depth = n
}

// 3. nth Fibonacci number (naive recursion)
int fibonacci(int n) {
    if (n == 0) return 0;       // Base case
    if (n == 1) return 1;       // Base case
    return fibonacci(n - 1) + fibonacci(n - 2);
    // TC: O(2^n) → each call splits into 2 calls (binary tree of calls)
    // SC: O(n) → maximum recursion depth = n (the longest path in the call tree)
}
*/
/*
=========================
SUMMARY TABLE
=========================
Function       | Time Complexity | Space Complexity | Notes
---------------|----------------|----------------|----------------------
sumOfN(n)      | O(n)           | O(n)           | Linear recursion, addition
factorial(n)   | O(n)           | O(n)           | Linear recursion, multiplication
fibonacci(n)   | O(2^n)         | O(n)           | Exponential recursion, naive approach
*/
