/*
Question Number: 1008
Question: Construct Binary Search Tree from Preorder Traversal
Brief: Given an array representing the preorder traversal of a BST, construct and return the BST.

Example 1:
Input: preorder = [8,5,1,7,10,12]
Output: Root of BST
        8
       / \
      5   10
     / \    \
    1   7    12

Example 2:
Input: preorder = [1,2,3]
Output: Root of BST
    1
     \
      2
       \
        3

Constraints:
- preorder contains distinct integers
- 1 <= preorder.length <= 100
- 1 <= preorder[i] <= 10^8

Approach Name: Preorder Recursive Construction using Upper Bound
Time Complexity: O(n)  // Each node processed exactly once
Space Complexity: O(h) // Recursion stack, h = height of BST
Optimal: Yes
Accepted on LeetCode: Yes
Warnings: Will not cause TLE or MLE under given constraints
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Definition for a binary tree node
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

    // Helper function to recursively build BST
    TreeNode* helper(vector<int>& preorder, int& i, int bound){
        /*
        Logic:
        - i: Current index in preorder traversal
        - bound: Upper limit for the current subtree
        - Base case: If we reach the end of preorder or the current value exceeds bound, stop recursion
        - Create root node with preorder[i]
        - Increment i BEFORE recursive calls to ensure the next element is correctly considered
        - Left subtree: Values less than root->val, bound = root->val
        - Right subtree: Values less than current upper bound, bound = bound (inherited from parent)
        */
        
        if(i >= preorder.size() || preorder[i] > bound) return NULL; // Stop if no valid node

        TreeNode* root = new TreeNode(preorder[i]); // Create current root
        i++; // Move index to next element for subsequent recursive calls

        root->left = helper(preorder, i, root->val); // Left subtree has upper bound = root value
        root->right = helper(preorder, i, bound);    // Right subtree has upper bound = inherited bound

        return root;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0; // Start from the first index
        return helper(preorder, i, INT_MAX); // Upper bound initially +infinity
    }
};

/*
Detailed Explanation & Logic:

1. Why increment i BEFORE recursion?
   - i represents the current index in preorder.
   - We create a node with preorder[i], then increment i so that the next call considers the next element.
   - This ensures we traverse preorder sequentially without missing or repeating elements.

2. Return type logic:
   - Each helper call returns a TreeNode* representing the root of that subtree.
   - Base case returns NULL if no valid node exists (either index out of bounds or value > bound).

3. Why only upper bound is needed, not lower bound:
   - Preorder traversal ensures nodes are visited Root -> Left -> Right.
   - Left subtree will always contain nodes < root->val and are visited first.
   - Right subtree nodes appear after left subtree nodes in preorder.
   - Example impossible scenario handled by preorder: [4, 8, 1] (cannot be preorder of valid BST)
   - Hence, lower bound is implicitly handled; no need to track it.

4. How recursion works:
   - Recursive calls build left subtree until bound is hit.
   - Once left subtree is done, the next element that exceeds left bound becomes part of right subtree.
   - Recursion unwinds naturally to parent nodes as bounds are exceeded.

5. Key insight:
   - Upper bound acts as a "guardrail" to know when a subtree ends.
   - Preorder + BST property ensures sequential correctness.
*/

/*
Working Example:
Preorder: [8,5,1,7,10,12]

Step by step:
i=0: root=8, i=1
    left subtree, bound=8:
        i=1: root=5, i=2
            left subtree, bound=5:
                i=2: root=1, i=3
                    left: i=3, preorder[3]=7>5 → NULL
                    right: i=3, preorder[3]=7>5 → NULL
            right subtree, bound=8:
                i=3: root=7, i=4
                    left: i=4, preorder[4]=10>7 → NULL
                    right: i=4, preorder[4]=10>8 → NULL
    right subtree, bound=INT_MAX:
        i=4: root=10, i=5
            left: i=5, preorder[5]=12>10 → NULL
            right: i=5, preorder[5]=12<=INT_MAX → root=12
*/

void printInorder(TreeNode* root){
    if(!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    vector<int> preorder = {8,5,1,7,10,12};
    Solution sol;
    TreeNode* root = sol.bstFromPreorder(preorder);

    cout << "Inorder Traversal of constructed BST: ";
    printInorder(root); // Should print sorted BST: 1 5 7 8 10 12
    cout << endl;

    return 0;
}

/*
Important Details, Key Insights & Warnings:

- Only upper bound is needed due to preorder's Root->Left->Right structure.
- Increment i before recursive calls ensures preorder index moves sequentially.
- Return NULL when out of bounds or current value exceeds bound to correctly stop subtree building.
- Optimal solution: O(n) time, O(h) space.
- Works for strictly increasing or decreasing preorder sequences.
- LeetCode constraints are safe; no risk of TLE or MLE.
- Similar questions / approaches:
    - Construct BST from Postorder (requires reverse traversal + bounds)
    - Validate BST using bounds
    - Serialize / Deserialize BST
    - Construct BST from Level Order (requires queue)
*/
