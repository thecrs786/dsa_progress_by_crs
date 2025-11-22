/*
=========================================================================
    LEETCODE PROBLEM 58: Length of Last Word
=========================================================================
📌 Problem Brief:
    Given a string s consisting of words and spaces, return the length 
    of the last word in the string. A word is a maximal substring 
    consisting of non-space characters only.

Example:
    Input: "   fly me   to   the moon  "
    Output: 4
    Explanation: The last word is "moon", which has length 4.

=========================================================================
    METHOD NAME:
    "Reverse Iteration + Counting"

    TIME COMPLEXITY: O(n) — single pass from end to start
    SPACE COMPLEXITY: O(1) — no extra storage used

    WILL IT BE ACCEPTED? ✅ Yes, no TLE/MLE risk
    IS IT MOST OPTIMAL? ✅ Yes, minimal time & space usage

=========================================================================
    KEY CONCEPTS:
    1. Iterate from the end to skip trailing spaces.
    2. Count characters until hitting the space before the last word.
    3. Edge cases handled:
        - String ends with spaces
        - String has only one word
        - String has multiple spaces between words
=========================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0; // Counter for letters in last word

        // Traverse string from the end
        for(int i = s.length() - 1; i >= 0; i--) {
            if(s[i] == ' ' && count == 0) continue; // Skip trailing spaces
            else if(s[i] == ' ') break;             // End of last word
            else count++;                            // Count letters
        }

        return count; // Return length of last word
    }
};

/*
=========================================================================
    LOGIC & FUNCTION WORKING:
=========================================================================
1. Start from the last index and move backwards.
2. Skip all trailing spaces first.
3. Once a non-space character is found, start counting.
4. If a space is encountered after counting started, break — the last 
   word is fully counted.
5. Return the count.

=========================================================================
    EXAMPLES WALKTHROUGH:
=========================================================================
Input: "Hello World  "
    - Start from end: skip spaces
    - Count 'd', 'l', 'r', 'o', 'W' → count = 5
    - Space encountered → break
    Output: 5

Input: "a"
    - Only one character, count = 1
    Output: 1

Input: "   fly me   to   the moon  "
    - Skip trailing spaces
    - Count 'n', 'o', 'o', 'm' → count = 4
    - Space encountered → break
    Output: 4

=========================================================================
    IMPORTANT DETAILS / KEY SIGHTS:
=========================================================================
- No need to split string or use additional storage.
- Backward traversal efficiently handles trailing spaces.
- O(1) space ensures optimal memory usage.
- Works for all edge cases including single-letter words.
- Extremely readable and maintainable for revision.
=========================================================================
*/

int main() {
    Solution sol;

    vector<string> tests = {
        "Hello World",                  // Expected: 5
        "a",                             // Expected: 1
        "   fly me   to   the moon  ",  // Expected: 4
        " day",                          // Expected: 3
        "   a   "                        // Expected: 1
    };

    for(auto &s : tests) {
        cout << "Input: \"" << s << "\" -> Length of Last Word: " 
             << sol.lengthOfLastWord(s) << "\n";
    }

    return 0;
}
