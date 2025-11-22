// INORDER TRAVERSAL : LEFT, ROOT, RIGHT

#include<iostream>
#include<vector>
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

    if(preOrderSeq[idx] == -1) return NULL; // NULL node encountered

    Node* root = new Node(preOrderSeq[idx]); // Create new node with current value

    root->left = buildTree(preOrderSeq);    // Recursively build left subtree
    root->right = buildTree(preOrderSeq);   // Recursively build right subtree

    return root;
}

// =======================
// INORDER TRAVERSAL VARIATIONS
// =======================

// Variation 1: Plain inorder traversal (Left, Root, Right)
void inorder(Node* root) {
    if(root == NULL) return;

    inorder(root->left);           // Visit left subtree
    cout << root->data << " ";    // Visit root
    inorder(root->right);          // Visit right subtree
}

// Variation 2: Inorder traversal with NULLs printed as -1 to show structure
void inorderWithNulls(Node* root) {
    if(root == NULL) {
        cout << -1 << " "; // Indicate NULL node for missing children
        return;
    }

    inorderWithNulls(root->left);
    cout << root->data << " ";
    inorderWithNulls(root->right);
}

// Variation 3: Indented inorder traversal to visually represent depth
void inorderIndented(Node* root, int depth = 0) {
    if(root == NULL) return;

    inorderIndented(root->left, depth + 1); // Visit left subtree first

    for(int i = 0; i < depth; i++) cout << "    "; // Indent according to depth
    cout << root->data << "\n";                   // Visit root node

    inorderIndented(root->right, depth + 1); // Visit right subtree next
}

// =======================
// MAIN FUNCTION
// =======================
int main() {
    // Preorder sequence of tree where -1 indicates NULL
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the tree from the given sequence
    Node* root = buildTree(binaryTree);

    // Inorder traversal in plain format
    cout << "Inorder Traversal (Plain):\n";
    inorder(root);
    cout << "\n\n";

    // Inorder traversal with NULLs printed as -1
    cout << "Inorder Traversal with NULLs:\n";
    inorderWithNulls(root);
    cout << "\n\n";

    // Inorder traversal with indentation to show depth
    cout << "Inorder Traversal (Indented):\n";
    inorderIndented(root);
    cout << "\n";

    return 0;
}

/*
========================
EXPLANATION
========================
✔ We are performing inorder traversal which visits nodes in the order:
    Left Subtree -> Root -> Right Subtree.

✔ Three variations are implemented:
    1. Plain traversal: Only node values are printed in inorder.
    2. With NULLs: Missing children are represented by -1 to show tree structure.
    3. Indented traversal: Nodes are printed with indentation representing their depth.

✔ The buildTree function constructs the binary tree from a preorder sequence.
✔ The sequence uses -1 to represent NULL nodes, helping us understand tree structure.
✔ Indentation helps visualize how nodes relate to each other hierarchically.

========================
WHY USE -1 IN TRAVERSAL WITH NULLS?
========================
✔ It clearly shows where a node has missing left or right child.
✔ Helpful when debugging or analyzing tree structure.
✔ Makes the output unambiguous.

========================
WHY INDENTED TRAVERSAL?
========================
✔ It shows how deep each node is.
✔ Helps visualize parent-child relationships.
✔ Great for understanding recursive tree structures.

========================
WHAT NEXT?
========================
✔ Explore level order traversal using queues.
✔ Learn about tree height, diameter, and balanced trees.
✔ Implement serialization and deserialization for trees.
✔ Practice recursion problems based on binary trees.
*/
