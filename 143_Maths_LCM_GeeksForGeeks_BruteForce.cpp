#include<iostream>
using namespace std;

// 🧠 BRUTE-FORCE METHOD TO CALCULATE LCM OF TWO NUMBERS

// LCM (Least Common Multiple) of two integers m and n is the smallest number that is divisible by both.
// Ex: LCM of 4 and 6 is 12. Because 12 is the smallest number divisible by both 4 and 6.

int lcm(int m, int n) {
    // ✅ Step 1: Find the bigger and smaller number
    int big = max(m, n);
    int small = min(m, n);

    // 💭 Our idea:
    // Try multiples of the bigger number (big * 1, big * 2, big * 3, ...) 
    // and check if any of them is divisible by the smaller number.
    // The first one that satisfies this condition is the LCM.

    // 🧨 This is brute-force because we are checking linearly and naively.

    for (int i = 1; i <= small; i++) {
        // 💡 We are multiplying the bigger number with 'i'
        // So 'big * i' is a multiple of the bigger number

        // 🤔 Now check: Is this multiple also divisible by the smaller number?
        if ((big * i) % small == 0) {
            // ✅ If yes, we've found the LCM
            return big * i;
        }
    }

    // 🚫 This line will never execute unless input is invalid
    return 0;
}

int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    // 📢 Output the LCM
    cout << "LCM = " << lcm(a, b) << endl;

    return 0;
}

/*
🧠 EXAMPLE:

Input:
a = 6, b = 8

Step-by-step:
- big = 8, small = 6
- Try 8*1 = 8 → 8 % 6 != 0 ❌
- Try 8*2 = 16 → 16 % 6 != 0 ❌
- Try 8*3 = 24 → 24 % 6 == 0 ✅
→ So, LCM = 24
*/


// 🔥 IS THIS BRUTE-FORCE?
// Yes. It linearly checks for common multiples starting from the bigger number.

// 🧨 TIME COMPLEXITY:
// Worst-case: O(min(m, n))
// It tries up to `small` iterations in the worst case.

// ⚠️ DRAWBACKS:
// - Slower for large numbers (e.g., m = 1,000,000 and n = 999,983)
// - Not elegant or scalable
// O(log(min(a,b))) | O(log) | 🚀 Very Fast | ✅ Yes        | ✅ Clean  |


