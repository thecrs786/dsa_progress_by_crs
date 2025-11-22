/*
LeetCode Problem 94 - Binary Tree Inorder Traversal

Based on Inorder Traversal : Already Discussed before (263)

Question (in brief):
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Approach Used:
- Recursive Inorder Traversal.
- We traverse left subtree → visit node → traverse right subtree.

Time Complexity: O(n), where n is the number of nodes (each node is visited once).
Space Complexity: O(n), for the recursion stack in worst case and the output vector.

Most Optimal?: 
✔ It's efficient and widely accepted for this problem.
✘ Not the most optimal in space. Morris Traversal offers O(1) extra space.
Accepted by LeetCode?: 
✔ Yes, this solution passes all test cases without MLE (Memory Limit Exceeded) or TLE (Time Limit Exceeded).
Warnings:
⚠ For very deep or skewed trees, recursion stack may cause MLE in extreme cases.
Key Insights:
✔ Simple and clean implementation.
✔ Good for interviews unless asked for space optimization.
Similar Questions:
- 145. Binary Tree Postorder Traversal (change the order of operations)
- 144. Binary Tree Preorder Traversal
- 102. Binary Tree Level Order Traversal (use BFS instead of DFS)
*/

#include <iostream>
#include <vector>
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

class Solution {
public:
    // Recursive helper function to perform inorder traversal.
    void helper(TreeNode* root, vector<int> &ans) {
        // Base case: If the current node is NULL, simply return.
        if (root == NULL) return;

        // Step 1: Traverse the left subtree recursively.
        helper(root->left, ans);

        // Step 2: Visit the current node by adding its value to the result vector.
        ans.push_back(root->val);

        // Step 3: Traverse the right subtree recursively.
        helper(root->right, ans);
    }

    // Main function that initializes the answer vector and calls helper.
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans; // Vector to store the inorder traversal sequence.
        helper(root, ans); // Start traversal from root.
        return ans; // Return the result vector.
    }
};

/*
LOGIC AND EXPLANATION:

1. The inorder traversal follows the sequence: left subtree → node → right subtree.
2. We recursively call the left child first, to process all nodes on the leftmost path.
3. Once left subtree is fully processed, we add the current node's value to the result.
4. We then proceed to the right subtree recursively.
5. This ensures that nodes are visited in the correct inorder sequence.
6. The base case is when the node is NULL; we simply return without processing further.

WORKING OF THE FUNCTION:

For example, given the tree:
        1
         \
          2
         /
        3

- First, we start at node 1.
- Left child is NULL → return → add 1 to ans.
- Move to right child 2.
- Move to left child 3.
- Left child is NULL → return → add 3 → right is NULL → return.
- Add 2 → move to right, which is NULL → return.

Final result = [1, 3, 2].

*/

// MAIN FUNCTION TO TEST AND ANALYZE OUTPUT
int main() {
    // Manually constructing the tree:
    //     1
    //      \
    //       2
    //      /
    //     3
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    Solution solution;
    vector<int> result = solution.inorderTraversal(root);

    // Printing the result to verify correctness
    cout << "Inorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, AND KEY INSIGHTS:

✔ Recursion is elegant but limited by stack size for deep trees.
✔ This solution is acceptable in most coding interviews.
✔ Iterative or Morris approaches can be used when space constraints are strict.
✔ Always remember that inorder traversal is widely used in BST problems.

⚠ Warning: Deep or skewed trees may cause runtime errors due to stack overflow.
✔ Good practice: Know both recursive and iterative implementations.

SIMILAR QUESTIONS:
- 144. Binary Tree Preorder Traversal (use root → left → right sequence)
- 145. Binary Tree Postorder Traversal (use left → right → root sequence)
- 102. Binary Tree Level Order Traversal (use BFS with queue)
- 98. Validate Binary Search Tree (use inorder traversal to check order)

APPROACH VARIATIONS:
✔ Recursive traversal (clean and simple)
✔ Iterative traversal with stack (handles deeper trees safely)
✔ Morris traversal (most space-efficient with O(1) extra space)
*/
