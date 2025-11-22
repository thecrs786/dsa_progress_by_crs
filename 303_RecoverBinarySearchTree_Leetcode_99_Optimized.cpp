/***************************************************************************************
 * LeetCode #99 - Recover Binary Search Tree
 *
 * Brief:
 *   Two nodes of a BST are swapped by mistake. Recover the BST by swapping the values
 *   of the two incorrect nodes so that the tree becomes a valid BST again.
 *
 * Input: root (pointer to root of BST where exactly two nodes are swapped)
 * Output: void (the tree is modified in-place). In LeetCode the function signature is:
 *   void recoverTree(TreeNode* root);
 *
 * Examples (as trees / inorder arrays):
 *
 * 1) Adjacent swapped nodes (one inversion)
 *    Tree (swapped):
 *        1
 *       /
 *      3
 *       \
 *        2
 *    Inorder: [3, 1, 2] -> violation at (3,1)
 *    Fix: swap 3 and 1 -> Inorder: [1, 3, 2] (after fix final tree valid)
 *
 * 2) Non-adjacent swapped nodes (two inversions)
 *    Original inorder: [1,2,3,4,5,6,7]
 *    Swap 2 and 6 -> [1,6,3,4,5,2,7]
 *    Violations:
 *      - 6 > 3  (first violation -> first = 6)
 *      - 5 > 2  (second violation -> sec becomes 2)
 *    Swap first and sec -> [1,2,3,4,5,6,7]
 *
 * Approach / Method name:
 *   Inorder traversal (recursive) with three pointer-trackers:
 *     - prev : pointer to previous node visited in inorder
 *     - first: pointer to the first node involved in the wrong ordering
 *     - sec  : pointer to the second node involved
 *   Pass prev/first/sec by reference so updates persist across recursion.
 *
 * Time Complexity:
 *   O(N) — one inorder traversal (we only visit each node constant times).
 *
 * Space Complexity:
 *   O(H) — recursion stack up to tree height H (worst O(N) for skewed tree).
 *
 * Optimality:
 *   - This is an accepted, standard solution on LeetCode (and will be accepted).
 *   - It is not the O(1) auxiliary-space theoretical optimum; Morris inorder traversal
 *     lets you do the same in O(1) extra space (apart from output), but is harder to code.
 *
 * Will it cause TLE/MLE?
 *   - No. O(N) time and O(H) stack is standard. LeetCode accepts this approach easily.
 *
 ***************************************************************************************/

#include <iostream>
#include <algorithm> // for swap
using namespace std;

// LeetCode-style TreeNode definition
struct TreeNode {
    int val;                    // node value
    TreeNode *left;             // pointer to left child
    TreeNode *right;            // pointer to right child
    TreeNode() : val(0), left(nullptr), right(nullptr) {}           // default constructor
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}      // value constructor
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {} // full constructor
};


/* --------------------- Your solution (unchanged, with inline comments) --------------------- */
class Solution {
public:

    // Inorder traversal to detect the two swapped nodes
    void inorder(TreeNode* &prev, TreeNode* &first, TreeNode* &sec, TreeNode* root){
        if(root==NULL) return;                        // base case: null node

        inorder(prev, first, sec, root->left);        // recursively visit left subtree

        // Check for BST violation: current value smaller than previous value
        if(prev && (root->val < prev->val)){
            if(!first) first = prev;                  // first violation → mark previous as first
            sec = root;                               // always update second to current node
        }

        prev = root;                                  // move prev pointer forward
        inorder(prev, first, sec, root->right);       // recursively visit right subtree
    }

    // Main function to recover BST
    void recoverTree(TreeNode* root) {
        TreeNode* first = NULL;                       // first misplaced node
        TreeNode* sec = NULL;                         // second misplaced node
        TreeNode* prev = NULL;                        // pointer to previous inorder node

        inorder(prev,  first, sec, root);              // perform inorder traversal to identify nodes

        if(first && sec) swap(first->val, sec->val);   // swap their values to fix BST
    }
};

/*  WITHOUT USING &  

 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 

class Solution {
public:

    TreeNode* prev = NULL;  CREATED GLOBAL VARIABLES
    TreeNode* first = NULL;   SO NO NEED OF &
    TreeNode* sec = NULL;

    void inorder( TreeNode* root){
        if(root==NULL) return;

        inorder(root->left);
        if(prev && (root->val < prev->val)){
            if(!first) first = prev;
            sec = root;
        }
        prev = root;
        inorder(root->right);
    }

    void recoverTree(TreeNode* root) {

        inorder(root);

        if(first && sec) swap(first->val, sec->val);
        
    }
};
*/

/* -------------------------------------------------------------------- */


