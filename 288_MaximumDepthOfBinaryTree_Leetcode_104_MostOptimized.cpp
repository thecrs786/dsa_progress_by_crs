/* 
LeetCode #104 - Maximum Depth of Binary Tree

Problem (brief):
  Given the root of a binary tree, return its maximum depth.
  The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Example:
  Input:  root = [3,9,20,null,null,15,7]
           3
          / \
         9  20
           /  \
          15   7
  Output: 3

  Input:  root = [1,null,2,null,3]  (skewed to right)
  Output: 3

Time Complexity:  O(n)   -- each node is visited exactly once.
Space Complexity: O(h)   -- recursion stack; h = tree height. Worst-case O(n) for skewed tree.

Approach used:
  Depth-first recursion. For each node, compute depth of left subtree and right subtree recursively.
  The max depth at current node = max(depth(left), depth(right)) + 1 (counting current node).

Is this asymptotically optimal?
  - Yes. You must inspect every node at least once to determine overall height -> O(n) time is optimal.
  - Space uses recursion stack O(h); an iterative BFS/stack can convert recursion-space into explicit queue/stack 
    but cannot improve worst-case auxiliary space below O(n) for skewed trees.

Will it be accepted on LeetCode / TLE / MLE?
  - Will be accepted for standard constraints. No TLE.
  - MLE only if recursion depth is too large (stack overflow) for extremely deep trees (e.g., >~10^5 depth on some systems).
    Use iterative approach if stack overflow is a practical concern.

(Boilerplate, headers, struct, and the user's solution implementation follow.)
*/

#include <bits/stdc++.h>
using namespace std;

/* Standard LeetCode TreeNode definition */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* ------------------ Solution Class ------------------ */
class Solution {
public:
    /*
      The solution you provided (kept functionally identical).
      Method name: Recursive DFS (post-order style)
      Rationale: depth depends on children depths -> compute children first, then combine.
    */
    int maxDepth(TreeNode* root) {
        // Base case: empty tree -> depth 0
        if(root==NULL) return 0;

        // Recursive case: compute max depth of left and right subtrees, then add 1 for current node
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

/* ------------------ Logic, step-by-step explanation & workings ------------------
   (Placed here as requested: below class and above main)

1) Why recursion / DFS?
   - The definition of tree height/depth is naturally recursive:
       depth(node) = 1 + max(depth(node->left), depth(node->right))
     So computing depth of a node requires depth of its children first -> recursion fits perfectly.

2) Base case:
   - if (root == NULL) return 0;
     Meaning: an empty subtree contributes 0 to the height.
     Stopping condition prevents infinite recursion.

3) Recursive step:
   - Call maxDepth(root->left) and maxDepth(root->right).
     These calls return depths (integers) for left and right subtrees.
   - Take the maximum of the two because the depth of a node is determined by the deeper branch.
   - Add 1 to count the current node's level.

4) Correctness reasoning:
   - By structural induction: for leaf node, both children are NULL -> both calls return 0 -> max(0,0)+1 = 1 (leaf depth correct).
   - For internal nodes, children depths are correct by induction; combining them via max + 1 yields correct depth.

5) Complexity proof:
   - T(n): each node is visited once and does O(1) work combining child results -> T(n) = O(n).
   - Space: recursion stack height equals tree height h. Balanced tree: h = O(log n). Skewed tree: h = O(n).

6) When recursion might fail / warnings:
   - Very deep trees (depth > system recursion limit) may cause stack overflow.
     If input trees can be pathologically deep (e.g., linked-list-like with 10^5 nodes), use iterative method.

7) Iterative alternative (when needed):
   - BFS level-counting using a queue: push root, while queue not empty increment depth for each level.
   - Or iterative DFS using an explicit stack that stores (node, depth).
   - These eliminate system recursion depth issues but still have O(n) time and O(n) worst-case space.

7a) Example iterative BFS skeleton (comment only):
   // int depth = 0;
   // if (!root) return 0;
   // queue<TreeNode*> q; q.push(root);
   // while (!q.empty()) {
   //   int sz = q.size(); depth++;
   //   for (int i = 0; i < sz; ++i) {
   //     TreeNode* cur = q.front(); q.pop();
   //     if (cur->left) q.push(cur->left);
   //     if (cur->right) q.push(cur->right);
   //   }
   // }
   // return depth;
-------------------------------------------------------------------------- */

int main() {
    // Working example 1:
    // Build tree: [3,9,20,null,null,15,7]
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
    int depth = sol.maxDepth(root);

    cout << "Max Depth (example 1): " << depth << "  (expected 3)\n";

    // Working example 2: skewed tree [1,null,2,null,3]
    TreeNode* sroot = new TreeNode(1);
    sroot->right = new TreeNode(2);
    sroot->right->right = new TreeNode(3);

    cout << "Max Depth (skewed example): " << sol.maxDepth(sroot) << "  (expected 3)\n";

    // Cleanup allocated memory (manual delete)
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;

    delete sroot->right->right;
    delete sroot->right;
    delete sroot;

    return 0;
}

/* ------------------ Important details, warnings, key insights, and similar problems ------------------

IMPORTANT DETAILS / WARNINGS:
- Use nullptr (modern C++) instead of NULL where possible. The provided solution uses NULL to match your snippet.
- Recursion is neat and concise but can hit stack limits for extremely deep trees (practical limit depends on platform).
  If you expect huge depths (e.g., > 10^4 - 10^5), prefer iterative BFS or explicit-stack DFS.
- This function returns number of nodes along the longest root-to-leaf path (height). If you need depth in edges,
  subtract 1 from this result (but LeetCode expects node-count).

KEY INSIGHTS:
- The recursive relation depth(node) = 1 + max(depth(left), depth(right)) is the core idea.
- The algorithm is essentially a post-order traversal: compute children's info -> combine -> return to parent.
- There's no way to compute tree height without touching each node at least once, so O(n) is optimal.

EDGE CASES:
- Empty tree (root == NULL) -> return 0.
- Single node -> return 1.
- Very deep chain (degenerate/skewed) -> recursion depth equals n (watch for stack overflow).

SIMILAR PROBLEMS & APPROACHES:
- LeetCode 111: Minimum Depth of Binary Tree -> similar recursion but be careful with single-child nodes
  (min depth should ignore NULL-only branches).
- LeetCode 543: Diameter of Binary Tree -> needs depth computation at each node plus tracking longest path through node.
- LeetCode 104 (this problem) pairs well with:
    * BFS-level-counting (iterative alternative)
    * DFS recursion (this solution)
- LeetCode 110: Balanced Binary Tree -> uses height calculation but early-stops when imbalance detected.

FINAL JAB (no sugar):
- Your implementation is correct, minimal, and idiomatic for the problem. It's optimal in time.
- The only real caveat is system recursion limits for pathological inputs — if you face that, rewrite with iterative BFS.
- If you want, I can convert this into an iterative BFS/stack solution and include worst-case memory/backtrace comparisons.
*/