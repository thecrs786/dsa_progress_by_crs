/*
LeetCode #102 - Binary Tree Level Order Traversal (Breadth-First Search)

Problem (brief):
  Given the root of a binary tree, return the level order traversal of its nodes' values.
  (i.e., from left to right, level by level).

Example:
  Input:  root = [3,9,20,null,null,15,7]
           3
          / \
         9  20
           /  \
          15   7

  Output: [[3],[9,20],[15,7]]

Time Complexity:  O(n)  -- every node is visited exactly once.
Space Complexity: O(n)  -- queue + output (worst-case last level ~ n/2)

Approach used:
  BFS using a queue. For each level:
    - capture the number of nodes at that level (size = q.size())
    - pop exactly `size` nodes, collecting their values into a vector
    - push each popped node's children into the queue for the next level
  This isolates levels cleanly and produces vector<int> per level.

Notes:
  - This is the standard, optimal BFS approach for level-order traversal.
  - Asymptotically optimal: O(n) time and O(n) auxiliary space in worst-case.
  - Will be accepted on LeetCode for normal input sizes; no TLE. MLE only if input size itself is absurd.
*/

/* -------------------- Headers / Boilerplate -------------------- */
#include <bits/stdc++.h>
using namespace std;

/* -------------------- Tree node definition (LeetCode standard) -------------------- */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* -------------------- Solution class -------------------- */
class Solution {
public:
    // --- Original user-provided snippet (kept here as reference; exact logic preserved) ---
    /*
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root==NULL) return ans;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int size = q.size();
            vector<int> level;

            for(int i=0; i<size; i++){
                level.push_back(q.front()->val);
                if(q.front()->left!=NULL) q.push(q.front()->left);
                if(q.front()->right!=NULL) q.push(q.front()->right);
                q.pop();
            }

            ans.push_back(level);
        }

        return ans;
    }
    */

    // --- Slightly cleaned, functionally identical implementation ---
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;               // final output: vector of levels
        if(root == NULL) return ans;          // edge-case: empty tree -> empty output

        queue<TreeNode*> q;
        q.push(root);                         // start BFS from the root

        while(!q.empty()){
            int size = (int)q.size();         // number of nodes in the current level
            vector<int> level;
            level.reserve(size);             // minor optimization: avoid reallocations

            for(int i = 0; i < size; ++i){
                TreeNode* node = q.front();  // cache front node to avoid repeated q.front()
                level.push_back(node->val);  // record value for this level

                // enqueue children for the next level (if present)
                if(node->left != NULL)  q.push(node->left);
                if(node->right != NULL) q.push(node->right);

                q.pop();                     // remove the processed node
            }

            ans.push_back(std::move(level)); // move level into answer (avoid copy)
        }

        return ans;
    }
};

/* -------------------- Detailed logic & step-by-step explanation --------------------
   (Placed here intentionally: explanation follows the class definition as requested)

1) Why BFS & a queue?
   - Level-order traversal explicitly requires visiting nodes level by level.
   - A queue naturally supports FIFO ordering: as we pop nodes, we can enqueue their children
     which belong to the next level. This enforces level-by-level processing.

2) Key trick to get each level separately:
   - At the start of processing a level, capture the current queue size:
       int size = q.size();
   - That `size` equals the number of nodes that belong to the current level.
     Note: q.size() will increase during processing when you push children, so you must
     capture it BEFORE the for-loop. Iterating `size` times ensures you only process nodes
     that were in the queue at the start of this level — children go to next level.

3) Why use a temporary vector<int> level?
   - Collect values of exactly those `size` nodes in order.
   - After the for-loop, `level` contains a complete list of values for the current level.
   - Push that `level` to the answer vector<vector<int>> ans.

4) Early return for empty tree:
   - If root is NULL, immediately return an empty vector. Simpler and avoids unnecessary work.

5) Minor performance details:
   - Using `TreeNode* node = q.front()` avoids calling q.front() multiple times.
   - Reserving `level.reserve(size)` reduces memory reallocations.
   - Using `ans.push_back(std::move(level))` moves the vector instead of copying.

6) Edge-cases:
   - Single-node tree -> returns [[root->val]]
   - Skewed tree (all lefts or rights) -> returns [[n1],[n2],[n3],...]
   - Large complete tree -> queue may hold roughly n/2 nodes at one time => O(n) space.

7) Alternatives:
   - DFS with depth parameter: push values into ans[depth] while recursing.
     Same asymptotic complexity (O(n) time, O(n) space) but recursion depth may cause stack overflow
     for very deep trees.
   - There is no O(1) extra-space algorithm that returns all levels as separate arrays in general.

7) Complexity summary:
   - Time: O(n), where n = number of nodes.
   - Space: O(n) worst-case (queue + output).
------------------------------------------------------------------------------- */

