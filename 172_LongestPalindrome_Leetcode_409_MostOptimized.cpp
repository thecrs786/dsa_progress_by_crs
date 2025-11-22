/*
====================================================================
    LEETCODE PROBLEM 409: Longest Palindrome
====================================================================
📌 Problem Brief:
    Given a string s, return the length of the longest palindrome 
    that can be built with those characters.
    Characters are case-sensitive ('A' ≠ 'a').

Example:
    Input: s = "abccccdd"
    Output: 7
    Explanation: One possible longest palindrome is "dccaccd", 
    which has length 7.

====================================================================
    METHOD NAME:
    "Hashing (Frequency Count) + Even/Odd Frequency Handling"

    TIME COMPLEXITY: O(n)
    SPACE COMPLEXITY: O(k), where k is the number of unique chars 
                      (at most 128 for ASCII)
====================================================================
    WILL IT BE ACCEPTED? 
    ✅ YES, passes all constraints on LeetCode.
    ❌ No MLE or TLE risk — extremely lightweight.

    IS IT MOST OPTIMAL? 
    ✅ YES — O(n) time with minimal space overhead.

====================================================================
    KEY CONCEPTS USED:
    1. HASHING with unordered_map<char,int> to count character 
       frequencies.
    2. Odd & even frequency handling for palindrome building.
    3. Using m[c]++ works even for new keys: if key not present, 
       unordered_map default-initializes value to 0, then increments.
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> m; // char freq map

        int n = s.length();
        if (n == 1) return 1; // Single char string is always palindrome length 1

        // STEP 1: Count frequency of each character
        for (int i = 0; i < n; i++) {
            m[s[i]]++; 
            // 🔹 m[s[i]]++ works even if s[i] is not in map yet:
            //    unordered_map will insert {s[i], 0} by default, then increment to 1
        }

        int even = 0; // total count of chars with even contribution
        int odd = 0;  // number of characters that have odd freq

        // STEP 2: Process each frequency
        for (auto &p : m) {
            int val = p.second;
            if (val % 2 == 0) {
                even += val; // full contribution from even count
            } else {
                odd++;           // we have at least one odd character
                even += val - 1; // contribute largest even part of the odd freq
            }
        }

        // STEP 3: Build the result length
        // If we had any odd frequency char, we can put exactly one odd char in the center
        if (odd >= 1) return even + 1;
        else return even;
    }
};

/*
====================================================================
    LOGIC EXPLAINED BRUTALLY:
====================================================================
1. We count character frequencies using hashing (unordered_map).
   - Hash table allows O(1) avg insert/lookup per character.
   - Keys = characters, Values = counts.

2. Palindrome property:
   - Characters with even counts can be fully used.
   - Characters with odd counts: we can use (count-1) of them 
     (to make them even), but only one character with odd count 
     can be placed in the middle.

3. Even/Odd case breakdown:
   - EVEN count: contributes all letters to palindrome.
   - ODD count: contributes (count-1) to keep things symmetric.
                We also note "odd++" so we can later add 1 
                if at least one odd exists (center char).

4. Final answer:
   - If odd >= 1 → length = even + 1 (for center char)
   - Else → length = even (perfect symmetry, no center odd needed)

====================================================================
    KEY SIGHTS:
====================================================================
- Using unordered_map instead of fixed array is slightly slower 
  but handles all possible characters (ASCII + Unicode if needed).
- m[key]++ default-inits missing keys with 0, saves manual checks.
- In competitive programming, we can use int freq[128] for pure 
  ASCII and get faster performance.
- Hashing here is just mapping each char to its frequency.

====================================================================
    WORKING EXAMPLE:
====================================================================
Example: s = "abccccdd"

Step 1: Count frequencies
    a → 1
    b → 1
    c → 4
    d → 2

Step 2: Process:
    a: odd → even += 0, odd++
    b: odd → even += 0, odd++
    c: even → even += 4
    d: even → even += 2

even = 6, odd = 2 → final length = 6 + 1 = 7

====================================================================
*/

int main() {
    Solution sol;

    // Example test cases
    vector<string> tests = {
        "abccccdd", // expected 7
        "a",        // expected 1
        "ccc",      // expected 3
        "abc",      // expected 1
        "Aa"        // expected 1 (case sensitive)
    };

    for (auto &t : tests) {
        cout << "Input: " << t 
             << " -> Longest Palindrome Length: " 
             << sol.longestPalindrome(t) << "\n";
    }

    return 0;
}
