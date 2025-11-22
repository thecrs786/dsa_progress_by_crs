/*
    ✅ LeetCode Problem: Count Primes
    ---------------------------------
    ❓ Question (in brief):
       - Count the number of prime numbers strictly less than a given number `n`.*/
    

#include <iostream>
#include <vector>
using namespace std;

/*
    ✅ Method Used: Sieve of Eratosthenes
    -------------------------------------
    - This is a classic and efficient algorithm to find all prime numbers in a range [2, n)
    - Time-efficient due to bulk marking of non-prime numbers

    ✅ Time Complexity: O(n log log n)
    ✅ Space Complexity: O(n)
    ✅ Optimality:
       - This is the most optimal known method for generating primes up to `n` in bulk.
       - Further space optimization (like using bitsets or skipping evens) possible, but this version is clean and efficient.
    ✅ Accepted by LeetCode:
       - ✅ No TLE (Time Limit Exceeded)
       - ✅ No MLE (Memory Limit Exceeded)
       - Efficient for `n` up to 5 * 10^6 on LeetCode
*/

class Solution {
public:
    int countPrimes(int n) {
        // Step 1: Create a boolean vector `isPrime` to mark prime status for each number from 0 to n
        // We allocate size (n+1) to safely index from 0 to n (inclusive), even though we'll only count up to n-1
        vector<bool> isPrime(n + 1, true);
        int ans = 0;

        // Step 2: Handle base cases: 0 and 1 are not prime
        if (n > 0) isPrime[0] = false;
        if (n > 1) isPrime[1] = false;

        // Step 3: Start checking from i = 2 up to n-1 (since the question asks primes < n)
        for (int i = 2; i < n; i++) {
            // If i is still marked prime
            if (isPrime[i]) {
                ans++; // It's a prime number, so count it

                // Step 4: Mark all multiples of i as not prime
                // Why start from i*2?
                // Because i*1 = i (which is prime), we start eliminating at i*2
                for (int j = i * 2; j < n; j += i) {
                    isPrime[j] = false; // Mark composite
                }
            }
        }

        // Step 5: Return the total count of primes less than n
        return ans;
    }
};

/*
    ✅ Logic Explained (in depth):
    -----------------------------
    - Prime number definition: A number greater than 1 with no positive divisors other than 1 and itself.
    - The Sieve of Eratosthenes marks all multiples of a prime number as not prime.
    - We only start from 2, since 0 and 1 are known to be not prime.
    - Whenever we find a number `i` that is still marked as true in `isPrime`, we know it's a prime.
    - We then eliminate all of its multiples starting from `i*2` (because `i` itself is prime).
    - By the end of the loop, all composite numbers have been marked false.
    - We count the total number of indices from [2, n) that are still true.

    ✅ Why this works:
    -----------------
    - Every composite number has at least one prime factor.
    - So every composite number will eventually be marked false when we reach its smallest prime factor.
    - This avoids redundant checks and gives O(n log log n) performance.
*/

/*
    ✅ Working Example:

    Let's check primes less than 10:
    Input: n = 10
    Primes < 10 are: 2, 3, 5, 7 → Count = 4

    We can test this below using main():
*/

int main() {
    Solution sol;
    int n = 10;
    cout << "Total primes less than " << n << ": " << sol.countPrimes(n) << endl;

    return 0;
}

/*
    ✅ Output:
    ----------
    Total primes less than 10: 4

    ✅ Flow:
    -------
    isPrime[] initially:
    [T, T, T, T, T, T, T, T, T, T, T]
     0  1  2  3  4  5  6  7  8  9 10

    After sieve:
    [F, F, T, T, F, T, F, T, F, F, ...]

    Count of T in [2 to 9] = 4 → correct

-------------------------------------------------------
    ✅ Final Verdict:
    - This is the most optimal and clean solution for this problem.
    - Handles edge cases, is space-safe, and gets accepted on LeetCode.
-------------------------------------------------------
*/
