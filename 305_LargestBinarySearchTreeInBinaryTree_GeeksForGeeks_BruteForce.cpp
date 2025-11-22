#include <iostream>
#include <climits>
using namespace std;

/*
--------------------------------------------------------------------------------
GFG / LeetCode Style Problem: Largest BST in a Binary Tree (Brute Force Approach)
--------------------------------------------------------------------------------
Question (Brief):
Given a Binary Tree, find the size (number of nodes) of the largest subtree which is also a Binary Search Tree (BST).

Input: Root of a binary tree
Output: Size of the largest BST subtree

Example 1:
       10
      /  \
     5   15
    / \    \
   1   8    7

Largest BST subtree: 
       5
      / \
     1   8
Size = 3

Example 2:
       5
      / \
     2   4
    / \
   1   3

Largest BST subtree: 
       2
      / \
     1   3
Size = 3

--------------------------------------------------------------------------------
Approach Name:
Brute Force / Recursive Validation Approach

--------------------------------------------------------------------------------
Time Complexity:  O(n^2)  (for each node, we may traverse entire subtree to validate BST)
Space Complexity: O(h)    (recursion stack, h = height of tree)
Optimal?          ❌ No, brute force is not optimal
Accepted on GFG?  ✅ Works for small trees, may TLE for large trees
--------------------------------------------------------------------------------
*/

// ✅ Define structure for binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:

    // Function to check if a subtree is BST
    bool isBST(Node* root, int minVal, int maxVal){
        if(root == nullptr) return true;

        // Check current node
        if(root->data <= minVal || root->data >= maxVal) return false;

        // Check left and right subtree
        return isBST(root->left, minVal, root->data) && isBST(root->right, root->data, maxVal);
    }

    // Function to count nodes in a subtree
    int countNodes(Node* root){
        if(root == nullptr) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    // Brute force function to find largest BST
    int largestBST(Node* root){
        if(root == nullptr) return 0;

        // If the subtree rooted at current node is BST
        if(isBST(root, INT_MIN, INT_MAX)) return countNodes(root);

        // Otherwise, recursively check left and right subtrees
        int leftAns = largestBST(root->left);
        int rightAns = largestBST(root->right);

        // Return the larger BST size
        return max(leftAns, rightAns);
    }
};

/*
--------------------------------------------------------------------------------
LOGIC & EXPLANATION (Above main)
--------------------------------------------------------------------------------

1️⃣ Concept:
- For each node, consider it as root of a subtree.
- Check if subtree is a valid BST using min/max validation.
- If yes, count nodes in subtree and update maximum.
- Otherwise, recursively check left and right children.

2️⃣ Step-by-step logic:
- Function isBST(root, minVal, maxVal):
    → Returns true if subtree rooted at root is BST with all values between minVal and maxVal
- Function countNodes(root):
    → Counts total nodes in subtree rooted at root
- Function largestBST(root):
    → Base case: if null, return 0
    → If root subtree is BST: return countNodes(root)
    → Else, recursively check left and right subtrees
    → Return max of leftAns and rightAns

3️⃣ Why Brute Force is inefficient:
- For every node, we may traverse its entire subtree twice (once for BST check, once for counting)
- This gives O(n^2) time in worst case

--------------------------------------------------------------------------------
*/

int main(){
    /*
        Example Binary Tree:
                10
               /  \
              5   15
             / \    \
            1   8    7
    */

    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(1);
    root->left->right = new Node(8);
    root->right->right = new Node(7);

    Solution obj;
    int largest = obj.largestBST(root);

    cout << "Size of largest BST subtree: " << largest << endl; // Expected: 3

    return 0;
}

/*
--------------------------------------------------------------------------------
KEY INSIGHTS, WARNINGS & SIMILAR PROBLEMS
--------------------------------------------------------------------------------
- Brute force checks every subtree for BST validity → O(n^2)
- Optimal approach exists using bottom-up traversal (postorder) in O(n):
  → Track min, max, size, and BST validity in single traversal
- Key point: Each node may be root of a BST, so must validate left and right
- Warning: Brute force may TLE on large trees (>1000 nodes)
- Similar problems:
  → Count number of BST subtrees
  → Maximum sum BST in Binary Tree
  → Recover BST (inorder property)
- Key takeaway:
  → Brute force is simple to implement
  → Use optimized bottom-up approach for large trees
--------------------------------------------------------------------------------
*/
