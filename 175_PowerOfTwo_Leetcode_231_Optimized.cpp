/*
Problem: Power of Two
---------------------------------------
Determine if a given integer `n` is a power of two. 
A number is a power of two if it can be written as 2^k for some integer k >= 0.

Example:
Input: n = 16
Output: true
Explanation: 16 = 2^4

Input: n = 18
Output: false
Explanation: 18 is not a power of two.

Solution Name / Method: Iterative division
1. If n <= 0 → immediately return false (negative numbers and zero cannot be powers of two).
2. Keep dividing n by 2 as long as it is divisible by 2.
3. If the final value becomes 1 → true (it was a power of two), otherwise false.

Time Complexity: O(log n) — number of divisions required to reduce n to 1
Space Complexity: O(1) — no extra storage used

Optimality:
- Works and accepted on LeetCode.
- Can be further optimized using bit manipulation (n & (n-1) == 0) in O(1) time.

Full Code with Explanation:
*/

#include <iostream>
using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        // Step 1: Negative numbers and zero are never powers of two
        if(n <= 0) return false;

        // Step 2: Divide n by 2 iteratively as long as it is divisible by 2
        while(n % 2 == 0) {
            n /= 2;
        }

        // Step 3: After division, if n becomes 1, it was a power of two
        if(n == 1) return true;

        // Step 4: Otherwise, n had factors other than 2
        return false;
    }
};

/*
Working Examples:
*/

int main() {
    Solution sol;

    // Example 1
    int n1 = 16;
    cout << "Input: " << n1 << ", Output: " << sol.isPowerOfTwo(n1) << endl;
    // Expected Output: true (16 = 2^4)

    // Example 2
    int n2 = 18;
    cout << "Input: " << n2 << ", Output: " << sol.isPowerOfTwo(n2) << endl;
    // Expected Output: false (18 is not power of 2)

    // Example 3
    int n3 = 1;
    cout << "Input: " << n3 << ", Output: " << sol.isPowerOfTwo(n3) << endl;
    // Expected Output: true (2^0 = 1)

    // Example 4
    int n4 = -8;
    cout << "Input: " << n4 << ", Output: " << sol.isPowerOfTwo(n4) << endl;
    // Expected Output: false (negative numbers cannot be power of 2)

    return 0;
}

/*
Key Insights:
1. Powers of two only have 1 as the leading bit in binary representation.
2. Iterative division works because each division reduces the power by 1.
3. Edge cases: n <= 0, n = 1 (2^0), n = large numbers.

Common Mistakes:
1. Forgetting to check n <= 0 → leads to wrong answers for negative inputs.
2. Assuming 1 is not a power of 2 → 1 = 2^0, so it is valid.
3. Not breaking the loop correctly → loop already stops when n % 2 != 0.
*/
