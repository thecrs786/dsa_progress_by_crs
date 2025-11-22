#include<iostream>
#include<vector>
#include<queue>
#include<algorithm> // Required for using max() function
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
// Function to calculate the height of the tree
// =======================
int height(Node* root){
    if(root == NULL) 
        return 0; // Base case: an empty tree has height 0

    // Recursively find the height of left subtree
    int leftht = height(root->left);

    // Recursively find the height of right subtree
    int rightht = height(root->right);

    // The height of the tree is max of left and right subtree heights plus 1 for current node
    return max(leftht, rightht) + 1;
}

// =======================
// MAIN FUNCTION
// =======================
int main(){
    // Preorder sequence where -1 indicates NULL nodes
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the binary tree from the sequence
    Node* root = buildTree(binaryTree);

    // Calculate and print the height of the tree
    cout << "Height of tree: " << height(root) << endl;

    return 0;
}

/*
========================
EXPLANATION
========================
✔ This program builds a binary tree using a preorder sequence where -1 denotes NULL nodes.
✔ It then computes the height of the tree using a recursive approach.

✔ Height of a tree is defined as the number of nodes on the longest path from the root node to a leaf node.
✔ For example, a tree with only one node has a height of 1.

========================
BUILD TREE LOGIC
========================
✔ We use a static index 'idx' to keep track of where we are in the input sequence.
✔ Each call to buildTree increments 'idx' to pick the next element.
✔ When we encounter -1, it means that node is NULL and we backtrack to the previous node.
✔ This way, the recursive function builds the entire tree correctly.

========================
HEIGHT FUNCTION LOGIC
========================
✔ Base case: If the node is NULL, its height is 0.
✔ Recursive case:
   - We compute the height of the left subtree.
   - We compute the height of the right subtree.
   - The height of the current node is the maximum of left and right subtree heights plus 1.

✔ max(leftht, rightht) chooses the taller subtree at each step, building up the correct height.

========================
EXAMPLE
========================
Given input sequence:
1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1

The constructed tree looks like:
        1
      /   \
     2     3
          / \
         4   5

The height is 3 because the longest path from root (1) to leaf (4 or 5) is 3 nodes.

========================
IMPORTANT DETAILS
========================
✔ The height is computed using recursion, which makes the code elegant and simple.
✔ The base case ensures that the recursion terminates.
✔ The max function is used to compare subtree heights.

========================
WHY USE RECURSION?
========================
✔ Recursion helps in breaking down the problem into smaller subproblems.
✔ It naturally fits tree traversal and calculation problems.
✔ Each subtree is handled independently, making the logic easy to implement.

========================
SIMILAR PROBLEMS
========================
✔ Finding diameter of a tree.
✔ Checking if a tree is balanced.
✔ Computing sum of all nodes.
✔ Finding maximum or minimum node value.

========================
PRACTICE TIP
========================
✔ Practice building trees from different traversal orders (preorder, inorder, postorder).
✔ Try finding height iteratively as a challenge.
✔ Combine height logic with other problems like finding diameter or path sums.
*/
