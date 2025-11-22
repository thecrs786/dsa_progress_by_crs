/*
LeetCode 1008 - Construct Binary Search Tree from Preorder Traversal
----------------------------------------------------------------------

Question (brief):
  Given the preorder traversal of a BST, construct the BST and return its root.

Example:
  preorder = [8, 5, 1, 7, 10, 12]
  Constructed BST:
          8
         / \
        5   10
       / \     \
      1   7     12

Constraints:
  - 1 <= preorder.length <= 100
  - All values are unique

Approach / Method:
  - Brute-force / Insert-each-value method
    Insert nodes one by one into an initially empty BST using normal BST rules.

Time Complexity:
  - Best/Average: O(n log n) if tree is balanced
  - Worst: O(n^2) if tree is skewed (e.g., sorted input)

Space Complexity:
  - O(h) recursion stack, h = tree height
  - Worst-case h = n -> O(n)
  
Accepted on LeetCode:
  - ✅ Yes, for n <= 100, will not cause TLE or MLE

Hint for optimization:
  - O(n) method using preorder index + bounds or stack, for large n
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    
    //Detailed recursive insertion
    // -----------------------------
    TreeNode* insertBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val); // create new node if empty
        if (val < root->val)
            root->left = insertBST(root->left, val); // assign returned node to left
        else
            root->right = insertBST(root->right, val); // assign returned node to right
        return root; // return root so parent pointer remains valid
    }

    // Build BST using Method 2
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode* root = nullptr;
        for (int val : preorder)
            root = insertBST(root, val); // insert each node
        return root;
    }
};

/* ---------------------------
   Logic & Explanation
---------------------------

High-level:
- Insert each preorder value into BST recursively.
- Preorder order ensures correct placement: root -> left subtree -> right subtree.
- Returning root in each call preserves parent-child linkages.

Step-by-step:
1. bstFromPreorder initializes root = nullptr.
2. First value creates root node (insertBST(NULL, val) returns new node).
3. Subsequent values traverse recursively:
   - Compare val with root->val
   - If val < root->val: recurse left
   - Else: recurse right
   - Assign recursive return to root->left or root->right
4. Final root returned after all insertions.

Important details:
- root==nullptr => create new node
- Assignment root->left/right = insertBST(...) ensures new node is linked
- Always return root to keep subtree structure
- Works for empty input, unique values, skewed tree handled (O(n^2) worst-case)
*/

/* ---------------------------
   Helper functions
--------------------------- */
void preorderTraversal(TreeNode* root, vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorderTraversal(root->left, out);
    preorderTraversal(root->right, out);
}

void inorderTraversal(TreeNode* root, vector<int>& out) {
    if (!root) return;
    inorderTraversal(root->left, out);
    out.push_back(root->val);
    inorderTraversal(root->right, out);
}

void printLevelOrder(TreeNode* root) {
    if (!root) { cout << "(empty tree)\n"; return; }
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            TreeNode* cur = q.front(); q.pop();
            cout << cur->val << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << "\n";
    }
}

/* ---------------------------
   Main function with inline comments
--------------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> preorder = {8,5,1,7,10,12};

    Solution sol;
    // Build BST using Method 2 (detailed)
    TreeNode* root = sol.bstFromPreorder(preorder);

    // To use Method 1 (compact):
    // TreeNode* root = nullptr;
    // for(int val: preorder) root = sol.insertBST_compact(root, val);

    vector<int> pre, in;

    // Collect preorder to verify constructed tree
    preorderTraversal(root, pre);
    // Collect inorder (should be sorted for BST)
    inorderTraversal(root, in);

    // Print input preorder
    cout << "Input preorder: "; 
    for(int v: preorder) cout << v << " "; 
    cout << "\n";

    // Print preorder of constructed BST
    cout << "Constructed BST preorder: "; 
    for(int v: pre) cout << v << " "; 
    cout << "\n";

    // Print inorder of constructed BST
    cout << "Constructed BST inorder (sorted): "; 
    for(int v: in) cout << v << " "; 
    cout << "\n";

    // Print level-order for visual check
    cout << "\nLevel-order:\n"; 
    printLevelOrder(root);

    return 0;
}

/* ---------------------------
   Key Points, Warnings & Insights
---------------------------
- Both methods recursively insert nodes; same logic, only difference is verbosity.
- Time Complexity: O(n^2) worst-case, O(n log n) average
- Space Complexity: O(h) recursion stack
- Works for LeetCode n <= 100; may TLE for n >> 1000
- Returning root ensures correct parent-child linkage
- root->left/right = insertBST(...) necessary for linking newly created nodes
- Edge cases: empty input, skewed tree
- Similar questions:
    - Reconstruct BST from preorder (this problem)
    - Reconstruct binary tree from preorder + inorder
    - Optimized O(n) approach: preorder index + bounds / stack
*/
