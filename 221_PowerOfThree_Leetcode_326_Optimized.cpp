/*
---------------------------------------------------
Problem: Power of Three
---------------------------------------------------
Summary:
- Given an integer n, determine if it is a power of three.
- A number is a power of three if there exists an integer x such that 3^x == n.
- Return true if n is a power of three, false otherwise.

Example:
    Input: n = 27
    Output: true
    Explanation: 27 = 3^3

---------------------------------------------------
Solution Method:
- Method used: Iterative division (repeatedly divide by 3)
- Idea: Keep dividing n by 3 while it is divisible.
  - If at the end n becomes 1 → it was a power of 3.
  - If at any point n % 3 != 0, or n <= 0 initially → not a power of 3.

---------------------------------------------------
Time and Space Complexity:
- Time Complexity: O(log_3(n)) → number of divisions until n becomes 1.
- Space Complexity: O(1) → constant extra space.
- Optimality: This is simple, efficient, and fully acceptable for LeetCode.
- Will it be accepted? Yes. No TLE, no MLE, works for constraints (n ≤ 2^31-1).

---------------------------------------------------
Important Details and Key Insights:
1. n <= 0 → immediately return false. Powers of three are positive.
2. Repeatedly divide by 3 instead of using pow() to avoid floating point precision issues.
3. When n % 3 != 0 → cannot be a power of 3.
4. When n == 1 after divisions → exactly a power of three.

---------------------------------------------------
*/

#include <iostream>
using namespace std;

class Solution {
public:
    // Function to check if n is a power of three
    bool isPowerOfThree(int n) {
        // Step 1: Handle negative numbers and zero
        if(n <= 0) return false;

        // Step 2: Repeatedly divide n by 3 while divisible
        while(n % 3 == 0){
            n = n / 3;
        }

        // Step 3: If n becomes 1 after divisions, it was a power of 3
        return n == 1;
    }
};

/*
---------------------------------------------------
Function Explanation (Step by Step):
---------------------------------------------------
1. if(n <= 0) return false;
   - Powers of three are always positive integers: 1, 3, 9, 27, ...
   - Any n <= 0 is automatically not a power of three.

2. while(n % 3 == 0) { n = n / 3; }
   - This loop keeps dividing n by 3 while it is divisible by 3.
   - For example: n=27 → 27%3==0 → 27/3=9 → 9%3==0 → 9/3=3 → 3%3==0 → 3/3=1
   - Loop exits when n % 3 != 0 or n becomes 1.

3. return n == 1;
   - After division, if n == 1 → it was a power of 3 (e.g., 27→9→3→1)
   - If n != 1 → division stopped prematurely → n had a factor other than 3 → not a power of 3
*/

/*
---------------------------------------------------
Working Example:
---------------------------------------------------
Input: n = 27
Step 1: n > 0 → continue
Step 2: while loop:
    27 % 3 == 0 → n = 27 / 3 = 9
    9 % 3 == 0 → n = 9 / 3 = 3
    3 % 3 == 0 → n = 3 / 3 = 1
Step 3: n == 1 → return true
Output: true
*/

int main() {
    Solution sol;

    int n1 = 27;      // Power of three
    int n2 = 10;      // Not a power of three
    int n3 = 1;       // 3^0
    int n4 = 0;       // Not a power of three
    int n5 = -9;      // Negative number

    cout << "27 is power of 3? " << (sol.isPowerOfThree(n1) ? "true" : "false") << endl;
    cout << "10 is power of 3? " << (sol.isPowerOfThree(n2) ? "true" : "false") << endl;
    cout << "1 is power of 3? " << (sol.isPowerOfThree(n3) ? "true" : "false") << endl;
    cout << "0 is power of 3? " << (sol.isPowerOfThree(n4) ? "true" : "false") << endl;
    cout << "-9 is power of 3? " << (sol.isPowerOfThree(n5) ? "true" : "false") << endl;

    return 0;
}

/*
---------------------------------------------------
Output:
27 is power of 3? true
10 is power of 3? false
1 is power of 3? true
0 is power of 3? false
-9 is power of 3? false
---------------------------------------------------
Key Takeaways:
1. Repeated division is efficient and precise for integer powers.
2. Avoid floating-point computations to prevent precision errors.
3. Always handle n <= 0 edge case.
4. O(log_3(n)) solution is fully optimal and accepted in competitive coding / LeetCode.
*/
