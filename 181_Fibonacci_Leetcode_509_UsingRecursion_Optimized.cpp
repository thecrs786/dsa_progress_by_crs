#include <bits/stdc++.h>
using namespace std;

/*
    ✅ QUESTION (LeetCode 509: Fibonacci Number):

    Given an integer n, return the nth Fibonacci number.
    The Fibonacci sequence is defined as:
      F(0) = 0
      F(1) = 1
      F(n) = F(n-1) + F(n-2), for n > 1

    Example:
      Input: n = 5
      Output: 5
      Explanation: Fibonacci sequence: 0, 1, 1, 2, 3, 5

    🔑 Key points:
      - Recursive solution directly implements the Fibonacci definition.
      - Extremely intuitive and simple to write.
      - Not efficient for large n due to repeated calculations.
*/

/*
    Solution provided:
    - Recursive method based directly on Fibonacci formula.
    - Name/Method: Simple Recursion (Naive Recursive Approach)
*/

class Solution {
public:

    int fib(int n) {
        // Base case: F(0) = 0, F(1) = 1
        if(n == 0 || n == 1) return n;

        // Recursive call: F(n) = F(n-1) + F(n-2)
        return fib(n-1) + fib(n-2);
    }
};

/*
    🔹 Function Explanation & Logic:

    1. We first check the base cases:
       - If n is 0, return 0
       - If n is 1, return 1
       These prevent infinite recursion and define the first two numbers of the Fibonacci sequence.

    2. For n > 1:
       - We recursively calculate the previous two Fibonacci numbers:
         fib(n-1) -> computes the (n-1)th Fibonacci
         fib(n-2) -> computes the (n-2)th Fibonacci
       - Then we sum them to get the nth Fibonacci number.

    3. This matches the mathematical Fibonacci definition exactly.
    
    🔹 Working of function (step-by-step for n=4):
       fib(4) 
       -> fib(3) + fib(2)
          -> (fib(2) + fib(1)) + (fib(1) + fib(0))
          -> ((fib(1)+fib(0)) + 1) + (1+0)
          -> ((1+0)+1) + (1+0)
          -> 2 + 1
          -> 3
*/

/*
    🔹 Time Complexity:

    T(n) = T(n-1) + T(n-2) + O(1)
    - Each call spawns 2 more calls (except base cases)
    - Number of calls grows exponentially with n
    - Exact growth ~ O(2^n)
    - Extremely inefficient for n >= 40, as many subproblems are recalculated multiple times

    🔹 Space Complexity:

    - Space used by recursion call stack
    - Maximum depth of recursion = n (from fib(n) down to fib(0))
    - Space complexity = O(n)

    🔹 Optimality:
      - This is NOT the optimal solution.
      - Will not cause TLE (Time Limit Exceeded) on LeetCode, but might cause tle  for large n on other platforms.
      - Memory usage is okay but redundant computation makes it slow.
      - Optimal solutions use:
        1. Memoization (top-down DP)
        2. Tabulation (bottom-up DP)
        3. Iterative constant space solution
*/

/*
    🔹 Key insights:
      - Recursive solution is simple, but exponential time is a huge drawback.
      - Base cases are critical to stop infinite recursion.
      - The call tree grows exponentially (fib(n-1) and fib(n-2) branches repeatedly)
      - For n=5, the recursion tree:
            fib(5)
           /      \
        fib(4)    fib(3)
        /   \     /   \
      fib(3) fib(2) fib(2) fib(1)
      ... repeated subcalls
*/

int main() {
    Solution sol;

    // Example: Calculate 5th Fibonacci number
    int n = 5;
    int result = sol.fib(n);

    cout << "Fibonacci of " << n << " is: " << result << endl;

    // Example: Analyze output for small n
    cout << "Fibonacci sequence up to n=" << n << ": ";
    for(int i=0; i<=n; i++){
        cout << sol.fib(i) << " ";
    }
    cout << endl;

    return 0;
}

/*
    ✅ Sample Output:

    Fibonacci of 5 is: 5
    Fibonacci sequence up to n=5: 0 1 1 2 3 5

    🔹 Observations:
      - Works perfectly for small n
      - Output matches the standard Fibonacci sequence
      - Recursive calls increase drastically for larger n
*/
