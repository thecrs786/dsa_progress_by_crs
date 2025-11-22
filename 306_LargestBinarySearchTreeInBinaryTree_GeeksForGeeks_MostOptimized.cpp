/*
Question: Largest BST in a Binary Tree (GFG / Interview problem)

Brief:
Given a binary tree, find the size of the largest subtree which is a Binary Search Tree (BST).

Example:
        10
       /  \
      5   15
     / \    \
    1   8    7

Output: 3
Explanation: The largest BST subtree is:
       5
      / \
     1   8
Size = 3

Approach Used: Bottom-Up Recursive Traversal with Helper Info Class

Time Complexity: O(n) - Each node is visited exactly once.
Space Complexity: O(h) - Recursive stack space, h = height of tree.

Is it optimal? ✅ Yes, linear time and only recursion stack is used.
Will it be accepted? ✅ Yes, it will not cause TLE or MLE for large trees.

Key Idea:
- For every node, we need to know:
    1. The minimum value in its subtree
    2. The maximum value in its subtree
    3. The size of the largest BST in its subtree
- We create a class Info to return these three values for each subtree.

Similar Problems:
1. Count number of BST subtrees.
2. Maximum sum BST in a binary tree.
3. Validate BST problem (simpler version of subtree check).

*/

#include <bits/stdc++.h>
using namespace std;

/* Tree Node structure */
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

/* Info class to hold information for each subtree */
class Info {
public:
    int min;    // Minimum value in the subtree
    int max;    // Maximum value in the subtree
    int size;   // Size of largest BST in the subtree

    Info(int mi, int ma, int sz) {
        min = mi;
        max = ma;
        size = sz;
    }
};

/* Helper function: recursively computes Info for each subtree */
Info helper(Node* root) {
    // Base Case: Empty subtree
    if(root == NULL) {
        // For empty subtree:
        // min = INT_MAX (so parent node can consider itself as BST)
        // max = INT_MIN
        // size = 0
        return Info(INT_MAX, INT_MIN, 0);
    }

    // Recurse for left and right subtrees
    Info left = helper(root->left);
    Info right = helper(root->right);

    // Check if current node forms a BST with its left and right subtrees
    if(root->data > left.max && root->data < right.min) {
        // Current node satisfies BST property with left and right
        int currMin = min(root->data, left.min); // Update min for this subtree
        int currMax = max(root->data, right.max); // Update max for this subtree
        int currSize = left.size + right.size + 1; // Total nodes in this BST
        return Info(currMin, currMax, currSize); // Return info for this subtree
    }

    // If current subtree is NOT a BST
    // Return invalid min/max to prevent parent from considering it a BST
    // Size will be the max of left or right largest BST
    return Info(INT_MIN, INT_MAX, max(left.size, right.size));
}

/* Solution Class */
class Solution {
public:
    int largestBst(Node *root) {
        Info info = helper(root); // Call helper for entire tree
        return info.size;         // Largest BST size
    }
};

/*
Explanation / Logic:

1. Info Class:
    - min: Minimum value in subtree. Helps parent to validate BST property.
    - max: Maximum value in subtree. Helps parent to validate BST property.
    - size: Size of largest BST in this subtree.

2. Base Case:
    - For NULL node, we return min=INT_MAX, max=INT_MIN, size=0.
      Reason: Parent comparisons (root->data > left.max && root->data < right.min) will hold.

3. Recursive Step:
    - Compute left and right Info.
    - If root->data > left.max && root->data < right.min:
        -> Current node is BST
        -> Update currMin, currMax, currSize
        -> Return Info(currMin, currMax, currSize)
    - Else:
        -> Not a BST, return Info(INT_MIN, INT_MAX, max(left.size, right.size))
        -> Parent will not incorrectly consider this as BST

4. Bottom-Up Approach:
    - We calculate BST info from leaves to root.
    - Single pass ensures O(n) time.

5. Why min/max for NULL or invalid BST:
    - NULL: INT_MAX/INT_MIN ensures parent can become BST if conditions satisfy.
    - Invalid BST: INT_MIN/INT_MAX ensures parent cannot consider it as BST.

6. Working Process:
    - Traverse recursively
    - For each node, check BST condition
    - Keep track of largest BST size using Info.size

7. Dry Run (example tree):

        10
       /  \
      5   15
     / \    \
    1   8    7

- Leaf nodes: 1,8,7 → BST size=1
- Node 5: left.max=1, right.min=8 → 5>1 & 5<8 → BST size=3
- Node 15: right.min=7 → 15<7 fails → Not BST, size=max(left.size,right.size)=1
- Node 10: left.max=8, right.min=7 → 10>8 & 10<7 fails → Not BST, size=max(left.size,right.size)=3

Answer = 3

*/


// Driver code for testing
int main() {
    /*
    Construct example tree:
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

    Solution sol;
    cout << "Size of largest BST is: " << sol.largestBst(root) << endl;

    return 0;
}

/*
Key Insights / Warnings:
1. Always use INT_MIN / INT_MAX when marking invalid BSTs or NULL.
2. Bottom-up traversal avoids recomputation → O(n).
3. Do not try to check BST by visiting each subtree separately (would be O(n^2)).
4. Works for skewed, balanced, or mixed binary trees.
5. Similar Questions:
    - Maximum sum BST in binary tree
    - Count number of BST subtrees
    - Validate BST problem

*/
