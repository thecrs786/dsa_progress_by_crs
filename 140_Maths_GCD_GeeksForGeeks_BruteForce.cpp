#include<iostream>
using namespace std;

// Brute Force GCD Method
int gcd(int m, int n) {

    // Handle negative input case
    
    m=abs(m); // for correct result if any of input is negative
    n=abs(n);
    // ✅ Handle edge cases first

    if (m == 0 && n == 0) return 0; // Undefined, but returning 0 to avoid crash

    if (m == 0) return n;  // If one number is 0, GCD is the other
    if (n == 0) return m;

    int small = min(m, n);
    int ans = 1;

    // 🔁 Brute force check from 2 to the smaller of m and n
    for (int i = 2; i <= small; i++) {
        if (m % i == 0 && n % i == 0) {
            ans = i;  // Update answer if i divides both m and n
        }
    }

    return ans;  // ✅ Final GCD result
}

int main() {
    // 🧪 Test cases
    cout << gcd(20, 28) << endl;   // Output: 4
    cout << gcd(100, 80) << endl;  // Output: 20
    cout << gcd(7, 13) << endl;    // Output: 1 (co-prime)
    cout << gcd(0, 5) << endl;     // Output: 5 (GCD rule)
    cout << gcd(10, 0) << endl;    // Output: 10 (GCD rule)

    return 0;
}

/*
🧠 FUNCTION EXPLANATION:

This is a brute-force method for calculating the GCD (Greatest Common Divisor) of two integers.

👉 LOGIC:
- GCD of two numbers is the largest number that divides both.
- So we loop from 2 up to the smaller of the two numbers.
- For each `i`, if both numbers are divisible by `i`, store it.
- Return the largest such number.

📦 TIME & SPACE COMPLEXITY:

⏱️ Time Complexity: O(min(m, n))
    - We loop from 2 to min(m, n), checking divisibility.
    - Not suitable for large numbers.

📦 Space Complexity: O(1)
    - Only constant variables used, no extra space.

📌 EXAMPLE:
    gcd(20, 28)
    → common divisors: 1, 2, 4 → GCD = 4 ✅

⚠️ LIMITATIONS:
- Very slow for large inputs (e.g., 10^9).
- Better to use Euclidean Algorithm: O(log(min(m, n)))
- Doesn’t handle negatives; use `abs()` if needed.

👀 NOTES:
- GCD(0, x) = x is valid (by definition)
- GCD(0, 0) is mathematically undefined but can return 0 to avoid crash

✅ GOOD FOR:
- Understanding GCD basics
- Very small input ranges (educational purposes)
*/
