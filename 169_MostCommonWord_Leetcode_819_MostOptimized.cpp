/*
    -----------------------------------------------------------
    LeetCode 819 - Most Common Word
    -----------------------------------------------------------

    QUESTION (BRIEF):
    - Given a paragraph (string) and a list of banned words (vector<string>),
      find the most frequent word in the paragraph that is NOT in the banned list.
    - Words are case-insensitive and consist only of letters/numbers.
    - Punctuation should be ignored.

    SOLUTION METHOD:
    - Approach: Hashing with `unordered_set` for banned words and `unordered_map` for frequency counting.
    - Steps:
        1. Store banned words in an `unordered_set` for O(1) lookup.
        2. Iterate through the paragraph character-by-character, building words.
        3. Normalize to lowercase while building.
        4. When a word is complete, check if it is NOT banned → increment its count in the map.
        5. After processing, find the word with maximum frequency.

    COMPLEXITY:
    - Time Complexity: O(n + b) where:
        n = length of paragraph
        b = size of banned list
    - Space Complexity: O(k + b) where:
        k = number of unique non-banned words
        b = number of banned words

    OPTIMALITY:
    - YES, this is the most optimal solution possible for the problem.
    - Both parsing and counting are done in a single pass (O(n)).
    - Lookup operations are O(1) on average due to hashing.

    LEETCODE ACCEPTANCE:
    - Will PASS without TLE (Time Limit Exceeded) or MLE (Memory Limit Exceeded).
    - Efficient for constraints given in the problem.

    IMPORTANT DETAILS:
    - `unordered_set` is used to store banned words for fast lookup.
    - `unordered_map` stores word → frequency mapping.
    - `m[word]++` works even if `word` does not exist yet because:
        * If `word` is not in the map, `unordered_map` default-constructs its value (0 for int),
          then increments it to 1.
    - Case normalization is important (all to lowercase).
    - `isalnum()` is used to detect valid word characters.

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        // Store banned words in a hash set for O(1) average lookup.
        unordered_set<string> b(banned.begin(), banned.end());

        // Frequency map: word -> count
        unordered_map<string, int> m;

        int n = paragraph.length();
        string word;

        // Iterate over each character in the paragraph
        for (int i = 0; i < n; i++) {
            word.clear(); // start fresh for each new word

            // Build a word from consecutive alphanumeric chars
            while (i < n && isalnum((unsigned char)paragraph[i])) {
                word += tolower((unsigned char)paragraph[i]); // normalize to lowercase
                i++;
            }

            /*We use unsigned char to prevent tolower from misbehaving on characters with 
            negative ASCII values (non-ASCII chars).
            Not strictly necessary for typical LeetCode inputs, but it’s a safe, portable
            practice in real-world code.
            */

            // If the word is valid (non-empty) and not banned → count it
            if (!word.empty() && b.find(word) == b.end()) {
                m[word]++; // increments even if `word` not in map yet
            }
        }

        // Find the word with the highest frequency
        string ans;
        int maxcount = 0;
        for (auto &p : m) {
            if (p.second > maxcount) {
                maxcount = p.second;
                ans = p.first;
            }
        }

        return ans;
    }
};

/*
    ------------------------------
    STEP-BY-STEP FUNCTION EXPLANATION
    ------------------------------
    1. Convert banned words to `unordered_set` b:
       - Allows O(1) lookup to check if a word is banned.
    2. Use `unordered_map` m to store frequency counts of words.
    3. Loop through paragraph character-by-character:
       - If char is alphanumeric → add lowercase version to current word.
       - If not → means word ended, so process it.
    4. Skip empty words and banned words.
    5. Increment count in map: `m[word]++` automatically creates entry if missing (starts at 0).
    6. After all words are processed → iterate over map to find max frequency word.
    7. Return that word.

    ------------------------------
    LOGIC / WORKING
    ------------------------------
    The key trick is hashing:
    - Banned words: `unordered_set` for O(1) check → no linear search needed.
    - Word frequency: `unordered_map` for O(1) insert/update.
    Parsing is done in a single pass → O(n) time.

    ------------------------------
    KEY INSIGHTS
    ------------------------------
    - Why unordered_set for banned words?
        Faster lookup (avg O(1)) vs. O(log n) for set or O(n) for vector.
    - Why unordered_map for frequencies?
        We need fast insert + update for each word.
    - How does m[word]++ work if key doesn't exist?
        The `operator[]` on unordered_map:
            1. Checks if key exists.
            2. If not → inserts it with default value (0 for int).
            3. Returns reference to value.
            4. The ++ increments from 0 to 1.
    - isalnum() ensures punctuation and spaces are skipped.
    - tolower() ensures case insensitivity.

*/

int main() {
    
    // Example to run and analyze
    string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    vector<string> banned = {"hit"};

    Solution sol;
    string result = sol.mostCommonWord(paragraph, banned);

    cout << "Most common non-banned word: " << result << endl;
    // Expected Output: "ball"
    // Explanation: "hit" is banned, "ball" appears twice (case-insensitive).

    return 0;
}
