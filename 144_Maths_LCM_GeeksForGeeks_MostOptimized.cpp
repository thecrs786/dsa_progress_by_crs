#include<iostream>
using namespace std;

/*
🔢 GCD and LCM - Most Optimized Code + Brutally Detailed Explanation

✅ Method Used for GCD: Euclidean Algorithm (Iterative)
→ GCD(a, b) = GCD(b, a % b)
→ It reduces the problem size with each iteration by replacing the larger number with the remainder.
→ This is mathematically proven to compute the greatest common divisor correctly.

→ Example:
   GCD(18, 12) → GCD(12, 6) → GCD(6, 0) = 6

✅ Time Complexity of Euclidean GCD:
→ O(log(min(a, b)))
→ Because each step reduces the size of the numbers significantly (approx. halved)

✅ Space Complexity:
→ O(1) — Constant space used

✅ Most Optimized LCM Formula:
→ LCM(a, b) = (a / GCD(a, b)) * b

⚠️ We divide *before* multiplication to prevent **integer overflow**:
→ If we did: a * b / GCD(a, b), it might overflow for large integers
→ But since GCD(a, b) divides both a and b, a / GCD(a, b) is guaranteed to be ≥ 1 for positive integers
→ Hence, division before multiplication is safe and accurate

📌 Example:
   a = 12, b = 18
   GCD = 6
   LCM = (12 / 6) * 18 = 2 * 18 = 36

📌 Edge Case:
   If either a or b is 0, the LCM is defined as 0
*/

// ✅ Most optimized GCD function using Euclidean Algorithm (Iterative)
int gcd(int a, int b) {
    // Ensure non-negative values for correctness
    a = abs(a);
    b = abs(b);

    // Repeat until the remainder becomes 0
    while (b != 0) {
        int remainder = a % b;  // Find remainder
        a = b;                  // Move 'b' to 'a'
        b = remainder;          // Update 'b' to the remainder
    }

    return a;  // When b becomes 0, a is the GCD
}

// ✅ Most optimized LCM using the relation: LCM * GCD = a * b
int lcm(int a, int b) {
    // Division first to avoid overflow
    return (a / gcd(a, b)) * b;
}

int main() {
    int a, b;
    cout << "Enter two positive integers: ";
    cin >> a >> b;

    // Edge case check
    if (a == 0 || b == 0) {
        cout << "LCM of 0 and any number is 0 (undefined conceptually)" << endl;
        return 0;
    }

    // Output result
    cout << "LCM of " << a << " and " << b << " is: " << lcm(a, b) << endl;

    return 0;
}
