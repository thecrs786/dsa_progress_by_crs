/*
Problem: Find the Celebrity
- Given a matrix 'mat' where mat[i][j] == 1 means person 'i' knows person 'j'.
- A celebrity is someone who:
    1. Is known by everyone else (all mat[j][c] == 1 for j ≠ c)
    2. Knows no one else (all mat[c][j] == 0 for j ≠ c)
- Find the index of the celebrity or return -1 if no celebrity exists.

Example:
Input: mat = [[1, 1, 0],
              [0, 1, 0],
              [1, 1, 1]]
Output: 1
Explanation: Person 1 is known by everyone and knows no one else.

Input: mat = [[1, 0],
              [0, 1]]
Output: -1
Explanation: No celebrity exists here.

Approach Used: Brute Force
- For each person, check if they are known by everyone else AND know no one else.
- Use two nested loops to check both conditions.

Time Complexity: O(n^2) 
- We check each person against all others in both row and column.

Space Complexity: O(1)
- No extra space used other than variables.

Optimality:
- This is a brute-force solution, not the most optimal.
- Optimal solutions exist with O(n) time complexity using elimination strategies.

Acceptance:
- This solution is accepted by platforms like GeeksforGeeks.
- It will not cause MLE or TLE for reasonable input sizes (as per problem constraints).
*/

// ✅ Boilerplate with explanation

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int celebrity(vector<vector<int>>& mat) {
        int n = mat.size();  // Number of people
        
        // Loop through each person to check if they can be a celebrity
        for(int i = 0; i < n; i++) {
            bool knownByAll = true;  // Assume i is known by everyone
            
            // Check if everyone knows person i
            for(int j = 0; j < n; j++) {
                if(i != j && mat[j][i] == 0) {
                    knownByAll = false; // If any person doesn't know i, i can't be celebrity
                    break;
                }
            }
            
            if(knownByAll) { // Only check further if i is known by all others
                bool knowsNoOne = true; // Assume i knows no one
                
                // Check if person i knows anyone else
                for(int j = 0; j < n; j++) {
                    if(i != j && mat[i][j] == 1) {
                        knowsNoOne = false; // If i knows someone, they can't be celebrity
                        break;
                    }
                }
                
                if(knowsNoOne)
                    return i; // i is the celebrity if both conditions are true
            }
        }
        
        return -1; // No celebrity found after checking everyone
    }
};

/*
✔ Logic Explained:
- We are trying to identify a person 'i' for whom:
    1. Everyone else knows 'i'.
    2. 'i' knows no one else.
- We used two bool variables:
    - knownByAll: starts as true, and we try to disprove it by checking if someone doesn't know 'i'.
    - knowsNoOne: starts as true, and we try to disprove it by checking if 'i' knows someone else.
- The outer loop iterates over each person 'i' as the candidate.
- The first inner loop checks column 'i' to ensure everyone knows 'i'.
- The second inner loop checks row 'i' to ensure 'i' knows no one.
- We skip self-reference (i == j) because a person knowing themselves isn't relevant.
- If both conditions are true, we return 'i' immediately.
- If no such 'i' is found, we return -1 at the end.

✔ Working of the function:
- For each candidate, we carefully verify both conditions without unnecessary checks.
- The function ensures correctness by early exiting when the condition is violated.

✔ How we redefined the problem:
- We converted the verbal definition of a celebrity into strict mathematical conditions.
- We needed two bool variables because each condition is independent but both must hold true.

✔ Why two bools:
- knownByAll ensures 'i' is a potential celebrity by seeing if everyone knows them.
- knowsNoOne ensures 'i' is a potential celebrity by checking if they don't know anyone else.
- Both are required to confidently identify the celebrity.

✔ How the nested loops work:
- The first loop verifies the 'known by all' property in O(n).
- The second loop verifies the 'knows none' property in O(n).
- Together, we process all possible pairs in O(n^2).
*/

// ✅ Main function with a working example to test and analyze the output

int main() {
    Solution sol;
    
    // Example 1
    vector<vector<int>> mat1 = {
        {1, 1, 0},
        {0, 1, 0},
        {1, 1, 1}
    };
    cout << "Celebrity index (Example 1): " << sol.celebrity(mat1) << endl;
    
    // Example 2
    vector<vector<int>> mat2 = {
        {1, 0},
        {0, 1}
    };
    cout << "Celebrity index (Example 2): " << sol.celebrity(mat2) << endl;
    
    return 0;
}

/*
✅ Important Details, Warnings & Key Insights:

✔ We redefined the problem using matrix properties:
    - Column check ensures everyone knows 'i'.
    - Row check ensures 'i' knows no one.

✔ We must skip the diagonal (i == j) because a person's self-knowledge is irrelevant.

✔ Two bool variables were necessary:
    - Without both, we could not fully verify a celebrity.

✔ This brute-force method is simple but not scalable for large datasets.
    - Time complexity is O(n^2), so performance drops rapidly as 'n' increases.

✔ It is accepted on GeeksforGeeks and won't cause TLE or MLE within problem constraints.

✔ Key insights:
    - We’re looking for global relationships, not local ones.
    - The elimination approach (used in optimized solutions) builds on this understanding.

✔ Similar Problems:
    - The optimized version using two pointers or a stack.
    - Graph problems where relationships are verified globally.
    - Problems involving transitive properties like "knows", "follows", etc.

✔ Approach used here:
    - Brute-force verification.
    - Clear separation of the two celebrity conditions.
    - Early exit strategies using 'break' for efficiency.

Keep practicing both brute-force and optimized solutions to strengthen problem-solving skills!
*/
