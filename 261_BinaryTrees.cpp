/*
Binary Tree - Complete Notes from Scratch to Mastery

1. What is a Tree?
   - A tree is a hierarchical non-linear data structure.
   - It consists of nodes connected by edges.
   - One node is designated as the root, and others are organized in levels.

2. Terminology:
   - Root: The topmost node.
   - Child: A node directly connected below another node.
   - Parent: A node directly connected above another node.
   - Leaf Node: A node with no children.
   - Internal Node: A node with at least one child.
   - Edge: Connection between two nodes.
   - Depth: Distance from root to the node.
   - Height: Longest distance from node to a leaf node.
   - Subtree: A smaller tree formed by any node and its descendants.

3. Why Trees?
   - Model hierarchical structures (e.g., file systems, org charts).
   - Used in databases, AI, search algorithms, network routing.
   - Optimize operations like searching, insertion, deletion.

4. Types of Trees:
   - General Tree: Any node can have 0 or more children.
   - Binary Tree: Each node has at most two children (left and right).
   - Binary Search Tree (BST): Left child < parent < right child.
   - Balanced Trees: Keep operations efficient (e.g., AVL, Red-Black).
   - Heap: Complete tree for priority queues.
   - Trie: Stores strings for prefix searches.
   - Segment/Fenwick Tree: Efficient range queries.

5. Binary Tree Properties:
   - Max nodes at level l = 2^l
   - Max nodes in tree of height h = 2^(h+1) - 1
   - Full, complete, and perfect trees are structural variations.

6. Example Tree Structure:
        1
      /   \
     2     3
         /   \
        4     5

   - Node 1 is root.
   - Nodes 2 and 3 are children of 1.
   - Nodes 4 and 5 are children of 3.

7. Applications:
   - Expression evaluation using expression trees.
   - Data compression using Huffman trees.
   - Decision-making algorithms.
   - Routing algorithms in networks.
   - Maintaining sorted data using BSTs.

8. Operations:
   - Insertion: Add nodes at correct position.
   - Traversal: Visit all nodes.
   - Searching: Find specific data.
   - Deletion: Remove nodes safely.
   - Height/Depth calculation.
   - Level-order traversal (BFS).
   - Maintaining balance (for efficiency).

9. Traversal Techniques:
   - Preorder (Root → Left → Right): Used in copying trees.
   - Inorder (Left → Root → Right): Used in retrieving sorted data in BST.
   - Postorder (Left → Right → Root): Used in deleting/freeing trees.
   - Level-order (BFS): Visit nodes level-wise using a queue.

10. Edge Cases:
   - Empty tree.
   - Single-node tree.
   - Skewed trees (all nodes to left or right).
   - Duplicate values in BST problems.

*/

// Example code structure for building and printing a binary tree
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// Node structure of Binary Tree
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

// Index to track position in input sequence while building the tree
static int idx = -1;

// Build binary tree from preorder sequence where -1 represents NULL node
Node* buildTree(vector<int> &preOrderSeq) {
    idx++; // Move to the next index

    // If value is -1, this node is NULL
    if(preOrderSeq[idx] == -1) return NULL;

    // Create a new node with current value
    Node* root = new Node(preOrderSeq[idx]);

    // Recursively build left subtree
    root->left = buildTree(preOrderSeq);

    // Recursively build right subtree
    root->right = buildTree(preOrderSeq);

    return root;
}

// Print tree using level-order traversal (BFS)
void printLevelOrder(Node* root) {
    if(root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        cout << temp->data << " ";

        // Push left child if exists
        if(temp->left != NULL)
            q.push(temp->left);

        // Push right child if exists
        if(temp->right != NULL)
            q.push(temp->right);
    }
}

int main() {
    /*
    Preorder sequence explanation:
    Sequence = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1}
    - 1 → root node
    - 2 → left child of 1
    - -1 → left child of 2 is NULL
    - -1 → right child of 2 is NULL
    - 3 → right child of 1
    - 4 → left child of 3
    - -1 → left child of 4 is NULL
    - -1 → right child of 4 is NULL
    - 5 → right child of 3
    - -1 → left child of 5 is NULL
    - -1 → right child of 5 is NULL
    */

    vector<int> binaryTree = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

    // Build the tree
    Node* root = buildTree(binaryTree);

    // Print tree in level order
    cout << "Level order traversal: ";
    printLevelOrder(root);
    cout << endl;

    return 0;
}

/*
Key Insights and Warnings:

1. We use 'idx' globally to keep track while building the tree recursively.
2. Preorder input sequence is enough to build the tree if NULLs are marked.
3. Level order traversal helps visualize the structure.
4. Avoid using circular structures or infinite recursion by handling NULLs properly.
5. Edge cases like empty input, skewed trees must be tested.
6. Tree problems are recursive by nature and require careful base case handling.
7. Advanced problems involve BST properties, balancing, and path-related queries.

Similar Questions:
- Binary Search Tree operations (Insert, Delete, Search).
- Lowest Common Ancestor problems.
- Diameter of a tree.
- Maximum path sum.
- Serialization and deserialization of trees.
- Expression tree evaluation.

Next Steps:
- Implement preorder, inorder, and postorder traversals.
- Learn BFS using queues more deeply.
- Explore BST and AVL trees.
- Solve problems involving recursion, dynamic programming on trees, etc.
*/

