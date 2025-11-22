#include<iostream>
#include<vector>
#include<queue>
#include<algorithm> // Required for using max() function if needed
using namespace std;

// =======================
// Node structure of Binary Tree
// =======================
class Node {
public:
    int data;       // Value stored in node
    Node* left;     // Pointer to left child
    Node* right;    // Pointer to right child

    Node(int val) {
        data = val;
        left = right = NULL; // Initially, children are NULL
    }
};

// =======================
// Global index to track position while building the tree
// =======================
static int idx = -1;

// =======================
// Build binary tree from preorder sequence where -1 represents NULL node
// =======================
Node* buildTree(vector<int> &preOrderSeq) {
    idx++; // Move to next index in sequence

    if(preOrderSeq[idx] == -1) return NULL; // NULL node encountered, return and backtrack

    Node* root = new Node(preOrderSeq[idx]); // Create new node with current value

    root->left = buildTree(preOrderSeq);    // Recursively build left subtree
    root->right = buildTree(preOrderSeq);   // Recursively build right subtree

    return root;
}

// =======================
// Function to calculate the sum of all nodes in the binary tree
// =======================
int sumOfNodes(Node* root){
    if(root == NULL) return 0; // Base case: empty tree contributes 0 to the sum

    // Recursively calculate the sum of nodes in left subtree
    int leftsum = sumOfNodes(root->left);

    // Recursively calculate the sum of nodes in right subtree
    int rightsum = sumOfNodes(root->right);

    // Total sum is left sum + right sum + value of current node
    return leftsum + rightsum + root->data;
}

// =======================
// MAIN FUNCTION
// =======================
int main(){
    // Preorder sequence where -1 indicates NULL nodes
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the binary tree from the sequence
    Node* root = buildTree(binaryTree);

    // Calculate and print the sum of all nodes in the tree
    cout << "Sum of all nodes: " << sumOfNodes(root) << endl;

    return 0;
}

/*
========================
EXPLANATION
========================
✔ The goal of this program is to calculate the sum of all nodes in a binary tree.

✔ Tree is built from a preorder sequence where -1 represents NULL nodes.

✔ The sumOfNodes function uses recursion:
   1. If the node is NULL, it contributes 0.
   2. It recursively sums nodes from the left and right subtrees.
   3. It adds the current node's value to the sum.

✔ The recursive function traverses the entire tree and accumulates the sum.

========================
EXAMPLE
========================
Given input sequence:
1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1

Constructed tree:

       1
      / \
     2   3
        / \
       4   5

Sum of all nodes:
1 + 2 + 3 + 4 + 5 = 15

Output:
Sum of all nodes: 15

========================
WHY THIS WORKS
========================
✔ Recursion ensures each node is visited exactly once.
✔ The base case prevents unnecessary computation for NULL nodes.
✔ The sum is accumulated by adding the node’s value to the sums from its children.

========================
KEY INSIGHTS
========================
✔ Recursive thinking is essential for tree problems.
✔ Every subtree can be treated as a smaller instance of the tree.
✔ The structure of the tree guides how recursion unfolds.

========================
RELATED PROBLEMS
========================
✔ Find the maximum or minimum value in the tree.
✔ Count the total number of nodes.
✔ Calculate the height of the tree.
✔ Find the diameter of the tree.
✔ Check if a tree is balanced or symmetric.

========================
PRACTICE TIPS
========================
✔ Trace the recursion by hand on paper to understand how values are combined.
✔ Practice similar problems with summation, counting, or other operations.
✔ Understand how base cases and recursive calls relate to tree structure.
*/
