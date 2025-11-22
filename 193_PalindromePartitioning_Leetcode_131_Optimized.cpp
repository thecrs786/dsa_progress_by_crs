/**************************************************************************************
🔹 Problem: Palindrome Partitioning (LeetCode 131)
Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitioning of s.

Example:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

**************************************************************************************

🔹 Approach: Backtracking (DFS)
We recursively explore all possible partitions of the string:
1. For every starting index, consider all substrings starting from this index.
2. Check if the substring is a palindrome.
3. If it is, include it in the current partition and recursively solve for the remaining string.
4. Use backtracking by removing the last added substring to explore other partition possibilities.

**************************************************************************************

🔹 Key Insights:
- Each recursive call represents a partitioning decision at the current start of string.
- The loop tries all possible end indices for substrings starting at the current position.
- Backtracking is done by `partitions.pop_back()` after recursive call returns.
- Palindrome check ensures only valid substrings are added.
- No DP is used here, so repeated palindrome checks occur, making it less optimized for large strings.
- Accepted by LeetCode, but not the most optimal (DP can speed up palindrome checking).

**************************************************************************************

🔹 Time Complexity:
- O(N * 2^N), where N is length of string.
  - There are 2^(N-1) possible partitions.
  - For each partition, palindrome check can take O(N) time.
- Space Complexity:
  - O(N) recursion stack depth + O(number of partitions * avg length of partitions) for result storage.

**************************************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Function to check if a given string is a palindrome
    bool ispalindrome(string s){
        int st = 0;
        int end = s.size()-1;
        while(st<=end){
            if(s[st]!=s[end]) return false; // mismatch → not palindrome
            else {st++; end--;} // move pointers inward
        }
        return true; // reached middle → palindrome
    }

    // Recursive function to generate all palindrome partitions
    void getallparts(string s, vector<string> &partitions, vector<vector<string>> &ans){
        // Base Case: if string is empty → store current partition
        if(s.length()==0){
            ans.push_back(partitions);
            return;
        }
        
        // Try all possible substrings starting from index 0
        for(int i=0; i<s.size(); i++){
            string part = s.substr(0, i+1); // substring from start to i
            if(ispalindrome(part)){         // check if substring is palindrome
                partitions.push_back(part); // include substring in current partition
                getallparts(s.substr(i+1), partitions, ans); // recurse on remaining string
                partitions.pop_back();      // backtrack → remove last substring to try next
            }
        }
    }

    // Main function
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> partitions;
        getallparts(s, partitions, ans);
        return ans;
    }
};

/**************************************************************************************
🔹 Explanation of Important Points:
1. Loop logic:
   - Iterates over possible end indices of substrings starting at index 0.
   - Generates all possible prefixes for current recursion.
2. Recursive call:
   - After adding a palindrome substring, recursion explores the rest of the string.
   - Each recursive path represents a choice of partition.
3. Backtracking:
   - After recursion returns, `pop_back()` removes last added substring.
   - Restores state for next iteration to explore new substring.
4. Palindrome checking:
   - Done using two pointers.
   - Ensures only valid palindromic substrings are included.
5. Partitioning logic:
   - Every path in recursion tree represents a sequence of palindromic substrings.
   - All valid paths are stored in `ans`.

**************************************************************************************/

int main() {
    Solution sol;
    string s = "aab";

    vector<vector<string>> result = sol.partition(s);

    cout << "Palindrome partitions of \"" << s << "\":\n";
    for (auto &vec : result) {
        cout << "[ ";
        for (string str : vec) cout << str << " ";
        cout << "]\n";
    }

    return 0;
}

/**************************************************************************************
🔹 Working Example:

Input: s = "aab"

Recursion Tree:
- Prefix "a" → palindrome → recurse on "ab"
  - Prefix "a" → palindrome → recurse on "b"
    - Prefix "b" → palindrome → recurse on "" → push ["a","a","b"]
  - Prefix "ab" → not palindrome → skip
- Prefix "aa" → palindrome → recurse on "b"
  - Prefix "b" → palindrome → recurse on "" → push ["aa","b"]
- Prefix "aab" → not palindrome → skip

Output: [["a","a","b"], ["aa","b"]]

**************************************************************************************/
