/*
Problem: Bottom View of Binary Tree (BFS Approach)
---------------------------------------------------
Given a binary tree, return the nodes visible from the bottom view 
when the tree is viewed from below. The nodes should be returned 
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

Bottom View Output: 2 4 5 6 3

Explanation:
- Nodes visible from bottom are 2, 4, 5, 6, 3.
- Node 1 is hidden by 4 and 5 when viewed from below.
- BFS ensures we overwrite nodes at same horizontal distance with deeper nodes.

Approach: BFS using queue + map
- BFS guarantees level-order traversal: upper levels are visited first.
- Map stores horizontal distance (hd) as key, node value as value.
- For bottom view, **always update** the map for a horizontal distance with the current node.
  This ensures the last node encountered at each hd is the bottom-most node.

Time Complexity (TC):
- O(N log N), N = number of nodes
  - BFS visits each node once → O(N)
  - Map insertion/overwrite → O(log N) per node → total O(N log N)

Space Complexity (SC):
- O(N) for map + O(N) for queue → O(N)

Optimality:
- BFS + map is considered most optimized standard solution.
- Won’t cause MLE/TLE for typical constraints.

Similar Problems / Approaches:
- Top View: Store **first node** at each hd (use `if(m.find(hd) == m.end())`).
- Vertical Order Traversal: Store vector of nodes per hd in map.
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
  
    // Function to return a list of nodes visible from the bottom view
    // from left to right in Binary Tree using BFS + map
    vector<int> bottomView(Node *root) {
        vector<int> ans;                   // Stores final bottom view nodes
        if(!root) return ans;              // Edge case: empty tree
        
        map<int, int> m;                   // Map: horizontal distance -> node value
        queue<pair<Node*, int>> q;         // Queue for BFS: stores (node, hd)
        
        q.push({root, 0});                 // Start BFS from root with hd=0
        
        while(!q.empty()){
            Node* curr = q.front().first;  // Current node being processed
            int currHd = q.front().second; // Its horizontal distance
            q.pop();                       // Remove from queue
            
            // Overwrite map at this horizontal distance with current node
            // Explanation: BFS guarantees that nodes are visited level by level
            // so the last node encountered at each hd will be the bottom-most node
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
1. BFS ensures **level-order traversal**, meaning nodes are visited from top to bottom level by level.
2. Horizontal distance (hd) tracks vertical columns:
   - root hd = 0
   - left child hd = parent hd - 1
   - right child hd = parent hd + 1
3. For bottom view, we **always overwrite** the node at a given hd:
   - Last node at each hd in BFS → bottom-most node in that column.
4. No `if(m.find(currHd) == m.end())` needed:
   - Top view: store **first node** at each hd → use `if`.
   - Bottom view: store **last node** at each hd → always overwrite.
5. Map ensures output is **sorted by hd**, giving left → right ordering.
6. Queue ensures BFS traversal, so deeper nodes naturally overwrite shallower nodes.

Key points:
- Map stores horizontal distance → node value; queue ensures level order.
- Correct horizontal distance update is essential: left=hd-1, right=hd+1.
- BFS guarantees bottom-most nodes without explicit level comparison.
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
    vector<int> res = sol.bottomView(root);

    cout << "Bottom View: ";
    for(int val : res) cout << val << " ";
    cout << endl;

    return 0;
}

/*
Key Insights / Warnings:
------------------------
- BFS naturally handles depth → no need for level variable.
- Horizontal distance must be correctly updated: left=hd-1, right=hd+1.
- Always overwriting map ensures bottom-most nodes are captured.
- Using unordered_map is **not safe** if left → right ordering is required; map guarantees sorted keys.
- Similar problems:
    - Top View: store first node only at hd.
    - Vertical Order Traversal: map<int, vector<int>> with BFS or DFS.
- Ensure proper queue usage for level-order correctness.
*/
