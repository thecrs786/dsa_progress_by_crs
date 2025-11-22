/*
LeetCode Problem 94 - Binary Tree Inorder Traversal

Question (in brief):
Given the root of a binary tree, return the inorder traversal of its nodes' values.
Inorder means visiting nodes in the order: left subtree → current node → right subtree.

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]
Explanation: We traverse left, root, then right.

Example 2:
Input: root = []
Output: []
Explanation: Empty tree means no nodes to traverse.

Example 3:
Input: root = [1]
Output: [1]
Explanation: Single node tree, traversal is itself.

Approach Used:
- Morris Traversal (Inorder traversal with O(1) extra space)
- Uses temporary threading to avoid recursion or stack.
- Restores tree structure after traversal.

Time Complexity: O(n), where n is the number of nodes. Each node is visited at most twice.
Space Complexity: O(1), ignoring the output vector. No recursion stack or explicit stack is used.

Most Optimal?: 
✔ Yes, this is the most space-efficient approach for inorder traversal.
✘ More complex and error-prone than recursive or iterative stack-based approaches.

Accepted by LeetCode?: 
✔ Yes, passes all test cases including very deep trees without causing MLE or TLE.

Warnings:
⚠ Careful pointer manipulation is required; missing thread restoration will corrupt the tree.
⚠ Debugging is harder due to in-place modification and pointer logic.

Key Insights:
✔ Morris traversal uses temporary "threads" to keep track of parent nodes.
✔ Threads are only created where safe — rightmost node’s right pointer is NULL.
✔ Threads are restored to NULL after use, ensuring tree remains unchanged.
✔ Avoids recursion stack, thus preventing stack overflow.

Similar Questions:
- 145. Binary Tree Postorder Traversal (can be approached iteratively with two stacks)
- 144. Binary Tree Preorder Traversal (similar logic but visiting node before left subtree)
- 102. Binary Tree Level Order Traversal (uses BFS, not DFS)
- 98. Validate Binary Search Tree (inorder traversal verifies sorted order)

*/

#include <iostream>
#include <vector>
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

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans; // Vector to store inorder traversal result
        TreeNode* curr = root; // Start traversal from root node

        while(curr != NULL){
            if(curr->left == NULL){
                // CASE 1: No left child → process current node and move to right
                ans.push_back(curr->val);
                curr = curr->right;
            }
            else{
                // CASE 2: There is a left child → find inorder predecessor (IP)

                TreeNode* IP = curr->left; // Start from left child
                while(IP->right != NULL && IP->right != curr)
                    IP = IP->right; // Move to rightmost node of left subtree

                // Inorder predecessor found → check if thread is present
                if(IP->right == NULL){
                    // Thread not created yet → create thread and move left
                    IP->right = curr; // Create temporary thread to parent
                    curr = curr->left; // Move to left child
                }
                else{
                    // Thread already created → process node and remove thread
                    IP->right = NULL; // Restore original right child
                    ans.push_back(curr->val); // Visit current node
                    curr = curr->right; // Move to right subtree
                }
            }
        }
        return ans;
    }
};

/*
LOGIC AND EXPLANATION (Detailed and understandable):

1. Inorder traversal means visiting nodes in the order: left subtree → node → right subtree.

2. The challenge is to do this without using recursion or extra stack space.

3. We use the concept of "threading":
   - Find the inorder predecessor (IP) → the rightmost node in the left subtree.
   - Temporarily link its right pointer to the current node (threading).
   - This helps us come back to the current node after processing the left subtree.

4. There are two cases in each iteration:

   CASE 1 → If curr->left is NULL:
     - There is no left subtree to process.
     - We can safely visit the current node and move to its right child.

   CASE 2 → If curr->left is not NULL:
     - Find IP → rightmost node in left subtree.
     - Check if IP’s right is NULL:
         → Create a temporary thread → IP->right = curr
         → Move left → curr = curr->left
     - Else (IP’s right == curr):
         → The thread already exists → remove it
         → Visit curr → ans.push_back(curr->val)
         → Move to the right subtree → curr = curr->right

5. This guarantees that every node is visited exactly once for processing, and at most twice for threading and unthreading.

6. Why no risk of losing the original tree?
   - We only create threads when IP->right is NULL → safe to modify.
   - Before visiting the current node after left traversal, we remove the thread → restoring tree structure.

7. Why does this guarantee full traversal?
   - Every node is either processed immediately (if no left child) or after exploring its left subtree through threading.
   - We eventually explore all leftmost paths before visiting nodes and their right children.

8. What is a thread and why create it?
   - Thread = temporary connection from the inorder predecessor back to the current node.
   - It simulates the stack return pointer that recursion would otherwise use.

9. Connections we are making:
   - We temporarily link IP->right → curr to revisit after left traversal.

10. By carefully creating and deleting threads, we ensure:
    ✔ Safe traversal
    ✔ No extra space
    ✔ Tree structure restored after traversal

*/

// MAIN FUNCTION TO TEST AND ANALYZE OUTPUT
int main() {
    // Constructing the following binary tree:
    //      1
    //     / \
    //    2   3
    //   / \
    //  4   5

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution solution;
    vector<int> result = solution.inorderTraversal(root);

    // Output the result
    cout << "Inorder Traversal: ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
IMPORTANT DETAILS, WARNINGS, AND KEY INSIGHTS:

✔ Threading is a temporary mechanism that helps simulate recursion using O(1) space.
✔ We only create threads where safe → at rightmost nodes with NULL pointers.
✔ Always check if the thread already exists before deleting it to avoid breaking the tree.
✔ After traversal, the tree structure is exactly as before → threads are removed.
✔ Understanding inorder predecessor is key to grasping Morris traversal.
✔ The algorithm guarantees every node is processed without missing or repeating any.

⚠ Warnings:
- Incorrect pointer manipulation will corrupt the tree or cause infinite loops.
- Debugging is harder because of temporary threads — thorough walkthroughs help.
- This approach is advanced and should be practiced multiple times before using in production.

✔ Key Insights:
- Space optimization doesn’t have to compromise correctness if we carefully manage temporary state.
- Morris traversal is a brilliant application of tree properties and recursion simulation.
- It's an excellent problem to understand how pointers and data structures work together.

SIMILAR QUESTIONS AND APPROACHES:
- 144. Binary Tree Preorder Traversal → visit node before left subtree.
- 145. Binary Tree Postorder Traversal → more complex threading or two stacks.
- 102. Binary Tree Level Order Traversal → BFS using queue, not DFS.
- 98. Validate Binary Search Tree → inorder traversal to check if nodes are sorted.

✔ Mastering this problem helps you understand advanced traversal techniques and pointer-based tree manipulation.
*/
