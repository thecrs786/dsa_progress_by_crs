/*
LeetCode 700 - Search in a Binary Search Tree

Problem (brief):
  Given the root of a Binary Search Tree (BST) and an integer val, 
  return the subtree rooted with the node whose value equals val. 
  If such a node does not exist, return nullptr.

  Reminder: In a BST for any node:
    - all values in left subtree  < node->val
    - all values in right subtree > node->val
    (Some BST variants allow equal values with a chosen policy; this solution assumes standard < / >.)

Example:
  Input: root = [4,2,7,1,3], val = 2
           4
          / \
         2   7
        / \
       1   3
  Output: subtree rooted at node 2 -> [2,1,3]

  Input: root = [4,2,7,1,3], val = 5
  Output: nullptr (not found)

Time Complexity:  O(h) where h = height of tree. 
                 - Balanced BST: h = O(log n) -> O(log n)
                 - Degenerate (linked-list) BST: h = O(n) -> O(n)
Space Complexity: O(1) iterative (no extra DS). Recursive variant would use O(h) stack.

Approach used:
  Iterative search using BST property:
    - Start at root.
    - If current->val == val -> return current (found).
    - If current->val > val -> go left (values smaller are there).
    - Else go right.
    - Repeat until you hit nullptr -> not found.

Is this asymptotically optimal?
  Yes for time in terms of tree height; you must walk down a path from root; you cannot do better than O(h).
  Space is optimal for iterative approach: O(1).

Accepted on LeetCode?
  Yes — this is the canonical accepted solution. No TLE. No MLE under normal constraints.
  Caveats: If input tree is not a BST or duplicates are handled differently, behavior differs.

Below: original user-provided solution (kept for reference), then a cleaned, annotated implementation,
detailed explanation, and a working example with outputs and comments.
*/

/* ---------------------- Headers ---------------------- */
#include <bits/stdc++.h>
using namespace std;

/* ---------------------- Standard TreeNode ---------------------- */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* ---------------------- Reference: User's original code ----------------------
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while(root!=NULL && root->val!=val){
            if(root->val>val) root = root->left;
            else root = root->right;
        }
        return root;
    }
};
------------------------------------------------------------------------------- */

/* ---------------------- Cleaned & Annotated Solution ---------------------- */
class Solution {
public:
    /*
      Method name: Iterative BST search
      Rationale: Use BST ordering to decide direction each step. Iterative avoids recursion overhead/stack.
    */
    TreeNode* searchBST(TreeNode* root, int val) {
        // Iterate down the tree until we either find the value or reach a null pointer.
        // Use nullptr (modern C++) instead of NULL.
        while (root != nullptr && root->val != val) {
            if (root->val > val) {
                // Current node value is greater than target -> target must be in left subtree (if exists).
                root = root->left;
            } else {
                // Current node value is less than target -> target must be in right subtree (if exists).
                root = root->right;
            }
            // Loop continues with the new root (next node on the path).
        }
        // Either root == nullptr (not found) or root->val == val (found). Return root (or nullptr).
        return root;
    }
};

/* ---------------------- Detailed logic & step-by-step explanation ----------------------
   (Placed here as requested: below class and above main)

1) Why iterative & why use BST property?
   - A BST's essential property lets us discard half the tree at each comparison:
       * If target < node->val -> search left subtree
       * If target > node->val -> search right subtree
   - This yields O(h) time where h is height. Recursing would produce same complexity but uses stack.

2) Walkthrough of the loop:
   - while (root != nullptr && root->val != val)
       * We check two conditions together:
         - root != nullptr ensures we haven't walked past leaf.
         - root->val != val: if equal, we break and return this node.
       * At every iteration we compare root->val with val:
         - If root->val > val -> move left: root = root->left
         - Else -> move right: root = root->right
       * Each step moves strictly down the tree — no cycles.

3) Why return the node (root) instead of value?
   - Problem expects the subtree rooted at the found node. Returning its pointer allows caller to inspect the subtree.
   - If you only need to know presence, return bool; if you need node pointer (LeetCode), return TreeNode*.

4) Correctness:
   - By induction: at each step we keep the invariant that 'root' is the root of the subtree that may contain the target.
     If target exists anywhere, following the comparisons will eventually hit it. If not, we'll end at nullptr.

5) Edge-cases:
   - Empty tree (root == nullptr) -> while condition false -> return nullptr.
   - Root holds the value -> loop condition false at start -> return root immediately.
   - Duplicates: BST definition matters. If duplicates exist and policy places duplicates on one side,
     the algorithm will find the first encountered matching node on the path defined by that policy.
6) Performance notes:
   - Iterative version uses constant extra memory O(1).
   - Recursion would use O(h) stack; iterative is often preferred for production to avoid stack overflow for deep trees.
------------------------------------------------------------------------------- */

