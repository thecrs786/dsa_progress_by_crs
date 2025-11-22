// Problem: LeetCode 236 - Lowest Common Ancestor of a Binary Tree
// Question in Brief:
// Given a binary tree and two nodes p and q in it, find their lowest common ancestor (LCA).
// The LCA of two nodes is the lowest node in the tree that has both p and q as descendants (where we allow a node to be a descendant of itself).
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// Output: 3
// Explanation: The LCA of nodes 5 and 1 is node 3.

// Time Complexity: O(N) → Every node is visited once in the worst case.
// Space Complexity: O(H) → H is the height of the tree, due to recursion stack.
// Is this the most optimal solution? → Yes, for a general binary tree, this is optimal.
// Will it be accepted by LeetCode or cause MLE or TLE? → Accepted. It won’t cause MLE or TLE because recursion depth is limited by tree height.

// Approach Used: Post-order DFS recursion → Traverse left and right subtrees, and use recursion return values to determine the LCA.

#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Base Case 1: If current node is NULL → return NULL.
        if (!root) return NULL;
        
        // Base Case 2: If current node is either p or q → return current node.
        if (root == p || root == q) return root;

        // Recursively search left subtree for p and q.
        TreeNode* left = lowestCommonAncestor(root->left, p, q);

        // Recursively search right subtree for p and q.
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // If both left and right are non-NULL → p and q are found in different subtrees → current node is LCA.
        if (left && right) return root;

        // If only one subtree is non-NULL → propagate the non-NULL result upward.
        return left ? left : right;
    }
};

/*
LOGIC EXPLAINED:

1. Base cases:
   - If root is NULL → nothing to process, return NULL.
   - If root is either p or q → we've found one of the targets, return it.

2. Recursion:
   - We call the function on left and right subtrees to explore where p and q are located.
   - The return values from left and right tell us whether the subtree contains p, q, or nothing.

3. Decision making:
   - If both left and right return non-NULL → p is in one subtree, q is in another → current node is their lowest common ancestor.
   - If only one subtree returns non-NULL → both nodes are deeper in that subtree → propagate that node upward.

4. Recursion return type:
   - The function returns NULL if neither p nor q is found.
   - Returns the node itself if it’s p or q.
   - Returns the node where paths to p and q diverge → this is the answer.

5. Why it guarantees the correct answer:
   - The recursion ensures we explore all paths.
   - The function bubbles up information from leaves to root.
   - The split at the correct ancestor node is caught because it’s the point where both sides return non-NULL.

6. Edge cases handled:
   - One node is ancestor of another → base case catches it.
   - Tree is skewed → recursion still works.
   - Both nodes are on same side → recursion bubbles correct result.

7. How stacks are erased:
   - As recursion unwinds, the correct ancestor is returned by checking where left and right subtrees meet.

*/

// WORKING EXAMPLE FOR TESTING OUTPUT
int main() {
    // Build example tree
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode* p = root->left;        // Node with value 5
    TreeNode* q = root->right;       // Node with value 1

    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);

    cout << "LCA of " << p->val << " and " << q->val << " is: " << lca->val << endl;
    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, KEY INSIGHTS:

✔ Edge Case 1: If p or q is the root → base case handles this.
✔ Edge Case 2: If p and q are on the same subtree → recursion bubbles the answer correctly.
✔ Edge Case 3: If p and q are in different subtrees → left and right non-NULL → correct result.
✔ Avoid unnecessary subtree searches → recursion return values carry required information.
✔ Time complexity cannot be improved further for general trees → O(N) is optimal.
✔ Space complexity depends on recursion depth → ensure stack size is sufficient for large trees.

KEY INSIGHTS:
✔ The recursion effectively traverses the entire tree and bubbles up the presence of p and q.
✔ The moment both left and right subtrees are non-empty, you have found the split point — hence the LCA.
✔ Recursion unwinding is how the correct ancestor is returned to the top.

SIMILAR QUESTIONS:
✔ LeetCode 235 - Lowest Common Ancestor of a Binary Search Tree → can be optimized using BST properties.
✔ LeetCode 865 - Smallest Subtree with all the Deepest Nodes → similar recursive logic.
✔ LeetCode 1123 - Lowest Common Ancestor of Deepest Leaves → applies same recursion principles.
✔ Euler tour + RMQ problems → for multiple LCA queries efficiently.

APPROACH VARIATIONS:
✔ Parent pointers → works but uses extra memory.
✔ Iterative DFS or BFS → possible but recursion is clearer.
✔ Binary Lifting → useful for multiple queries, but unnecessary for single queries.
✔ BST-based optimization → only for ordered trees.

*/
