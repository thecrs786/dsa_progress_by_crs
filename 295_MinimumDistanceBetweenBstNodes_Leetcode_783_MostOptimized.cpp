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

Time Complexity: O(n) — each node visited at most twice  
Space Complexity: O(1) extra space — Morris traversal (no recursion, no stack)  
Is it most optimal? ✅ Yes, both time and extra space are optimal  
Will it be accepted by LeetCode? ✅ Yes, no TLE or MLE issues

Approach Used:
  - Morris Inorder Traversal (on-the-fly)
  - Maintain a pointer 'prev' to track previously visited node in inorder
  - Update minimum difference during traversal
  - No vector or extra memory used
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

    // ---------------------------------
    // minDiffInBST (Morris traversal O(1) space)
    // ---------------------------------
    // Purpose:
    //   Find minimum absolute difference between any two nodes in BST
    // Method:
    //   - Traverse inorder using Morris traversal
    //   - Keep previous node pointer (prev)
    //   - Update mindis = min(mindis, curr->val - prev->val)
    int minDiffInBST(TreeNode* root) {
        TreeNode* curr = root;       // Current node in traversal
        TreeNode* prev = nullptr;    // Previous node visited in inorder
        int mindis = INT_MAX;        // Initialize minimum difference

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // CASE 1: No left child → current node is next in inorder
                if (prev) mindis = min(mindis, curr->val - prev->val);
                prev = curr;
                curr = curr->right;
            } else {
                // CASE 2: Left child exists → find inorder predecessor
                TreeNode* IP = curr->left;
                while (IP->right != nullptr && IP->right != curr)
                    IP = IP->right;

                if (IP->right == nullptr) {
                    // Create thread to return to curr after left subtree
                    IP->right = curr;
                    curr = curr->left;
                } else {
                    // Thread exists → left subtree visited, remove thread
                    IP->right = nullptr;
                    if (prev) mindis = min(mindis, curr->val - prev->val);
                    prev = curr;
                    curr = curr->right;
                }
            }
        }
        return mindis;
    }
};

/* --------------------------------------------------------------------------------
Detailed Explanation & Logic (below class, above main)
--------------------------------------------------------------------------------

1) Why inorder traversal?
   - BST inorder yields sorted values.
   - Minimum difference occurs between consecutive values in sorted order.

2) Why Morris traversal?
   - Avoid recursion/stack → O(1) extra space.
   - Temporarily link inorder predecessor to current node (thread) to backtrack.

3) Why 'prev' pointer?
   - Only need difference between consecutive nodes in sorted order.
   - prev stores last visited node; curr - prev gives candidate minimum.

4) Threading logic:
   - For node with left child, find rightmost node in left subtree (IP)
   - If IP->right is null, create thread to curr, move left
   - Else remove thread, visit curr, move right

5) Complexity:
   - Time: O(n)
   - Space: O(1) extra (prev, curr, IP pointers)
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
    int ans = sol.minDiffInBST(root);
    cout << "Minimum absolute difference: " << ans << "\n";

    // Clean up to avoid memory leaks
    delete n1; delete n3; delete n2; delete n6; delete root;

    return 0;
}

/*
--------------------------------------------------------------------------------
KEY INSIGHTS, WARNINGS, AND SIMILAR QUESTIONS / APPROACHES
--------------------------------------------------------------------------------

Important details / warnings:
  - Always remove temporary threads; otherwise tree is corrupted.
  - Be careful with integer overflow for large node values.
  - Works only for BST; for arbitrary binary trees, inorder is not sorted.

Key insights:
  - BST property + inorder → sorted → only consecutive pairs needed
  - Morris traversal allows O(1) extra space computation
  - No vector needed; min difference computed on-the-fly

Similar LeetCode problems / variants:
  - LeetCode 530: Minimum Absolute Difference in BST
  - Recursive inorder with prev → O(h) space
  - Iterative stack-based inorder → O(h) space
  - Non-BST trees → need sorting or tree set to find min difference

--------------------------------------------------------------------------------
End of notes + complete, runnable code block.
--------------------------------------------------------------------------------
*/
