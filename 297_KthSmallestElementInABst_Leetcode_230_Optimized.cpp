/*
LeetCode — Problem Notes & Complete Code
Question Number: 230
Title (brief): Kth Smallest Element in a BST

Problem (brief):
  Given the root of a Binary Search Tree (BST) and an integer k, return the k-th smallest element
  in the BST.

Examples (as comments):
  // Example 1:
  // Input: root = [3,1,4,null,2], k = 1
  // Tree:
  //       3
  //      / \
  //     1   4
  //      \
  //       2
  // Inorder: [1,2,3,4] -> 1st smallest = 1
  // Output: 1

  // Example 2:
  // Input: root = [5,3,6,2,4,null,null,1], k = 3
  // Tree:
  //         5
  //       /   \
  //      3     6
  //     / \
  //    2   4
  //   /
  //  1
  // Inorder: [1,2,3,4,5,6] -> 3rd smallest = 3
  // Output: 3

Approach used: Morris Inorder Traversal
  - This is an iterative, O(1) auxiliary space method (excluding output storage).
  - Visits nodes in inorder without recursion or stack by temporarily creating "threads" (right pointers to parent).

Time Complexity: O(n)  -> Each node is visited at most twice.
Space Complexity: O(n) -> Vector stores inorder elements. If we do on-the-fly counting, can reduce to O(1) extra space.

Is it most optimal?
  - Time: yes, O(n) is required.
  - Space: Not absolute optimal since we store a vector; can reduce to O(1) with on-the-fly counting.
  
LeetCode Acceptance:
  - Yes, accepted. Will not cause TLE or MLE for typical constraints.

--------------------------------------------------------------------------------
BOILERPLATE, FULL WORKING SOLUTION (Morris + Vector)
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

    // ------------------------------------------
    // kthSmallest using Morris Traversal (with vector)
    // ------------------------------------------
    // Purpose:
    //   Generate inorder sequence (sorted values) of BST and return k-th element.
    int kthSmallest(TreeNode* root, int k) {
        vector<int> ans;         // store inorder traversal result
        TreeNode* curr = root;   // start from root node

        while(curr != nullptr){
            if(curr->left == nullptr){
                // CASE 1: No left child → visit node and move right
                ans.push_back(curr->val);
                curr = curr->right;
            }
            else{
                // CASE 2: Left child exists → find inorder predecessor
                TreeNode* IP = curr->left; // left subtree root
                while(IP->right != nullptr && IP->right != curr)
                    IP = IP->right; // rightmost node in left subtree

                if(IP->right == nullptr){
                    // Create thread back to parent
                    IP->right = curr;
                    curr = curr->left; // continue left
                }
                else{
                    // Thread exists → restore tree and visit current
                    IP->right = nullptr;
                    ans.push_back(curr->val);
                    curr = curr->right;
                }
            }
        }

        // k-th smallest in 1-based indexing
        return ans[k-1];
    }
};

/*

 NOTE ABOUT DUPLICATES:
 Standard BSTs do NOT allow duplicate values.
 The in-order traversal produces a strictly increasing sequence.
 This is why accessing ans[k-1] correctly gives the k-th smallest element.
 If duplicates were allowed, the sequence could have repeated values,
 and simply using k-1 could return the wrong element.
 Always remember: the correctness of this approach depends on unique BST values.

 */

/*
--------------------------------------------------------------------------------
Detailed Explanation & Logic (below class, above main)
--------------------------------------------------------------------------------

1) Why inorder traversal?
   - BST property: left < root < right.
   - Inorder traversal produces nodes in **sorted order**.
   - k-th smallest element = (k-1)-th index in inorder sequence.

2) Why Morris traversal?
   - Avoids recursion stack and explicit stack.
   - Uses temporary "threads" to remember return points.
   - Each node visited twice: once when creating thread, once when removing.

3) How it works step-by-step:
   - For each node:
     * If no left child → visit node (push_back), move right.
     * Else → find inorder predecessor in left subtree.
       - If predecessor's right is null → create thread, move left.
       - Else → thread exists → remove thread, visit node, move right.

4) Why vector works:
   - Collect all elements in sorted order.
   - Return ans[k-1] directly.
   - Alternative: keep a counter and return immediately after k elements (O(1) extra space).

5) Key points:
   - Do not return before restoring threads → breaks tree and can crash program.
   - Vector approach simpler and safer for learning.
   - Count-based approach avoids extra memory.

--------------------------------------------------------------------------------
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example BST: [3,1,4,null,2]
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n1 = new TreeNode(1, nullptr, n2);
    TreeNode* n4 = new TreeNode(4);
    TreeNode* root = new TreeNode(3, n1, n4);

    Solution sol;
    int k = 1;
    int ans = sol.kthSmallest(root, k);
    cout << "The " << k << "-th smallest element is: " << ans << "\n";

    // Free memory
    delete n2;
    delete n1;
    delete n4;
    delete root;

    return 0;
}

/*
--------------------------------------------------------------------------------
KEY INSIGHTS, WARNINGS, SIMILAR QUESTIONS / APPROACHES
--------------------------------------------------------------------------------

Important details / warnings:
  - Thread must be removed before visiting parent (or before returning).
  - k is 1-based indexing; ans[k-1] in vector.
  - Vector approach uses O(n) extra space.
  - On-the-fly count tracking avoids vector and achieves O(1) extra space.

Key insights:
  - BST inorder = sorted order → simplifies "k-th smallest" problem.
  - Morris traversal avoids stack/recursion overhead.

Similar LeetCode problems:
  - 230: Kth Smallest Element in a BST
  - 78: Subset problems using iterative/recursion techniques
  - Variants: find kth largest → reverse inorder

Alternative approaches:
  1) Recursive inorder + counter (simplest, O(h) stack)
  2) Iterative stack-based inorder
  3) Morris traversal with counter (O(1) space, no vector)
  4) Maintain node counts in BST → O(log n) query for k-th smallest

--------------------------------------------------------------------------------
End of notes + complete, runnable code block.
--------------------------------------------------------------------------------
*/
