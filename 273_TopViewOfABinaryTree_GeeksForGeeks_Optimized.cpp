/*
Problem: Top View of Binary Tree

Given a binary tree, return the nodes visible from the top view from left to right.

- Nodes at the same horizontal distance from the root are seen from top based on their depth.
- Only the topmost node at each horizontal distance is considered.

Example:
        1
       / \
      2   3
       \
        4
         \
          5

Top View Output: 2 1 3

Explanation:
- Node 2 is the leftmost at horizontal distance -1.
- Node 1 is at hd=0.
- Node 3 is at hd=1.
- Nodes 4 and 5 are at the same horizontal distance as nodes above, so they are ignored.

Approach Used:
- DFS recursion with depth tracking.
- Use a map to store the first/topmost node for each horizontal distance.
- Compare levels (depths) to decide whether to overwrite a value.

Time Complexity:
- O(N log N), where N is the number of nodes.
- Map operations take O(log N) per insert/check.
- Traversal is O(N).

Space Complexity:
- O(N), for storing the map and recursion stack in worst case.

Is this the most optimized solution?
- ❌ No, BFS would give O(N) time complexity.
- ✅ But this DFS approach is correct, acceptable, and widely used.

Will it be accepted on GeeksforGeeks?
- ✅ Yes, it will be accepted and run successfully.
- ❌ It won't cause MLE or TLE unless the tree is extremely large or deeply skewed.

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
        if(root == NULL) return; // Base case: if node is null, stop recursion
        
        // If the horizontal distance is not yet in the map OR the current node is at a higher position (smaller level)
        if(m.find(index) == m.end() || level < m[index].second) {
            m[index] = {root->data, level}; // Store the node's value and level at this horizontal distance
        }
        
        // Explore left subtree with hd - 1 and level + 1
        helper(root->left, m, index - 1, level + 1);
        
        // Explore right subtree with hd + 1 and level + 1
        helper(root->right, m, index + 1, level + 1);
    }

    // Main function to return top view nodes from left to right
    vector<int> topView(Node* root) {
        vector<int> ans; // Stores final result
        
        map<int, pair<int, int>> m; // Stores horizontal distance, node value and level
        
        helper(root, m, 0, 0); // Start DFS from root at index 0 and level 0
        
        // Extract the values from the map in sorted order of horizontal distance
        for(auto& it : m) {
            ans.push_back(it.second.first);
        }
        
        return ans;
    }
};

/*
Logic Explanation:

1. Why do we use a map and not unordered_map?
   - The problem requires output in left-to-right order based on horizontal distance.
   - `map` maintains sorted order, so we can iterate from the smallest to largest horizontal distance.
   - `unordered_map` would require extra sorting after traversal, increasing complexity and error chances.

2. Why track 'level'?
   - Recursion does not guarantee that nodes closer to the root are processed before deeper ones.
   - A deeper node at the same horizontal distance could overwrite a top node if we don't compare levels.
   - Level helps us ensure that only the topmost node is considered at each horizontal distance.

3. Why track 'index' (horizontal distance)?
   - To group nodes based on their left/right displacement from the root.
   - Nodes at the same index share the same vertical line when seen from the top.

4. What does the 'if' block check in helper()?
   - It ensures that either:
     a) this horizontal distance is not yet encountered, OR
     b) the current node is at a shallower depth than the stored node.

5. Line-by-line explanation:
   - `if(root == NULL) return;`: Stops recursion at leaf nodes.
   - `if(m.find(index) == m.end() || level < m[index].second)`: Checks if we should insert or overwrite.
   - `m[index] = {root->data, level};`: Stores the node at this horizontal distance if conditions are met.
   - Recursive calls to left and right subtrees with updated index and level.

6. How it works:
   - Starts from root at index 0, level 0.
   - Traverses left and right subtrees while updating index and level.
   - Stores only the topmost nodes per horizontal distance in the map.
   - Iterates over the map to extract nodes in sorted order.

*/

int main() {
    // Creating a sample tree:
    /*
             1
           /   \
         2       3
          \
           4
            \
             5
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->left->right->right = new Node(5);

    Solution sol;
    vector<int> result = sol.topView(root);

    cout << "Top view of the binary tree: ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Important Details, Warnings, and Key Insights:

✔ Always use map when output order matters based on some key like horizontal distance.
✔ Level tracking is essential because recursion order can't be trusted to process upper nodes first.
✔ Index (horizontal distance) helps group nodes by their vertical position when viewed from top.
✔ The if condition ensures that we only store the node if it's the first at that index or at a shallower level.
✔ Avoid using unordered_map unless you explicitly track min/max keys and sort afterward.

Similar Questions and Approaches:
✔ Bottom View – requires overwriting nodes at the same index but keeps the deepest node.
✔ Vertical Order Traversal – collects all nodes at the same index and sorts by level.
✔ Left View – depends only on the first node seen at each depth when traversing from left.
✔ Right View – similar but from the right side.

Approach Variations:
✔ BFS – more efficient, guarantees level-order traversal, avoids depth tracking.
✔ DFS with depth – educational, helps understand recursion, but slightly less optimal.
✔ Iterative solutions – often used in contests to avoid stack overflow with deep trees.

*/