/*
 * ------------------------- DETAILED EXPLANATION -------------------------
 *
 * How to imagine the tree and why the method works:
 *
 * 1) Inorder of a BST is sorted in ascending order.
 *    So if two nodes are swapped, the inorder sequence will have violations of
 *    the increasing property. There can be either:
 *      - exactly one violation (adjacent swapped nodes in inorder)
 *      - or two violations (non-adjacent swapped nodes)
 *
 * 2) Violations explained (in array terms):
 *    Let inorder array = A.
 *    A violation is when A[i] > A[i+1].
 *
 *    - Adjacent swap: only one i where A[i] > A[i+1].
 *      Example: [1, 3, 2, 4] -> violation at (3,2)
 *      first = 3, sec = 2
 *      swap(first, sec) fixes the array.
 *
 *    - Non-adjacent swap: two violations.
 *      Example: [1, 6, 3, 4, 5, 2, 7] (2 and 6 swapped)
 *      Violations:
 *        6 > 3   -> first = 6, sec = 3  (sec will be overwritten later)
 *        5 > 2   -> sec = 2 (final)
 *      final first = 6, sec = 2 -> swap fixes the array.
 *
 * 3) Why using only two pointers (first, sec) is enough:
 *    - At the first violation we capture the earlier larger element (prev) as 'first'.
 *    - For each violation we set 'sec' = current node (root) — the later smaller element.
 *    - If there is only one violation, 'sec' ends up as the right node of that violation.
 *    - If there are two violations, 'sec' gets updated at the second violation to the
 *      last wrong node — so finally (first, sec) point to the two swapped values.
 *
 *    So we effectively capture:
 *      - first = the left-of-first-violation (the big element that moved right),
 *      - sec   = the right-of-last-violation  (the small element that moved left).
 *
 *    We don't need four variables because the second element of the first pair is
 *    always the same node as the first element of the second pair in terms of
 *    inversion detection in some edge patterns — but more simply:
 *    tracking just the first big node and last small node is sufficient to identify
 *    the two swapped nodes (proof by enumerating the adjacent/non-adjacent cases).
 *
 * 4) Why pass prev/first/sec by reference?
 *    - Because recursion creates separate copies of parameters per frame.
 *      We need a single shared set of pointers that all recursion frames update.
 *    - prev must be globally updated to the last visited node as we traverse.
 *      If prev were passed by value, changes inside recursion won't propagate back.
 *
 * 5) Why swap first->val with sec->val?
 *    - The structure of the tree must remain unchanged; only values were swapped.
 *    - Swapping values of the two misplaced nodes restores BST property.
 *
 * 6) Edge cases:
 *    - If the tree has only two nodes and they are swapped, algorithm catches it.
 *    - If one of the BST nodes equals nullptr (degenerate), nothing happens.
 *    - Duplicates: if input allowed duplicates, careful interpretation of BST ordering
 *      is required. Classic problem assumes distinct values or consistent duplicate rule.
 *
 * 7) Proof sketch:
 *    - Inorder visits nodes in sorted order if tree is a valid BST.
 *    - Swapping two nodes creates at most two inversions in that sorted order.
 *    - The first inversion reveals the left swapped node (first), and the last
 *      inversion reveals the right swapped node (sec). Swapping them restores order.
 *
 * ------------------------- DRY RUNS (step-by-step) -------------------------
 *
 *  A) Adjacent swapped example
 *     Tree (LeetCode example):
 *         1
 *        /
 *       3
 *        \
 *         2
 *
 *     Inorder traversal sequence by steps:
 *       Visit 3 (leftmost of the left subtree) -> prev = 3
 *       Visit 1 -> prev=3, root=1 -> 1 < 3 => violation:
 *            first = prev (3), sec = root (1)
 *       prev = 1
 *       Visit 2 -> check 2 < prev(1)? No
 *     End: first=3, sec=1 -> swap values -> tree recovered.
 *
 *  B) Non-adjacent swapped example
 *     Build tree whose inorder is [1,2,3,4,5,6,7] and then swap 2 and 6
 *     Imagine inorder sequence during traversal:
 *
 *       visit 1: prev=1 (no check)
 *       visit 6: prev=1 -> 6 > 1 OK -> prev = 6
 *       visit 3: prev=6 -> 3 < 6 -> first = prev(6), sec = root(3)  (first violation)
 *           prev = 3
 *       visit 4: prev=3 -> ok -> prev = 4
 *       visit 5: prev=4 -> ok -> prev = 5
 *       visit 2: prev=5 -> 2 < 5 -> sec = 2  (second violation)
 *           prev = 2
 *       visit 7: prev=2 -> ok
 *
 *     End: first=6, sec=2 -> swap values -> inorder becomes sorted.
 *
 * Explanation of "pair logic" (why swap first of first pair with second of second pair):
 *   - First violation identifies a node that is larger than its successor in inorder (call it X)
 *     The swapped pair includes X (a node moved to the right).
 *   - The second violation identifies a node that is smaller than its predecessor (call it Y)
 *     The swapped pair includes Y (a node moved to the left).
 *   - The actual swapped nodes are X and Y (the early large and late small).
 *
 *   If only one violation is found, the pair is adjacent, and first/second point to the two
 *   adjacent nodes involved in that single violation (so swapping them fixes it).
 *
 */

