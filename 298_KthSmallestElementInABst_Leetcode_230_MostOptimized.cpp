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

Solution Method: Recursive Inorder Traversal with Counter (prevOrder)
Time Complexity: O(h + k) ~ Average O(log n + k), Worst O(n)
Space Complexity: O(h) due to recursion stack (h = height of BST)
Optimal: Yes, more memory efficient than storing all nodes in a vector.
Accepted by LeetCode: Yes, no MLE or TLE.
*/

#include <bits/stdc++.h>
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
    int prevOrder = 0; // Counter to track number of nodes visited in-order
    
    int kthSmallest(TreeNode* root, int k) {
        if(root == NULL) return -1; // Safety check

        // Step 1: Traverse left subtree first
        if(root->left){
            int leftans = kthSmallest(root->left, k);
            if(leftans != -1) return leftans; // If k-th found in left subtree, return immediately
        }

        // Step 2: Process current node
        // prevOrder counts how many nodes have been visited so far
        if(prevOrder + 1 == k) return root->val; // Found k-th smallest
        prevOrder++; // Increment counter after visiting node

        // Step 3: Traverse right subtree
        if(root->right){
            int rightans = kthSmallest(root->right, k);
            if(rightans != -1) return rightans; // If k-th found in right subtree, return
        }

        return -1; // Not found in this path
    }
};

/*
Logic Explanation:

1. We perform an **inorder traversal** because in BST, inorder gives nodes in **sorted order**.
2. `prevOrder` keeps track of the number of nodes we have visited in inorder sequence.
3. When `prevOrder + 1 == k`, we have reached the k-th smallest node.
4. Recursion allows **early stopping**: once we find the k-th smallest, we propagate the value back.
5. Space is O(h) due to recursion stack. No extra vector is used, unlike other methods storing all nodes.
6. The function handles null nodes safely. If k is larger than total nodes, it returns -1.

Working of the function (Example walkthrough):
- BST: [3,1,4,null,2], k=1
- Inorder traversal: left -> root -> right
  - Go left: Node 1
    - Left of 1 is null
    - prevOrder=0; prevOrder+1==k → return 1
  - Function terminates early without visiting other nodes
- Efficient: only visits necessary nodes

Important Details, Warnings, Key Insights:
- This **works only for BST** due to sorted property of inorder traversal.
- No duplicates assumed in BST (standard definition), otherwise `prevOrder` logic needs adjustment.
- Avoid using vectors if k << n to save memory.
- Early stopping prevents unnecessary recursion and improves runtime.
- Recursion stack is O(h). For skewed BST, worst-case O(n).

Similar Questions / Approaches:
- Kth Largest Element in BST: Reverse inorder traversal (right -> root -> left).
- Find Median in BST: Use inorder traversal with counters.
- Recover BST, Range Sum BST: Can also use inorder traversal to efficiently traverse sorted nodes.
*/

int main() {
    // Construct BST manually
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);

    Solution sol;
    int k = 1;
    cout << "The " << k << "-th smallest element is: " << sol.kthSmallest(root, k) << endl;

    // Example output: 1
    return 0;
}
