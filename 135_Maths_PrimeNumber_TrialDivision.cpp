#include <iostream>
#include <cmath>
using namespace std;

/*
    PRIME CHECK USING √n METHOD — CLEAN & EFFICIENT

    ✔ Definition:
      A prime number is a number greater than 1 that has no divisors other than 1 and itself.

    ✔ Brute force idea:
      Loop from 2 to n-1 and check if n is divisible by any number.
      → But that's O(n), too slow for large numbers.

    ✔ Optimization — Why √n?
      If a number `n` is divisible by a number `a`, then there must exist a pair `b` such that:
          a * b = n
      
      Now, if both a and b were > √n, then:
          a * b > √n * √n = n  ❌ (this contradicts a * b = n)

      So:
        → At least one of the divisors must be ≤ √n.
        → That means if n is divisible by anything, we will definitely find it by checking up to √n.

      This reduces the time complexity from O(n) → O(√n)

    ✔ Space Complexity:
      Constant, O(1)
*/

bool isPrime(int n) {
    if (n <= 1) return false; // 0 and 1 are not prime numbers

    // Loop from 2 to √n and check for any divisor
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0)
            return false; // Found a divisor other than 1 and n, so not prime
    }

    return true; // No divisors found, so it's a prime number
}

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    if (isPrime(num))
        cout << num << " is a prime number.\n";
    else
        cout << num << " is NOT a prime number.\n";

    return 0;
}

/*
    ✅ Example:

    Input:
    Enter a number: 49

    Output:
    49 is NOT a prime number.

    Explanation:
    - sqrt(49) = 7
    - We check divisibility from i = 2 to 7
    - 49 % 7 == 0 → Divisible → Not a prime

----------------------------------------------------

    ✅ Key Takeaways:

    ✔ Works up to 10^7 - 10^8 easily
    ✔ Best method for checking primality of a single number
    ✔ Essential for coding interviews and DSA rounds
    ✔ No unnecessary checks or optimizations unless needed
    ✔ If you need to check many numbers, use the Sieve of Eratosthenes (O(n log log n))

----------------------------------------------------
*/
