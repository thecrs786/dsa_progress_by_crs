#include<iostream>
#include<vector>
#include<queue>
#include<algorithm> // Required for using max() or other algorithms if needed
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
        left = right = NULL; // Initially, both children are NULL
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

    if(preOrderSeq[idx] == -1) return NULL; // NULL node encountered, backtrack

    Node* root = new Node(preOrderSeq[idx]); // Create new node with current value

    // Recursively build left and right subtrees
    root->left = buildTree(preOrderSeq);
    root->right = buildTree(preOrderSeq);

    return root;
}

// =======================
// Count the total number of nodes in the binary tree
// =======================
int countNodes(Node* root){
    if(root == NULL) return 0; // Base case: no nodes in an empty subtree

    // Recursively count nodes in left subtree
    int leftcount = countNodes(root->left);

    // Recursively count nodes in right subtree
    int rightcount = countNodes(root->right);

    // Total nodes = left subtree count + right subtree count + current node
    return leftcount + rightcount + 1;
}

// =======================
// MAIN FUNCTION
// =======================
int main(){
    // Input sequence for building the tree
    // -1 represents NULL nodes
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the tree from the input sequence
    Node* root = buildTree(binaryTree);

    // Count and print the total number of nodes in the tree
    cout << "Total number of nodes in the tree: " << countNodes(root) << endl;

    return 0;
}

/*
========================
EXPLANATION
========================
✔ We are building a binary tree from a preorder traversal sequence where -1 indicates NULL nodes.
✔ After constructing the tree, we recursively count the total number of nodes.

✔ The buildTree function works by:
   1. Moving through the sequence using a global index.
   2. Creating a node when a value is found.
   3. Recursively building left and right subtrees.
   4. Backtracking when -1 is encountered.

✔ The countNodes function:
   1. Checks if the current node is NULL and returns 0.
   2. Recursively counts nodes in the left subtree.
   3. Recursively counts nodes in the right subtree.
   4. Adds 1 for the current node and returns the total count.

========================
EXAMPLE
========================
Input sequence:
1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1

Constructed tree:

       1
      / \
     2   3
        / \
       4   5

Output:
Total number of nodes in the tree: 5

✔ The program counts every node and sums them up accurately.

========================
INLINE COMMENTS EXPLANATION
========================
✔ Every step is explained including base cases and recursive cases.
✔ The recursive structure is ideal for tree problems.
✔ Using -1 in the input allows us to build the exact structure easily.

========================
WHY THIS WORKS
========================
✔ The tree is traversed in a depth-first manner.
✔ Each node is counted exactly once.
✔ Recursion handles both empty and non-empty subtrees effectively.

========================
IMPORTANT DETAILS
========================
✔ The recursive approach is elegant and simple for tree operations.
✔ Base cases prevent unnecessary recursion and infinite loops.
✔ The input sequence is crucial to accurately constructing the tree.

========================
SIMILAR QUESTIONS
========================
✔ Find the sum of all nodes in a tree.
✔ Calculate the height or diameter of the tree.
✔ Check if the tree is balanced or symmetric.
✔ Serialize and deserialize binary trees.

========================
PRACTICE TIPS
========================
✔ Trace the recursion using paper and pencil.
✔ Visualize how the sequence translates into tree structure.
✔ Practice counting leaves, internal nodes, and applying similar recursion problems.

========================
KEY INSIGHTS
========================
✔ Trees are best solved using recursive thinking.
✔ Understanding base cases is essential for correct implementation.
✔ The structure of input data plays a vital role in how recursion progresses.
*/
