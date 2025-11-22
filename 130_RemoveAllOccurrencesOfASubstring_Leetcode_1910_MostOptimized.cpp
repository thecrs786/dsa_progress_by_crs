// ✅ Leetcode Problem: Remove All Occurrences of a Substring
// https://leetcode.com/problems/remove-all-occurrences-of-a-substring/
// 🔹 Given two strings `s` and `part`, repeatedly remove all occurrences of `part` from `s`
// until `part` no longer exists in `s`. Return the final modified string.

// 🔹 Solution Name: Iterative Erase using find()
// 🔹 Time Complexity: O(N * M) 
//     → N = size of s, M = size of part
//     → Worst case: each erase triggers a full scan using find() which is O(N), and we do it up to N times
// 🔹 Space Complexity: O(1) extra (modifying `s` in-place, no additional allocations)
// 🔹 Status: ✅ Accepted on LeetCode
// 🔹 Optimality: Yes, for standard constraints. May not be optimal for huge inputs (use KMP/Z-algo in that case)
// 🔹 No TLE or MLE expected in practice due to in-place modifications and efficient string implementation in C++

// ----------------------------------------
// ✅ Function: removeOccurrences
// ----------------------------------------

#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
    string removeOccurrences(string s, string part) {
        // Continue removing until part is no longer found
        // Condition 1: s.length() > 0 → string is not empty
        // Condition 2: s.find(part) < s.length() → part found within the bounds

        while (s.length() > 0 && s.find(part) < s.length()) {
            // STEP 1: Locate the index of first occurrence of `part` in `s`
            size_t fidx = s.find(part);  // returns the first index of part

            // NOTE: If `part` is not found, s.find() returns string::npos
            // string::npos is defined as a very large value (usually 2^64 - 1)
            // So fidx < s.length() ensures that a valid index was found

            // STEP 2: Erase the substring from index `fidx` of length `part.length()`
            // This removes one full occurrence of `part`
            s.erase(fidx, part.length());
        }

        // Once all occurrences are removed, return the final string
        return s;
    }
};

// ----------------------------------------
// ✅ Working Example and Output Analysis
// ----------------------------------------



int main() {
    Solution sol;
    string s = "daabcbaabcbc";
    string part = "abc";

    string result = sol.removeOccurrences(s, part);
    cout << "Final String after removing all occurrences: " << result << endl;

    return 0;
}

/*
----------------------------------------
🧠 FULL LOGIC EXPLAINED:
----------------------------------------

1. We are given a string `s` and a substring `part`.
2. The task is to remove **all** occurrences of `part` from `s`, even if after one removal, more `part` substrings are formed.
3. The `.find(part)` function scans the string from start to finish and returns:
   - The **index of first occurrence** of `part` in `s`
   - If `part` does not exist, it returns a **huge value** (called `string::npos`) — this value is implementation-defined but usually = `18446744073709551615` on 64-bit systems (i.e., `2^64 - 1`)
4. The condition `s.find(part) < s.length()` ensures we **don’t try to erase** when `part` isn’t found.
   - Because `string::npos` is always greater than any possible valid index
5. The `.erase(fidx, part.length())` deletes the whole substring `part` starting from the found index
   - For example: if s = "daabcbaabcbc" and part = "abc"
     - First find() returns index 2
     - We erase 3 characters starting from index 2 → becomes "daabcbc"
     - On next loop: find("abc") = index 3 → erase again
     - Becomes "dabc" → final erase gives "dab"
6. This continues until `.find(part)` fails to find a match → loop exits
7. We return the final modified string

----------------------------------------
🔍 Example Execution Trace:
----------------------------------------

Initial string: "daabcbaabcbc"
part to remove: "abc"

1st iteration:
  find("abc") → index 2
  erase from index 2, length 3 → "daabcbc"

2nd iteration:
  find("abc") → index 3
  erase from index 3, length 3 → "dabc"

3rd iteration:
  find("abc") → index 1
  erase from index 1, length 3 → "dab"

4th iteration:
  find("abc") → not found → s.find(part) = string::npos
  exits loop

Final result = "dab"

----------------------------------------
🧪 Output:
Final String after removing all occurrences: dab

*/
