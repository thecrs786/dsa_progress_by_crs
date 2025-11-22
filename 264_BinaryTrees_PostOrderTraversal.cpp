// POST ORDER TRAVERSAL : LEFT, RIGHT, ROOT

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
// POSTORDER TRAVERSAL VARIATIONS
// =======================

// Variation 1: Plain postorder traversal (Left, Right, Root)
void postorder(Node* root) {
    if(root == NULL) return;

    postorder(root->left);           // Visit left subtree first
    postorder(root->right);          // Then visit right subtree
    cout << root->data << " ";      // Finally, visit root node
}

// Variation 2: Postorder traversal with NULLs printed as -1 to show structure
void postorderWithNulls(Node* root) {
    if(root == NULL) {
        cout << -1 << " "; // Indicate NULL node for missing children
        return;
    }

    postorderWithNulls(root->left);   // Visit left subtree
    postorderWithNulls(root->right);  // Visit right subtree
    cout << root->data << " ";        // Visit root node
}

// Variation 3: Indented postorder traversal to visually represent depth
void postorderIndented(Node* root, int depth = 0) {
    if(root == NULL) return;

    postorderIndented(root->left, depth + 1);   // Visit left subtree first
    postorderIndented(root->right, depth + 1);  // Then visit right subtree

    for(int i = 0; i < depth; i++) cout << "    "; // Indent according to depth
    cout << root->data << "\n";                   // Finally, visit root node
}

// =======================
// MAIN FUNCTION
// =======================
int main() {
    // Preorder sequence of tree where -1 indicates NULL
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the tree from the given sequence
    Node* root = buildTree(binaryTree);

    // Postorder traversal in plain format
    cout << "Postorder Traversal (Plain):\n";
    postorder(root);
    cout << "\n\n";

    // Postorder traversal with NULLs printed as -1
    cout << "Postorder Traversal with NULLs:\n";
    postorderWithNulls(root);
    cout << "\n\n";

    // Postorder traversal with indentation to show depth
    cout << "Postorder Traversal (Indented):\n";
    postorderIndented(root);
    cout << "\n";

    return 0;
}

/*
========================
EXPLANATION
========================
✔ We are performing postorder traversal which visits nodes in the order:
    Left Subtree -> Right Subtree -> Root.

✔ Three variations are implemented:
    1. Plain traversal: Only node values are printed in postorder.
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
