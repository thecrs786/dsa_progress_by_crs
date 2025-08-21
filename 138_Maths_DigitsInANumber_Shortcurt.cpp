// ============================================================================
// ✅ Problem: Count the Number of Digits in an Integer
// ----------------------------------------------------------------------------
// 🔸 Objective: Given an integer 'n', return the number of digits it contains.
// 🔸 Method: Use logarithmic properties (base-10 logarithm).
// ----------------------------------------------------------------------------
// 🔸 Approach Name: Logarithmic Method (base-10 digit count)
// 🔸 Time Complexity: O(1) — constant time
// 🔸 Space Complexity: O(1) — no extra space used
// 🔸 Optimal: YES — this is the most efficient method for counting digits
// 🔸 LeetCode Safety: YES — won't cause TLE or MLE
// ============================================================================

#include <iostream>
#include <cmath>     // for log10 and abs
using namespace std;

// ----------------------------------------------------------------------------
// ✅ Function: countDigitsUsingLog
// ----------------------------------------------------------------------------
// 🔹 Takes an integer input (positive or negative or zero).
// 🔹 If number is zero, directly returns 1 (since log10(0) is undefined).
// 🔹 For all other values, it takes absolute value to handle negative numbers.
// 🔹 Applies floor(log10(n)) + 1 to get digit count.
// ----------------------------------------------------------------------------
int countDigitsUsingLog(int n) {
    if (n == 0) return 1; // Edge case: log10(0) is undefined

    // Taking abs to ensure negative numbers don't break log10
    return floor(log10(abs(n))) + 1;
}

// ----------------------------------------------------------------------------
// ✅ MAIN FUNCTION FOR DEMO PURPOSES
// ----------------------------------------------------------------------------
int main() {
    // Test Example 1: Positive number
    int num1 = 12345;
    cout << "Digits in " << num1 << " = " << countDigitsUsingLog(num1) << endl;
    // Output: 5

    // Test Example 2: Negative number
    int num2 = -987654;
    cout << "Digits in " << num2 << " = " << countDigitsUsingLog(num2) << endl;
    // Output: 6

    // Test Example 3: Edge case zero
    int num3 = 0;
    cout << "Digits in " << num3 << " = " << countDigitsUsingLog(num3) << endl;
    // Output: 1

    return 0;
}

// ============================================================================
// ✅ LOGIC EXPLAINED:
// ----------------------------------------------------------------------------
// • Every digit place increases by a power of 10.
//      1 digit: [1, 9]         → log10 in [0, 0.95] → floor = 0 → +1 = 1 digit
//      2 digits: [10, 99]      → log10 in [1.0, 1.99] → floor = 1 → +1 = 2 digits
//      3 digits: [100, 999]    → log10 in [2.0, 2.99] → floor = 2 → +1 = 3 digits
//      ...
// • So, to find number of digits: floor(log10(n)) + 1
//
// ⚠️ log10(0) is undefined, so must return 1 manually in that case.
// ⚠️ Negative numbers must be converted to positive using abs().
// ----------------------------------------------------------------------------
// ✅ FORMULA SUMMARY:
//     Digits(n) = (n == 0) ? 1 : floor(log10(abs(n))) + 1
// ============================================================================

