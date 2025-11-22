/*
    📌 Problem: Reverse Words in a String
    ➤ Given a string `s` with words and possibly extra spaces, reverse the order of words.
    ➤ Remove leading/trailing spaces and reduce multiple spaces between words to a single space.

    Example:
        Input:  "  hello   world  "
        Output: "world hello"

    🔍 Solution Method: reverseWords (Reversal + Manual Word Parsing)
    ⏱ Time Complexity: O(n)
        - Reversing full string: O(n)
        - Scanning string and reversing each word: O(n)
        - Final concatenation: O(n)
    📦 Space Complexity: O(n)
        - Result string and temporary word string use linear space
    🚀 Is this optimal?: ✅ Yes, it is near-optimal and accepted by LeetCode
    🟢 LeetCode Status: ✅ Accepted (No TLE/MLE)
*/

#include <iostream>
#include<algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        // Step 1: Reverse the entire string
        // This makes the words come in reverse order, but the characters within each word are also reversed.
        reverse(s.begin(), s.end());

        string ans = "";  // To build the final result
        int n = s.length();

        // Step 2: Loop through each character to extract words
        for (int i = 0; i < n; i++) {
            string word = "";

            // Step 3: Collect a word (non-space characters)
            while (i < n && s[i] != ' ') {
                word.push_back(s[i]); // better than word+=s[i] for larger words
                i++;
            }

            // Step 4: If the word is not empty, reverse it to fix character order
            if (!word.empty()) {  // or word.length() > 0, same complexity
            reverse(word.begin(), word.end());

         // Step 5: Append the reversed word to the result with a space
         // We add space before the word and trim it later using substr
        ans += " " + word;
}

        }

        // Step 6: Return final result after removing leading space (from first " ans += " " + word ")
        return ans.substr(1);  // substr(1) removes the leading space from result
    }
};

/*
------------------------------------------
📌 Function Explanation (Line-by-Line Logic)
------------------------------------------
1. We reverse the entire input string so the last word comes first, etc.
   - Example: "hello world" → "dlrow olleh"

2. Then, we iterate over each character.
   - We build each word by skipping spaces and collecting non-space characters.

3. As we collect a word, it's reversed (since characters are reversed from step 1).
   - So we reverse the word again to restore it to correct character order.

4. We append each valid word to the answer string with a space before it.
   - We do this because it's easier to handle one leading space than many trailing ones.

5. Finally, we remove the first space from the result using `substr(1)`.

✅ This method handles:
   - Extra spaces between words
   - Leading and trailing spaces
   - Efficient parsing in O(n) time

*/


// -----------------------------
// ✅ Working Example (for testing)
// -----------------------------


int main() {
    Solution sol;

    string input = "  hello   world  ";
    string output = sol.reverseWords(input);

    cout << "Input: \"" << input << "\"" << endl;
    cout << "Output: \"" << output << "\"" << endl;

    return 0;
}

/*
----------------------
🧪 Example Execution:
----------------------

Input:  "  hello   world  "
After full reversal: "  dlrow   olleh  "
Parsing word by word (and reversing each):
    → "dlrow" becomes "world"
    → "olleh" becomes "hello"
Result: " world hello"
After substr(1): "world hello"

🟢 Output:
Input: "  hello   world  "
Output: "world hello"
*/
