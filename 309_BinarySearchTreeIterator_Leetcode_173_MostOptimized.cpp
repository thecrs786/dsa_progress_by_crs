/*******************************************************
 * Question Number: LeetCode 173
 * Question: Binary Search Tree Iterator
 * 
 * Brief: Implement an iterator over a BST (Binary Search Tree)
 * that returns nodes in ascending order (in-order traversal) 
 * with next() and hasNext() methods.
 *
 * Example:
 *     BST:       7
 *               / \
 *              3   15
 *                 /  \
 *                9    20
 *
 *     BSTIterator iterator = BSTIterator(root);
 *     iterator.next();    // returns 3
 *     iterator.next();    // returns 7
 *     iterator.hasNext(); // returns true
 *     iterator.next();    // returns 9
 *******************************************************/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/********************************************************
 * Class: BSTIterator
 * Method: Stack-based Inorder Traversal
 * Approach: Lazy in-order traversal using stack
 * Time Complexity:
 *      - Constructor: O(h)  [push left spine of root]
 *      - next(): O(1) amortized, worst-case O(h) 
 *      - hasNext(): O(1)
 * Space Complexity:
 *      - O(h), where h is the height of BST (stack stores left spine)
 * Optimality: Most optimal in space-time trade-off.
 ********************************************************/

class BSTIterator {
public:
    stack<TreeNode*> s;  // stack to store the path to the next smallest node

    // Constructor: push the entire left spine of the root onto the stack
    BSTIterator(TreeNode* root) {

        while(root != NULL){
            s.push(root);  // store current node
            root = root->left;  // move left
        }
    }
    
    // Returns the next smallest element in the BST
    int next() {
        TreeNode* curr = s.top(); // the top of stack is always next smallest
        s.pop();

        // If current node has right child, push all its left children onto stack
        if(curr->right){
            TreeNode* t2 = curr->right;
            while(t2 != NULL){
                s.push(t2);  // left spine of right child
                t2 = t2->left;
            }
        }

        return curr->val;
    }
    
    // Returns true if there is a next smallest element
    bool hasNext() {
        return !s.empty();
    }
};

/********************************************************
 * Logic and Explanation:
 *
 * 1. Redefining the Problem:
 *    - Instead of flattening the BST into an array (O(n) space),
 *      we lazily traverse using a stack that holds the path
 *      from root to the next smallest element.
 *
 * 2. Constructor:
 *    - Push all nodes along the left spine of the root into stack.
 *    - This ensures the top of stack is always the next smallest.
 *
 * 3. next():
 *    - Pop the top node (next smallest value).
 *    - If the popped node has a right child, push all left children
 *      of that right child to the stack.
 *    - This maintains the invariant: stack top = next smallest node.
 *
 * 4. hasNext():
 *    - Simply checks whether the stack is empty.
 *
 * 5. Edge Cases:
 *    - If BST is empty → stack is empty → hasNext() = false.
 *    - Node with no left child → already correctly on top of stack.
 *    - Node with no right child → no new nodes to push, next smallest comes from stack.
 *
 * 6. Key Insight:
 *    - We only store the path to next node (O(h) space), not all nodes.
 *    - Each node is pushed and popped exactly once → next() amortized O(1).
 *    - Traversing left gives the smallest remaining node; right child introduces new subtree.
 ********************************************************/

/********************************************************
 * Working Example:
 ********************************************************/
int main(){
    // Construct the BST
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    BSTIterator* it = new BSTIterator(root);

    cout << it->next() << endl;    // 3
    cout << it->next() << endl;    // 7
    cout << it->hasNext() << endl; // 1 (true)
    cout << it->next() << endl;    // 9
    cout << it->hasNext() << endl; // 1 (true)
    cout << it->next() << endl;    // 15
    cout << it->next() << endl;    // 20
    cout << it->hasNext() << endl; // 0 (false)

    return 0;
}

/********************************************************
 * Important Details, Warnings, and Key Insights:
 * - Do not precompute all nodes → O(n) space is not optimal.
 * - Always push left spine of right child after popping current.
 * - Stack stores only the “path to next smallest node.”
 * - Amortized analysis is crucial: each node visited once → O(1) amortized.
 * - Edge Case: Empty BST handled naturally (stack empty).
 *
 * Similar Questions / Approaches:
 * - Flatten BST to array (simpler, but O(n) space)
 * - Recursive in-order traversal with global vector
 * - Design BST iterator for reverse in-order (next largest)
 ********************************************************/
