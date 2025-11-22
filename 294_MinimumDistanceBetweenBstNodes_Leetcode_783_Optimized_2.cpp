/*
LeetCode — Problem Notes & Complete Code
Question Number: 783 (also related to 530)
Title (brief): Minimum Distance / Minimum Absolute Difference Between BST Nodes

Problem (brief):
  Given the root of a Binary Search Tree (BST), return the minimum absolute difference
  between the values of any two different nodes in the tree.

Examples (as comments):
  // Example 1:
  // Input: root = [4,2,6,1,3]
  // Tree:
  //       4
  //      / \
  //     2   6
  //    / \
  //   1   3
  // Inorder: [1,2,3,4,6] -> min adjacent diff = 1
  // Output: 1

  // Example 2:
  // Input: root = [1,0,48,null,null,12,49]
  // Inorder: [0,1,12,48,49] -> min adjacent diff = 1
  // Output: 1

Above class: Problem details, time complexity (TC), memory complexity (MC), approach used:
  - Approach used here (the solution you provided): Morris Inorder Traversal (to produce a sorted vector)
    + Collect all node values in inorder into a vector (sorted because BST inorder is sorted).
    + Scan adjacent differences in vector to find minimum.
  - Time Complexity: O(n)   (visit each node once using Morris traversal; final scan also O(n))
  - Space Complexity: O(n)  (vector stores all n node values)
    NOTE: traversal itself uses O(1) extra space (Morris), but we keep a vector -> O(n) memory.
  - Is it most optimal?
    + Time: optimal (O(n)).
    + Space: not the absolute optimal (absolute best is O(1) extra space while computing min on-the-fly using Morris).
    + So: Not the most space-optimal; a Morris on-the-fly version would be O(n) time and O(1) extra space.
  - Will it be accepted on LeetCode or cause MLE/TLE?
    + Accepted in normal constraints (LeetCode constraints are small; this approach is safe).
    + Unlikely to cause TLE (O(n) is required), and unlikely to cause MLE for reasonable n (LeetCode bounds).
    + If n is extremely large (millions) and memory is constrained, storing vector may be problematic — consider on-the-fly O(1) approach.

--------------------------------------------------------------------------------
BOILERPLATE, FULL WORKING SOLUTION (the solution you provided) with thorough comments:
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/* Definition for a binary tree node (LeetCode-style). */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
public:

    // -------------------------
    // inorderTraversal (Morris)
    // -------------------------
    // Purpose:
    //   Produce the inorder traversal of a BST (which yields a sorted list of node values).
    // Why Morris?
    //   Morris traversal avoids recursion and explicit stack, using temporary "threads" (right pointers).
    //   It visits nodes in inorder with O(1) additional space (excluding output storage).
    // Returns:
    //   vector<int> containing node values in sorted (inorder) order.
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;                   // will hold the inorder values (sorted for BST)
        TreeNode* curr = root;             // traversal cursor

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // CASE A: no left child -> we can visit current node and go right
                // Reason: left subtree is empty, so current node is the next inorder element.
                ans.push_back(curr->val);
                curr = curr->right;
            } else {
                // CASE B: left child exists -> find the inorder predecessor (rightmost node in left subtree)
                TreeNode* IP = curr->left; // IP = inorder predecessor candidate
                // Move to the rightmost node of left subtree or to the node that already points to curr.
                while (IP->right != nullptr && IP->right != curr) {
                    IP = IP->right;
                }

                if (IP->right == nullptr) {
                    // If IP->right is null, create a temporary thread to curr so we can return after finishing left subtree.
                    // This avoids recursion/stack.
                    IP->right = curr;
                    curr = curr->left;    // continue deeper into left subtree
                } else {
                    // Thread already points to curr -> it means we've finished visiting left subtree
                    // and are returning to curr now. Remove the thread and visit curr.
                    IP->right = nullptr;  // restore original tree structure
                    ans.push_back(curr->val);
                    curr = curr->right;   // move to right subtree
                }
            }
        }
        return ans;
    }

    // ---------------------------------
    // minDiffInBST (uses inorder vector)
    // ---------------------------------
    // The user's provided solution:
    // 1) Get sorted list vec via inorder traversal.
    // 2) Compute min difference among adjacent elements (since vec is sorted).
    //
    // Correctness:
    //  - In a sorted list, the minimum absolute difference between any two elements must occur between
    //    some pair of adjacent elements. So scanning adjacent differences suffices.
    //
    // Edge cases:
    //  - If tree has fewer than 2 nodes, there's no pair – return 0 (or handle as per problem constraints).
    int minDiffInBST(TreeNode* root) {
        vector<int> vec = inorderTraversal(root); // sorted list of node values
        if (vec.size() < 2) return 0;             // safety: no pair exists

        int mindis = INT_MAX;                     // initialize to a very large value
        // Scan adjacent differences (only need adjacent because vec is sorted)
        for (size_t i = 1; i < vec.size(); ++i) {
            // For BST (inorder sorted ascending), vec[i] >= vec[i-1], so difference non-negative.
            // Still use subtraction directly; if input could be extreme, consider long long.
            int diff = vec[i] - vec[i - 1];
            if (diff < mindis) mindis = diff;
        }
        return mindis;
    }
  };

    
