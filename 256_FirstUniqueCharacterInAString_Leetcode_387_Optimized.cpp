#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

/*
LeetCode 387: First Unique Character in a String

Problem in brief:
-----------------
Given a string s, find the first non-repeating character in it and return its index.
If it does not exist, return -1.

Example:
--------
Input: s = "leetcode"
Output: 0
Explanation: 'l' is the first character that appears only once.

Input: s = "loveleetcode"
Output: 2
Explanation: 'v' is the first unique character.

Input: s = "aabb"
Output: -1
Explanation: There is no unique character.

Constraints:
-------------
- 1 <= s.length <= 10^5
- s consists of only lowercase English letters.

Solution Approach:
------------------
Method Name: Optimized Queue + Hash Map (One-pass)
- Use a queue to store indices of characters in order of their first appearance.
- Use an unordered_map to count frequency of characters.
- For each character in the string:
    - If this is the first occurrence, push its index to the queue.
    - Increment its frequency in the map.
    - Remove indices from the front of the queue if their characters are no longer unique (frequency > 1).
- At the end:
    - If queue is empty, return -1.
    - Otherwise, return the index at the front of the queue.

Time Complexity:
----------------
- O(n), where n = length of string
  - Each character index is pushed at most once and popped at most once.

Space Complexity:
-----------------
- O(n) in worst case (all characters unique)
- Hash map stores character counts → O(1) practically (26 lowercase letters)

Optimality:
------------
- Optimized for streaming / one-pass scenarios.
- Will be accepted on LeetCode; will not cause TLE or MLE.
- For static strings, two-pass hash map solution may use slightly less memory.

*/

class Solution {
public:
    // Function to find index of first unique character
    int firstUniqChar(string s) {
        unordered_map<char, int> m; // map to count frequency of each character
        queue<int> q;               // queue to store indices of characters in order of first appearance

        // Iterate over the string
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];

            // Push index only if this is the first occurrence of character
            if(m.find(c) == m.end()) q.push(i);

            // Increment frequency of character
            m[c]++;

            // Remove indices from front whose characters are no longer unique
            while(!q.empty() && m[s[q.front()]] > 1) {
                q.pop();
            }
        }

        // If queue is empty → no unique character
        return q.empty() ? -1 : q.front();
    }
};

/*
Logic & Explanation:
--------------------
1. Why unordered_map:
   - Provides O(1) insertion and lookup for each character.
   - Essential to track character frequencies dynamically.

2. Why queue:
   - Maintains **order of first appearance**.
   - Allows efficiently accessing the first unique character at any moment.
   - Removing repeated characters ensures queue front always points to first unique.

3. How it works:
   - For each character:
     a) Check if it's the first occurrence → push index into queue.
     b) Increment frequency in map.
     c) While front character's frequency > 1 → pop from queue.
   - After iteration:
     - If queue is empty → return -1.
     - Else → front index corresponds to first unique character.

4. Why optimized:
   - Single-pass solution: counts frequencies and tracks first unique simultaneously.
   - Avoids pushing duplicate indices → fewer operations on queue.
   - Each index pushed/popped at most once → O(n) time.

5. Key insight:
   - Queue ensures **FIFO**, giving first unique character.
   - Map ensures fast frequency checking.
*/

int main() {
    Solution sol;

    string s1 = "leetcode";
    string s2 = "loveleetcode";
    string s3 = "aabb";
    string s4 = "abcabcde";

    cout << "First unique in '" << s1 << "': " << sol.firstUniqChar(s1) << endl; // Expected: 0
    cout << "First unique in '" << s2 << "': " << sol.firstUniqChar(s2) << endl; // Expected: 2
    cout << "First unique in '" << s3 << "': " << sol.firstUniqChar(s3) << endl; // Expected: -1
    cout << "First unique in '" << s4 << "': " << sol.firstUniqChar(s4) << endl; // Expected: 6

    return 0;
}

/*
Key Insights, Warnings & Similar Questions:
-------------------------------------------
1. Key Insights:
   - Queue ensures **order of appearance**.
   - Map + queue combination allows **dynamic first-unique tracking** in one pass.
   - Efficient for **streaming inputs**.

2. Warnings:
   - Always check `!q.empty()` before accessing `q.front()`.
   - Map stores frequencies; queue stores indices → maintain consistency.
   - Worst-case space O(n) if all characters are unique.

3. Similar Questions & Approaches:
   - LeetCode 387: Two-pass hash map (simpler for static strings)
   - LeetCode 136: Single Number using XOR (finding unique element)
   - First unique character in a stream → uses same queue + map one-pass method
   - Can be extended to find first k unique characters using similar technique
*/
