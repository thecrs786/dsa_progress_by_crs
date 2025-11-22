/***************************************************************
 Rat in a Maze — All Paths (Backtracking, 4-directional moves)

 ▶ PROBLEM (brief):
   - Given an N×N grid `maze` of 0/1, where 1 = open cell, 0 = blocked.
   - Start at (0,0). Target is (N-1,N-1).
   - You may move in 4 directions: Down (D), Left (L), Right (R), Up (U),
     staying inside the grid and only stepping on cells with value 1.
   - Find ALL possible paths from start to end as strings of moves.
   - If multiple paths exist, online judges (like GfG) typically want
     them in *lexicographic* order of strings.

 ▶ YOUR PROVIDED SOLUTION (kept as-is in logic):
   - DFS + backtracking.
   - We pass a `path` string down recursion.
   - We mark the current cell visited by setting `maze[row][col] = 0`,
     and unmark on backtrack by restoring to 1.
   - We also prune immediate reversals using `path.empty()` / `path.back()`.
   - Move order used here: D, L, R, U (which is lexicographic for 'D'<'L'<'R'<'U').

 ▶ METHOD NAME:
   Backtracking DFS (with in-place visited marking and immediate-reversal pruning)

 ▶ TIME & SPACE COMPLEXITY:
   - Let N be the grid dimension. In the worst case (all 1s), the number of distinct
     simple paths can blow up **exponentially** w.r.t. the number of cells.
     Upper bound often quoted: O(4^(N*N)) for naive expansion; with visited marking,
     we enumerate *all simple paths*, which is still exponential.
   - Time: O(#paths) to generate + O(length_of_each_path) per path. Exponential in worst case.
   - Space: O(N*N) recursion depth in the worst case (path length) + O(#paths * avg_path_len) to store answers.

 ▶ IS THIS “MOST OPTIMAL”?
   - For enumerating *all* paths, you can’t asymptotically beat exponential —
     there may be exponentially many valid paths to list. So the approach is optimal in that sense.
   - Micro-optimizations:
       * Pruning immediate reversals via `path.back()` saves useless calls.
       * Following order D,L,R,U naturally produces lexicographic paths on GfG,
         which can remove the need to sort, but sorting at the end is a safe fallback.

 ▶ WILL THIS BE ACCEPTED ON LEETCODE / GfG / TLE/MLE?
   - LeetCode: There isn’t this exact classic problem under the same name. So N/A.
   - GeeksforGeeks (GfG): Yes, but **the judge expects**:
       * Function signature: `vector<string> findPath(vector<vector<int>> &m, int n)`
       * Lexicographic order of results (D < L < R < U). You can either:
           - Traverse in D,L,R,U order (as below) and likely get sorted output,
           - OR call `sort(ans.begin(), ans.end())` before returning to be bulletproof.
     Your approach passes typical GfG constraints. TLE/MLE only if grids are huge or #paths explodes.

 ▶ KEY INSIGHTS / PITFALLS:
   - **Visited marking is mandatory** to avoid cycles: `maze[row][col] = 0`, restore to 1 on backtrack.
   - `path.back()` checks only prevent *immediate* reverse (e.g., D→U next step),
     but DO NOT prevent longer cycles; that’s why visited marking is the real safety.
   - Check bounds & cell open (1) before recursing.
   - If judge requires exact **lexicographic** output, either maintain D,L,R,U order
     or run a final `sort`.
   - Don’t use `maze[row,col]` (comma operator bug) — always `maze[row][col]`.

****************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* =========================
   YOUR SOLUTION (as provided)
   =========================
   We keep the exact idea and ordering you wrote:
   - getpath(...) does the DFS
   - ratInMaze(...) is the wrapper returning all paths
*/
class Solution {
public:
    // DFS to gather all paths
    void getpath(vector<vector<int>> &maze, int row, int col, string path, vector<string> &ans) {

        // 'path' is passed by value → each recursive call gets its own copy, so it auto-restores on return.  
        // 'maze' is passed by reference → changes persist, so we must manually backtrack (reset to 1).  

        int n = (int)maze.size();

        // ---- Base Case #1: Out of bounds ----
        if (row < 0 || row >= n || col < 0 || col >= n) return;

        // ---- Base Case #2: Blocked or already visited ----
        if (maze[row][col] == 0) return;

        // ---- Base Case #3: Reached destination ----
        if (row == n - 1 && col == n - 1) {
            ans.push_back(path);     // record the current path
            return;
        }

        // Mark current cell visited: critical to avoid revisiting in this path
        // We "consume" this cell so recursive calls can't re-enter it.
        maze[row][col] = 0;

        // Move order: D, L, R, U  (lexicographic on 'D','L','R','U')
        // We also prune immediate backtracking with path.back() checks.
        // NOTE: This check is an optimization, not a correctness requirement,
        // because visited marking already prevents all cycles.

        // Down
        if (path.empty() || path.back() != 'U')  // avoid immediate U after D
            getpath(maze, row + 1, col, path + 'D', ans);

        // Left
        if (path.empty() || path.back() != 'R')  // avoid immediate R after L
            getpath(maze, row, col - 1, path + 'L', ans);

        // Right
        if (path.empty() || path.back() != 'L')  // avoid immediate L after R
            getpath(maze, row, col + 1, path + 'R', ans);

        // Up
        if (path.empty() || path.back() != 'D')  // avoid immediate D after U
            getpath(maze, row - 1, col, path + 'U', ans);

        // Unmark (backtrack): restore the cell for other branches
        maze[row][col] = 1;
    }

