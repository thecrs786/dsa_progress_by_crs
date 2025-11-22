/*
LeetCode Problem 114 - Flatten Binary Tree to Linked List

Question (in brief):
Given the root of a binary tree, flatten it into a "linked list" in-place following preorder traversal.
- The left child of each node should be set to NULL.
- The right child should point to the next node in preorder.

Example 1:
Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
Explanation:
The preorder traversal is 1 → 2 → 3 → 4 → 5 → 6.
The left pointers are set to NULL and right pointers form the sequence.

Example 2:
Input: root = []
Output: []
Explanation: An empty tree returns an empty output.

Example 3:
Input: root = [0]
Output: [0]
Explanation: A single node tree is already flattened.

Approach Used:
✔ Reverse preorder traversal (right → left → root) to flatten the tree in place.
✔ We maintain a class-level pointer 'nextRight' to keep track of the previously processed node.
✔ By processing the right subtree first, we ensure the nextRight pointer always points to the correct node to attach.

Time Complexity: O(n), where n is the number of nodes. Each node is visited once.
Space Complexity: O(h), where h is the height of the tree due to recursion stack.

Is this the most optimal solution?
✔ Time complexity is optimal at O(n), since each node must be visited once.
✘ Space complexity is O(h) due to recursion stack, so not strictly O(1).
✔ It is elegant, intuitive once understood, and widely acceptable in interviews unless constant space is required.

Will it be accepted by LeetCode?
✔ Yes, it passes all test cases without causing MLE or TLE for typical tree depths.

Similar questions and approaches:
✔ 144. Binary Tree Preorder Traversal → processes nodes in root-left-right order.
✔ 145. Binary Tree Postorder Traversal → processes nodes in left-right-root order.
✔ 98. Validate Binary Search Tree → uses inorder traversal.
✔ 102. Binary Tree Level Order Traversal → BFS approach.
✔ 117. Populating Next Right Pointers → uses level connections similar to pointer manipulation.

*/

#include <iostream>
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
    TreeNode* nextRight = nullptr; // Tracks the previously processed node during recursion

    void flatten(TreeNode* root) {
        if(root == nullptr) return; // Base case: nothing to process

        // Recursively flatten the right subtree first
        flatten(root->right);
        // Recursively flatten the left subtree next
        flatten(root->left);

        // Set the current node's left to NULL as required
        root->left = nullptr;

        // Attach the previously processed node to the current node's right pointer
        root->right = nextRight;

        // Update the nextRight pointer to the current node
        nextRight = root;
    }
};

/*
LOGIC AND EXPLANATION (Fully detailed):

1. The problem requires flattening the tree into a linked list using preorder traversal.

2. We use reverse preorder traversal (right → left → root) because:
   - When we process the right subtree first, the nextRight pointer always holds the correct node to attach.
   - This avoids the need to search for the rightmost node after processing left.

3. The 'nextRight' pointer:
   - It is a class-level variable that persists across recursive calls.
   - It always points to the previously processed node.
   - After processing both subtrees, we set 'root->right' to nextRight and update nextRight to root.

4. Recursion works because:
   - The call stack ensures that deeper nodes are processed before shallower ones.
   - As recursion unwinds, each node attaches itself to the already flattened subtree.

5. Edge cases:
   - If the node is NULL → we simply return.
   - If there is no left or right subtree → the recursive call returns immediately.
   - For single-node trees → base case handles it naturally.

6. How stacks are connected:
   - The recursion stack stores each function call separately.
   - At each return, we process the node by attaching it to the previously flattened subtree.

7. This approach guarantees:
   - Every node is visited once → O(n) time complexity.
   - No need to find the end of the subtree after flattening → more efficient than naive recursion.
   - The tree structure is flattened in preorder.

*/

/*
WORKING EXAMPLE
*/

int main() {
    // Create the binary tree:
    //      1
    //     / \
    //    2   5
    //   / \   \
    //  3   4   6

    TreeNode* root = new TreeNode(1,
                        new TreeNode(2,
                            new TreeNode(3),
                            new TreeNode(4)),
                        new TreeNode(5,
                            nullptr,
                            new TreeNode(6)));

    Solution solution;
    solution.flatten(root);

    // Output the flattened tree as a sequence by traversing right pointers
    TreeNode* curr = root;
    cout << "Flattened tree: ";
    while(curr != nullptr){
        cout << curr->val << " ";
        curr = curr->right;
    }
    cout << endl;

    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, AND KEY INSIGHTS:

✔ The nextRight pointer must be maintained across recursive calls; it links processed nodes.
✔ Always process the right subtree before the left to ensure preorder order when attaching nodes.
✔ Set the left pointer to NULL before linking to nextRight as required.
✔ Avoid searching for the rightmost node — this is what makes the approach elegant.
✔ This method avoids unnecessary pointer manipulation or traversal loops.

⚠ Common mistakes:
- Forgetting to process the right subtree first → leads to wrong preorder.
- Not updating nextRight → breaks the link between nodes.
- Not setting left to NULL → violates problem constraints.

✔ Edge cases like empty trees or single-node trees are handled naturally by the base case.

✔ The recursion stack serves as temporary storage and ensures that deeper nodes are processed before attaching shallower nodes.

SIMILAR QUESTIONS AND APPROACHES:
✔ 144. Binary Tree Preorder Traversal → use root-first processing.
✔ 145. Binary Tree Postorder Traversal → similar but with left-right-root order.
✔ 98. Validate Binary Search Tree → uses traversal to maintain ordering.
✔ 102. Binary Tree Level Order Traversal → BFS approach, useful for layer-based processing.
✔ 117. Populating Next Right Pointers → pointer manipulation across nodes.

MASTERING THIS APPROACH:
✔ Practice tracing recursion with diagrams and dry runs.
✔ Visualize how nextRight points to previously processed nodes.
✔ Understand why right subtree must be processed before left.
✔ Try converting this into iterative form once you are comfortable.

This is a complete, structured, and deep explanation tailored for mastery, interviews, and long-term learning.
Let me know if you want diagrams, dry run examples, or iterative transformation next!
*/ 
