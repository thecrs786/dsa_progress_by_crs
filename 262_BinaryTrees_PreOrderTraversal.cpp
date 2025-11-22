// PRE ORDER TRAVERSAL : ROOT , LEFT , RIGHT

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// =======================
// Node structure of Binary Tree
// =======================
class Node {
public:
    int data;       // Value stored in the node
    Node* left;     // Pointer to left child
    Node* right;    // Pointer to right child

    Node(int val) {
        data = val;
        left = right = NULL; // Initially, both children are NULL
    }
};

// =======================
// Global index used while building the tree from preorder input
// =======================
static int idx = -1;

// =======================
// Build binary tree from preorder sequence where -1 represents NULL node
// =======================
Node* buildTree(vector<int> &preOrderSeq) {
    idx++; // Move to the next index in the input

    // Base case: if current element is -1, it's a NULL node
    if(preOrderSeq[idx] == -1) return NULL;

    // Create a new node with current value
    Node* root = new Node(preOrderSeq[idx]);

    // Recursively build the left subtree
    root->left = buildTree(preOrderSeq);

    // Recursively build the right subtree
    root->right = buildTree(preOrderSeq);

    return root; // Return the constructed subtree rooted at 'root'
}

// =======================
// METHOD 1: Simple preorder traversal (just printing values)
// =======================
void printTree(Node* root){
    if(root == NULL) {
        return; // Base case: if node is NULL, stop recursion
    }

    cout << root->data << " "; // Visit current node
    printTree(root->left);      // Traverse left subtree
    printTree(root->right);     // Traverse right subtree
}

// =======================
// METHOD 2: Preorder traversal including NULLs to maintain structure
// =======================
void printTreeWithNulls(Node* root){
    if(root == NULL) {
        cout << -1 << " "; // Print -1 for NULL nodes to understand structure
        return;
    }

    cout << root->data << " ";     // Visit current node
    printTreeWithNulls(root->left);  // Traverse left subtree
    printTreeWithNulls(root->right); // Traverse right subtree
}

// =======================
// METHOD 3: Preorder traversal with indentation to visualize tree structure
// =======================
void printTreeIndented(Node* root, int depth = 0) {
    if(root == NULL) return; // Base case: stop if node is NULL

    // Indent based on depth to visualize tree levels
    for(int i = 0; i < depth; i++) cout << "    "; 
    cout << root->data << "\n"; // Print current node value

    printTreeIndented(root->left, depth + 1);  // Visit left subtree with increased depth
    printTreeIndented(root->right, depth + 1); // Visit right subtree with increased depth
}

// =======================
// MAIN FUNCTION
// =======================
int main(){

    // Input: Preorder sequence where -1 represents NULL nodes
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the binary tree using the preorder sequence
    Node* root = buildTree(binaryTree);

    // Print the tree in different ways for better understanding
    cout << "Just Values" << endl;
    printTree(root); // Print nodes in preorder, ignoring NULLs
    cout << "\n\nWith NULLs" << endl;
    printTreeWithNulls(root); // Print preorder including NULLs (-1)
    cout << "\n\nUsing Indentation" << endl;
    printTreeIndented(root); // Print tree structure visually

    return 0;
}

/*
========================
EXPLANATION & IMPROVEMENTS
========================

Key Points:
1. We build the tree using a preorder sequence where -1 denotes NULL.
2. Index 'idx' is global and tracks position while building the tree recursively.
3. We explore three methods to print the tree for better understanding.

Method 1: Just Values
- Traverses the tree in preorder.
- Prints only existing node values.
- Does not indicate structure or NULLs.

Method 2: With NULLs
- Traverses the tree in preorder.
- Prints -1 wherever a NULL node is present.
- Helps understand where branches end and how siblings/children are aligned.

Method 3: Indented Format
- Traverses the tree in preorder.
- Prints tree structure using spaces for depth visualization.
- Makes parent-child relationships and siblings easy to grasp.*/