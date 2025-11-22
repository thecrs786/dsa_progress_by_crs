#include <bits/stdc++.h>
using namespace std;

/*
Question Number: LeetCode 116
Question: Populating Next Right Pointers in Each Node

Brief:
Given a perfect binary tree, populate each node's "next" pointer to point to its next right node. 
If there is no next right node, the "next" pointer should be set to NULL.

Examples:
Input:             1
                  / \
                 2   3
                / \ / \
               4  5 6  7

Output: Each node's next pointer is populated as:
1->NULL
2->3->NULL
4->5->6->7->NULL

Approach used: Level-order traversal (BFS) using queue
Time Complexity: O(n)  -> each node is visited once
Space Complexity: O(n) -> queue can hold maximum nodes of a level (~n/2)
Optimality: Not most optimal in space (recursive pointer approach is O(1) extra space)
Accepted by LeetCode? Yes. Will not cause TLE. Memory usage is acceptable for typical constraints.
*/

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:

    Node* connect(Node* root) {

        // Base case: empty tree or single node (no children)
        if(root==NULL || root->left==NULL) return root;

        // Queue for BFS; we will push NULL markers to identify end of each level
        queue<Node*> q;

        q.push(root);    // push root to start BFS
        q.push(NULL);    // marker for level-end
        Node* prev = NULL; // pointer to keep track of previous node at same level

        while(!q.empty()){
            Node* curr = q.front(); // get the current node
            q.pop();
            
            if(curr==NULL) {
                // End of current level
                if(q.size()==0) break; // If queue is empty, we are done
                else{
                    q.push(NULL); // add marker for next level
                }
                prev = NULL; // reset prev for next level
            }

            else{
                // Push children of current node into queue if they exist
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);

                // Connect previous node's next to current node
                if(prev) prev->next = curr;

                // Move prev to current node
                prev = curr;
            }
        }

        return root; // return modified tree
    }
};

/*
Logic and Explanation:

1. We perform a level-order traversal using a queue. Each level is separated using a NULL marker.
2. 'prev' is used to keep track of the previous node in the same level.
   - For the first node of a level, prev is NULL and nothing is connected.
   - For subsequent nodes, prev->next = curr establishes the link.
3. When we encounter NULL in the queue, it means the level ended:
   - We reset prev to NULL for the next level.
   - We push a new NULL if the next level exists.
4. Children of each node are pushed into the queue for BFS.
5. This ensures all nodes are connected correctly level by level.
6. Complexity:
   - Time: O(n) because each node is processed once.
   - Space: O(n) due to queue storing nodes of one level (~n/2 nodes max).

Key Insights:
- Using NULL markers allows tracking the end of a level in BFS easily.
- 'prev' pointer ensures we can connect nodes without nested loops.
- For perfect binary trees, recursive pointer approach is more space optimal.
- Similar problems: LeetCode 117 (non-perfect trees), connect nodes level-wise in any tree.
- Caution: Forgetting to reset prev at end of level can link nodes across levels incorrectly.
*/

int main() {
    // Constructing perfect binary tree for testing
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;
    sol.connect(root);

    // Print next of each level
    Node* level_start = root;
    while(level_start) {
        Node* curr = level_start;
        while(curr) {
            cout << curr->val << "->";
            if(curr->next) cout << curr->next->val << " ";
            else cout << "NULL ";
            curr = curr->next;
        }
        cout << endl;
        level_start = level_start->left;
    }

    return 0;
}

/*
Output:
1->NULL 
2->3->NULL 
4->5->6->7->NULL 

Explanation:
- Each level's nodes are printed in order with their next pointers.
- NULL signifies the end of level.
- This confirms that the BFS + prev pointer approach works perfectly.
*/
