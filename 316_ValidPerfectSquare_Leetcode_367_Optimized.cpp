#include <iostream>
using namespace std;

/*
====================================================================================
📌 LeetCode 367 — Valid Perfect Square
====================================================================================

📝 Problem (Brief):
-------------------
Given a positive integer `num`, determine if it is a **perfect square** or not.  
Return `true` if it is a perfect square, `false` otherwise.

🔹 Examples:

Example 1:
Input: num = 16
Output: true
Explanation: 16 = 4 * 4, so it's a perfect square.

Example 2:
Input: num = 14
Output: false
Explanation: 14 is not a perfect square.

====================================================================================
💡 Approach / Method:
---------------------
Binary Search Approach:
- Use binary search to find a number `mid` such that mid*mid == num.
- Search range: 1 to num.
- If mid*mid < num → search right half.
- If mid*mid > num → search left half.

====================================================================================
⏱ Time Complexity: O(logN)
   - Each iteration halves the search space.
📌 Space Complexity: O(1)
   - Constant extra space, no recursion or extra data structures.

✔ Optimality:
- This approach is optimal for the constraints of the problem (num up to 2^31-1).
- Will **not cause TLE or MLE** on LeetCode.
- Alternative methods exist: Newton's method (also O(logN)), but binary search is simple and robust.

====================================================================================
*/

class Solution {
public:
    bool isPerfectSquare(int num) {
        // -------------------------
        // Step 1: Define search range
        // -------------------------
        // We search between 1 and num (inclusive).
        // Use long long to prevent overflow when computing mid*mid.
        long long st = 1;
        long long end = num;

        // -------------------------
        // Step 2: Binary Search Loop
        // -------------------------
        while(st <= end) {
            // mid = st + (end - st)/2 to prevent integer overflow
            long long mid = st + (end - st)/2;

            // square of mid
            long long sq = mid * mid;

            // -------------------------
            // Step 3: Compare square with num
            // -------------------------
            if(sq == (long long)num) 
                return true;          // found perfect square
            else if(sq > (long long)num) 
                end = mid - 1;        // mid*mid too big, search left
            else 
                st = mid + 1;         // mid*mid too small, search right
        }

        // If loop finishes, no perfect square found
        return false;
    }
};

/*
====================================================================================
📌 LOGIC / FUNCTION WORKING:
------------------------------------------------------------------------------------
1. We want to find an integer `x` such that x*x = num.
2. We use **binary search** between 1 and num:
   - mid = (st + end)/2, but we write st + (end-st)/2 to avoid overflow.
   - Compute mid*mid (stored in long long to avoid overflow for large num).
3. Compare mid*mid with num:
   - If equal → perfect square → return true.
   - If mid*mid > num → discard right half, end = mid-1.
   - If mid*mid < num → discard left half, st = mid+1.
4. Repeat until st > end.
5. If we exit the loop without returning → no perfect square → return false.

🔹 Step-by-step Example (num=16):
- st=1, end=16 → mid=8, 8*8=64 > 16 → end=7
- st=1, end=7 → mid=4, 4*4=16 == 16 → return true

🔹 Step-by-step Example (num=14):
- st=1, end=14 → mid=7, 49>14 → end=6
- mid=3 → 9<14 → st=4
- mid=5 → 25>14 → end=4
- mid=4 → 16>14 → end=3 → exit loop → return false
====================================================================================
*/

int main() {
    Solution sol;

    // Test Case 1
    int num1 = 16;
    cout << "Is " << num1 << " a perfect square? " 
         << (sol.isPerfectSquare(num1) ? "Yes" : "No") << endl;

    // Test Case 2
    int num2 = 14;
    cout << "Is " << num2 << " a perfect square? " 
         << (sol.isPerfectSquare(num2) ? "Yes" : "No") << endl;

    // Test Case 3
    int num3 = 1; // Edge case
    cout << "Is " << num3 << " a perfect square? " 
         << (sol.isPerfectSquare(num3) ? "Yes" : "No") << endl;

    // Test Case 4
    int num4 = 2147395600; // Large perfect square (46340*46340)
    cout << "Is " << num4 << " a perfect square? " 
         << (sol.isPerfectSquare(num4) ? "Yes" : "No") << endl;

    return 0;
}

/*
====================================================================================
📌 IMPORTANT DETAILS, WARNINGS, AND KEY INSIGHTS:
------------------------------------------------------------------------------------
1. Use long long for mid*mid to prevent **integer overflow** (critical for large numbers).
2. Using st + (end - st)/2 prevents overflow in computing mid.
3. Binary search is optimal for 32-bit integer constraints.
4. This approach is simple and readable compared to Newton's method.

====================================================================================
🔹 SIMILAR QUESTIONS & APPROACHES:
------------------------------------------------------------------------------------
1. LeetCode 69 — Sqrt(x): compute integer square root using binary search.
2. LeetCode 367 (this problem) — variation for perfect square check.
3. Newton-Raphson method — faster convergence, O(log num) time, alternative approach.
4. Using built-in sqrt() → works but not recommended for interviews due to precision issues.
====================================================================================
*/
