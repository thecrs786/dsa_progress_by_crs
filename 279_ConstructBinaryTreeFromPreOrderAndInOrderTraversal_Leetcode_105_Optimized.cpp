// Problem: LeetCode 105 - Construct Binary Tree from Preorder and Inorder Traversal
// Question in Brief:
// Given preorder and inorder traversals of a binary tree, construct and return the original tree.
// preorder is the list where the first element is the root, followed by left and right subtree traversals.
// inorder is the list where the left subtree, root, and then right subtree are arranged.
// Example:
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: The tree built is: 
/*
      3
     / \
    9  20
       /  \
      15   7

*/

// Time Complexity: O(N^2) → Searching for the index in inorder array takes O(N) for each node.
// Space Complexity: O(H) → Stack space due to recursion, where H is the height of the tree.
// Is this the most optimal solution? → ❌ No, because searching takes O(N) for each node. A hash map can reduce it to O(1).
// Will it be accepted by LeetCode or cause MLE/TLE? → ✅ Accepted for small to medium test cases, but ❌ may cause TLE for larger inputs.

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
    // Function to find index of value in inorder traversal.
    int search(vector<int>& inorder, int left, int right, int val){
        for(int i = left; i <= right; i++){
            if(inorder[i] == val) return i;
        }
        return -1; // Should never happen if input is valid.
    }

    // Recursive helper function to build tree.
    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int& preIdx, int left, int right){
        // Base case: if the current segment is invalid, return NULL.
        if(left > right) return NULL;

        // Create a new node with the current value from preorder.
        TreeNode* root = new TreeNode(preorder[preIdx]);

        // Find the index of this node in inorder traversal.
        int inIdx = search(inorder, left, right, preorder[preIdx]);

        // Move to the next element in preorder for future recursive calls.
        preIdx++;

        // Recursively build the left subtree using elements before inIdx.
        root->left = helper(preorder, inorder, preIdx, left, inIdx - 1);

        // Recursively build the right subtree using elements after inIdx.
        root->right = helper(preorder, inorder, preIdx, inIdx + 1, right);

        // Return the constructed subtree rooted at 'root'.
        return root;
    }

    // Main function to start building tree from given traversals.
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int preIdx = 0; // Initialize preorder index.
        return helper(preorder, inorder, preIdx, 0, inorder.size() - 1);
    }
};

/*
LOGIC EXPLAINED:

1. Base case:
   - If left > right, it means there's no node to process → return NULL.

2. Picking the root:
   - The current node is at preorder[preIdx] → build a TreeNode with this value.

3. Finding the division point:
   - Locate this value's index in inorder traversal → it separates left and right subtrees.

4. Recursive calls:
   - Left subtree → elements before inIdx in inorder.
   - Right subtree → elements after inIdx in inorder.

5. Preorder index management:
   - Increment preIdx after creating the node → so next call uses the correct element.

6. Return the root:
   - Once left and right subtrees are built, return the root node.

WHY THIS WORKS:
- Preorder gives the current root node.
- Inorder tells how to divide nodes into left and right subtrees.
- Recursion solves subproblems for each segment.
- The process ensures correct tree reconstruction.

EDGE CASES HANDLED:
✔ Single-node tree → works.
✔ Skewed tree (all left or all right) → recursion handles it.
✔ Complete binary tree → correctly splits into left/right parts.
✔ Empty segments → base case returns NULL.

RETURN TYPE:
✔ Each call returns the subtree built from that segment.

STACK ERASE EXPLANATION:
✔ Recursive calls are handled and unwind properly, connecting subtrees at the correct root nodes.

*/

// FUNCTION TO PRINT TREE INORDER FOR VERIFICATION
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// MAIN FUNCTION WITH EXAMPLE TEST CASE
int main() {
    Solution sol;
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    TreeNode* root = sol.buildTree(preorder, inorder);

    cout << "Inorder traversal of constructed tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, KEY INSIGHTS:

✔ Warning 1: The 'search' function is O(N), so this solution is inefficient for large inputs.
✔ Warning 2: Ensure input traversals are valid and correspond to the same tree → otherwise index -1 or segmentation faults may occur.
✔ Insight 1: Preorder always gives the root node → use it to pick nodes in order.
✔ Insight 2: Inorder helps divide the problem → find left and right subtrees.
✔ Insight 3: Recursive structure mirrors the tree’s actual shape → ideal for constructing trees.
✔ Insight 4: Recursion unwinds and connects the correct subtrees → forming the full tree.

SIMILAR QUESTIONS:
✔ LeetCode 106 - Construct Binary Tree from Inorder and Postorder Traversal → similar logic, use postorder instead.
✔ LeetCode 889 - Construct Binary Tree from Preorder and Postorder Traversal → requires handling missing information differently.
✔ LeetCode 98 - Validate Binary Search Tree → not construction, but uses recursion to process tree structure.

APPROACH VARIATIONS:
✔ Optimized approach → use a hash map to store inorder indices and reduce search to O(1).
✔ Iterative approach → more complex, less intuitive than recursion.
✔ Dynamic programming approaches → unnecessary for this problem, recursion is best.
*/
