// LEVEL ORDER TRAVERSAL : WITH ITERATIVE APPROACH (BFS ) USING QUEUE

#include<iostream>
#include<vector>
#include<queue>
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
// Level Order Traversal (BFS using queue) with level separation
// =======================
void levelOrderTraverse(Node* root) {
    if(root == NULL) return; // Edge case: empty tree, nothing to print

    queue<Node*> q; // Create an empty queue for BFS traversal
    q.push(root);   // Start with the root node
    q.push(NULL);   // NULL marker used to signify end of level

    /*
    LOGIC BEHIND USING NULL:
    ✔ NULL helps us detect when we've processed all nodes at the current level.
    ✔ Once we reach NULL, we know it's time to print a new line and separate levels.
    ✔ It prevents the need for counting nodes or tracking levels separately.
    */

    while(!q.empty()) {
        Node* curr = q.front(); // Get the front node in the queue
        q.pop();                // Remove it from the queue

        if(curr == NULL) { // End of current level reached
            cout << endl; // Move to next line to print the next level

            if(!q.empty()) {
                /*
                Only add a new NULL marker if there are still nodes left to process.
                ✔ This prevents adding unnecessary NULL markers when traversal is complete.
                */
                q.push(NULL); // Insert marker to separate next level
            }
        } else {
            cout << curr->data << " "; // Print current node's value followed by a space

            // If left child exists, add it to the queue for future processing
            if(curr->left != NULL) q.push(curr->left);

            // If right child exists, add it to the queue for future processing
            if(curr->right != NULL) q.push(curr->right);
        }
    }
}

// =======================
// MAIN FUNCTION
// =======================
int main() {
    // Preorder input sequence where -1 represents NULL nodes
    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the binary tree from the given sequence
    Node* root = buildTree(binaryTree);

    // Perform level order traversal and print nodes level by level
    cout << "Level Order Traversal Output:\n";
    levelOrderTraverse(root);

    cout << endl; // Final newline for clean output
    return 0;
}

/*
========================
EXPLANATION
========================
✔ This code demonstrates Level Order Traversal (BFS) using a queue with explicit level separation.
✔ It traverses the binary tree breadth-first, printing nodes level by level.

✔ How it works:
1. We push the root node into the queue to start.
2. We use a NULL marker to indicate the end of a level.
3. While the queue is not empty:
   - We process nodes one by one.
   - If the node is not NULL:
     ✔ We print its value.
     ✔ We enqueue its left and right children if they exist.
   - If the node is NULL:
     ✔ We print a newline to mark the end of the level.
     ✔ We enqueue another NULL marker if more nodes remain to be processed.

✔ This approach is simple, intuitive, and avoids complex bookkeeping.

========================
EXAMPLE
========================
Given preorder sequence:
1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1

The tree built is:

       1
      / \
     2   3
        / \
       4   5

Output:
Level Order Traversal Output:
1 
2 3 
4 5 

✔ Nodes are printed level by level with separation between levels.

========================
IMPORTANT DETAILS
========================
✔ The queue ensures FIFO order, crucial for BFS.
✔ NULL markers help distinguish levels without extra counters or structures.
✔ Efficient traversal without recursion makes it suitable for large trees.

========================
WHY USE NULL MARKERS?
========================
✔ NULL markers allow us to easily separate levels during traversal.
✔ They make output formatting simple and prevent tracking multiple variables.
✔ They're particularly useful when we need to process or analyze tree levels.

========================
INLINE COMMENTS ON NULL AND LINE MAINTAINING
========================
✔ NULL is pushed after the root to separate levels visually.
✔ When we encounter NULL during processing, it signals the end of a level.
✔ We print a newline and, if nodes are pending, add another NULL to continue.
✔ This ensures that each level is printed clearly and intuitively.

========================
EDGE CASE HANDLING
========================
✔ If the tree is empty (root == NULL), the function immediately exits.
✔ The traversal stops once all nodes are processed and no further NULL markers are needed.

========================
SIMILAR QUESTIONS AND USE CASES
========================
✔ Check completeness or balance of binary trees.
✔ Find the maximum width or depth of the tree.
✔ Serialize and deserialize trees using BFS.
✔ Solve graph traversal problems like shortest path.

========================
PRACTICE TIP
========================
✔ Practice manually tracing the queue’s state for small trees.
✔ Try modifying the traversal to print nodes in zigzag or spiral order.
✔ Compare BFS with DFS to understand their different use cases.
*/