    // Wrapper: collect all paths from (0,0) to (n-1,n-1)
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        vector<string> ans;
        string path = "";

        // Optional guard: if start is blocked, there are no paths
        // (Not strictly necessary; getpath will return immediately anyway)
        // if (maze.empty() || maze[0][0] == 0) return ans;

        getpath(maze, 0, 0, path, ans);

        // If an online judge strictly requires lexicographic order,
        // you can uncomment the sort. With D,L,R,U order, this often
        // is already lexicographic, but sort is a safe guarantee.
        // sort(ans.begin(), ans.end());

        return ans;
    }
};

/* ===========================================================
   DETAILED EXPLANATION — WHY EACH STEP EXISTS (READ THIS)
   -----------------------------------------------------------
   1) Bounds & Block Check:
      We must reject moves that go outside [0..n-1] or into 0-cells.
      This prevents invalid recursion and stops us from entering walls.

   2) Destination Check:
      When (row,col) == (n-1,n-1), we’ve formed a valid path string,
      push it into `ans` and return. No further moves necessary.

   3) Visited Marking: maze[row][col] = 0
      This is the heart of backtracking correctness. Without it, the DFS
      could revisit the same cell later in the same path, creating cycles
      (and likely infinite recursion). Marking as 0 bans revisits.
      After exploring all directions from this cell, we MUST restore it
      to 1 so that *other* branches (coming from different parents) can
      use this cell.

   4) path.empty() / path.back() Pruning:
      - `path.back()` gives the last move we took.
      - We avoid immediate reversals: e.g., if we just moved 'D', we
        don’t immediately try 'U' next; that recursive call would be
        pointless because visited marking already blocks the origin cell.
      - This reduces useless recursion calls, improving runtime a bit.
      - NOTE: Even if you DELETE these checks, the algorithm stays CORRECT
        thanks to visited marking. These checks are an optimization, not a fix.

   5) Move Order D,L,R,U:
      - Chosen to match lexicographic order of the characters 'D'<'L'<'R'<'U'.
      - Many judges (GfG) want output sorted lexicographically. By exploring
        in this order, paths tend to be generated in lexicographic order.
        If you need to be 100% sure, just sort the final vector.

   6) Backtrack Restore: maze[row][col] = 1
      We must undo the visited mark before returning up the recursion.
      Otherwise, other independent paths would incorrectly treat this
      cell as blocked.

   ▶ THE “JOURNEY OF path” (mental model):
      - Start: path = "" at (0,0).
      - Suppose we go Down: now path = "D", position (1,0).
      - From there, say we go Right: path = "DR", position (1,1).
      - Each recursive call extends path by exactly one character that
        describes the move taken to reach the *child* cell.
      - When we reach (n-1,n-1), we *record* the path string we built.
      - We then backtrack: pop the recursion stack, restoring cells (1),
        and keep exploring other directions from previous positions so
        we enumerate ALL possible strings that reach the goal.

   ▶ WHY BOTH visited marking AND path.back()?:
      - visited marking: **required** to prevent cycles of any length.
      - path.back() pruning: **optional** micro-optimization to avoid
        the obvious immediate reversal call that will get rejected anyway.

===========================================================*/

