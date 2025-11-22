/*
Problem: Top View of Binary Tree (BFS Approach)
------------------------------------------------
Given a binary tree, return the nodes visible from the top view 
when the tree is viewed from above. The nodes should be returned 
from leftmost to rightmost.

Example:
Input:
        1
       / \
      2   3
       \
        4
         \
          5
           \
            6

Top View Output: 2 1 3 6

Explanation: 
- Nodes 2, 1, 3, 6 are visible from top when viewed from above.
- Nodes 4 and 5 are hidden behind others.

Approach: BFS using queue + map
- BFS ensures level by level processing (upper levels first).
- Map stores horizontal distance (hd) as key, node value as value.
- For top view, store the **first node encountered at each hd**.

Time Complexity (TC):
- O(N log N), N = number of nodes
  - BFS visits each node once → O(N)
  - Map insertion → O(log N) per node → total O(N log N)

Space Complexity (SC):
- O(N) for map + O(N) for queue → O(N)

Optimality:
- Yes, BFS + map is considered **most optimized standard solution**.
- Won’t cause MLE/TLE for typical constraints.

Similar Problems / Approaches:
- Bottom View: Use BFS, overwrite map for each hd.
- Vertical Order Traversal: Use BFS + map<int, vector<int>>.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Node structure for binary tree
*/
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

class Solution {
  public:
  
    // Function to return a list of nodes visible from the top view
    // from left to right in Binary Tree using BFS + map
    vector<int> topView(Node *root) {
        vector<int> ans;                   // Stores final top view nodes
        if(!root) return ans;              // Edge case: empty tree
        
        map<int, int> m;                   // Map: horizontal distance -> node value
        queue<pair<Node*, int>> q;         // Queue for BFS: stores (node, hd)
        
        q.push({root, 0});                 // Start BFS from root with hd=0
        
        while(!q.empty()){
            Node* curr = q.front().first;  // Current node being processed
            int currHd = q.front().second; // Its horizontal distance
            q.pop();                       // Remove from queue
            
            // If this horizontal distance is not yet seen, store node value
            // BFS ensures uppermost nodes are encountered first
            if(m.find(currHd) == m.end()) 
                m[currHd] = curr->data;
            
            // Add left child to queue with hd-1
            if(curr->left != NULL) 
                q.push({curr->left, currHd - 1});
            
            // Add right child to queue with hd+1
            if(curr->right != NULL) 
                q.push({curr->right, currHd + 1});
        }
        
        // Extract nodes from map in sorted order of hd (left to right)
        for(auto &it : m){
            ans.push_back(it.second);
        }
        return ans;
    }
};

/*
Logic / Explanation:
-------------------
1. BFS processes nodes level by level, so **upper levels are visited first**.
2. Horizontal distance (hd) is used to track vertical columns.
   - root hd = 0
   - left child hd = parent hd - 1
   - right child hd = parent hd + 1
3. Map stores the **first node encountered** at each hd → ensures top view.
4. No need to track level explicitly:
   - BFS guarantees upper levels first, so first node stored at hd is topmost.
5. Queue ensures all nodes are visited systematically (FIFO order).
6. Iterating over map gives nodes in **left to right** order (map keys are sorted).

Key points:
- Using `map` instead of `unordered_map` ensures left-to-right ordering.
- BFS naturally handles level-order traversal → no extra level variable.
- Each if/loop explained above ensures correct top view without missing nodes.
*/

int main() {
    // Construct example tree:
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->left->right->right = new Node(5);
    root->left->right->right->right = new Node(6);

    Solution sol;
    vector<int> res = sol.topView(root);

    cout << "Top View: ";
    for(int val : res) cout << val << " ";
    cout << endl;

    return 0;
}

/*
Key Insights / Warnings:
------------------------
- BFS ensures uppermost nodes are visited first → no level tracking needed.
- Map guarantees output in left-to-right order.
- Horizontal distance must be updated correctly:
    - left = hd-1, right = hd+1
- If unordered_map is used, output order can be wrong → not accepted in GFG.
- Similar problems: Bottom view (overwrite map), Vertical Order Traversal (store vectors per hd).

*/