/* --------------------------- Helper & main (examples) -------------------------- */

// Utility to print inorder traversal (to visualize before/after)
void printInorder(TreeNode* root) {
    if (!root) return;                 // base case
    printInorder(root->left);          // go left
    cout << root->val << " ";          // print current node
    printInorder(root->right);         // go right
}

int main() {
    ios::sync_with_stdio(false);       // fast I/O
    cin.tie(nullptr);

    Solution sol;                      // create Solution object

    // -------- Example 1: Adjacent swapped nodes (LeetCode example) ----------
    // Create:
    //     1
    //    /
    //   3
    //    \
    //     2
    //
    // Inorder before: 3 1 2  (violation at 3>1)
    TreeNode* ex1 = new TreeNode(1);                   // root = 1
    ex1->left = new TreeNode(3);                       // left child = 3
    ex1->left->right = new TreeNode(2);                // right child of 3 = 2

    cout << "Example 1 (adjacent swapped) - inorder before: ";
    printInorder(ex1);                                 // print before recovery
    cout << "\n";

    sol.recoverTree(ex1);                              // fix the BST

    cout << "Example 1 - inorder after:  ";
    printInorder(ex1);                                 // print after recovery
    cout << "\n\n";


    // -------- Example 2: Non-adjacent swapped nodes -------------------------
    // Build balanced BST with inorder 1 2 3 4 5 6 7, then swap the values 2 and 6
    //
    //        4
    //       / \
    //      2   6
    //     / \ / \
    //    1  3 5  7
    //
    // After swapping 2 <-> 6 (values), inorder will be: 1 6 3 4 5 2 7 (two violations)
    
     TreeNode* ex2 = new TreeNode(4);                   // root = 4
    ex2->left = new TreeNode(2);                       // left child = 2
    ex2->right = new TreeNode(6);                      // right child = 6
    ex2->left->left = new TreeNode(1);                 // left-left = 1
    ex2->left->right = new TreeNode(3);                // left-right = 3
    ex2->right->left = new TreeNode(5);                // right-left = 5
    ex2->right->right = new TreeNode(7);               // right-right = 7

    swap(ex2->left->val, ex2->right->val);             // simulate wrong swap (2 <-> 6)

    cout << "Example 2 (non-adjacent swapped) - inorder before: ";
    printInorder(ex2);                                 // print before fix
    cout << "\n";

    sol.recoverTree(ex2);                              // fix the BST

    cout << "Example 2 - inorder after:  ";
    printInorder(ex2);                                 // print after fix
    cout << "\n\n";

    // Cleanup omitted intentionally (fine for test/demo environments)
    return 0;
}

/*
 * --------------------------- KEY INSIGHTS & WARNINGS ----------------------------
 *
 * - Passing pointers by reference:
 *     We pass prev, first, sec as TreeNode*& because we need a single shared variable
 *     that all recursion frames update. If we passed them by value, each recursive
 *     frame would have its own copy and updates would not persist.
 *
 * - Why only two pointers (first, sec) are enough:
 *     The swapped nodes produce at most two violations in the inorder sequence.
 *     The first violation identifies the left (larger) node (first),
 *     and the last violation identifies the right (smaller) node (sec).
 *     Swapping their values fixes the BST.
 *
 * - Edge cases & validation:
 *     - Always check `if(first && sec)` before swapping to avoid null deref.
 *     - Works for both adjacent and non-adjacent swapped nodes.
 *     - For skewed trees recursion depth can be O(N). Use Morris traversal for O(1) extra space.
 *
 * - Alternative (optimal-space) approach:
 *     Morris inorder traversal can be used to find the two nodes in O(1) space
 *     (excluding the stack/recursion). It uses threaded binary tree technique.
 *
 * - Similar problems:
 *     - "Two swapped elements in a sorted array" — same detection logic on an array.
 *     - "Convert sorted array to balanced BST" (reverse of part of this).
 *     - "Flatten BST to sorted doubly linked list" + merge two lists problems.
 *     - "Recover tree using Morris Traversal" (same problem but O(1) space).
 *
 * --------------------------- FINAL VERDICT ------------------------------------
 *
 * - This solution is standard, clean, and will be accepted on LeetCode.
 * - Time O(N), Space O(H). No TLE or MLE in typical constraints.
 * - If you need strict O(1) extra space, learn the Morris traversal version.
 *
 * ------------------------------------------------------------------------------
 */
