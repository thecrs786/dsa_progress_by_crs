/*****************************************************
 * BINARY SEARCH TREE (BST) - COMPLETE NOTES (10/10)
 * ---------------------------------------------------
 * WHAT IS A BST?
 * - A Binary Search Tree is a binary tree where:
 *   1. Each node has at most two children (left, right).
 *   2. For every node:
 *        - Values in the left subtree are strictly smaller.
 *        - Values in the right subtree are strictly larger.
 *
 * WHY BST?
 * - Provides fast lookup, insertion, and deletion.
 * - Average time complexity: O(log N).
 * - Worst case (skewed tree): O(N).
 *
 * INORDER TRAVERSAL PROPERTY :
 * - Inorder traversal of a BST always gives sorted order.
 *   (Left → Root → Right ensures ascending values).
 *
 * MAIN OPERATIONS :
 * 1. Insert a node (Recursive + Iterative).
 * 2. Search for a node (Recursive + Iterative).
 * 3. Delete a node (Recursive + Iterative).
 * 4. Traversal (Inorder, Preorder, Postorder).
 *
 * EXTRA :
 * - Insert after creation is always allowed → call insert again with new value.
 * - Deletion has 3 cases:
 *     a) Node has no child (leaf).
 *     b) Node has 1 child.
 *     c) Node has 2 children → replace with inorder successor.
 *
 * WARNINGS :
 * - Be careful in delete: don’t free extra nodes.
 * - Always return root after recursion, otherwise modifications won’t propagate.
 * - BST must avoid duplicates for correctness (we’ll assume no duplicates).
 *****************************************************/

#include<iostream>
#include<vector>
using namespace std;

// ------------------ NODE DEFINITION ------------------
class Node {
public:
    int data;       // Value stored in node
    Node* left;     // Pointer to left child
    Node* right;    // Pointer to right child

