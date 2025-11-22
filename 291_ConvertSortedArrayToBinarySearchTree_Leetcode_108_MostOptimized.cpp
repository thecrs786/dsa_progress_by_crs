/*
LeetCode 108 - Convert Sorted Array to Binary Search Tree

Problem (brief):
  Given a sorted (ascending) integer array, convert it to a height-balanced Binary Search Tree (BST).
  Height-balanced: depths of left and right subtrees of every node differ by no more than 1.

Example:
  Input: nums = [-10, -3, 0, 5, 9]
  One valid output (level-order): [0, -3, 9, -10, null, 5]
  Visual (one valid balanced BST):
           0
          / \
       -3    9
       /    /
    -10    5

Time Complexity:  O(n)  -- each array element becomes exactly one tree node (constant work per element).
Space Complexity: O(log n) auxiliary (recursion stack) for balanced tree; worst-case O(n) if recursion happens on skewed input (but choosing mid prevents skew).

Approach used (name/method):
  - Recursive divide-and-conquer: choose middle element as root, recursively build left subtree from left half and right subtree from right half.
  - This guarantees near-equal subtree sizes -> balanced tree -> minimum possible height.

Is this the most optimal?
  - Yes in asymptotic terms: O(n) time and O(log n) auxiliary space (for balanced result). This is the canonical and optimal approach for this problem.
Will LeetCode accept it? TLE/MLE?
  - Will be accepted. No TLE. MLE only if platform constraints are absurdly tiny — not realistic here.

(Implementation follows)
*/

#include <bits/stdc++.h>
using namespace std;

/* Standard TreeNode definition (LeetCode style) */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* ------------------ Solution (user-provided, functionally identical) ------------------ */
class Solution {
public:
    // Recursively build BST from nums[st..end], picking middle as root
    TreeNode* helper(vector<int>& nums, int st, int end){
        if(st > end) return nullptr;                  // empty range => no node

        int mid = st + (end - st) / 2;                // pick middle to ensure balance
        TreeNode* root = new TreeNode(nums[mid]);     // create root with mid value

        // recursively build left and right subtrees
        root->left  = helper(nums, st, mid - 1);
        root->right = helper(nums, mid + 1, end);

        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int st = 0;
        int end = (int)nums.size() - 1;
        return helper(nums, st, end);
    }
};

/* ------------------ Detailed logic & step-by-step explanation ------------------
   (Placed here as requested: below the class and above main)

1) Why pick the middle element?
   - Picking mid splits the array into two halves whose sizes differ by at most 1.
   - That produces left and right subtrees with sizes as equal as possible → gives a height-balanced tree.
   - Balanced trees have optimal height = O(log n), improving subsequent search/traversal performance.

2) Correctness reasoning:
   - For each recursive call on range [st..end]:
       * If st > end -> empty range -> return nullptr (no node).
       * Otherwise, mid exists. Make node with nums[mid].
       * All values in nums[st..mid-1] < nums[mid] → safe to put in left subtree.
       * All values in nums[mid+1..end] > nums[mid] → safe to put in right subtree.
   - Recursively applying this respects BST invariants at every node.

3) Why recursion?
   - Tree structure is recursive by nature. The subarray maps naturally to subtrees.
   - Depth of recursion equals height of constructed tree. Since we pick mid, recursion depth ≈ O(log n).

4) Memory and micro-optimizations:
   - We allocate exactly n TreeNode objects (new).
   - Minor micro-optimization: none required; default is efficient.
   - If you want to be ultra-safe with memory, consider reusing a memory pool or using iterative construction — but not required here.

5) Edge cases:
   - Empty array -> returns nullptr.
   - Single element -> returns a single node (leaf).
   - Large arrays -> recursion depth ~ log2(n) -> safe for typical constraints (n ≤ 10^4..10^5 depending on platform).

6) Practical note:
   - Using mid = st + (end - st) / 2 avoids overflow (good practice).
------------------------------------------------------------------------------- */

/* ------------------ Helpers for demonstration in main ------------------ */

// Print tree in level-order to inspect shape (returns nothing, prints to stdout).
void printLevelOrder(TreeNode* root) {
    if (!root) {
        cout << "[]\n";
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    vector<vector<int>> levels;
    while (!q.empty()) {
        int sz = (int)q.size();
        vector<int> level;
        for (int i = 0; i < sz; ++i) {
            TreeNode* node = q.front(); q.pop();
            if (node) {
                level.push_back(node->val);
                q.push(node->left);
                q.push(node->right);
            } else {
                // Use a sentinel to preserve structure if desired (we'll skip pushing children for nullptr)
                // But to keep output compact we don't add placeholders here.
            }
        }
        if (!level.empty()) levels.push_back(level);
    }

    // pretty-print levels
    cout << "[";
    for (size_t i = 0; i < levels.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < levels[i].size(); ++j) {
            cout << levels[i][j];
            if (j + 1 < levels[i].size()) cout << ", ";
        }
        cout << "]";
        if (i + 1 < levels.size()) cout << ", ";
    }
    cout << "]\n";
}

// Delete all nodes in tree (post-order)
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ------------------ Working example (main) ------------------ */
int main() {
    // Example 1: standard LeetCode sample
    vector<int> nums1 = {-10, -3, 0, 5, 9};
    Solution sol;
    TreeNode* root1 = sol.sortedArrayToBST(nums1);

    cout << "Level-order of constructed BST (example 1): ";
    printLevelOrder(root1);
    // Expected-like output (one valid balanced layout): [[0], [-10, 5], [-3, 9]] OR other valid balanced variations
    // Note: exact level-order can vary based on mid-choice for even-length segments; still valid BST.

    // Example 2: even number of elements (checks mid tie handling)
    vector<int> nums2 = {1, 2, 3, 4};
    TreeNode* root2 = sol.sortedArrayToBST(nums2);
    cout << "Level-order of constructed BST (example 2): ";
    printLevelOrder(root2);
    // Expected: balanced tree; e.g., [[2], [1, 3], [4]] or [[3], [1,4],[2]] depending on mid selection policy.
    // Our mid = st + (end - st)/2 picks lower-middle for even lengths (stable choice).

    // Cleanup
    deleteTree(root1);
    deleteTree(root2);

    return 0;
}

/* ------------------ Key insights, warnings, and similar problems ------------------

KEY INSIGHTS:
- Choosing midpoint is the single critical idea. It directly produces balanced subtrees and minimal height.
- The algorithm maps array index ranges to subtree domains deterministically and preserves BST ordering.

WARNINGS:
- If you picked leftmost/rightmost element instead of mid repeatedly, you'd build a skewed tree (height ~ n).
- Recursion depth equals tree height; with midpoint it is O(log n). For constraints where recursion depth is
  problematic (very large n and strict stack limits), you could implement iterative strategies or increase stack size.

SIMILAR PROBLEMS:
- LeetCode 109: Convert Sorted List to Binary Search Tree — same idea but the source is a linked list; requires finding mid in O(n) (fast/slow pointer) or converting list to array first.
- LeetCode 95: Unique Binary Search Trees II — generate all structurally unique BSTs for n (different problem: combinatorics + recursion).
- LeetCode 1382 / 1099 variants — balanced BST construction and transformations.

FINAL (no fluff):
- This solution is the textbook, optimal solution for converting a sorted array into a height-balanced BST. It's simple, correct, and what interviewers expect. If you want iterative construction or an explanation of mid-choice variants (lower-mid vs upper-mid) and how that affects tree shape, I can show that too.
*/
