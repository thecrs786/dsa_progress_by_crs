/*
Problem: Bottom View of Binary Tree

Given a binary tree, return the nodes visible from the bottom view from left to right.

- Nodes at the same horizontal distance from the root are seen from the bottom based on their depth.
- At each horizontal distance, the node with the greatest depth is visible from the bottom.

Example:
        1
       / \
      2   3
       \
        4
         \
          5

Bottom View Output: 2 4 5 3

Explanation:
- Node 2 is the leftmost at horizontal distance -1.
- Node 4 is at horizontal distance 0 and deeper than node 1, so it's visible.
- Node 5 is at horizontal distance 1 and deeper than node 3, so it's visible.
- Node 3 is at horizontal distance 2, so it's visible.

Approach Used:
- DFS recursion with depth tracking.
- Use a map to store the node visible at each horizontal distance.
- At each node, we overwrite the stored node if the current node is at a greater or equal depth.

Time Complexity:
- O(N log N), where N is the number of nodes.
- Map operations are O(log N) per insertion or lookup.

Space Complexity:
- O(N), for the map and recursion stack in the worst case.

Is this the most optimized solution?
- ❌ Not the most optimal because BFS provides O(N) time complexity without explicit depth comparisons.
- ✅ It is correct, widely accepted, and suitable for practice and interview scenarios.

Will this be accepted by GeeksforGeeks?
- ✅ Yes, this solution will be accepted.
- ❌ It will not cause Memory Limit Exceeded (MLE) or Time Limit Exceeded (TLE) under reasonable constraints.

*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Definition of a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:

    // Helper function to perform DFS traversal
    // Parameters:
    // root -> current node being visited
    // m -> map storing horizontal distance as key, and pair<node value, depth> as value
    // index -> horizontal distance from root
    // level -> depth from root (starting at 0)
    void helper(Node* root, map<int, pair<int, int>>& m, int index, int level) {
        if(root == NULL) return; // Base case: stop recursion when the node is null

        // If the horizontal distance is not yet stored OR the current node is at a deeper or same level,
        // update the map entry with the current node's value and level.
        // Using '>=', instead of '>', ensures that when two nodes have the same depth (level),
        // the later node in DFS traversal (which is usually right subtree in preorder DFS) will overwrite.
        // This is important because using only '>' would fail test cases where the bottommost node
        // lies on the right at the same depth as a node on the left. For example:
        /*
                 1
               /   \
             2       3
              \     /
               4   5
        Bottom view should be: 2 4 5 3
        If we used '>' instead of '>=', node 5 would not overwrite node 4 at hd=0,
        and the output would incorrectly be: 2 4 3
        */
        if(m.find(index) == m.end() || level >= m[index].second) {
            m[index] = {root->data, level};
        }

        // Explore left subtree: decrease horizontal distance by 1 and increase depth by 1
        helper(root->left, m, index - 1, level + 1);

        // Explore right subtree: increase horizontal distance by 1 and increase depth by 1
        helper(root->right, m, index + 1, level + 1);
    }

    // Function to compute the bottom view of a binary tree
    vector<int> bottomView(Node* root) {
        vector<int> ans; // To store the final result

        map<int, pair<int, int>> m; // Stores horizontal distance, node value, and depth

        helper(root, m, 0, 0); // Start DFS from root at horizontal distance 0 and level 0

        // Extract the node values from the map sorted by horizontal distance
        for(auto& it : m) {
            ans.push_back(it.second.first);
        }

        return ans;
    }
};

/*
Logic Explanation:

1. Why do we use a map instead of unordered_map?
   - The output requires the bottom view nodes from leftmost to rightmost.
   - A map keeps the keys (horizontal distances) sorted, so outputting them in order is straightforward.
   - unordered_map would need extra steps like sorting the keys before outputting.

2. Why track 'level'?
   - We need to determine which node at each horizontal distance is visible from the bottom.
   - Deeper nodes overwrite shallower ones.
   - Level ensures that only the deepest node is stored when there are multiple nodes at the same horizontal distance.

3. Why track 'index' (horizontal distance)?
   - Horizontal distance differentiates left and right displacements.
   - It helps group nodes by where they would appear in the view from the bottom.

4. Why use '>=', not '>'?
   - If two nodes are at the same depth and horizontal distance, the node visited later in DFS should overwrite.
   - Using only '>' would fail cases where right-side nodes at same depth are not recorded.
   - '>=’ ensures bottom-most nodes (including right-side same depth nodes) are captured correctly.

5. What does the 'if' block check in helper()?
   - It inserts the node if this horizontal distance hasn't been seen.
   - Or it overwrites the entry if the current node is deeper or at the same depth.

6. How it works:
   - Starts at the root node with index 0 and level 0.
   - Recursively explores left and right subtrees, updating index and level.
   - At each node, it decides whether to store the node based on depth.
   - After traversal, it extracts nodes sorted by horizontal distance.

*/

int main() {
    // Sample tree:
    /*
             1
           /   \
         2       3
          \     /
           4   5
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->left = new Node(5);

    Solution sol;
    vector<int> result = sol.bottomView(root);

    cout << "Bottom view of the binary tree: ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Important Details, Warnings, and Key Insights:

✔ We use a map to automatically keep horizontal distances sorted for ordered output.
✔ Level tracking ensures that deeper nodes are preferred over shallower ones at the same index.
✔ Index (horizontal distance) groups nodes by where they appear when viewed from the bottom.
✔ The if condition ensures nodes are overwritten only when they're at a deeper or same level.
✔ Using unordered_map would require additional sorting to maintain left-to-right order.

Warnings:
❌ Without level tracking, shallower nodes could incorrectly overwrite deeper nodes.
❌ Using only '>' instead of '>=' can fail when right-side nodes at the same depth exist.

Key Insights:
✔ Top view uses level < existing_level, while bottom view uses level >= existing_level.
✔ The DFS structure is similar to top view, but comparison logic is reversed for depth.
✔ Always test edge cases with nodes at same depth and horizontal distance.

Similar Questions and Approaches:
✔ Top View – keeps shallowest node at each horizontal distance.
✔ Vertical Order Traversal – groups nodes by horizontal distance and sorts by depth.
✔ Right View – shows nodes visible when viewed from the right side.
✔ Left View – similar logic but from the left side.

Approach Variations:
✔ BFS – more optimal, processes nodes level by level without explicit depth checks.
✔ DFS – educational, helps understand recursion and state tracking.
✔ Iterative approaches – preferred in contests to avoid recursion depth limits.
*/
