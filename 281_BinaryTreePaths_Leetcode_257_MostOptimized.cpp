// Problem: Leetcode 257 :Binary Tree Paths
// Question in Brief:
// Given a binary tree, return all root-to-leaf paths in string format. Each path should use "->" to
// separate node values. Paths must be represented from root to leaf.
// Example:
// Input:
//       1
//      / \
//     2   3
//      \
//       5
// Output: ["1->2->5","1->3"]
//
// Explanation:
// - There are two root-to-leaf paths:
//   1. 1 -> 2 -> 5
//   2. 1 -> 3

// Approach: DFS (Depth-First Search) with recursion and string accumulation (post-order style traversal)
// Time Complexity: O(N), where N = number of nodes, as each node is visited once.
// Space Complexity: O(H + N*L), H = tree height (recursion stack), N*L = storage for all paths as strings
// Optimal? ✔ Yes, using DFS + string concatenation is clean and widely accepted.
// Accepted on platforms? ✔ Yes, this is accepted on LeetCode, GFG, etc.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Definition for a binary tree node
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

    // Recursive helper function for DFS traversal
    void helper(TreeNode* root, vector<string>& ans, string path){
        // Base case: if current node is a leaf
        if(root->left == NULL && root->right == NULL){
            ans.push_back(path); // add completed path to results
            return;
        }

        // If left child exists, recurse with updated path string
        if(root->left){
            // Pass a new string to recursion: ensures left and right branches don't interfere
            helper(root->left, ans, path + "->" + to_string(root->left->val));
        }

        // If right child exists, recurse similarly
        if(root->right){
            // Again, pass a new string to avoid modifying shared state
            helper(root->right, ans, path + "->" + to_string(root->right->val));
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;  // stores all root-to-leaf paths
        if(!root) return ans; // edge case: empty tree

        string path = to_string(root->val); // initialize path with root value
        helper(root, ans, path); // start DFS traversal
        return ans;
    }
};

/*
LOGIC AND EXPLANATION:

1. Core Idea:
   - We need all paths from root to leaves.
   - Use DFS recursion to explore every root-to-leaf path.
   - Accumulate the path in a string as we traverse.

2. Why Strings are Passed Like This:
   - In recursion, each call must work with an independent path string.
   - Using `path + "->" + value` creates a **new string** for the recursive call.
   - Prevents sibling recursive calls from modifying each other's paths (avoids bugs).

3. Edge Cases:
   - Empty tree → return empty vector.
   - Tree with only root → returns vector with one element (root value).
   - Tree with multiple branches → each branch handled independently due to new string copy.

4. How Recursion Guarantees Correctness:
   - Base case triggers on leaf nodes → path string is complete → push to result.
   - Each recursive call accumulates correct path up to that node.
   - Post-order recursion ensures children paths are fully explored before returning.

5. Why No Errors Occur:
   - Each call gets its own path string copy → no shared mutable state.
   - Strings are concatenated using `+` operator → no memory overwrite.

6. String Formation:
   - Start with root value.
   - For every child, append `"->"` + child value → builds path from root to leaf.
   - Leaf node triggers storing the path in the results vector.

*/

// Helper function to print all paths
void printPaths(const vector<string>& paths) {
    for(const string &s : paths) cout << s << endl;
}

// MAIN FUNCTION WITH WORKING EXAMPLE
int main() {
    Solution solution;

    // Constructing example tree:
    //       1
    //      / \
    //     2   3
    //      \
    //       5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);

    cout << "Binary Tree Paths:" << endl;
    vector<string> result = solution.binaryTreePaths(root);
    printPaths(result);

    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, KEY INSIGHTS:

✔ Warning 1: Do NOT modify the same string in place before recursion → sibling paths get corrupted.
✔ Warning 2: Always pass a **new string copy** when branching in recursion.
✔ Insight 1: Post-order DFS traversal ensures leaf nodes are reached before storing paths.
✔ Insight 2: Each recursive call forms a complete path for its branch without affecting others.
✔ Insight 3: Handles trees of all shapes (skewed, balanced, complete, sparse).

SIMILAR QUESTIONS:
✔ Print all paths in N-ary tree → similar DFS path accumulation.
✔ Sum of all root-to-leaf numbers → similar traversal with numeric accumulation.
✔ Leaf-to-root paths → reverse accumulation string or vector in recursion.
✔ All paths with certain conditions → adapt DFS + path accumulation pattern.

APPROACH VARIATIONS:
✔ Iterative DFS with stack → more complex, less intuitive for path strings.
✔ BFS level-order traversal with parent pointers → also works, but recursion is cleaner.
✔ Using vectors to store nodes and then converting to string → alternative but more memory intensive.

This note captures everything: recursion logic, string handling in backtracking, edge cases, correctness guarantee, and practical tips for similar problems.
*/