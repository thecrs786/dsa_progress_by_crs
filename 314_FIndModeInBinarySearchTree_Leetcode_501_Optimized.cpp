#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*
====================================================================================
🧩 PROBLEM: LeetCode 501 — Find Mode in Binary Search Tree (Map/BFS Version)
====================================================================================

📜 Problem Statement:
---------------------
Given the root of a Binary Search Tree (BST), return all the mode(s) (i.e., the
element(s) that appear most frequently) in the given BST.

If the tree has multiple modes, return them in any order.

------------------------------------------------------------------------------------
⚠️ NOTE:
This approach **does not rely on BST properties**. It works for any binary tree.
It uses a **hash map to count frequencies** and a **queue for BFS traversal**.

====================================================================================
💡 KEY INSIGHTS:
----------------
1. Traverse the tree using **BFS (level-order traversal)**.
2. Count the frequency of each node value using an **unordered_map<int,int>**.
3. After traversal:
   - Determine the **maximum frequency**.
   - Collect all values that appear with that frequency into a result vector.

4. This method is conceptually simpler but uses **extra space O(N)** for the map.

====================================================================================
⏱️ COMPLEXITY:
---------------
Time Complexity:  O(N) — each node is visited once.
Space Complexity: O(N) — for unordered_map storing all node values, and queue for BFS.

====================================================================================
📘 EXAMPLE:
-----------
BST:
        1
         \
          2
         /
        2

Traversal order (BFS): [1, 2, 2]

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
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;

        unordered_map<int, int> freq; // store frequency of each value
        queue<TreeNode*> q;           // BFS queue
        q.push(root);

        // -------- BFS Traversal & Counting --------
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            freq[node->val]++; // increment frequency

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        // ------------------------------------------

        // Find maximum frequency
        int maxFreq = 0;
        for (auto &it : freq) {
            if (it.second > maxFreq) maxFreq = it.second;
        }

        // Collect all values that have frequency == maxFreq
        for (auto &it : freq) {
            if (it.second == maxFreq) ans.push_back(it.first);
        }

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
*/

int main() {
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
        BFS queue: [1] -> [2] -> [2]
        Frequency Map: {1:1, 2:2}
        maxFreq = 2
        ans = [2]
    */

    return 0;
}

/*
====================================================================================
🧭 QUICK REVISION NOTES:
------------------------
1. Use BFS (queue) to traverse all nodes.
2. Use unordered_map<int,int> to track frequency of each node value.
3. After traversal:
   - Determine max frequency.
   - Push all values with frequency == maxFreq into result vector.
4. Works for any binary tree, including BSTs with duplicates.
5. Time: O(N), Space: O(N)
====================================================================================
*/
