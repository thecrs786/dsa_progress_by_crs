// 💡 LeetCode Problem: String Compression
// Problem Statement (brief):
// Given an array of characters `chars`, compress it **in-place**.
// Replace sequences of the same character by the character followed by the count.
// Return the new length after compression.
// Example: ['a','a','b','b','c','c','c'] → ['a','2','b','2','c','3']

// 🔧 Solution Name: Two-pointer In-place Compression using Index Tracking

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();      // Total number of characters
        int idx = 0;               // Write index for final compressed result

        // We traverse the array using index 'i'
        for (int i = 0; i < n; i++) {
            char ch = chars[i];    // Current character being processed
            int count = 0;         // Counter for how many times this char appears consecutively

            // Count the occurrences of the current character
            while (i < n && chars[i] == ch) {
                count++;
                i++;
            }

            // Step back by one to allow outer loop's i++ to land correctly
            i--;

            // Write the character to the compressed result
            chars[idx++] = ch;

            // If count > 1, convert count to string and add its digits one by one
            if (count > 1) {
                string str = to_string(count);  // 🔄 Converts an integer to a string (e.g., 12 → "12")
                for (char digit : str) {
                    chars[idx++] = digit;       // Add each digit of the count into chars
                }
            }
            // If count == 1, we already wrote just the character above
        }

        // Resize the array to remove trailing characters from original input
        // 🧹 Optional for LeetCode since only length is returned, but ensures array is clean for debugging
        chars.resize(idx);

        return idx; // Final length of compressed array
    }
};

/*
📘 Explanation of Key Concepts:

1. to_string(count):
   - Converts an integer (like 12) into its string representation ("12") so we can
     access each digit individually and store it in the char array.

2. chars.resize(idx):
   - Removes all characters beyond the compressed size `idx`.
   - Not mandatory for LeetCode since it only expects the length,
     but it's good practice for memory cleanliness and when testing/debugging locally.

3. Why idx++ is used:
   - We use `idx` as a separate write pointer to insert the compressed characters from left to right.
   - It prevents overwriting characters that we still need to process.

4. Why we use `i--` after the inner while:
   - The inner while loop ends **after** the last repeating character.
   - But the outer `for` loop also does an `i++`, which would skip the next character.
   - So we backtrack one step to avoid skipping the next group.

🧠 Logic Summary:
- Traverse the input from left to right.
- For each group of same characters, count how many times it appears.
- Add the character once.
- If the count > 1, convert the count into string and add each digit.
- Keep writing the result to the same array using a separate index (`idx`).
- Return `idx` as the new compressed length.

⏱️ Time Complexity: O(n)
- Each character is visited only once, and written once.

📦 Space Complexity: O(1)
- No extra space used other than variables. Everything is done in-place.

✅ Will this pass LeetCode?
- YES. It’s accepted and **most optimized** for the given constraints.
- No chance of TLE or MLE since time is linear and space is constant.

*/

int main() {
    vector<char> chars = {'a','a','b','b','c','c','c'};
    Solution sol;
    int newLength = sol.compress(chars);

    cout << "Compressed Length: " << newLength << endl;
    cout << "Compressed Array: ";
    for (int i = 0; i < newLength; ++i) {
        cout << chars[i] << ' ';
    }
    cout << endl;

    // Example Output:
    // Compressed Length: 6
    // Compressed Array: a 2 b 2 c 3
}
