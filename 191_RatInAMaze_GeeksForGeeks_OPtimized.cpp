#include <bits/stdc++.h>
using namespace std;

/*
=========================================
🐀 Rat in a Maze Problem (GFG version)
=========================================

📌 Problem in Brief:
- You are given an `n x n` binary maze.
- 1 → open cell, 0 → blocked cell.
- Rat starts at (0,0) and must reach (n-1,n-1).
- Rat can move in 4 directions: Down (D), Left (L), Right (R), Up (U).
- Task: Return all possible paths as strings ("DRRUL..." etc.).
- The result must be in lexicographic order (L < R < U < D by dictionary rules).

-----------------------------------------
📌 Method Used Here:
- Recursive **Backtracking** with an auxiliary `visited[][]` matrix.
- Keep track of current path as a string.
- Add path to result when rat reaches destination.
- Mark cell as visited before exploring neighbors.
- Backtrack (unmark visited) after exploring all options.

-----------------------------------------
📌 Why visited[][]?
- In the previous solution we directly modified `maze[row][col] = 0/1` to prevent revisiting.
- In this solution we keep `maze` untouched, and instead use an extra `visited[row][col]`.
- This improves readability, but uses extra memory (O(n²)).

-----------------------------------------
📌 Time & Space Complexity:
- Time Complexity: O(4^(n*n)) in the worst case (every cell can branch into 4 directions).
  (Practical runs are much faster due to blocked cells and visited checks).
- Space Complexity:
   * Path string depth: O(n²).
   * Recursion stack: O(n²).
   * Extra visited[][]: O(n²).
   → Total still O(n²), but heavier than the maze-modification version.

-----------------------------------------
📌 Is it Optimal?
- Functionally same as the maze-marking approach.
- Slightly less optimized due to extra memory.
- But safer for production-style coding (doesn’t mutate input).
- Will NOT cause TLE/MLE on GFG or LeetCode for typical input sizes.

-----------------------------------------
*/

class Solution {
  public:
  
   void getpath(vector<vector<int>> &maze, int row, int col, string path, vector<string> &ans, vector<vector<bool>> &visited){
       int n  = maze.size();

       // 🔹 Base Case 1: Out of bounds
       if(row<0 || row>=n || col<0 || col>=n) return;

       // 🔹 Base Case 2: Blocked cell or already visited
       if(maze[row][col]==0 || visited[row][col]) return;

       // 🔹 Base Case 3: Destination reached
       if(row==n-1 && col == n-1){
           ans.push_back(path);
           return;
       }

       // 🔹 Step 1: Mark current cell as visited
       visited[row][col]=true;

       // 🔹 Step 2: Explore all directions in lexicographic order
       getpath(maze, row+1, col , path+"D", ans, visited); // down
       getpath(maze, row, col-1 , path+"L", ans, visited); // left
       getpath(maze, row, col+1 , path+"R", ans, visited); // right
       getpath(maze, row-1, col , path+"U", ans, visited); // up
       
       // 🔹 Step 3: Backtrack (unmark visited cell)
       // We mark the current cell as unvisited again before returning.
       // Why? Because recursion explores *all possible paths*.
       // If we leave it as visited, other valid paths coming through this cell later
       // will be blocked, and we’ll lose solutions.
       // Example: if (0,2) was visited during one path, but after returning we don’t unmark it,
       // then another path that legitimately reaches (0,2) will be skipped.
       // Hence, backtracking = reset state → allow future paths to reuse the cell

       visited[row][col]=false;
   }
   
   vector<string> ratInMaze(vector<vector<int>>& maze) {
        int n = maze.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        vector<string> ans;
        string path = "";
        
        getpath(maze, 0,0,path,ans,visited);

        // Ensure lexicographic order of result
        sort(ans.begin(), ans.end());
        return ans;
   }
};


/*
=========================================
📌 Key Explanations:
=========================================

🔹 1. Why do we need visited[row][col] = true and then false?
- Imagine rat at (row,col).
- If we don’t mark visited, the recursion may go back to the same cell → infinite loop.
- Setting visited=true means: "Currently exploring this path, don’t revisit."
- After recursion ends for this path, we reset visited=false → "Available again for other different paths."
- This is the essence of **backtracking**.

🔹 2. Difference from previous solution:
- Previous: maze[row][col] = 0 (block it), then reset maze[row][col] = 1 after backtracking.
- Current: keep maze untouched, use separate visited[][] to track exploration.
- Functionally the same. Only difference = extra memory vs input mutation.


🔹 4. Lexicographic order:
- We recurse in the order D, L, R, U (or sort at the end).
- Sorting ensures the answer matches GFG requirements.

=========================================
📌 Dry Run Example (3x3 maze):

Maze:
1 0 0
1 1 0
1 1 1

Start: (0,0)
Visited[][] all false initially.

Call stack journey:
- Start path="", (0,0) → mark visited.
- Explore D → (1,0), path="D"
   - From (1,0), go D → (2,0), path="DD"
       - From (2,0), go R → (2,1), path="DDR"
           - From (2,1), go R → (2,2), path="DDRR" ✅ destination → ans={"DDRR"}.
       - Backtrack step resets visited[][] properly each time.

Thus rat explores systematically all paths without revisiting same cell.

=========================================
*/

int main() {
    Solution sol;

    vector<vector<int>> maze = {
        {1, 0, 0},
        {1, 1, 0},
        {1, 1, 1}
    };

    vector<string> result = sol.ratInMaze(maze);

    cout << "All possible paths:\n";
    for(string &p : result) cout << p << "\n";

    return 0;
}

/*
=========================================
📌 Example Output:
All possible paths:
DDRR
=========================================
*/
