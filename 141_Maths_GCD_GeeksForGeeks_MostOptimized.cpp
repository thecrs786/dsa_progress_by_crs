#include<iostream>
using namespace std;

// ✅ GCD using Euclid's Algorithm
// This is the most efficient and accepted method (used even in STL __gcd)
// Time Complexity: O(log(min(a,b)))
// Space Complexity: O(1)

int gcd(int m, int n) {
    // ✅ Loop continues until one number becomes zero
    while (m > 0 && n > 0) {
        // 🔁 Key idea: Replace the larger number with its remainder when divided by the smaller one
        // If m is greater, reduce m
        if (m > n) {
            m = m % n;
        }
        // If n is greater or equal, reduce n
        else {
            n = n % m;
        }
    }

    // 📌 At this point, one number is 0, and the other is the GCD
    if (m == 0) return n;
    return m;
}

int main() {
    int a, b;
    cout << "Enter two numbers separated by a space: ";
    cin >> a >> b;
    cout << "GCD of these two numbers is: " << gcd(a, b) << endl;
    return 0;
}


/*
--------------------------------------------
📘 FULL EXPLANATION (Brutal, Raw, Precise)
--------------------------------------------

🔥 What is GCD?

The GCD (Greatest Common Divisor) of two integers is the largest number that divides both of them without leaving a remainder.
Example: GCD(20, 28) = 4

---------------------------------------------
🚀 Why does GCD(a, b) == GCD(min(a, b), abs(a - b))?
---------------------------------------------

This is a core principle of Euclid’s algorithm:

Let a > b:
- Any number that divides both a and b will also divide (a - b).
- Because: a = k1*d, b = k2*d => (a - b) = (k1 - k2)*d ⇒ d divides (a - b)
- So: GCD(a, b) == GCD(b, a-b)

This can be repeated:
GCD(a, b) = GCD(b, a - b)
         = GCD(a - b, b - (a - b)) 
         = ... until one is 0

Eventually, this leads to:
👉 GCD(a, b) = GCD(smaller, remainder)

But subtracting many times is slow — that’s where `%` helps.

---------------------------------------------
🧠 Why use `a % b` instead of subtraction?
---------------------------------------------

Because:
- Doing `a - b` repeatedly is slow
- Instead of subtracting `b` from `a` many times,
  do: `a % b` → directly gives what's left after maximum subtraction

Example:
a = 20, b = 6
→ 20 % 6 = 2  (which is same as 20 - 6 - 6 - 6 = 2)

This reduces `a` in fewer steps.
So:
- `a % b` is optimized subtraction
- Loop becomes logarithmic in time, not linear

---------------------------------------------
🔁 Loop Logic
---------------------------------------------

while (m > 0 && n > 0):
- Keep reducing the bigger number using `%` with the smaller one
- When one becomes 0, the other is the GCD

if (m > n) m = m % n
- If m is bigger, shrink it to its remainder w.r.t n

else n = n % m
- If n is bigger (or equal), shrink it to its remainder w.r.t m

This loop reduces the pair (m, n) rapidly, like:
→ (20, 28) → (20, 8) → (4, 8) → (4, 0)

---------------------------------------------
🧮 Example Dry Run: GCD(20, 28)
---------------------------------------------

m = 20, n = 28

→ m < n → n = n % m = 28 % 20 = 8
Now: m = 20, n = 8

→ m > n → m = m % n = 20 % 8 = 4
Now: m = 4, n = 8

→ m < n → n = n % m = 8 % 4 = 0
Now: m = 4, n = 0 → return m = 4 ✅

---------------------------------------------
⏱️ Time Complexity
---------------------------------------------

- Each iteration reduces the larger number using modulo
- That’s a log-scale reduction → O(log(min(a,b)))
- Much faster than brute-force (which is O(min(a,b)))

---------------------------------------------
🛑 Edge Case Handling (Optional Enhancements)
---------------------------------------------

If required, you can safely add:
```cpp
m = abs(m); n = abs(n);  // For negative inputs
if (m == 0 && n == 0) return 0;  // Undefined, but safe fallback

*/