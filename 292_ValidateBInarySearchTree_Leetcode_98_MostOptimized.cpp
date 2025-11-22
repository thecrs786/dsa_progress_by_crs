/*
LeetCode #98 - Validate Binary Search Tree (BST)

Problem (brief):
  Given the root of a binary tree, determine if it is a valid Binary Search Tree (BST).
  A BST must satisfy for every node:
    - all values in left subtree  < node->val
    - all values in right subtree > node->val
  (i.e., inorder traversal of a valid BST is strictly increasing.)

Examples:
  1) root = [2,1,3]   -> valid BST -> true
       2
      / \
     1   3

  2) root = [10,5,15,null,null,6,20] -> invalid BST -> false
         10
        /  \
       5    15
           /  \
          6    20
     (6 is in right subtree of 10 but 6 < 10 -> violates BST)

Time Complexity:  O(n) — visit each node once.
Space Complexity: O(h) — recursion stack depth = tree height h (worst-case O(n) for skewed tree, O(log n) for balanced).

Approach used (name/method):
  Depth-First Traversal with range/bound checks (min/max propagation).
  Each node must lie in an allowed interval: (low, high). For root initial interval is (−∞, +∞).
  When going left: new high = node->val.
  When going right: new low = node->val.

Is this asymptotically optimal?
  Yes — O(n) time is necessary (must inspect every node). Space O(h) is optimal for recursion-based DFS.
  Alternative approach: iterative inorder traversal checking strictly increasing sequence (also O(n), O(h) space).

Will LeetCode accept it?
  Yes. This is a canonical accepted solution. No TLE/MLE under normal constraints.

Notes in code below: full implementation + detailed explanation, working examples in main, and extended comments.
*/

#include <bits/stdc++.h>
#include <climits> // for LLONG_MIN / LLONG_MAX
using namespace std;

/* -------------------- Standard TreeNode (LeetCode) -------------------- */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* -------------------- Solution: DFS with bounds (clean & correct) -------------------- */
class Solution {
public:
    /*
      helper(root, low, high)
      - Ensures every node in the subtree rooted at `root` satisfies: low < node->val < high.
      - low and high are exclusive bounds (strict), because BST requires strictly smaller/larger values.
      - Use long long bounds to avoid edge-case errors with INT_MIN / INT_MAX node values.
    */
    bool helper(TreeNode* root, long long low, long long high){
        if (root == nullptr) return true; // empty subtree is valid

        // Current node must be strictly between low and high.
        if (root->val <= low || root->val >= high) return false;

        // Left subtree: values must be in (low, root->val)
        // Right subtree: values must be in (root->val, high)
        return helper(root->left, low, root->val) &&
               helper(root->right, root->val, high);
    }

    bool isValidBST(TreeNode* root) {
        // Use the full range of long long to avoid rejecting edge values like INT_MIN or INT_MAX.
        // LLONG_MIN / LLONG_MAX are safe sentinels outside the int range.
        return helper(root, LLONG_MIN, LLONG_MAX);
    }
};

/* -------------------- Detailed logic & explanation (below class, above main) --------------------
   (This section explains WHY the bounds method is used, why long long, and why simple parent-child checks fail.)

1) The core invariant (why low/high):
   - At any point when visiting node `x`, we maintain bounds (low, high) such that:
       low < x->val < high
     This invariant is derived from all ancestor constraints:
       - If we moved left from ancestor `A`, then all nodes in this branch must be < A->val -> sets an upper bound.
       - If we moved right from ancestor `B`, then all nodes must be > B->val -> sets a lower bound.
     Combining these for the current path yields the (low, high) interval.

2) How bounds propagate:
   - Start: (low, high) = (−∞, +∞).
   - When going left from node `x`: new bounds = (low, x->val) because left-subtree values must be < x->val but still > low.
   - When going right from node `x`: new bounds = (x->val, high) because right-subtree values must be > x->val but still < high.

3) Why NOT just check immediate children?
   - That only verifies:
       left->val < node->val and right->val > node->val
     which is necessary but not sufficient. It doesn't check values deeper in subtrees relative to ancestors.
   - Counterexample:
         10
        /  \
       5    15
           /  \
          6    20
     Here 6 < 15 (so parent-child check passes) but 6 < 10 which violates being in the right subtree of 10.
     The bounds method catches this because for node 6 the allowed interval is (10, +∞); since 6 <= 10 it's invalid.

4) Why use `long long` for bounds (and LLONG_MIN/LLONG_MAX)?
   - Tree node values are `int` (32-bit). Using `int` sentinel bounds (INT_MIN/INT_MAX) can cause incorrect rejections if a node has value equal to the sentinel.
     Example: node->val == INT_MAX. If high == INT_MAX and we check node->val >= high, we get (INT_MAX >= INT_MAX) true -> falsely invalid.
   - By using `long long` and LLONG_MIN/LLONG_MAX, we ensure sentinels lie strictly outside the `int` range, eliminating false negatives.
   - Alternatively, `numeric_limits<long long>::min()` / `max()` works too.

5) Strict inequalities (<= / >=) vs non-strict:
   - BST (as defined here) requires **strict** ordering: left < node < right.
   - Use `root->val <= low || root->val >= high` to reject equal values.
   - If the BST definition allowed duplicates on one side, adjustments would be required.

6) Complexity:
   - Time: O(n) — every node visited once.
   - Space: O(h) — recursion stack depth (balanced: O(log n), worst-case: O(n)).

7) Alternative approach:
   - Inorder traversal should produce a strictly increasing sequence for a valid BST.
   - Do iterative inorder (stack) or recursive inorder while tracking previous value (prev). For each node, check prev < node->val.
   - This is another standard O(n), O(h) solution.

------------------------------------------------------------------------------- */

 // -------------------- Helper test & printing utilities --------------------