    // Constructor to initialize a new node
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// -----------------------------------------------------
// INSERTION (RECURSIVE)
// -----------------------------------------------------
/*
 * LOGIC OF RECURSIVE INSERTION:
 * 1. Base Case: If current root is NULL → create a new node and return it.
 * 2. Recursive Case:
 *    - If val < root->data → insert into left subtree.
 *    - If val > root->data → insert into right subtree.
 * 3. Return root pointer to propagate changes upwards.
 *
 * WHY IT WORKS?
 * - Recursively travels down until it finds correct NULL position.
 * - Inserts node there while maintaining BST property.
 *
 * TIME COMPLEXITY: O(h), where h = height of tree.
 * SPACE COMPLEXITY: O(h) (recursion stack).
 */
Node* insertRecursive(Node* root, int val) {
    if (root == NULL) {                       // If tree is empty
        return new Node(val);                 // Create new node
    }
    if (val < root->data) {                   // If smaller
        root->left = insertRecursive(root->left, val);
    }
    else {                                    // If larger
        root->right = insertRecursive(root->right, val);
    }
    return root;                              // Return root after insertion
}

// -----------------------------------------------------
// INSERTION (ITERATIVE)
// -----------------------------------------------------
/*
 * LOGIC OF ITERATIVE INSERTION:
 * 1. Create new node.
 * 2. If tree is empty → return new node as root.
 * 3. Otherwise, traverse from root:
 *    - Keep track of parent pointer.
 *    - If val < curr->data → go left.
 *    - Else → go right.
 * 4. When NULL position found → attach new node as child of parent.
 *
 * WHY IT WORKS?
 * - Directly simulates recursive path but without recursion.
 *
 * TIME COMPLEXITY: O(h)
 * SPACE COMPLEXITY: O(1)
 */
Node* insertIterative(Node* root, int val) {
    Node* newNode = new Node(val);
    if (root == NULL) return newNode;         // Empty tree

    Node* parent = NULL;
    Node* curr = root;

    while (curr != NULL) {                    // Traverse until NULL
        parent = curr;
        if (val < curr->data) curr = curr->left;
        else curr = curr->right;
    }

    // Attach new node
    if (val < parent->data) parent->left = newNode;
    else parent->right = newNode;

    return root;
}

// -----------------------------------------------------
// BUILD BST FROM ARRAY
// -----------------------------------------------------
/*
 * LOGIC:
 * - Start with empty root.
 * - Insert each element from array one by one.
 * - Each insertion maintains BST property.
 *
 * WHY INORDER OF RESULT IS SORTED?
 * - Inorder traversal naturally respects "left < root < right".
 */
Node* buildBST(vector<int> arr) {
    Node* root = NULL;
    for (int val : arr) {
        root = insertRecursive(root, val);
    }
    return root;
}

// -----------------------------------------------------
// INORDER TRAVERSAL
// -----------------------------------------------------
/*
 * LOGIC:
 * - Traverse left subtree → visit root → traverse right subtree.
 * - In BST, ensures ascending order output.
 */
void inorderPrint(Node* root) {
    if (root == NULL) return;
    inorderPrint(root->left);                 // Visit left
    cout << root->data << " ";                // Print root
    inorderPrint(root->right);                // Visit right
}

// -----------------------------------------------------
// SEARCH (RECURSIVE)
// -----------------------------------------------------
/*
 * LOGIC:
 * 1. If root is NULL → not found.
 * 2. If root->data == val → found.
 * 3. If val < root->data → search left.
 * 4. Else search right.
 *
 * TIME: O(h), SPACE: O(h).
 */
bool searchRecursive(Node* root, int val) {
    if (root == NULL) return false;
    if (root->data == val) return true;
    if (val < root->data)
        return searchRecursive(root->left, val);
    else
        return searchRecursive(root->right, val);
}

// -----------------------------------------------------
// SEARCH (ITERATIVE)
// -----------------------------------------------------
/*
 * LOGIC:
 * - Start at root, traverse down:
 *   If val < curr->data → go left.
 *   If val > curr->data → go right.
 *   If equal → found.
 * - Stop when NULL reached.
 *
 * TIME: O(h), SPACE: O(1).
 */
bool searchIterative(Node* root, int val) {
    while (root != NULL) {
        if (root->data == val) return true;
        else if (val < root->data) root = root->left;
        else root = root->right;
    }
    return false;
}

// -----------------------------------------------------
// HELPER FOR DELETION (FIND MINIMUM)
// -----------------------------------------------------
/*
 * LOGIC:
 * - Inorder successor = smallest node in right subtree.
 * - Keep moving left until NULL.
 */
Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// -----------------------------------------------------
// DELETION (RECURSIVE)
// -----------------------------------------------------
/*
 * LOGIC:
 * 1. If key < root->data → go left.
 * 2. If key > root->data → go right.
 * 3. If equal → handle deletion:
 *    - CASE 1: No child → delete node, return NULL.
 *    - CASE 2: One child → delete node, return non-NULL child.
 *    - CASE 3: Two children → find inorder successor,
 *              replace node’s value with successor,
 *              recursively delete successor.
 *
 * WHY IT WORKS?
 * - Maintains BST property after removal.
 */
Node* deleteRecursive(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteRecursive(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteRecursive(root->right, key);
    }
    else {
        if (root->left == NULL && root->right == NULL) { // Case 1
            delete root;
            return NULL;
        }
        else if (root->left == NULL) {                   // Case 2
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {                  // Case 2
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {                                           // Case 3
            Node* succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteRecursive(root->right, succ->data);
        }
    }
    return root;
} 

/*
BST Deletion using Inorder Predecessor (brief notes):

1. Predecessor = rightmost node in left subtree (largest value smaller than current node).
2. To delete a node with two children:
   - Find predecessor.
   - Copy predecessor's value to current node.
   - Recursively delete predecessor from left subtree.
3. Why it works:
   - Replacing with predecessor preserves BST property:
       * All nodes in left subtree < new value
       * All nodes in right subtree > new value
   - Only the predecessor node is removed, maintaining the rest of the tree intact.
4. Result: BST remains valid, node is effectively deleted, structure slightly differs from using successor.
*/


// -----------------------------------------------------
// DELETION (ITERATIVE)
// -----------------------------------------------------
/*
 * LOGIC:
 * - Find node to delete + its parent.
 * - Handle cases:
 *   Case 1 & 2: Node has <=1 child → directly connect parent to child.
 *   Case 3: Node has 2 children → find inorder successor,
 *            copy its data, delete successor node.
 */
Node* deleteIterative(Node* root, int key) {
    Node* parent = NULL;
    Node* curr = root;

    while (curr != NULL && curr->data != key) {
        parent = curr;
        if (key < curr->data) curr = curr->left;
        else curr = curr->right;
    }

    if (curr == NULL) return root;  // Not found

    if (curr->left == NULL || curr->right == NULL) { // Case 1 & 2
        Node* child = (curr->left) ? curr->left : curr->right;
        if (parent == NULL) { delete curr; return child; }
        if (parent->left == curr) parent->left = child;
        else parent->right = child;
        delete curr;
    }
    else {                                           // Case 3
        Node* succParent = curr;
        Node* succ = curr->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
        curr->data = succ->data;
        if (succParent->left == succ) succParent->left = succ->right;
        else succParent->right = succ->right;
        delete succ;
    }

    return root;
}

/*****************************************************
 * KEY INSIGHTS:
 * - Insert after creation: just call insert again.
 * - Delete handles 3 cases (0, 1, 2 children).
 * - Always return root from recursive functions.
 * - Inorder always gives sorted order.
 *
 * WARNINGS:
 * - Don’t forget NULL checks.
 * - Don’t lose subtrees during deletion.
 *****************************************************/

int main() {
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    Node* root = buildBST(arr);

    cout << "Inorder Traversal: ";
    inorderPrint(root); cout << endl;

    root = insertRecursive(root, 7);
    cout << "After inserting 7: ";
    inorderPrint(root); cout << endl;

    cout << "Search 6 (Recursive): " << boolalpha << searchRecursive(root, 6) << endl;
    cout << "Search 10 (Iterative): " << boolalpha << searchIterative(root, 10) << endl;

    root = deleteRecursive(root, 5);
    cout << "After deleting 5 (Recursive): ";
    inorderPrint(root); cout << endl;

    root = deleteIterative(root, 2);
    cout << "After deleting 2 (Iterative): ";
    inorderPrint(root); cout << endl;

    return 0;
}
