/*
------------------------------------
🔎 LeetCode Problem: Permutation in String
------------------------------------
📌 Problem Summary:
Given two strings `s1` and `s2`, return true if `s2` contains a permutation of `s1`, else return false.
In other words, check if a substring of `s2` is an anagram of `s1`.

✅ Function Used: Sliding Window (Optimized Incremental Updates)

------------------------------------
🕒 Time Complexity:
Let M = length of s1, N = length of s2

🔹 Building the frequency array of s1 → O(M)
🔹 Initializing the first window in s2 → O(M)
🔹 Sliding the window across s2:
   - Update frequencies in O(1) per move (only one char leaves, one char enters)
   - Compare frequencies in O(26) = O(1)
🔹 Total: O(N * 26) → effectively O(N)

👉 This is **optimal** for fixed alphabet size (26 lowercase letters).

------------------------------------
🧠 Space Complexity:
- O(1): Two fixed-size frequency arrays of size 26 (constant space)
------------------------------------
🔥 Is this the Most Optimal?
✅ Yes. This uses a true sliding window with incremental updates.
No extra passes over each substring, no nested O(M) loops.

------------------------------------
💥 Will it be Accepted?
✅ YES → Accepted in **fastest possible complexity** for this problem.
------------------------------------
*/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:

    // 📦 Utility Function: Compares two frequency arrays of 26 characters
    // This checks if both windows (s1 and current window in s2) have exact same char count
    bool isFreqSame(int freq1[], int freq2[]){
        for(int i = 0; i < 26; i++){
            if(freq1[i] != freq2[i]){
                return false; // ❌ Frequencies differ → Not a permutation
            }
        }
        return true; // ✅ All counts match → Valid permutation
    }

    // 🧠 Core Function: checkInclusion
    bool checkInclusion(string s1, string s2) {
        // ⚠️ Edge case: If s1 is longer than s2, s2 cannot contain a permutation of s1
        if(s1.size() > s2.size()) return false;

        // Step 1: Build frequency count of s1
        int freq[26] = {0};  // freq[i] stores count of (i + 'a') in s1
        for(char ch : s1){
            freq[ch - 'a']++;  // Increment the count for this letter
        }

        // Step 2: Build frequency count of the first window in s2
        int windowfreq[26] = {0};
        for(int i = 0; i < s1.length(); i++){
            windowfreq[s2[i] - 'a']++; // Count each letter in the first window
        }

        // Step 3: If the first window matches → Permutation found
        if(isFreqSame(freq, windowfreq)) return true;

        // Step 4: Sliding the window over s2
        // "end" is the index of the new char entering the window
        // "start" is the index of the char leaving the window
        int start = 0;
        for(int end = s1.length(); end < s2.length(); end++){
            // Remove frequency of the outgoing char
            windowfreq[s2[start] - 'a']--;
            // Add frequency of the incoming char
            windowfreq[s2[end] - 'a']++;
            start++;

            // After updating, check if frequencies match
            if(isFreqSame(freq, windowfreq)) return true;
        }

        // Step 5: No window matched → return false
        return false;
    }
};

/*
------------------------------------
🧠 FULL LOGIC EXPLANATION:

1️⃣ GOAL:
   We want to see if any substring in `s2` has the **same characters in the same counts** as `s1`.
   If yes → that substring is a permutation (anagram) of `s1`.

2️⃣ CHARACTER COUNTING:
   - We create an array `freq[26]` for `s1` where each index 0–25 represents 'a'–'z'.
   - Example: if s1 = "ab", then freq[0] = 1, freq[1] = 1, rest = 0.

3️⃣ FIRST WINDOW:
   - Take the first `s1.length()` characters of `s2` and count them into `windowfreq[26]`.
   - This is our initial "window".

4️⃣ COMPARISON:
   - If at any point `windowfreq` matches `freq` → We found a permutation → return true.

5️⃣ SLIDING WINDOW OPTIMIZATION:
   - Instead of recalculating the whole frequency for each new window:
     - Decrease count for the char leaving the window (at index `start`)
     - Increase count for the char entering (at index `end`)
   - This makes each move O(1), only requiring a 26-char check for equality.

6️⃣ END CONDITION:
   - If we finish sliding through `s2` without finding a match → return false.

------------------------------------
🔁 Example Test Case:
s1 = "ab"
s2 = "eidbaooo"

Step-by-step:
- s1 freq: [1(a), 1(b), 0, ..., 0]
- First window "ei": freq → no match
- Slide:
  "id": no match
  "db": no match
  "ba": ✅ match (freq matches s1)

Return true.

------------------------------------
✅ OUTPUT:
Permutation Found ✅
Because "ba" in "eidbaooo" is a valid permutation of "ab"
------------------------------------
*/

int main() {
    Solution sol;

    string s1 = "ab";
    string s2 = "eidbaooo";

    bool result = sol.checkInclusion(s1, s2);

    cout << (result ? "Permutation Found " : "No Permutation ") << endl;

    return 0;
}
