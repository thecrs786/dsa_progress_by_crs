/*
🔢 Topic: Modulo Arithmetic

👉 Why Modulo?
  - In programming, we often work with very large numbers.
  - Modulo operation keeps results within a range (typically 0 to m-1).
  - Very useful in competitive programming and number theory (especially with primes).

🧠 Key Properties of Modulo:
    For integers x, y, and modulus m:

    1. (x + y) % m = ((x % m) + (y % m)) % m
    2. (x - y) % m = ((x % m) - (y % m) + m) % m
    3. (x * y) % m = ((x % m) * (y % m)) % m

    ✅ The extra `% m` ensures result stays within [0, m-1].
    🧠 Why? Because (x % m) might still be large if not reduced.

🔎 Let's see these properties with actual examples:
*/

#include <iostream>
using namespace std;

int main() {
    int x = 17;
    int y = 23;
    int m = 5;

    // (x + y) % m
    int add_normal = (x + y) % m;
    int add_mod = ((x % m) + (y % m)) % m;

    // (x - y) % m
    int sub_normal = (x - y) % m;  // might be negative
    int sub_mod = ((x % m) - (y % m) + m) % m;  // guaranteed non-negative

    // (x * y) % m
    int mul_normal = (x * y) % m;
    int mul_mod = ((x % m) * (y % m)) % m;

    cout << "Using x = 17, y = 23, m = 5\n\n";

    cout << "(x + y) % m = " << add_normal << " | ((x % m) + (y % m)) % m = " << add_mod << endl;
    cout << "(x - y) % m = " << sub_normal << " | ((x % m) - (y % m) + m) % m = " << sub_mod << endl;
    cout << "(x * y) % m = " << mul_normal << " | ((x % m) * (y % m)) % m = " << mul_mod << endl;

    return 0;
}

/*
📘 Detailed Explanation:

1. Addition:
    x = 17, y = 23, m = 5
    x % m = 2, y % m = 3
    (x + y) = 40 → 40 % 5 = 0
    ((2 + 3) % 5) = 5 % 5 = 0 ✅

2. Subtraction:
    x = 17, y = 23
    x - y = -6 → (-6 % 5) = -1 (in C++) ❌ unsafe
    ((x % m) - (y % m) + m) % m = (2 - 3 + 5) % 5 = 4 ✅

3. Multiplication:
    x = 17, y = 23
    x * y = 391 → 391 % 5 = 1
    (2 * 3) % 5 = 6 % 5 = 1 ✅

⚠️ C++ mod (%) operator gives negative results when numerator is negative.
That's why in subtraction we always add `+ m` before `% m`.

🧠 Bottom line:
    These modulo properties are **not optional hacks**, they are based on congruence modulo m theory:
    - If a ≡ b (mod m), then a + c ≡ b + c (mod m)
    - a - c ≡ b - c (mod m)
    - a * c ≡ b * c (mod m)

That’s why we need to mod operands individually *before* combining them — this allows safe arithmetic even with huge values.
*/
