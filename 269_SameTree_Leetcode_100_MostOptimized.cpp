// =======================
// LeetCode Problem 100: Same Tree
// =======================
// Given the roots of two binary trees p and q, write a function to check if they are the same or not.
// Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

// Example 1:
// Input: p = [1,2,3], q = [1,2,3]
// Output: true
// Explanation: Both trees are exactly the same.

// Example 2:
// Input: p = [1,2], q = [1,null,2]
// Output: false
// Explanation: The structure of the trees is different.

// Example 3:
// Input: p = [1,2,1], q = [1,1,2]
// Output: false
// Explanation: The structure is the same, but node values differ.

// =======================
// Approach Used: Recursive Depth-First Search (DFS)
// =======================
// We compare each corresponding node from the two trees:
// 1. If both are NULL -> they are same at this branch.
// 2. If one is NULL and the other is not -> trees differ.
// 3. If values differ -> trees differ.
// 4. Otherwise, recursively check left and right subtrees.

// =======================
// Time Complexity: O(N)
// Where N is the total number of nodes in the smaller tree.
// We visit each node once.

// Space Complexity: O(H)
// Where H is the height of the tree due to recursion stack space.
// In worst case (skewed tree): O(N), best case (balanced tree): O(log N).

// =======================
// Is it optimal? ✅ Yes
// Will it be accepted? ✅ Yes, it will not cause TLE or MLE.
// It's the standard optimal recursive solution.

#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// =======================
// Class Solution with recursive approach
// =======================
class Solution {
public:

    // Helper function that recursively checks if two trees are identical.
    bool helper(TreeNode* p, TreeNode* q) {
        // 1. Base Case 1:
        // If both nodes are NULL, this branch is identical so far.
        if(p == nullptr && q == nullptr) return true;

        // 2. Base Case 2:
        // If one node is NULL and the other is not, trees differ here.
        if(p == nullptr || q == nullptr) return false;

        /* INSTEA OF 1 & 2
        if(p == nullptr || q == nullptr) return p==q; 
        */

        // Base Case 3:
        // If the values of current nodes are not equal, trees differ here.
        if(p->val != q->val) return false;

        // Recursive Case:
        // Check both left and right subtrees. Both must be identical for the whole tree to be identical.
        return helper(p->left, q->left) && helper(p->right, q->right);
    }

    // Main function that initiates the recursive checking.
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return helper(p, q);
    }
};

// =======================
// EXPLANATION OF LOGIC & FUNCTION WORKING
// =======================
/*
✔ We use recursion to compare nodes at each level of the trees.
✔ Base case 1 ensures that both NULL nodes are treated as matching leaves.
✔ Base case 2 ensures early exit if one node is NULL and the other isn't.
✔ Base case 3 ensures that mismatched values at any node stop further recursion.
✔ We recursively check left and right subtrees, ensuring structure and values match at every step.
✔ Logical AND is used because both left and right subtrees must be identical for the trees to be the same.
✔ This method avoids unnecessary traversals and stops early when mismatches are detected.
*/

// =======================
// MAIN FUNCTION WITH EXAMPLES
// =======================
int main() {
    // Example 1:
    TreeNode* tree1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    TreeNode* tree2 = new TreeNode(1, new TreeNode(2), new TreeNode(3));

    Solution sol;
    cout << "Example 1 - Trees are same? " << (sol.isSameTree(tree1, tree2) ? "True" : "False") << endl;

    // Example 2:
    TreeNode* tree3 = new TreeNode(1, new TreeNode(2), nullptr);
    TreeNode* tree4 = new TreeNode(1, nullptr, new TreeNode(2));

    cout << "Example 2 - Trees are same? " << (sol.isSameTree(tree3, tree4) ? "True" : "False") << endl;

    // Example 3:
    TreeNode* tree5 = new TreeNode(1, new TreeNode(2), new TreeNode(1));
    TreeNode* tree6 = new TreeNode(1, new TreeNode(1), new TreeNode(2));

    cout << "Example 3 - Trees are same? " << (sol.isSameTree(tree5, tree6) ? "True" : "False") << endl;

    return 0;
}

// =======================
// IMPORTANT DETAILS, WARNINGS & KEY INSIGHTS
// =======================
/*
✔ Recursive base cases are crucial. Missing one will result in incorrect output or infinite recursion.
✔ Always check for NULL nodes before accessing node values to avoid segmentation faults.
✔ Using logical AND ensures both subtrees must match, not just one.
✔ Recursive depth depends on tree height. For very deep trees, stack overflow might occur; iterative solutions can be explored then.

Key Insights:
✔ Early stopping saves computation time.
✔ Structure and value comparison must go hand-in-hand.
✔ The recursive approach aligns naturally with tree structures.

Warnings:
✔ Ensure NULL checks come before dereferencing nodes.
✔ Avoid redundant recursive calls once mismatch is found.

Similar Questions:
✔ Symmetric Tree (LeetCode 101)
✔ Subtree of Another Tree (LeetCode 572)
✔ Maximum Depth of Binary Tree (LeetCode 104)
✔ Check Completeness of a Binary Tree

Approach Variations:
✔ Iterative BFS using queues.
✔ Iterative DFS using stacks.
✔ Serialization-deserialization methods for tree comparison.
*/
