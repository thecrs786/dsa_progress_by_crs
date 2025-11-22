#include <iostream>
#include <vector>
using namespace std;

/*
====================================================================================
🧩 PROBLEM: LeetCode 501 — Find Mode in Binary Search Tree
====================================================================================

📜 Problem Statement:
---------------------
Given the root of a Binary Search Tree (BST), return all the mode(s) (i.e. the
element(s) that appear most frequently) in the given BST.

If the tree has multiple modes, return them in any order.

====================================================================================
💡 KEY INSIGHTS:
----------------
1. In a BST, performing an **inorder traversal** gives node values in **sorted
   (non-decreasing)** order.
   → Therefore, duplicate values appear *consecutively*.

2. We can use this property to count consecutive duplicate values efficiently
   without using extra memory like a hash map.

3. During traversal, we maintain:
   - `prev` → pointer to previous node (to compare with current node)
   - `count` → frequency of current value
   - `maxFreq` → highest frequency seen so far
   - `ans` → vector storing all values that currently have frequency = maxFreq

====================================================================================
⚙️ APPROACH (Inorder Traversal — Optimized O(1) Space):
--------------------------------------------------------
1. Perform **inorder traversal** recursively.
2. For each node visited:
   - If current node’s value == prev node’s value → increment `count`.
   - Else → reset `count = 1` (new value encountered).
3. Compare `count` with `maxFreq`:
   - If `count > maxFreq`: update `maxFreq`, clear ans, and push this value.
   - If `count == maxFreq`: push this value to ans (another mode found).
4. Continue traversal until done.
5. Return `ans`.

====================================================================================
⏱️ COMPLEXITY:
---------------
Time Complexity:  O(N) — each node is visited once.
Space Complexity: O(H) — recursion stack (H = height of tree, ~logN for balanced).

====================================================================================
⚠️ IMPORTANT NOTE ON DUPLICATES IN BST:
---------------------------------------
- The *strict* theoretical definition of BST forbids duplicates.
- But LeetCode uses a **right-inclusive BST rule**:
  → Left subtree: values < node
  → Right subtree: values >= node
  So duplicates go to the right subtree, making inorder output *non-decreasing*.

====================================================================================
📘 EXAMPLE:
-----------
BST:
        1
         \
          2
         /
        2

Inorder Traversal: [1, 2, 2]

Frequencies:
- 1 → 1 time
- 2 → 2 times
Mode = [2]

====================================================================================
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* prev = nullptr;  // keeps track of previous node during inorder
    int count = 0;             // frequency of current value
    int maxFreq = 0;           // highest frequency so far
    vector<int> ans;           // stores all modes

    void inorder(TreeNode* root) {
        if (!root) return;

        inorder(root->left);   // traverse left subtree first

        // ---- Processing current node ----
        if (prev && prev->val == root->val) {
            // same value as previous → increment count
            count++;
        } else {
            // new value → reset count
            count = 1;
        }

        // compare with maxFreq
        if (count > maxFreq) {
            // new mode found → clear previous modes
            maxFreq = count;
            ans.clear();
            ans.push_back(root->val);
        } else if (count == maxFreq) {
            // another mode with same frequency
            ans.push_back(root->val);
        }

        prev = root;  // update prev for next comparison
        // ----------------------------------

        inorder(root->right);  // traverse right subtree
    }

public:
    vector<int> findMode(TreeNode* root) {
        inorder(root);
        return ans;
    }
};

/*
====================================================================================
🧪 EXAMPLE USAGE:
====================================================================================

Input BST:
        1
         \
          2
         /
        2

Expected Output: [2]

====================================================================================
*/

int main() {
    // Construct the example BST
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(2);

    Solution sol;
    vector<int> modes = sol.findMode(root);

    cout << "Modes: ";
    for (int x : modes) cout << x << " ";
    cout << endl;

    /*
        Dry Run Summary:
        ----------------
        Inorder sequence = [1, 2, 2]
        -> count(1)=1, maxFreq=1, ans=[1]
        -> count(2)=1, maxFreq=1, ans=[1,2]
        -> count(2)=2, maxFreq=2, ans=[2]
        => Output: 2
    */

    return 0;
}

/*
====================================================================================
🧭 QUICK REVISION NOTES:
------------------------
1. Use inorder traversal for sorted values.
2. Maintain:
   - prev pointer (for comparing consecutive nodes)
   - count (current streak)
   - maxFreq (highest streak)
3. When count > maxFreq → clear vector, push new mode.
4. When count == maxFreq → push current value.
5. Works even when BST has duplicates (right-inclusive rule).
====================================================================================
*/
