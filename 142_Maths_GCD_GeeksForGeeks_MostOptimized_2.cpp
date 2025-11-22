// USING RECURSION

#include<iostream>
using namespace std;

// ✅ Recursive GCD using Euclid’s Algorithm
int gcd(int a, int b) {
    // 🔴 Handle negative input to make logic consistent
    a = abs(a);
    b = abs(b);

    // 🔚 Base case: If b is 0, GCD is a
    if (b == 0) return a;

    // 🔁 Recursive case: Call gcd with (b, a % b)
    return gcd(b, a % b);
}

int main() {
    int a, b;

    cout << "Enter two numbers (separated by space): ";
    cin >> a >> b;

    cout << "GCD is: " << gcd(a, b) << endl;

    return 0;
}

/*

====================== ⚔️ BRUTAL EXPLANATION ======================

🧠 What is GCD(a, b)?
GCD (Greatest Common Divisor) of two integers a and b is the largest number that divides both without leaving a remainder.

🔥 WHY Euclid’s algorithm works:
GCD(a, b) = GCD(b, a % b)
Why? Because:
➡️ Any number that divides both a and b also divides (a - b*q), which is just a % b.
➡️ So we reduce the problem to a smaller one (b, a%b), again and again,
    until one of them becomes 0.
➡️ At that point, the other is the GCD.

📌 RECURSION LOGIC FLOW (Dry run for a = 48, b = 18):
gcd(48, 18)
=> gcd(18, 48 % 18) → gcd(18, 12)
=> gcd(12, 18 % 12) → gcd(12, 6)
=> gcd(6, 12 % 6)   → gcd(6, 0)
=> base case reached → return 6

🧾 How recursion works:
Each call waits for the next call to return a value.
The last call returns the answer (6), which bubbles up to the first call.

📌 WHY WE USE %:
The modulo operator finds the remainder when a is divided by b.
That remainder is what matters — we’re reducing the size of the problem
without changing the GCD.

⚠️ Edge cases handled:
- Negative inputs → we take abs() to make them positive
- GCD(0, 0) → not defined mathematically, but here it returns 0 safely
- GCD(x, 0) or GCD(0, x) → returns x as per mathematical definition

🕒 TIME COMPLEXITY: O(log(min(a, b)))
Why?
Because in each recursive step, the second number reduces roughly by half or more.

📦 SPACE COMPLEXITY: O(log(min(a, b)))
Because of recursive function stack calls.

===================================================================

💡 Example Test Cases:

Input: a = 48, b = 18
Output: 6

Input: a = -24, b = 36
Output: 12

Input: a = 0, b = 7
Output: 7

Input: a = 0, b = 0
Output: 0 (undefined mathematically, but code-safe)

===================================================================

*/
