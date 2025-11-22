/*
LeetCode Question #543: Diameter of Binary Tree

Problem Summary:
Given the root of a binary tree, you need to find the diameter of the tree. 
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.

Example 1:
Input: root = [1,2,3,4,5]
Output: 3
Explanation: The longest path is [4,2,1,3] or [5,2,1,3], with 3 edges.

Example 2:
Input: root = [1,2]
Output: 1
Explanation: The longest path is [2,1], with 1 edge.

Time Complexity: O(N), where N is the number of nodes.
Each node is visited once during the traversal.

Space Complexity: O(H), where H is the height of the tree, due to recursion stack space.

Optimality: This is the most optimal solution using recursion with O(N) time complexity. 
It avoids redundant calculations by computing diameter during height computation.

Will it be accepted by LeetCode?
✔ Yes, it will pass all test cases within time and memory constraints.
✘ It will not cause TLE or MLE since it processes each node once and uses only the recursion stack.
*/

/* =================== BOILERPLATE START =================== */
#include <iostream>
#include <algorithm>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/* =================== BOILERPLATE END =================== */

/* =================== CLASS SOLUTION START =================== */
class Solution {
public:
    // Recursive function to compute height and update diameter
    int height(TreeNode* root, int &ans){
        if(root == NULL) return 0; // Base case: empty subtree has height 0
        
        // Recursively compute height of left subtree
        int leftht = height(root->left, ans);
        
        // Recursively compute height of right subtree
        int rightht = height(root->right, ans);

        // Update the maximum diameter found so far
        ans = max(ans, leftht + rightht);

        // Return the height of the current node
        return max(leftht, rightht) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 0; // Initialize the maximum diameter
        height(root, ans); // Compute heights and update diameter
        return ans; // Return the final diameter
    }
};
/* =================== CLASS SOLUTION END =================== */

/* =================== LOGIC AND EXPLANATION =================== */
/*
LOGIC:
We are tasked to find the diameter (longest path between two nodes) in a binary tree. A naive approach would be:
1. For each node, compute the height of left and right subtrees.
2. Calculate the path length (left height + right height).
3. Repeat for all nodes.
This leads to O(N^2) complexity because the height function is repeatedly called for the same nodes.

OPTIMAL SOLUTION:
We merge height calculation and diameter update into one traversal:
- While computing the height of a node, we also update the maximum diameter.
- This avoids redundant calculations.

HOW THIS WORKS:
- At each node, we compute the height of left and right subtrees.
- The diameter passing through that node is the sum of left and right heights.
- We track the maximum diameter using a reference variable 'ans'.
- The height function returns the maximum height for the subtree rooted at the current node.

WHY IT’S OPTIMAL:
- Every node is visited once → O(N) time.
- The recursion stack depth is at most the height of the tree → O(H) space.
- The diameter is updated while computing height, so there's no need for separate traversal.

IMPORTANT LINE:
    ans = max(ans, leftht + rightht);
This single line redefines the problem:
- Instead of solving diameter after heights are computed, we combine both operations.
- This reduces the complexity from O(N^2) to O(N), making it a truly optimal solution.

WORKING EXAMPLE:
Input Tree:
        1
       / \
      2   3
     / \
    4   5

Height of node 4 = 1
Height of node 5 = 1
Height of node 2 = max(1,1) + 1 = 2
Diameter at node 2 = 1 + 1 = 2
Height of node 3 = 1
Height of node 1 = max(2,1) + 1 = 3
Diameter at node 1 = 2 + 1 = 3
Final answer = 3
*/

/* =================== MAIN FUNCTION AND TEST CASE =================== */
int main() {
    // Create the tree nodes
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // Create Solution object
    Solution sol;
    int result = sol.diameterOfBinaryTree(root);

    // Output the result
    cout << "Diameter of the binary tree is: " << result << endl;

    return 0;
}
/* =================== END OF MAIN FUNCTION =================== */

/* =================== KEY INSIGHTS, WARNINGS, AND SIMILAR QUESTIONS =================== */
/*
KEY INSIGHTS:
✔ The diameter at a node is the sum of heights of its left and right subtrees.
✔ Updating diameter during height calculation avoids unnecessary recomputation.
✔ Using a reference variable lets us track the global state efficiently.

WARNINGS:
✘ If you compute height separately in another function without caching, it will lead to O(N^2) complexity.
✘ Not passing the reference to 'ans' would prevent diameter updates.
✘ Returning incorrect base case values like -1 or 0 inconsistently will lead to wrong results.

SIMILAR QUESTIONS:
1. LeetCode #104: Maximum Depth of Binary Tree → Only computes height, not diameter.
2. LeetCode #124: Binary Tree Maximum Path Sum → Similar, but includes node values.
3. Diameter variations → Find diameter through specific nodes or constraints.

SIMILAR APPROACHES:
✔ Tree DP (Dynamic Programming on Trees)
✔ Post-order traversal to gather information from children before updating parent
✔ Using global/reference variables to accumulate results during recursion
*/
