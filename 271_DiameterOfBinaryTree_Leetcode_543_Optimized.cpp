// =======================
// LeetCode Problem 543: Diameter of Binary Tree
// =======================
// Problem Brief:
// Given the root of a binary tree, return the length of the diameter of the tree.
// The diameter is the length of the longest path between any two nodes in the tree.
// The path may or may not pass through the root.
//
// Example:
// Input: [1,2,3,4,5]
// Output: 3
// Explanation: The longest path is [4,2,1,3] or [5,2,1,3], with length 3.

// =======================
// Approach used:
// Recursive approach to calculate diameter by finding the maximum of:
// 1. Diameter of left subtree
// 2. Diameter of right subtree
// 3. Sum of heights of left and right subtrees at current node (which represents path through current node)
// =======================
// Time Complexity:
// O(n^2) — because at each node, we compute height by traversing subtrees again.
//
// Space Complexity:
// O(h) — due to recursion stack, where h is the height of the tree.

// ✅ This approach will be accepted by LeetCode but it's not the most optimal.
// ✅ For larger inputs, this may cause TLE because of recalculating heights multiple times.

// =======================
// Headers
// =======================
#include<iostream>
#include<algorithm>
using namespace std;

// =======================
// Definition for binary tree node
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
    // Function: height
    // =======================
    // Calculates the height of the tree rooted at 'root'.
    int height(TreeNode* root){
        if(root == NULL)
            return 0; // Base case: empty tree has height 0

        // Recursively calculate the height of the left subtree
        int leftht = height(root->left);

        // Recursively calculate the height of the right subtree
        int rightht = height(root->right);

        // The height of the current node is the max of left/right subtree heights plus 1
        return max(leftht, rightht) + 1;
    }

    // =======================
    // Function: diameterOfBinaryTree
    // =======================
    // Calculates the diameter of the tree rooted at 'root'
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL)
            return 0; // Base case: empty tree has diameter 0

        // Diameter of left subtree
        int leftDiameter = diameterOfBinaryTree(root->left);

        // Diameter of right subtree
        int rightDiameter = diameterOfBinaryTree(root->right);

        // Diameter through the current node is sum of heights of left and right subtrees
        int currDiameter = height(root->left) + height(root->right);

        // Final diameter is the maximum among:
        // 1. left subtree diameter
        // 2. right subtree diameter
        // 3. current node's diameter
        return max(leftDiameter, max(rightDiameter, currDiameter));
    }
};

// =======================
// Logic Explanation
// =======================
// ✔ We want to find the longest path between any two nodes in the tree.
// ✔ At each node, the longest path might either:
//   - Be entirely in the left subtree
//   - Be entirely in the right subtree
//   - Go through the current node (combining left and right subtree heights)
// ✔ We calculate all three possibilities and take the maximum at each node.
// ✔ The 'height' function helps compute the longest path through the current node.
// ✔ 'leftDiameter' and 'rightDiameter' are recursive calls that calculate the maximum path in subtrees.
// ✔ 'currDiameter' represents the path length passing through the current node.
// ✔ We return the maximum among these to ensure that we account for all paths.
// ✔ This solution recalculates heights at each node, leading to increased complexity.

// =======================
// Main Function & Working Example
// =======================
int main() {
    // Create the binary tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution solution;
    int result = solution.diameterOfBinaryTree(root);

    cout << "Diameter of the binary tree is: " << result << endl;

    return 0;
}

// =======================
// Important Details, Warnings & Key Insights
// =======================
// ✔ This approach is correct but inefficient for large trees due to recalculating subtree heights.
// ✔ It will be accepted by LeetCode but can lead to TLE on larger inputs.
// ✔ It's essential to avoid redundant calculations to optimize performance.

// ⚠ Warning:
// Do not use this method for very large trees unless you are certain that it fits within the problem constraints.

// ✅ Key Insights:
// - The diameter is either fully contained in a subtree or passes through the current node.
// - Recursive functions can be combined or separated depending on how information is shared.
// - Understanding how to redefine problems (like turning diameter into a max of three cases) is crucial for problem-solving.

// ✅ Similar Questions & Approaches:
// • Diameter of N-ary Tree — using DFS with memoization.
// • Maximum Depth of Binary Tree — simpler version focusing only on subtree height.
// • Check if a tree is balanced — recursive subtree height comparisons.
// • Optimize this problem by combining height and diameter calculations in a single traversal using a helper function.
