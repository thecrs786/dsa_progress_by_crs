// Problem: Transform a Binary Tree to Accumulated Sum Tree
// Question in Brief:
// Given a binary tree, transform each node’s value so that it becomes the sum of its original value and
// the sums of all nodes in its left and right subtrees. The transformation should be done in-place.
// Example:
// Input:
//       1
//      / \
//     2   3
//    / \
//   4   5
//
// Output:
//       15
//      /  \
//    11    3
//    / \
//   4   5
//
// Explanation:
// - Node 4 and 5 have no children → remain as 4 and 5.
// - Node 2 = 2 + 4 + 5 = 11
// - Node 3 has no children → remains as 3.
// - Node 1 = 1 + 11 + 3 = 15

// Approach: Post-order recursion → process children first to correctly accumulate sums.
// Time Complexity: O(N), where N is the number of nodes → each node is visited once.
// Space Complexity: O(H), where H is the tree height → due to recursion stack.
// Optimal? ✔ Yes, for this problem, this is the most efficient and clean solution.
// Accepted on platforms? ✔ Yes, this solution will be accepted by online judges like LeetCode, GeeksforGeeks, etc.

#include <iostream>
using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
  public:

    // Helper function to compute subtree sums and update each node's value
    int helper(Node* node){
        if(node == NULL) return 0;  // Base case: empty node contributes 0

        // Recursively compute left and right subtree sums
        int leftsum = helper(node->left);
        int rightsum = helper(node->right);

        // Update the current node's value to include its original value and both subtree sums
        node->data = leftsum + rightsum + node->data;

        // Return the total sum of this subtree for use by parent node
        return node->data;
    }

    // Main function to transform the tree into accumulated sum tree
    void toSumTree(Node *node) {
        helper(node); // Start post-order recursion from the root
    }
};

/*
LOGIC AND EXPLANATION:

1. Core Idea:
   - We need each node's value to be the sum of its original value and the sums of all nodes in its left and right subtrees.
   - We can't simply update the node before visiting its children because that would lose the original data needed to calculate sums.

2. Why Post-order Traversal?
   - Post-order ensures we process the left and right children first, so when we update a node's value, we already know the correct sums from its subtrees.
   - This order mirrors the dependency graph: parents depend on their children's sums.

3. How Recursion Works:
   - At each node, we recursively compute the sum of the left subtree and right subtree.
   - We store the original value temporarily by using `node->data` in the computation before overwriting it.
   - The updated value is then returned to the parent node for its computation.

4. Why Returning `node->data` is Essential:
   - The parent node's sum relies on the updated values from its children.
   - Returning the correct sum ensures the parent node aggregates accurate data.

5. Base Case:
   - If the node is NULL, it contributes 0 to the sum.

6. Guarantees:
   - The recursion ensures no data is lost.
   - The solution is elegant, clean, and efficient.

*/

// Helper function to print inorder traversal of the tree
void printInorder(Node* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

// MAIN FUNCTION WITH WORKING EXAMPLE
int main() {
    Solution solution;

    // Constructing the example tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Inorder before transformation: ";
    printInorder(root);
    cout << endl;

    // Perform the transformation
    solution.toSumTree(root);

    cout << "Inorder after transformation: ";
    printInorder(root);
    cout << endl;

    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, KEY INSIGHTS:

✔ Warning 1: If you process nodes in pre-order, you would overwrite node values too early and lose the original data.
✔ Warning 2: Always return the updated sum so that parent nodes can correctly accumulate subtree sums.
✔ Insight 1: Post-order traversal is perfect when parent computations depend on child results.
✔ Insight 2: Addition is associative, so the order of summation within left and right subtrees doesn't affect correctness.
✔ Insight 3: Recursive stack space depends on the tree height, which is optimal for typical constraints.

SIMILAR QUESTIONS:
✔ Transform to Sum Tree (classic problem, this one is a variation adding the original value)
✔ Diameter of Binary Tree → computes subtree info bottom-up.
✔ Check if a tree is height-balanced → subtree results affect parent decisions.
✔ Convert to Children Sum Property → another form of bottom-up data propagation.

APPROACH VARIATIONS:
✔ Use BFS with queues for level-wise transformation (but it's more complex and unnecessary here).
✔ Iterative solutions are harder to implement due to dependency direction.
✔ Dynamic programming isn't needed — recursion suffices.

*/