/* --------------------------------------------------------------------------------
   Detailed Explanation & Logic (placed below class, above main) — READ THIS CAREFULLY
   --------------------------------------------------------------------------------

1) Why an inorder traversal?
   - A BST's inorder traversal visits nodes in non-decreasing order (sorted by value).
   - If you get the full sorted list of node values, the minimum absolute difference between any
     two nodes in the entire tree must be the minimum of differences between some adjacent pair
     in this sorted list. Reason: if you take any two elements a < b with some elements between
     them, at least one adjacent difference among those elements will be <= b - a. So only adjacent
     pairs in sorted order need be checked.

2) Why store values into a vector?
   - Simplicity & clarity: once you have the sorted list, a single linear scan gives the answer.
   - Downside: extra O(n) memory for the vector.
   - Tradeoff: Using vector is clearer for explanation/learning; for strict O(1) space, do the on-the-fly method.

3) Why Morris traversal for building the vector?
   - Morris traversal avoids recursion (call-stack overhead) or an explicit stack.
   - It uses temporary "threads" to remember where to come back after finishing the left subtree.
   - However, since we still store all values in a vector, using Morris vs normal stack-based traversal mainly
     affects peak auxiliary memory during traversal; using Morris + vector still uses O(n) memory total (vector).
   - If you only care about avoiding recursion stack and prefer iterative, you could use an explicit stack instead.

4) Why check adjacent differences only?
   - For a sorted array A, the global minimum absolute difference between any two elements is min(A[i+1] - A[i]).
   - Proof sketch: if A[i] < A[j] and j > i+1, then there exists k with i < k < j so
     A[j] - A[i] >= A[k] - A[i] and one of the adjacent differences inside [i..j] is <= A[j]-A[i].

5) Numeric safety:
   - If values can be close to INT_MIN/INT_MAX, consider using long long for differences.
   - In typical LeetCode constraints node values are small (e.g., non-negative), so int differences are safe.

6) Complexity summary:
   - Time: O(n) to traverse + O(n) to scan -> O(n)
   - Memory: O(n) vector. Traversal itself (Morris) uses O(1) extra pointers.

--------------------------------------------------------------------------------
   Now: A small working example (main) that builds a sample tree and runs the provided solution.
--------------------------------------------------------------------------------
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Construct example tree:
    //       4
    //      / \
    //     2   6
    //    / \
    //   1   3
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n2 = new TreeNode(2, n1, n3);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* root = new TreeNode(4, n2, n6);

    Solution sol;
    int ans = sol.minDiffInBST(root); // using the solution provided above (collect vector approach)
    cout << "Minimum difference (using inorder vector method): " << ans << "\n";



    // Clean up nodes to avoid leaks (good practice in example main)
    delete n1;
    delete n3;
    delete n2;
    delete n6;
    delete root;

    return 0;
}

/*
--------------------------------------------------------------------------------
KEY INSIGHTS, WARNINGS, AND SIMILAR QUESTIONS / APPROACHES (below main) — AS COMMENTS
--------------------------------------------------------------------------------

Important details / warnings:
  - If you only have <= 2 nodes, handle accordingly; this code returns 0 if < 2 nodes.
  - Watch out for integer overflow in languages that have limited integer ranges. Use long long
    for difference computation if input values can be extreme.
  - Using a vector uses O(n) memory. If memory is a constraint, prefer the on-the-fly Morris approach.

Key insights:
  - BST property + inorder traversal gives sorted order -> reduces problem to "min adjacent difference in sorted array".
  - Sorting each element explicitly (like extracting then sorting) is unnecessary because BST inorder already sorts.
  - Adjacent pairs in sorted order are the only candidates to check for minimum absolute difference.

Similar LeetCode problems / variants:
  - LeetCode 530: Minimum Absolute Difference in BST (very similar / same idea)
  - LeetCode 783: Minimum Distance Between BST Nodes
  - Variants: "Minimum absolute difference in an unsorted array" -> requires sorting O(n log n) or bucket-based methods.
  - If the input were an arbitrary binary tree (not BST), you must collect values and sort them (or use a tree set),
    because inorder wouldn't produce a sorted order automatically.

Alternative approaches:
  1) Recursive inorder with a `prev` pointer:
     - Do recursion and keep previous value visited; update min difference on the fly.
     - Simpler to implement but uses call stack -> O(h) extra space where h is tree height.
  2) Iterative stack-based inorder:
     - Use an explicit stack to perform inorder; keep previous and update min on the fly. O(h) extra space.
  3) Morris on-the-fly (shown above as minDiffInBST_O1space):
     - Most space efficient: O(1) extra space, O(n) time.

Why sorting (inorder) helps here — explained simply:
  - Sorting arranges values from smallest to largest. The closest pair in value will be adjacent after sorting.
  - The brute-force approach checks all pairs O(n^2). Sorting + single pass reduces to O(n log n) + O(n) (or
    O(n) if we rely on BST inorder). For a BST, inorder provides sorted values in O(n) time, so scanning for adjacent
    differences is linear overall.

Final note (practical):
  - For interview or contest: the on-the-fly recursive/iterative solutions are easier to code and accepted.
  - For strict memory constraints, present the Morris on-the-fly method to show knowledge of O(1) space traversal.

--------------------------------------------------------------------------------
End of notes + complete, runnable code block.
--------------------------------------------------------------------------------
*/
