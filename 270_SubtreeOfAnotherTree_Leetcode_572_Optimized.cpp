// =======================
// LeetCode Problem 572: Subtree of Another Tree
// =======================
// Problem Brief:
// Given two binary trees, root and subRoot, check if subRoot is a subtree of root.
// A subtree of a tree is a tree consisting of a node in the tree and all of its descendants.
// The tree could also be exactly the same as the original tree.
//
// Example 1:
// Input:
// root = [3,4,5,1,2], subRoot = [4,1,2]
// Output: true
//
// Example 2:
// Input:
// root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
// Output: false

// =======================
// Approach: Recursion with helper function
// Name: isIdentical helper function to compare two trees for identical structure and values
// =======================
// Time Complexity:
// O(m * n), where m and n are the number of nodes in root and subRoot respectively.
// In the worst case, we might compare every node in root with subRoot.
//
// Space Complexity:
// O(h), where h is the height of the tree (due to recursive call stack).

// This is not the most optimized solution. There are approaches using hashing or serialization to improve time complexity.
// It will be accepted by LeetCode and will not cause MLE or TLE, but may not be the fastest for large inputs.

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// =======================
// Definition for a binary tree node
// =======================
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// =======================
// Solution Class
// =======================
class Solution {
public:

    // =======================
    // Helper Function: isIdentical
    // =======================
    // Checks if two trees are exactly the same in structure and values.
    // It is necessary because even if we find a node with the same value in root as subRoot, 
    // the subtree must also match completely.
    bool isIdentical(TreeNode* p, TreeNode* q){
        // Base case: if both nodes are NULL, they are identical
        if(p == nullptr || q == nullptr) return p == q;

        // Check current node value and recursively check left and right subtrees
        return p->val == q->val && isIdentical(p->left, q->left) && isIdentical(p->right, q->right);
    }

    // =======================
    // Main Function: isSubtree
    // =======================
    // Checks if subRoot is a subtree of root
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // Base case: if either is NULL, return if they are both NULL (true) or one is NULL (false)
        if(root == nullptr || subRoot == nullptr) return root == subRoot;

        // If current node matches, check if the trees are identical from here
        if(root->val == subRoot->val && isIdentical(root, subRoot)){
            return true;
        }

        // Otherwise, check left and right subtrees
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};

// =======================
// Explanation & Working
// =======================
// ✅ isSubtree starts at the root and looks for a node matching subRoot’s root value.
// ✅ Once found, isIdentical is called to ensure the whole subtree matches.
// ✅ isIdentical checks both structure and node values recursively.
// ✅ Base cases handle scenarios where one or both trees are empty.
// ✅ The recursive traversal ensures all possible subtree roots are checked.

// ✅ The helper function is necessary because finding a matching value does not guarantee identical structure and descendants.
// ✅ The recursion ensures that all nodes are explored, covering the entire root tree.

// =======================
// Main Function: Example run
// =======================
int main() {
    // Building the main tree root: [3,4,5,1,2]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(2);

    // Building the subtree subRoot: [4,1,2]
    TreeNode* subRoot = new TreeNode(4);
    subRoot->left = new TreeNode(1);
    subRoot->right = new TreeNode(2);

    Solution solution;
    bool result = solution.isSubtree(root, subRoot);

    cout << "Is subRoot a subtree of root? " << (result ? "Yes" : "No") << endl;

    return 0;
}

// =======================
// Important Details
// =======================
// ✔ Base cases are crucial to avoid null pointer errors and handle empty trees.
// ✔ The recursive approach elegantly traverses and compares trees node-by-node.
// ✔ The helper function ensures we only confirm subtree presence when structure matches completely.
// ✔ This method is clear, simple, and widely acceptable for typical problem sizes.

// =======================
// Warnings
// =======================
// ⚠ Deep recursion may cause stack overflow for very large trees.
// ⚠ Comparing trees naively may be inefficient for large datasets.

// =======================
// Key Insights
// =======================
// ✅ Tree problems often require traversal combined with condition checking.
// ✅ Separate helper functions improve readability and reusability.
// ✅ Recursive base cases are essential for correct termination and edge handling.

// =======================
// Similar Questions & Approaches
// =======================
// ✔ "Same Tree" problem - requires tree comparison similar to isIdentical.
// ✔ "Serialize and Deserialize Binary Tree" - efficient subtree checking using serialization.
// ✔ "Find Duplicate Subtrees" - hashing subtree structures for optimization.
// ✔ Approach variations include BFS, iterative DFS, or hashing techniques to improve performance.
