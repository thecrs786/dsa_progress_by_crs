/*
──────────────────────────────────────────────────────────────────────────────
📌 PROBLEM: Reverse String
──────────────────────────────────────────────────────────────────────────────
🔸 LeetCode Link: https://leetcode.com/problems/reverse-string/
🔸 You are given a character array `s`. Reverse the array **in-place**.
🔸 Do not return anything from the function. You must modify the input array directly.

──────────────────────────────────────────────────────────────────────────────
📌 METHOD: Two-Pointer Approach
──────────────────────────────────────────────────────────────────────────────
🔹 Time Complexity     : O(n)       → Each character is visited once
🔹 Space Complexity    : O(1)       → In-place; uses no extra memory
🔹 Is it Optimal?      : ✅ Yes, this is the most optimal solution
🔹 LeetCode Acceptance : ✅ Yes (No TLE or MLE)
*/

#include <iostream>
#include <algorithm>  // for swap()
#include <vector>
using namespace std;

// short cut (same space and time complexity as two pointer approach)

/*class Solution {
public:
    void reverseString(vector<char>& s) {
      reverse(s.begin(), s.end());
    }
};
*/

class Solution {
public:
    void reverseString(vector<char>& s) {
        // Initialize two pointers: one at the start and one at the end
        int start = 0;
        int end = s.size() - 1;

        // Loop runs until the pointers cross
        while (start < end) {
            // Swap characters at start and end indices
            swap(s[start], s[end]);

            // Move both pointers toward the center
            start++;
            end--;
        }

        /*
        ░░ WHY THIS WORKS:
        🔸 We're using two pointers to mirror elements from both ends inward.
        🔸 Each iteration swaps the ith element from the start with the ith element from the end.
        🔸 Since we're modifying in-place and using no extra memory, it meets the problem's constraints.
        */
    }
};

/*
──────────────────────────────────────────────────────────────────────────────
📌 EXAMPLE: Driver Code for Testing and Understanding
──────────────────────────────────────────────────────────────────────────────
*/

int main() {
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};

    // Print original string
    cout << "Original: ";
    for (char c : s) cout << c << " ";
    cout << endl;

    // Reverse the string
    Solution().reverseString(s);

    // Print reversed string
    cout << "Reversed: ";
    for (char c : s) cout << c << " ";
    cout << endl;

    return 0;
}

/*
──────────────────────────────────────────────────────────────────────────────
📌 FUNCTION LOGIC EXPLAINED IN DETAIL:

1. 🟩 `int start = 0; int end = s.size()-1;`
   ▪ We need two pointers to reverse a string.
   ▪ `start` begins at the front of the array, `end` begins at the back.

2. 🟩 `while (start < end)`
   ▪ This loop ensures we keep swapping until both pointers meet or cross.
   ▪ Once `start >= end`, we know we've reversed the whole array.

3. 🟩 `swap(s[start], s[end]);`
   ▪ Swaps the characters at the current `start` and `end` positions.

4. 🟩 `start++; end--;`
   ▪ Move the pointers inward, getting ready for the next pair to swap.

🔄 This continues until the entire string is reversed, character by character.

──────────────────────────────────────────────────────────────────────────────
📌 SAMPLE OUTPUT:
Original: h e l l o 
Reversed: o l l e h 
──────────────────────────────────────────────────────────────────────────────

*/
