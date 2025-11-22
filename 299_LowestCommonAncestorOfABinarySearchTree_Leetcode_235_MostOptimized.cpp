/*
LeetCode 235: Lowest Common Ancestor of a Binary Search Tree (BST)
Problem Brief:
Given a BST and two nodes p and q, find their lowest common ancestor (LCA). 
The LCA of two nodes in a BST is the lowest node that has both p and q as descendants 
(we allow a node to be a descendant of itself).

Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: LCA of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: LCA of nodes 2 and 4 is 2 (node itself).

Solution Method: Recursive BST Property Approach
Time Complexity: O(h), where h = height of the BST
Space Complexity: O(h), due to recursion stack
Optimality: Yes, this is optimal for recursive approach.
Accepted on LeetCode: Yes, will not cause TLE or MLE.
*/

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

        if(root==NULL) return root; // not necessary as it is guarenteed that p and q will exist in BST
        
        // Conditional 1: if both nodes are smaller than root, LCA lies in left subtree
        if(root->val > p->val && root->val > q->val){
            return lowestCommonAncestor(root->left, p, q);
        }
        // Conditional 2: if both nodes are larger than root, LCA lies in right subtree
        else if(root->val < p->val && root->val < q->val){
            return lowestCommonAncestor(root->right, p, q);
        }
        // Conditional 3: if nodes are on opposite sides or one node equals root, root is LCA
        else return root;
    }
};

/*
Logic Explanation:
- BST property: left < root < right
- Start from root:
  1. If both p and q < root → both must be in left subtree → recurse left.
  2. If both p and q > root → both must be in right subtree → recurse right.
  3. Otherwise, they are split across root → current root is LCA.
- Guarantee:
  - The split point ensures the lowest node that has both p and q as descendants is returned.
  - Dry Run Example:
    root=6, p=2, q=8 → 2<6<8 → LCA=6 (split point)
    root=6, p=2, q=4 → 2<6 and 4<6 → recurse left → root=2 → 2==p → LCA=2

Important Details, Warnings, Key Insights:
- No need for NULL check if p and q guaranteed to exist in BST.
- Works because BST property allows direct decisions.
- Recursive stack is proportional to height h.
- Iterative approach can reduce space to O(1).
- Similar Problems:
  1. 236. LCA of Binary Tree (general BT)
  2. 1644. Lowest Common Ancestor of a Binary Tree II
  3. 1123. Lowest Common Ancestor of Deepest Leaves
*/

int main() {
    // Construct BST Example:
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);

    Solution sol;
    TreeNode* p = root->left;       // Node 2
    TreeNode* q = root->right;      // Node 8

    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);
    cout << "LCA of " << p->val << " and " << q->val << " is " << lca->val << endl;

    p = root->left;       // Node 2
    q = root->left->right; // Node 4
    lca = sol.lowestCommonAncestor(root, p, q);
    cout << "LCA of " << p->val << " and " << q->val << " is " << lca->val << endl;

    return 0;
}

/*
Key Notes:
- Recursive approach is simple and optimal for BST.
- Iterative approach can achieve O(1) space by walking down the tree:
    while(root){
        if(root->val > p->val && root->val > q->val) root = root->left;
        else if(root->val < p->val && root->val < q->val) root = root->right;
        else return root;
    }
- LCA is always guaranteed by BST split property.
- Dry-run examples are crucial to fully understand why base NULL check is unnecessary here.
*/