/* -------------------- Example driver: build a tree, run solution, print output -------------------- */
int main() {
    // Construct example tree used in LeetCode example:
    //       3
    //      / \
    //     9  20
    //       /  \
    //      15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution sol;
    vector<vector<int>> result = sol.levelOrder(root);

    // Print result in a readable format
    cout << "[";
    for(size_t i = 0; i < result.size(); ++i){
        cout << "[";
        for(size_t j = 0; j < result[i].size(); ++j){
            cout << result[i][j];
            if(j + 1 < result[i].size()) cout << ", ";
        }
        cout << "]";
        if(i + 1 < result.size()) cout << ", ";
    }
    cout << "]\n";

    // Expected output:
    // [[3], [9, 20], [15, 7]]

    // Cleanup (not strictly necessary in short-lived examples, but good habit)
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}

/* -------------------- Important details, warnings, key insights, and similar problems --------------------

IMPORTANT DETAILS / WARNINGS:
- Capturing q.size() BEFORE the for-loop is critical. If you used `for (int i = 0; i < q.size(); ++i)` directly,
  q.size() would change as you push children into the queue, and the loop boundary would be incorrect.
- Using recursion to build level vectors is clean, but deep trees can cause stack overflow.
- Memory: level-order requires storing nodes of at least one whole level (queue). For balanced trees, that's O(n).
  If you have extremely large trees (millions of nodes), any approach producing full level lists will be memory-heavy.
- Prefer `nullptr` over `NULL` in modern C++ for clarity and type-safety. The above code preserves user style in places
  but uses `NULL` checks equivalently; prefer switching to `nullptr` if you follow modern C++ guidelines.
- For slight micro-optimizations:
    * reserve level vector capacity: level.reserve(size);
    * move the level into ans: ans.push_back(std::move(level));
  These reduce allocations/copies but do not change asymptotic complexity.

WILL THIS BE ACCEPTED ON LEETCODE?
- Yes. This is the standard accepted solution. It will not TLE under normal constraints.
- MLE only in degenerate cases where the input itself is huge (bigger than platform limits).

KEY INSIGHTS:
- The `size = q.size()` technique isolates levels cleanly — that's the single most important trick.
- BFS is the natural fit when answers must be grouped by level.
- If you only needed values in order (not grouped by level), a simple BFS would suffice without the size trick.

SIMILAR PROBLEMS (and recommended approach):
- LeetCode 103: Binary Tree Zigzag Level Order Traversal -> same BFS, alternate direction per level.
- LeetCode 107: Binary Tree Level Order Traversal II -> same BFS, but return levels bottom-up (post-process or insert at front).
- LeetCode 637: Average of Levels in Binary Tree -> same BFS, compute average per level.
- LeetCode 199: Binary Tree Right Side View -> BFS and pick last (or first) element of each level.
- Approach for these: BFS with level-size capture (same core technique), or DFS with depth tracking.

If you want, I can:
  - produce the DFS recursive variant with identical outputs (and line-by-line comments),
  - convert this to an iterative variant that collects results in a single vector-of-vectors but prints bottom-up,
  - or prepare multiple solved variations (zigzag, averages, right-side view) using the same template.

No sugar: this is the right solution. It's already the standard optimal approach — don't waste time chasing a better asymptotic complexity because there isn't one for this problem.*/