/* ======================
   WORKING EXAMPLE (main)
   ======================
   - We'll run a couple of mazes:
     1) A classic 4x4 GfG-like example with multiple paths.
     2) A blocked-start example to show empty output.
   - We print the resulting paths.
*/

static void printPaths(const vector<string>& paths, const string& title) {
    cout << "---- " << title << " ----\n";
    if (paths.empty()) {
        cout << "(no paths)\n";
    } else {
        for (const auto& p : paths) cout << p << "\n";
    }
    cout << "------------------------\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    // Example 1: Classic 4x4 maze (1=free, 0=blocked)
    // Expected: multiple paths like DDRR, DRDR, DRRD, etc. (depending on walls)
    vector<vector<int>> maze1 = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    {
        vector<vector<int>> m = maze1;              // copy because we mutate
        auto paths = sol.ratInMaze(m);
        // If judge requires lexicographic order strictly, uncomment:
        // sort(paths.begin(), paths.end());
        printPaths(paths, "Paths in maze1");
    }

    // Example 2: Fully open 3x3 to see more paths easily
    vector<vector<int>> maze2 = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
    {
        vector<vector<int>> m = maze2;
        auto paths = sol.ratInMaze(m);
        // sort(paths.begin(), paths.end());  // optional
        printPaths(paths, "Paths in open 3x3 (many)");
    }

    // Example 3: Start blocked -> no paths
    vector<vector<int>> maze3 = {
        {0,1},
        {1,1}
    };
    {
        vector<vector<int>> m = maze3;
        auto paths = sol.ratInMaze(m);
        printPaths(paths, "Blocked start (no paths)");
    }

    // Example 4: End blocked -> no paths
    vector<vector<int>> maze4 = {
        {1,1},
        {1,0}
    };
    {
        vector<vector<int>> m = maze4;
        auto paths = sol.ratInMaze(m);
        printPaths(paths, "Blocked end (no paths)");
    }

    return 0;
}

/* ===========================================================
   OPTIONAL: GfG-COMPLIANT WRAPPER (for the actual judge)
   -------------------------------------------------------
   If you submit on GeeksforGeeks, they want:

     vector<string> findPath(vector<vector<int>> &m, int n)

   You can adapt as follows (uncomment and use instead):

class Solution {
public:
    void dfs(vector<vector<int>> &m, int n, int r, int c, string path, vector<string>& ans) {
        if (r < 0 || c < 0 || r >= n || c >= n || m[r][c] == 0) return;
        if (r == n-1 && c == n-1) { ans.push_back(path); return; }
        m[r][c] = 0;
        dfs(m, n, r+1, c, path+'D', ans); // D
        dfs(m, n, r, c-1, path+'L', ans); // L
        dfs(m, n, r, c+1, path+'R', ans); // R
        dfs(m, n, r-1, c, path+'U', ans); // U
        m[r][c] = 1;
    }
    vector<string> findPath(vector<vector<int>> &m, int n) {
        vector<string> ans;
        if (n == 0 || m[0][0] == 0) return ans;
        dfs(m, n, 0, 0, "", ans);
        // Bulletproof: enforce lexicographic order
        sort(ans.begin(), ans.end());
        return ans;
    }
};

   Notes:
   - The traversal order is D, L, R, U (lexicographic).
   - We still use in-place visited marking.
   - We finalize with sort() to match judge’s lexicographic requirement.
===========================================================*/
