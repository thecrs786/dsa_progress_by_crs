/**************************************************************************************************
 * Question 123: Maximum Width of Binary Tree
 *
 * Brief:
 * Given a binary tree, find the maximum width of the tree. 
 * The width of one level is defined as the length between the leftmost and rightmost non-null nodes,
 * counting all the null nodes in between (like a complete binary tree).
 *
 * Example 1:
 * Input: [1,3,2,5,3,null,9]
 *           1
 *         /   \
 *        3     2
 *       / \     \
 *      5   3     9
 * Output: 4
 * Explanation: Maximum width is level 3: nodes = [5,3,null,9], width = 4
 *
 * Example 2:
 * Input: [1,3,null,5,3]
 *           1
 *         / 
 *        3   
 *       / \
 *      5   3
 * Output: 2
 *
 * Approach / Method:
 * - BFS (Breadth First Search / Level Order Traversal) using a queue
 * - Use indices as if the tree is a Complete Binary Tree (CBT) to track positions
 * - This helps calculate exact width even when some nodes are missing (null)
 *
 * Time Complexity: O(N), N = number of nodes, each node is visited once
 * Space Complexity: O(N), queue can hold at most N nodes (widest level)
 * Optimal: Yes, accepted by LeetCode, no TLE or MLE due to unsigned long long
 **************************************************************************************************/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
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
    int widthOfBinaryTree(TreeNode* root) {
        // Queue stores pairs: {node, index_as_if_CBT}
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0}); // root index = 0
        int maxwid = 0;    // stores maximum width

        while(!q.empty()){
            int currlevel = q.size();  // number of nodes at current level
            unsigned long long stIdx = q.front().second; // first node's index
            unsigned long long endIdx = q.back().second; // last node's index

            // calculate width of current level
            maxwid = max(maxwid, (int)(endIdx - stIdx + 1));

            // Process all nodes at this level
            for(int i = 0; i<currlevel; i++){
                auto curr = q.front(); q.pop();
                unsigned long long idx = curr.second; // index of current node

                // left child index in CBT formula = 2*idx + 1
                if(curr.first->left) q.push({curr.first->left, idx*2+1});
                // right child index in CBT formula = 2*idx + 2
                if(curr.first->right) q.push({curr.first->right, idx*2+2});
            }
        }
        return maxwid;
    }
};

/**************************************************************************************************
 * Logic & Detailed Explanation:
 *
 * 1. CBT (Complete Binary Tree) Concept:
 *    - Every level is fully filled except possibly last
 *    - All nodes in last level are left-aligned
 *    - Indexing CBT helps handle "null gaps" in incomplete trees
 *
 * 2. Role of Queue:
 *    - Standard BFS / Level Order Traversal
 *    - Each node processed level by level
 *    - Queue stores both node pointer and its "CBT index"
 *
 * 3. Role of Indices:
 *    - Treat tree as array: root = 0
 *      - left = 2*idx + 1
 *      - right = 2*idx + 2
 *    - This "virtual index" allows calculation of width including nulls
 *    - Helps compute width = rightmost_index - leftmost_index + 1
 *
 * 4. Variables:
 *    - maxwid: maximum width seen so far
 *    - currlevel: number of nodes in current level
 *    - stIdx, endIdx: first and last index of current level
 *    - idx: CBT index of current node
 *
 * 5. Overflow Considerations:
 *    - Multiplying indices can overflow int for deep trees
 *    - Use unsigned long long to prevent overflow
 *
 * 6. Edge Cases Handled:
 *    - Null nodes are naturally skipped; CBT indexing accounts for gaps
 *    - Single node tree → width = 1
 *    - Sparse tree → width correctly calculated using CBT indices
 *
 * 7. Loop Explanation:
 *    - Outer while → iterates over levels
 *    - Inner for → iterates all nodes at current level
 *    - Index formulas assign correct positions to left/right children
 *
 * 8. CBT Indexing Formula & Virtual Array Explanation (Added Detail):
 *    - We **imagine the binary tree stored as a CBT array**, like heap array storage:
 *        - Root at index 0
 *        - For node at index idx:
 *            - Left child → 2*idx + 1
 *            - Right child → 2*idx + 2
 *    - Missing nodes (nulls) occupy "virtual positions" in this array
 *    - Example Tree:
 *          1
 *        /   \
 *       3     2
 *      / \     \
 *     5   3     9
 *    Virtual array positions (indices):
 *    [0]=1, [1]=3, [2]=2, [3]=5, [4]=3, [5]=null, [6]=9
 *    - Width of a level = index of last node - index of first node + 1
 *    - This works even if some nodes are missing (null) because their "virtual index" is counted
 *
 * 9. How the indexing helps solve the problem:
 *    - Even if the tree is sparse, the formula gives exact positions
 *    - BFS + indices ensures we measure distance between leftmost and rightmost nodes
 *    - Allows us to correctly handle nulls without actually storing them
 *    - Guarantees maximum width calculation
 *
 * 10. Guarantee:
 *    - Each node's CBT index ensures correct width calculation even with missing nodes
 *    - Queue ensures level-by-level processing
 *    - BFS + CBT indexing → exact maximum width
 *
 * 11. Similar Questions / Variations:
 *    - Maximum Width using DFS (with level & min/max index map)
 *    - Minimum Depth / Maximum Depth of Binary Tree
 *    - Binary Tree Right / Left Side View
 *
 **************************************************************************************************/

// Working Example for Running & Output
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(9);

    Solution sol;
    int maxWidth = sol.widthOfBinaryTree(root);
    cout << "Maximum Width of Binary Tree: " << maxWidth << endl; // Expected: 4

    return 0;
}

/**************************************************************************************************
 * Key Insights / Warnings / Notes:
 *
 * - Use unsigned long long for CBT indices to prevent overflow
 * - CBT indexing allows inclusion of nulls in width calculation
 * - Queue stores nodes + indices for level order processing
 * - maxwid stores final answer
 * - Width of level = last_index - first_index + 1
 * - Inner loop processes all nodes in current level
 * - BFS ensures level by level, guaranteeing correctness
 * - Similar approaches: DFS with map<int, pair<min_idx, max_idx>>
 * - Edge case: deep trees may need index normalization (optional) to prevent extreme overflow
 *
 **************************************************************************************************/
