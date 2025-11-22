#include <iostream>
using namespace std;

/*
--------------------------------------------------------------------------------
LeetCode Problem 99: Recover Binary Search Tree
--------------------------------------------------------------------------------
Question (Brief):
Two elements of a Binary Search Tree (BST) are swapped by mistake. 
Recover the tree without changing its structure.

Input: A BST with exactly two nodes swapped.
Output: Corrected BST where inorder traversal is sorted.

Example 1:
Original BST inorder: [1,3,2,4]  (nodes 2 and 3 swapped)
Corrected BST inorder: [1,2,3,4]

Example 2:
Original BST inorder: [3,1,4,null,null,2]  (nodes 3 and 2 swapped)
Corrected BST inorder: [2,1,4,null,null,3]

--------------------------------------------------------------------------------
Approach Name:
Morris Inorder Traversal (Threaded Binary Tree) + Detect Swapped Nodes

--------------------------------------------------------------------------------
Time Complexity:  O(n)   (each node visited at most twice)
Space Complexity: O(1)  (no recursion stack, no extra data structures)
Optimal?          ✅ Yes, most memory-efficient approach
Accepted on LeetCode? ✅ Yes, no TLE or MLE
--------------------------------------------------------------------------------
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void recoverTree(TreeNode* root) {

        // Pointers to track the swapped nodes and previous node in inorder
        TreeNode* first = NULL;
        TreeNode* second = NULL;
        TreeNode* prev = NULL;

        // Start Morris Inorder Traversal
        while(root != NULL){

            // Case 1: Left subtree does not exist → visit node and move right
            if(root->left == NULL){
                // Check if previous node value is greater than current (violation)
                if(prev != NULL && prev->val > root->val){
                    if(!first) first = prev;  // first violation: store prev
                    second = root;            // store current node
                }
                prev = root;       // update previous node
                root = root->right; // move to right child
            }

            // Case 2: Left subtree exists → find inorder predecessor
            else {
                TreeNode* IP = root->left;           // Inorder Predecessor
                while(IP->right != NULL && IP->right != root) IP = IP->right;

                // If predecessor's right is NULL → create thread and move left
                if(IP->right == NULL){
                    IP->right = root;  // thread created
                    root = root->left; // move to left subtree
                }
                else {
                    // Predecessor's right already points to current → thread exists
                    // So visit current node now (left subtree fully visited)
                    if(prev != NULL && prev->val > root->val){
                        if(!first) first = prev;  // detect first violation
                        second = root;            // detect second violation
                    }

                    prev = root;       // update previous node
                    IP->right = NULL;  // remove temporary thread (restore tree)
                    root = root->right; // move to right subtree
                }
            }
        }

        // Swap values of the two nodes to fix the BST
        if(first && second) swap(first->val, second->val);
    }
};

/*
--------------------------------------------------------------------------------
LOGIC & EXPLANATION (Above main)
--------------------------------------------------------------------------------

1️⃣ Concept:
- Inorder traversal of BST yields sorted order.
- Swapped nodes break this order.
- By tracking previous node in inorder, we detect the violations.

2️⃣ Why Morris Traversal?
- Recursive inorder uses O(h) stack space.
- Morris traversal uses O(1) space:
  → Uses threads (temporary right pointers from predecessor to current node)
  → No recursion, no stack

3️⃣ How violations are detected:
- Keep pointer 'prev' to previous inorder node.
- If prev->val > current->val, a violation is found.
- First violation → first = prev, second = current
- Second violation (if exists) → second = current
- After traversal, swap first->val and second->val

4️⃣ Why only two pointers (first and second) are enough?
- Only two nodes are swapped.
- Possible cases:
  a) Adjacent nodes swapped → one violation → first = prev, second = current
  b) Non-adjacent nodes swapped → two violations → first = prev from first violation, second = current from second violation
- No need for four pointers; one pair captures both scenarios

5️⃣ Why swap first->val with second->val?
- We only need to restore BST values.
- Swapping these two nodes fixes both adjacent and non-adjacent cases.

6️⃣ Working of Morris Traversal in simple terms:
- For each node with a left child:
    → Find its inorder predecessor (rightmost in left subtree)
    → If thread not created, create it and go left
    → If thread exists, remove it and visit node
- For nodes without left child, just visit and go right
- Always check violations during visit

--------------------------------------------------------------------------------
*/

void printInorder(TreeNode* root){
    if(!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/*
--------------------------------------------------------------------------------
WORKING EXAMPLE (Main)
--------------------------------------------------------------------------------
*/

int main(){

    /*
        Example BST:
            3
           / \
          1   4
             /
            2
        Nodes 3 and 2 are swapped
    */

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);

    cout << "Original inorder traversal: ";
    printInorder(root); // Output: 1 3 2 4
    cout << endl;

    Solution obj;
    obj.recoverTree(root);

    cout << "Corrected inorder traversal: ";
    printInorder(root); // Output: 1 2 3 4
    cout << endl;

    return 0;
}

/*
--------------------------------------------------------------------------------
KEY INSIGHTS, WARNINGS & SIMILAR PROBLEMS
--------------------------------------------------------------------------------
- Only two nodes are swapped → first & second pointers are enough
- Check violation using 'prev->val > current->val' in inorder traversal
- Morris Traversal is O(1) space, unlike recursion O(h)
- Must restore temporary threads or tree will be corrupted
- Works for both adjacent & non-adjacent swaps

Similar Questions / Approaches:
- Recover BST using recursive inorder traversal (O(h) space)
- Convert BST to sorted array, fix array, rebuild BST
- Detect swapped nodes in sorted array (logic is identical)
- Any problem involving "inorder property of BST"

Key Takeaways:
- Conceptually treat BST as a sorted array
- Two violations correspond to two swapped elements
- Morris Traversal = optimal solution for memory-critical cases
--------------------------------------------------------------------------------
*/
