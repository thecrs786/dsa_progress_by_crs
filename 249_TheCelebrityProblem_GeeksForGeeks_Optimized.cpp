/*
Problem No: Celebrity Problem (Common in GeeksforGeeks and coding interviews)

Problem in brief:
Given an n x n matrix 'mat' where mat[i][j] = 1 means person 'i' knows person 'j', and 0 otherwise.
A celebrity is defined as someone:
1. Known by everyone else (i.e., for all i ≠ c, mat[i][c] = 1)
2. Knows no one else (i.e., for all j ≠ c, mat[c][j] = 0)

The task is to find the index of the celebrity if one exists, else return -1.

Example 1:
n = 3
mat = [[0, 1, 0],
       [0, 0, 0],
       [0, 1, 0]]
Output: 1
Explanation: Person 1 is known by everyone else and knows no one.

Example 2:
n = 3
mat = [[0, 1, 0],
       [0, 0, 1],
       [1, 0, 0]]
Output: -1
Explanation: There is no celebrity.

Approach name: Stack-based elimination method
Time Complexity: O(n)
Space Complexity: O(n)
Most optimal: ❌ Not most optimal because of O(n) space used by stack
Accepted on GeeksforGeeks: ✅ It will be accepted and will not cause TLE or MLE
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
  public:
    int celebrity(vector<vector<int>>& mat) {
        // code here
        stack<int> s;
        int size = mat.size();
        
        // Push all persons into the stack as potential celebrities
        for(int i=0; i<size; i++){
            s.push(i);
        }
        
        // Eliminate candidates until one remains
        while(s.size()>1){
            int num = s.top();
            s.pop();
            if(mat[num][s.top()]==0){
                // If num does not know s.top(), then s.top() cannot be celebrity
                s.pop();
                s.push(num);
            }
            // If num knows s.top(), then num cannot be celebrity, so s.top() remains
        }
        
        // Candidate celebrity
        int n = s.top();
        
        // Verify the candidate
        for(int i=0; i<size; i++){
            if(i==n) continue;
            if(mat[i][n]==0) return -1; // Someone doesn't know the candidate
            if(mat[n][i]==1) return -1; // Candidate knows someone
        }
        
        return n;
    }
};

/*
Logic Explanation (Detailed):

1. Problem Redefinition – Index Elimination:
   Instead of checking each person whether they satisfy celebrity conditions, we compare two persons at a time and eliminate one.
   At each step, we only need to keep the person who could still be a celebrity.
   This reduces the problem from checking n persons to comparing pairs and narrowing down to one.

2. How we find the candidate:
   - We push all people into a stack.
   - Compare the top two persons.
   - If the first knows the second, the first cannot be celebrity → remove it.
   - Else, the second cannot be celebrity → remove it.
   - Repeat until one candidate remains.

3. How this actually works:
   Every comparison eliminates at least one non-celebrity.
   The last person remaining is the only possible candidate.

4. Why verification is required:
   The elimination only ensures the candidate may be a celebrity, but we must check:
   - Everyone knows the candidate.
   - The candidate knows no one.
   Hence, a final verification is essential.

5. Why we skip self-comparison:
   mat[n][n] is irrelevant because one’s knowledge of oneself is not considered.

Working of the function:
- Stack holds all people initially.
- By repeatedly comparing and popping, we reduce the stack to one candidate.
- We then verify this candidate against all others.
- Return the candidate’s index if all conditions are satisfied or -1 otherwise.
*/

// Main function to test the solution with working examples


int main() {
    Solution solution;

    // Example 1: Celebrity exists
    vector<vector<int>> mat1 = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}
    };
    cout << "Celebrity index (Example 1): " << solution.celebrity(mat1) << endl; // Expected output: 1

    // Example 2: No celebrity
    vector<vector<int>> mat2 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };
    cout << "Celebrity index (Example 2): " << solution.celebrity(mat2) << endl; // Expected output: -1

    return 0;
}

/*
Important Details, Warnings, and Key Insights:

✔ Redefining the problem using index elimination drastically reduces unnecessary checks.
✔ The stack helps keep track of possible candidates efficiently.
✔ Final verification is crucial because elimination alone doesn't guarantee correctness.
✔ Self-comparison must be skipped when verifying.
✔ The stack-based solution is optimized in time but not space — O(n) space is used.
✔ For interviews or follow-ups, the two-pointer method is better with O(1) space.
✔ Similar problems include:
   - Find the town judge (same concept with a different story)
   - Graph problems with in-degree and out-degree conditions
✔ Always analyze both elimination and verification steps separately.
✔ This approach is practical and accepted in competitive platforms like GFG.

*/

