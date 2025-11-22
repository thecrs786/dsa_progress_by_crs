/*
LeetCode Problem: 342. Power of Four
------------------------------------
Problem Summary:
Given an integer n, return true if it is a power of four. Otherwise, return false.

Method:
Repeated division method — divide by 4 until n becomes 1. 
If at any step n is not divisible by 4, return false.

Time Complexity: O(log4(n))
Space Complexity: O(1)
Optimal: ✅ (Yes, accepted by LeetCode) 

NOT MOST OPTIMIZED

Note: Can also be solved using bitwise tricks, but this is a simple iterative method.

Edge Cases:
- n <= 0 should return false
- n = 1 should return true (4^0)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) return false;  // powers of 4 are positive only
        while (n % 4 == 0) {       // keep dividing while divisible by 4
            n /= 4;
        }
        return n == 1;             // should end at 1 if it's power of 4
    }
};

int main() {
    Solution sol;
    
    // Working Examples:
    cout << boolalpha; // prints true/false instead of 1/0
    cout << sol.isPowerOfFour(1) << "\n";   // true  (4^0)
    cout << sol.isPowerOfFour(4) << "\n";   // true  (4^1)
    cout << sol.isPowerOfFour(16) << "\n";  // true  (4^2)
    cout << sol.isPowerOfFour(64) << "\n";  // true  (4^3)
    cout << sol.isPowerOfFour(8) << "\n";   // false (not a power of 4)
    cout << sol.isPowerOfFour(-4) << "\n";  // false (negative)
}
