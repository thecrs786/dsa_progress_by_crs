/*
LeetCode — Problem Notes & Complete Code
Question Number: 530
Title (brief): Minimum Absolute Difference in BST

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
  // Output: 1 (minimum absolute difference between 1-2, 2-3, 3-4, 4-6)
  
  // Example 2:
  // Input: root = [1,0,48,null,null,12,49]
  // Output: 1 (minimum absolute difference between 0-1, 12-48, 48-49)
  
Time Complexity: O(n) — each node is visited once
Space Complexity: O(1) extra space — using Morris traversal; no recursion/stack needed
Is it most optimal? ✅ Time-optimal and space-optimal (O(1) extra space)
Will it be accepted by LeetCode? ✅ Yes, no TLE or MLE issues

Approach Used:
  - Morris Inorder Traversal (on-the-fly)
  - Keep a pointer 'prev' to track previously visited node in inorder
  - Update minimum difference between prev and current node
  - Avoids extra vector or recursion stack

--------------------------------------------------------------------------------
BOILERPLATE, FULL WORKING SOLUTION WITH THOROUGH COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/* Definition for a binary tree node (LeetCode-style). */
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
    // getMinimumDifference: Morris Inorder O(1) space
    // ---------------------------------
    // Logic:
    //   - Use Morris inorder traversal to visit nodes in ascending order (BST property)
    //   - Maintain 'prev' pointer to previous node visited
    //   - At each node, update mindis = min(mindis, curr->val - prev->val)
    //   - This gives minimum difference without using extra vector
    int getMinimumDifference(TreeNode* root) {
        TreeNode* curr = root;
        TreeNode* prev = nullptr; // previous node in inorder
        int mindis = INT_MAX;

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // No left child → process current node
                if (prev) mindis = min(mindis, curr->val - prev->val);
                prev = curr;
                curr = curr->right;
            } else {
                // Find inorder predecessor (rightmost node in left subtree)
                TreeNode* IP = curr->left;
                while (IP->right != nullptr && IP->right != curr)
                    IP = IP->right;

                if (IP->right == nullptr) {
                    // Thread not created → create temporary thread to return
                    IP->right = curr;
                    curr = curr->left;
                } else {
                    // Thread already created → left subtree visited, process current node
                    IP->right = nullptr; // remove temporary thread
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
1) Why Morris inorder traversal?
   - BST inorder visits nodes in ascending order.
   - Minimum absolute difference between any two nodes occurs between
     some pair of consecutive nodes in this inorder sequence.
   - Morris allows us to traverse without recursion/stack, using O(1) extra memory.

2) Why keep 'prev' pointer?
   - We only care about differences between consecutive nodes in sorted order.
   - prev stores the last visited node; current node - prev node gives candidate difference.

3) Why update mindis only for consecutive nodes?
   - In sorted array, the closest values are always neighbors.
   - Non-adjacent nodes will have differences larger or equal to some neighbor difference.
   - This guarantees we find the minimum difference efficiently.

4) Threading logic:
   - If node has left subtree:
       - Find rightmost node (inorder predecessor)
       - If right pointer of predecessor is null → create thread to curr
       - Else → remove thread, process curr, move right
   - This avoids recursion/stack overhead.

5) Edge Cases:
   - Tree with <2 nodes → problem constraints guarantee at least 2 nodes.
   - Duplicate values in BST → absolute difference could be 0 (problem allows this).

6) Complexity Summary:
   - Time: O(n)
   - Space: O(1) extra (thread pointers), O(1) tracking variables

--------------------------------------------------------------------------------
   Now: A working example (main) that builds a sample tree and runs the solution.
--------------------------------------------------------------------------------
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Construct example tree:
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
    int ans = sol.getMinimumDifference(root); // using O(1) Morris traversal solution
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
  - Do not forget to remove threads after visiting left subtree, else tree gets corrupted.
  - If values are very large, consider using long long for differences to avoid overflow.
  - Morris traversal modifies tree temporarily but restores it before moving right.

Key insights:
  - Inorder traversal of BST produces sorted values → reduces problem to min difference in sorted array.
  - Only consecutive nodes need to be checked.
  - This solution is O(n) time and O(1) extra space — optimal for interviews.

Similar LeetCode problems / variants:
  - LeetCode 783: Minimum Distance Between BST Nodes (same problem, different wording)
  - Variants: "Minimum absolute difference in array" → must sort array first or use set
  - Recursive / stack-based inorder solutions → use O(h) extra space

--------------------------------------------------------------------------------
End of notes + complete, runnable code block.
--------------------------------------------------------------------------------
*/
