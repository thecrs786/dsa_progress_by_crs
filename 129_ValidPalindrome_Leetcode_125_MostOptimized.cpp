// 🔍 PROBLEM: Valid Palindrome (LeetCode)
// ❓ Given a string, determine if it is a palindrome,
// ignoring non-alphanumeric characters and case sensitivity.
//
// ✅ Example:
// Input:  "A man, a plan, a canal: Panama"
// Output: true

// 🧠 METHOD USED: Two Pointer Approach (Most Optimal)
// ⏱ TIME COMPLEXITY: O(n) — one full pass through the string
// 🧠 SPACE COMPLEXITY: O(1) — no extra space used
// ✅ LeetCode Accepted: YES
// 🚫 TLE: No chance | 🚫 MLE: No chance

// 📌 Built-in functions used:
// 🔹 `isalnum(char)` → returns true if character is alphanumeric [a-z, A-Z, 0–9]
// 🔹 `tolower(char)` → converts an uppercase letter to lowercase (if it's already lowercase, returns same), and RETURNS the character's ASCII in `int` form

// ⚠️ tolower() returns ASCII value of lowercase character
// Example:
// tolower('A') = 97 → which is 'a' (ASCII of 'a' is 97)
// tolower('a') = 97
// tolower('3') = 51 → no change for digits, just ASCII returned

/* 
   char k = tolower('L');  // Now k = 'l'

   Explanation:
   The tolower() function returns the lowercase equivalent of a character.
   Since it returns an int (ASCII value), assigning it to a char automatically
   converts it to the corresponding character.

   For example:
   tolower('L') returns 108 (ASCII of 'l'), so:
   char k = 108 → k stores the character 'l'
*/


#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {

        // 🔁 Two pointers from both ends
        int start = 0;
        int end = s.length() - 1;

        while (start < end) {

            // 🧼 Ignore non-alphanumeric chars from the left
            if (!isalnum(s[start])) {
                start++;
                continue;
            }

            // 🧼 Ignore non-alphanumeric chars from the right
            if (!isalnum(s[end])) {
                end--;
                continue;
            }

            // 🔡 Compare characters after converting to lowercase
            // tolower ensures 'A' == 'a' etc.
            if (tolower(s[start]) != tolower(s[end])) {
                return false; // ❌ Not a palindrome
            }

            // ✅ Move both pointers inward
            start++;
            end--;
        }

        // ✅ If loop ends, it's a valid palindrome
        return true;
    }
};

// 🧪 Example usage
int main() {
    Solution sol;
    
    string test1 = "A man, a plan, a canal: Panama";
    string test2 = "race a car";
    string test3 = "12321";
    string test4 = "No 'x' in Nixon";

    cout << boolalpha; // prints true/false instead of 1/0
    cout << "Test 1: " << sol.isPalindrome(test1) << endl;  // true
    cout << "Test 2: " << sol.isPalindrome(test2) << endl;  // false
    cout << "Test 3: " << sol.isPalindrome(test3) << endl;  // true
    cout << "Test 4: " << sol.isPalindrome(test4) << endl;  // true

    return 0;
}

/*
────────────────────────────────────────────────────
🧠 LOGIC EXPLANATION:

1. We want to compare characters from both ends of the string and move towards the center.
2. We skip any character that is not alphanumeric (using isalnum).
3. While comparing, we make sure to normalize the case using tolower so that 'A' and 'a' are treated the same.
4. If any pair doesn't match → immediately return false.
5. If the loop completes → all characters matched → return true.

This approach is most optimal:
✅ O(n) time because each character is visited at most once.
✅ O(1) space because we don’t create new strings or use extra data structures.
✅ No edge cases missed because we skip invalid characters and normalize all cases.

🚀 This is the exact logic used in most editorial or top-voted LeetCode submissions.
────────────────────────────────────────────────────
*/
