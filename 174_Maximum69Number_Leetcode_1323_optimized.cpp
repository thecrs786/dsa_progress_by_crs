/*
Problem Summary:
---------------
LeetCode Problem: 1323. Maximum 69 Number

We are given a positive integer 'num' consisting only of digits 6 and 9.
We can change at most one digit from 6 → 9. The task is to maximize 'num'
and return the result.

Example:
--------
Input: num = 9669
Output: 9969
Explanation: Change the first 6 → 9. Result = 9969 (maximum possible).

LeetCode Insights:
------------------
- Constraints are very small: 1 <= num <= 10^4
- At most 4 digits (since num ≤ 9999).
- So brute-force digit manipulation is efficient enough.
- Trick: To maximize, flip the **first (leftmost) 6** only, since it has the highest place value.

Solution Method:
----------------
Greedy + Digit Manipulation
1. Break the number into digits.
2. Traverse from left → right:
   - Flip the first '6' into '9'.
   - Stop further changes (only one allowed).
3. Reconstruct the integer from digits.
4. Return the result.

Time & Space Complexity:
------------------------
- Time: O(d) where d = number of digits (≤ 4). Effectively O(1).
- Space: O(d) for vector (≤ 4). Effectively O(1).

Optimality:
-----------
- Yes, this is the optimal solution.
- Accepted on LeetCode since it guarantees the maximum number.

Why it works:
-------------
- Changing the leftmost 6 maximizes the number because higher place values
  contribute more to the result.
- Example: num = 6699
    - Flip 1st 6 → 9699 (max)
    - Flip 2nd 6 → 6999 (smaller)
    - Flip later 6’s → less effect.

----------------------------------------------------------------------
Full Code with Explanation and Example:
----------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximum69Number (int num) {
        vector<int> digits;

        // Step 1: Break number into digits (left to right order)
        int n = num;
        while (n > 0) {
            digits.insert(digits.begin(), n % 10); // insert at front
            n /= 10;
        }

        // Step 2: Change the first 6 → 9
        int size = digits.size();
        for (int i = 0; i < size; i++) {
            if (digits[i] == 6) {
                digits[i] = 9;
                break; // only one change allowed
            }
        }

        // Step 3: Reconstruct number
        int ans = 0;
        for (int i = 0; i < size; i++) {
            ans = ans * 10 + digits[i];
        }
        return ans;
    }
};

int main() {
    Solution sol;

    // Example test case
    int num = 9669;
    int result = sol.maximum69Number(num);

    cout << "Input: " << num << endl;
    cout << "Maximum number after flipping at most one 6 → 9: " << result << endl;

    /*
    Walkthrough:
    ------------
    num = 9669
    Digits = [9, 6, 6, 9]
    Flip first 6 → [9, 9, 6, 9]
    Reconstruct → 9969
    Output = 9969
    */

    return 0;
}
