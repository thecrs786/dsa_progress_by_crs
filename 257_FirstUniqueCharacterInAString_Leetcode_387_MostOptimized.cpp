#include <iostream>
#include <unordered_map>
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
Method Name: Two-pass Hash Map
- First pass: Count the frequency of each character using an unordered_map.
- Second pass: Iterate over the string and return the index of the first character with frequency 1.
- If no such character exists, return -1.

Time Complexity:
----------------
- O(n), where n = length of string
- Two passes over the string, but overall linear time

Space Complexity:
-----------------
- O(1) practically (only 26 lowercase letters), or O(k) in generalized case

Optimality:
------------
- This is considered the standard and optimized solution for this problem.
- Will be accepted on LeetCode; does not cause TLE or MLE.

*/

class Solution {
public:
    // Function to find first unique character's index
    int firstUniqChar(string s) {
        unordered_map<char, int> m; // map to store frequency of each character
        int n = s.length();         // length of string
        int i = 0;

        // First pass: count frequency of each character
        while(i < n) {
            m[s[i]]++;   // increment count of current character
            i++;
        }

        // Second pass: find first character with frequency 1
        i = 0;
        while(i < n) {
            if(m[s[i]] == 1) { // check if this character is unique
                return i;      // return its index
            }
            i++;
        }

        return -1; // no unique character found
    }
};

/*
Logic & Explanation:
--------------------
1. Why unordered_map:
   - Allows O(1) insertion and lookup per character
   - Efficiently stores counts of each character in string

2. First pass:
   - Iterate over string s
   - Increment count of each character in map
   - Step ensures we know frequency of all characters

3. Second pass:
   - Iterate again over string s
   - Check map for frequency of current character
   - First character with count 1 is the answer
   - Return its index immediately

4. If no character has frequency 1:
   - Return -1

5. Why this works:
   - First pass ensures we have all counts
   - Second pass ensures we return **first unique character**
   - Time complexity remains O(n)

6. Key insights:
   - Using unordered_map avoids O(n^2) brute-force comparisons
   - Two-pass approach is simple and readable
   - Space is minimal (constant for lowercase English letters)
*/

int main() {
    Solution sol;

    string s1 = "leetcode";
    string s2 = "loveleetcode";
    string s3 = "aabb";

    cout << "First unique in '" << s1 << "': " << sol.firstUniqChar(s1) << endl; // Expected: 0
    cout << "First unique in '" << s2 << "': " << sol.firstUniqChar(s2) << endl; // Expected: 2
    cout << "First unique in '" << s3 << "': " << sol.firstUniqChar(s3) << endl; // Expected: -1

    return 0;
}

/*
Key Insights, Warnings & Similar Questions:
-------------------------------------------
1. Key Insights:
   - Using a hash map allows counting in O(n)
   - Two-pass approach ensures first unique character is returned
   - Works efficiently for large strings up to 10^5 characters

2. Warnings:
   - Do not try to check uniqueness with nested loops → O(n^2) brute-force
   - unordered_map insertion and lookup are amortized O(1), not strictly guaranteed

3. Similar Questions & Approaches:
   - LeetCode 387 variants: First Unique Character in a Stream
     - Use queue + map for real-time streaming (one-pass)
   - LeetCode 136: Single Number (finding unique element using XOR)
   - Can extend to find first k unique characters using similar map + queue approach
*/
