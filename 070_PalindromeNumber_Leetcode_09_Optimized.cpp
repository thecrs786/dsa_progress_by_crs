// ✅ LeetCode Problem: Palindrome Number
// 🔗 https://leetcode.com/problems/palindrome-number/

#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        // ❌ Step 1: Negative numbers are not palindromes
        // E.g., -121 is not the same as 121-
        if (x < 0) return false;

        // ❌ Step 2: Any number ending in 0 but not 0 itself is NOT a palindrome
        // E.g., 10 becomes 01 after reverse, which is invalid
        if (x != 0 && x % 10 == 0) return false;

        // ✅ Step 3: Store the original number before modifying x
        // Reason: We will reverse x, and need original value for comparison
        int original = x;

        // ✅ Step 4: Reverse the number
        int reversed = 0;

        while (x > 0) {
            int digit = x % 10;

            // ⚠️ Step 5: Overflow check (optional for LeetCode Q9, but good practice)
            if (reversed > (INT_MAX - digit) / 10)
                return false;  // Would overflow

            reversed = reversed * 10 + digit;
            x = x / 10;
        }

        // ✅ Step 6: Compare reversed with original
        return reversed == original;
    }
};

// ✅ Example test case (main function for testing)
int main() {
    Solution sol;
    int num = 121;

    if (sol.isPalindrome(num)) {
        cout << num << " is a palindrome." << endl;
    } else {
        cout << num << " is not a palindrome." << endl;
    }

    return 0;
}
