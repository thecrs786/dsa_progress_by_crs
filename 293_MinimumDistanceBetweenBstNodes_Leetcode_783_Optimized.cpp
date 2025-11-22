/*
LeetCode — Problem Notes & Complete Code
Question Number: 783
Title (brief): Minimum Distance Between BST Nodes

Problem (brief):
  Given the root of a Binary Search Tree (BST), return the minimum absolute difference
  between the values of any two different nodes in the tree.

Examples (as comments):
  // Example 1:
  // Input: root = [4,2,6,1,3]
  // Tree:
  //       4
  //      / \
  //     2   6
  //    / \
  //   1   3
  // Inorder traversal (sorted): [1,2,3,4,6]
  // Minimum difference between consecutive values: 1
  // Output: 1

  // Example 2:
  // Input: root = [1,0,48,null,null,12,49]
  // Inorder: [0,1,12,48,49]
  // Minimum difference: 1
  // Output: 1

Time Complexity: O(n) — each node visited exactly once in recursion  
Space Complexity: O(h) — recursion stack, where h is tree height  
Is it most optimal? ✅ Yes, for extra space this recursive approach is fine.  
Will it be accepted by LeetCode? ✅ Yes, no TLE or MLE issues for normal constraints.

Approach Used:
  - Recursive inorder traversal
  - Maintain a class-level pointer 'prev' to store previously visited node
  - Update minimum difference while traversing nodes in sorted (inorder) order
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/* Definition for a binary tree node (LeetCode-style) */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    TreeNode* prev = nullptr; // Keeps track of previously visited node in inorder traversal

    // -------------------------
    // minDiffInBST (Recursive)
    // -------------------------
    // Purpose:
    //   Find minimum absolute difference between any two nodes in a BST
    // Method:
    //   - Recursive inorder traversal: left -> current -> right
    //   - prev stores last visited node in inorder (sorted order)
    //   - Update minimum difference at current node using prev
    int minDiffInBST(TreeNode* root) {
        if (root == nullptr) return INT_MAX; // Base case: empty node

        int ans = INT_MAX;

        // Recurse left
        if (root->left) {
            int leftMin = minDiffInBST(root->left);
            ans = min(ans, leftMin); // Update min with left subtree
        }

        // Process current node
        if (prev) {
            ans = min(ans, root->val - prev->val); // Difference with previous inorder node
        }
        prev = root; // Update prev to current node

        // Recurse right
        if (root->right) {
            int rightMin = minDiffInBST(root->right);
            ans = min(ans, rightMin); // Update min with right subtree
        }

        return ans;
    }
};

/* --------------------------------------------------------------------------------
Detailed Explanation & Logic (below class, above main)
--------------------------------------------------------------------------------

1) Why recursive inorder?
   - BST inorder traversal visits nodes in ascending order.
   - Consecutive nodes in inorder sequence are closest in value.
   - prev pointer keeps track of previously visited node in this sorted order.

2) How minimum difference is computed:
   - At each node, compute `curr->val - prev->val` (prev != nullptr)
   - Compare with current minimum and update.
   - This ensures all adjacent differences are considered.

3) Why 'prev' is class-level:
   - Because recursion moves left -> current -> right, we need persistent storage of last visited node.
   - A local variable would reset during recursion.

4) Base case:
   - If node is NULL, return INT_MAX (no contribution to min difference)

5) Complexity:
   - Time: O(n) — every node visited once
   - Space: O(h) — recursion stack (h = height of BST)
--------------------------------------------------------------------------------
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Build example tree:
    //       4
    //      / \
    //     2   6
    //    / \
    //   1   3
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n2 = new TreeNode(2, n1, n3);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* root = new TreeNode(4, n2, n6);

    Solution sol;
    int ans = sol.minDiffInBST(root); // Using recursive approach with prev pointer
    cout << "Minimum absolute difference: " << ans << "\n";

    // Clean up nodes to avoid memory leaks
    delete n1; delete n3; delete n2; delete n6; delete root;

    return 0;
}

/*
--------------------------------------------------------------------------------
KEY INSIGHTS, WARNINGS, AND SIMILAR QUESTIONS / APPROACHES
--------------------------------------------------------------------------------

Important details / warnings:
  - Always update prev after visiting current node.
  - Do not reset prev during recursion; it must persist across left -> current -> right.
  - Integer overflow: if node values can be large negatives/positives, use long long for difference.

Key insights:
  - BST property + inorder traversal → sorted values → min difference occurs between consecutive nodes.
  - Recursion makes the logic simpler; O(h) space is acceptable in interviews.
  - prev pointer is essential to track the last node visited in sorted order.

Similar LeetCode problems / variants:
  - LeetCode 530: Minimum Absolute Difference in BST
  - Iterative stack-based inorder solution (O(h) space)
  - Morris inorder traversal (O(1) space)
  - For non-BST trees, inorder does not sort → must collect all values and sort before computing min.

--------------------------------------------------------------------------------
End of notes + complete, runnable code block.
--------------------------------------------------------------------------------
*/