void printBool(bool b) { cout << (b ? "true" : "false") << "\n"; }

// clean-up helper
void deleteTree(TreeNode* root){
    if(!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* -------------------- main: working examples & outputs -------------------- */
int main() {
    Solution sol;

    // Example A: valid BST [2,1,3]
    TreeNode* vroot = new TreeNode(2);
    vroot->left = new TreeNode(1);
    vroot->right = new TreeNode(3);

    cout << "Example A (valid BST [2,1,3]) -> expected: true. got: ";
    printBool(sol.isValidBST(vroot)); // true

    // Example B: invalid BST [10,5,15,null,null,6,20]
    TreeNode* iroot = new TreeNode(10);
    iroot->left = new TreeNode(5);
    iroot->right = new TreeNode(15);
    iroot->right->left = new TreeNode(6);   // violates BST because 6 < 10 but is in right subtree of 10
    iroot->right->right = new TreeNode(20);

    cout << "Example B (invalid BST [10,5,15,null,null,6,20]) -> expected: false. got: ";
    printBool(sol.isValidBST(iroot)); // false

    // Edge-case: node values at int limits
    TreeNode* edge = new TreeNode(INT_MAX);
    edge->left = new TreeNode(INT_MIN); // valid: INT_MIN < INT_MAX
    cout << "Edge case (INT_MIN left, INT_MAX root) -> expected: true. got: ";
    printBool(sol.isValidBST(edge)); // true, demonstrates LLONG sentinels protect correctness

    // Cleanup
    deleteTree(vroot);
    deleteTree(iroot);
    deleteTree(edge);

    return 0;
}

/* -------------------- Important details, warnings, key insights, similar problems --------------------

IMPORTANT DETAILS / WARNINGS:
- Always use exclusive bounds (low, high) and strict inequalities for the problem as defined.
- Use a data type for bounds that strictly exceeds node value range (long long + LLONG_MIN/MAX) to avoid false rejections for extreme int values.
- Recursion depth equals tree height. For extremely deep trees (e.g., depth ~10^5) recursion may overflow the call stack — use iterative inorder or iterative DFS with your own stack in that case.
- If problem allows duplicates in BST with a policy (e.g., duplicates go to left), adapt inequalities accordingly (<= or >= where appropriate).

KEY INSIGHTS (10/10 summary):
- The BST invariant is global, not just local. A node must satisfy constraints set by ALL ancestors, not only its parent.
- The bounds method encodes all ancestor constraints into two values (low, high) and is the simplest, cleanest way to enforce the global invariant during DFS.
- Using LLONG sentinels is a tiny but crucial engineering detail to avoid edge-case failures.
- Inorder-checking (prev < current) is a neat alternative; both are O(n) and commonly accepted in interviews.

SIMILAR PROBLEMS & VARIANTS:
- LeetCode 98 (this problem) — Validate BST.
- Variant: "Validate BST allowing duplicates on one side" — adjust inequality semantics.
- Use-case: "Convert BST to sorted list" / "Check if tree is BST and balanced" — combine techniques (inorder + height checks).
- Related: "Find min/max in BST", "Lowest Common Ancestor in BST" — all exploit BST ordering property.

If you want, I can also:
 - Provide the iterative inorder implementation (stack-based) with comments,
 - Provide a version that detects and returns the first violating node (useful for debugging),
 - Or produce a compact one-file template you can paste into your notes with all variants.

No fluff: the bounds method is the correct minimal fix to your original code. Use LLONG_MIN / LLONG_MAX and you're done.
*/