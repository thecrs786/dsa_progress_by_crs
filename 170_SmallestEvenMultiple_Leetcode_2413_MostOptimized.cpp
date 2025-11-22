/*
------------------------------------------------------------
📜 Problem Summary:
Given a positive integer `n`, return the smallest positive integer 
that is a multiple of both `n` and 2.

------------------------------------------------------------
💡 Solution Name:
Direct Conditional Check (Even/Odd Approach)

------------------------------------------------------------
⏳ Time Complexity:
O(1) → Constant time, since only one modulus check and multiplication.

💾 Space Complexity:
O(1) → No extra space used.

------------------------------------------------------------
✅ Optimality:
Yes — This is the simplest and fastest approach possible.
Accepted on LeetCode.

------------------------------------------------------------
🔍 Deep Explanation of Each Step:
1. If `n` is even, then `n` itself is already a multiple of 2 → return `n`.
2. If `n` is odd, multiply by 2 to make it even and a multiple of both `n` and 2.
3. No loops or extra variables are required; purely a mathematical check.

------------------------------------------------------------
⚙️ Full Logic & Function Walkthrough:
Example 1:
Input: n = 5  
Step 1: 5 % 2 = 1 → odd  
Step 2: Multiply by 2 → 5 * 2 = 10  
Step 3: Return 10.

Example 2:
Input: n = 6  
Step 1: 6 % 2 = 0 → even  
Step 2: Return 6 directly.

------------------------------------------------------------
🧪 Edge Cases:
- n = 1 → odd → returns 2
- n = 2 → even → returns 2
- Large n (within constraints) → still O(1) performance.

------------------------------------------------------------
🚫 Common Errors:
- Unnecessary loops or GCD/LCM calculations (overkill for this problem).
- Forgetting to multiply by 2 for odd numbers.

------------------------------------------------------------
🔹 Code Implementation:
*/
#include<iostream>
using namespace std;


class Solution {
public:
    int smallestEvenMultiple(int n) {
        // If n is even, it's already the smallest even multiple
        // If odd, multiply by 2 to make it even and still divisible by n
        return (n % 2 == 0) ? n : n * 2;
    }
};

// ============================
// 🚀 Working Example in main()
// ============================
int main() {

    Solution sol;
    // Example 1:
    int n1 = 5;
    cout << "Input: " << n1 << "\n";
    cout << "Smallest Even Multiple: " << sol.smallestEvenMultiple(n1) << "\n\n";

    // Example 2:
    int n2 = 6;
    cout << "Input: " << n2 << "\n";
    cout << "Smallest Even Multiple: " << sol.smallestEvenMultiple(n2) << "\n\n";

    // Example 3 (Edge Case):
    int n3 = 1;
    cout << "Input: " << n3 << "\n";
    cout << "Smallest Even Multiple: " << sol.smallestEvenMultiple(n3) << "\n";

    return 0;
}

/*
=============================
💻 Example Run:
Input: 5
Smallest Even Multiple: 10

*/