/* ---------------------- Working example / driver ---------------------- */
int main() {
    /*
      Build the following BST:
                 4
                / \
               2   7
              / \
             1   3

      We'll search for val = 2 (exists) and val = 5 (doesn't exist).
    */

    // Construct nodes
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;

    // Test 1: value exists
    int target1 = 2;
    TreeNode* found1 = sol.searchBST(root, target1);
    if (found1 != nullptr) {
        cout << "Found node with val = " << found1->val << "\n";
        // Print subtree rooted at found1 (in-order) to verify structure: expect 1 2 3
        cout << "In-order of found subtree: ";
        // simple iterative inorder using stack or recursive helper; using recursive lambda for brevity
        function<void(TreeNode*)> inorder = [&](TreeNode* node){
            if (!node) return;
            inorder(node->left);
            cout << node->val << " ";
            inorder(node->right);
        };
        inorder(found1);
        cout << "\n";
    } else {
        cout << "Value " << target1 << " not found in BST.\n";
    }

    // Test 2: value does not exist
    int target2 = 5;
    TreeNode* found2 = sol.searchBST(root, target2);
    if (found2 != nullptr) {
        cout << "Found node with val = " << found2->val << "\n";
    } else {
        cout << "Value " << target2 << " not found in BST.\n";
    }

    // Cleanup nodes (good practice)
    delete root->left->right;  // 3
    delete root->left->left;   // 1
    delete root->left;         // 2
    delete root->right;        // 7
    delete root;               // 4

    return 0;
}

/* ---------------------- Important details, warnings, key insights, similar problems ----------------------

IMPORTANT DETAILS / WARNINGS:
- This algorithm assumes the tree is a valid BST. If the tree is NOT a BST, this method is invalid.
- If duplicates exist in your BST, be clear about insertion policy (left or right). The search will find
  the matching node encountered on the path; it may not be the "first inserted" duplicate.
- Use nullptr (modern C++). Original user code used NULL; both work on many compilers but prefer nullptr.
- Iterative approach avoids recursion stack overflow for deep trees — prefer it in competitive programming.

KEY INSIGHTS:
- At each node, you discard exactly one entire subtree based on a single comparison -> that's why it's efficient.
- The path length you traverse is bounded by tree height h. So optimizing tree height (balancing) is crucial for repeated operations.
- This is a textbook example of exploiting data structure invariants (BST property) to speed up search.

SIMILAR PROBLEMS & APPROACHES:
- LeetCode 701: Insert into a Binary Search Tree -> identical traversal idea; insert at leaf when nullptr reached.
- LeetCode 450: Delete Node in a BST -> find node using this search, then handle deletion cases (0/1/2 children).
- LeetCode 108/109: Convert Sorted Array/List to BST -> build balanced BST to optimize subsequent searches.
- If you need to search many values repeatedly, consider keeping a balanced BST (AVL/Red-Black) or using an ordered set/map.

FINAL (BLUNT) TAKE:
- Your provided code is correct and idiomatic for iterative BST search. It's optimal in time for the BST model (O(h)) and uses O(1) extra space.
- Don't overthink micro-optimizations here — the core win comes from the BST property and keeping tree balanced if you need repeated fast searches.
*/