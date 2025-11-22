/*
Problem: Print All Nodes at Kth Level of Binary Tree

Given a binary tree and an integer K, return all the nodes present at the Kth level of the binary tree from left to right.

- The root node is considered at level 1.
- Nodes at level K should be returned in left-to-right order as they appear in the tree.

Example 1:
        1
       / \
      2   3
       \
        4
         \
          5

K = 3
Output: 4

Explanation:
- Level 1: 1
- Level 2: 2 3
- Level 3: 4 (only one node at this level)

Example 2:
        1
       / \
      2   3
     / \
    4   5

K = 2
Output: 2 3

Explanation:
- Level 1: 1
- Level 2: 2 3
- Level 3: 4 5 (not included because K=2)

Approach Used:
- DFS (Depth First Search) recursion to track the current level.
- Base case stops recursion if the current node is NULL.
- When current level == K, push node's value to the result vector.

Time Complexity:
- O(N), where N is the number of nodes in the tree. Each node is visited once.

Space Complexity:
- O(H), where H is the height of the tree due to recursion stack.
- O(N) in worst case for skewed tree.

Is it the most optimal?
- ✅ Acceptable for recursion-based approach.
- ✅ BFS level-order traversal could also be used iteratively and is similarly efficient.

Will it be accepted by online platforms?
- ✅ Yes, it won't cause MLE or TLE for standard constraints.

*/

#include <iostream>
#include <vector>
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

    // Helper function to traverse the tree and collect nodes at kth level
    // Parameters:
    // root -> current node being visited
    // ans -> vector storing nodes at kth level
    // k -> target level
    // level -> current level during DFS traversal
    void helper(Node* root, vector<int> &ans, int k, int level) {
        if(!root) return;  // Base case: stop recursion at NULL node
        
        if(level == k) {   // If current node is at target level
            ans.push_back(root->data);  // Add node to result
            return;  // No need to go deeper as we only need kth level
        }

        // Recursive call to left subtree with level incremented by 1
        helper(root->left, ans, k, level+1);

        // Recursive call to right subtree with level incremented by 1
        helper(root->right, ans, k, level+1);
    }

    // Main function to return all nodes at kth level
    vector<int> kthLevelOfTree(Node* root, int k) {
        vector<int> ans;  // Result vector to store nodes at kth level
        helper(root, ans, k, 1);  // Start DFS from root at level 1
        return ans;
    }
};

/*
Logic Explanation:

1. Base condition:
   - If the current node is NULL, we stop recursion.
   - This prevents runtime errors and ensures we don't traverse beyond leaves.

2. Checking level:
   - If current level equals K, we add the node to result.
   - We return immediately to avoid unnecessary recursion beyond the kth level.

3. Recursive calls:
   - Traverse left subtree first, then right subtree.
   - Increment current level by 1 in recursive calls to track depth.

4. Why DFS works:
   - DFS ensures we visit nodes depth-wise.
   - Left-to-right order is maintained because left recursion happens before right recursion.

5. Why recursion stack is enough:
   - We only need to track the current level and node.
   - No extra data structures are required unlike BFS.

6. Base of recursion guarantees safety:
   - Stops at NULL nodes.
   - Stops adding nodes once we reach kth level for each branch.

*/

int main() {
    // Constructing binary tree for testing
    /*
             1
           /   \
         2       3
        / \     
       4   5
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    Solution sol;
    int k = 2;

    vector<int> result = sol.kthLevelOfTree(root, k);

    cout << "Nodes at level " << k << ": ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Important Details, Warnings, and Key Insights:

✔ Base case is critical: if(!root) return; prevents crashes and unnecessary recursion.
✔ Use 'level' parameter to track depth; starts at 1 if root is considered level 1.
✔ DFS recursion ensures left-to-right order automatically due to call sequence.
✔ Pushing nodes at level == k ensures correctness and stops recursion further.
✔ BFS can be used for iterative solution with queue for similar results.

Warnings:
❌ Forgetting NULL check will cause runtime errors.
❌ Forgetting return after pushing node at kth level will traverse deeper unnecessarily.

Similar Questions and Approaches:
✔ Level Order Traversal – prints all nodes level by level.
✔ Right View / Left View of Binary Tree – only certain nodes at each level.
✔ Nodes at K Distance from Target Node – requires additional tracking.

Approach Variations:
✔ DFS recursion (as above) – simple and elegant.
✔ BFS iterative using queue – avoids recursion stack, useful for very deep trees.
*/
