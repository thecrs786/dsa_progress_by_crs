#include <iostream>
using namespace std;

/*
    Question 116: Populating Next Right Pointers in Each Node
    -------------------------------------------------------------------
    Given a perfect binary tree (all leaves are at same level, and every parent has two children),
    populate each node's `next` pointer to point to its next right node. If there is no next right node,
    the `next` pointer should be set to NULL.

    Example:
    
        Input:          1
                       / \
                      2   3
                     / \ / \
                    4  5 6  7

        Output: After connecting next pointers:
        
            Level 1: 1->NULL
            Level 2: 2->3->NULL
            Level 3: 4->5->6->7->NULL

    Approach:
    -------------------------------------------------------------------
    Recursive cross-parent linking method:
    - For each node:
        - Connect left child to right child.
        - Connect right child to root->next->left if root->next exists.
    - Recur for left and right children.
    - Works only for perfect binary trees where we know every node has both left and right children.
    
    Time Complexity: O(n) → each node visited exactly once
    Space Complexity: O(h) → recursion stack, h = height of tree (log n for perfect tree)
    Optimal? Yes, for perfect binary trees. Avoids extra queue or array usage.
    Accepted on LeetCode? ✅ Yes
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
        if(root==NULL) return root; // Base case: empty tree

        // Step 1: connect left child to right child
        if(root->left){
            root->left->next = root->right;

            // Step 2: connect right child to next subtree's left child if it exists
            if(root->next){
                root->right->next = root->next->left;
            }
        }

        // Step 3: recursively process left and right subtrees
        connect(root->left);
        connect(root->right);

        // Step 4: return root after connecting all next pointers
        return root;
    }
};

/*
    Logic & Explanation:
    -------------------------------------------------------------------
    1. This recursion starts **from the root (top)** and goes downward.
       - Each call processes current node connections before going deeper.
    2. The "if(root->left)" ensures we only process internal nodes with children.
    3. root->left->next = root->right → always valid for perfect tree.
    4. root->right->next = root->next->left → connects across subtrees.
       - Only done if root->next exists.
       - This is the key "cross-parent" connection.
    5. Recurse left and right ensures every level is fully linked.
    6. Each node's next pointer is set exactly once.
    
    Dry run example:
    ----------------
    Input:  1
           / \
          2   3
    Level 1: connect 2->3
    - 2->next = 3
    - 3->next = NULL (since 1->next = NULL)

    Recurse left:
      Node 2:
      - Connect 4->5
      - Connect 5->6 (because 2->next = 3, 3->left = 6)
    Recurse right:
      Node 3:
      - Connect 6->7
      - 7->next = NULL
    Done!

    This ensures all nodes at each level are connected in **O(n) time**.

    Important Details / Warnings:
    ----------------------------------
    - Works **only for perfect binary trees**.
    - For non-perfect trees, need BFS or prev-pointer tracking.
    - Space optimized: recursion stack only, O(log n).
    - Key insight: "cross-parent linking" is what makes it O(1) extra space.
    
    Similar Questions / Approaches:
    ----------------------------------
    - 117. Populating Next Right Pointers in Each Node II (handles any tree)
        → Requires BFS or prev-pointer approach.
    - BFS Level order traversal with queue
        → O(n) time, O(n) space.
    - DFS with prev pointer
        → O(n) time, O(log n) stack, slightly more general.
*/

/* Utility function to print next pointers of each level */
void printNextPointers(Node* root) {
    while(root) {
        Node* curr = root;
        while(curr) {
            cout << curr->val << "->";
            if(curr->next)
                cout << curr->next->val << " ";
            else
                cout << "NULL ";
            curr = curr->next;
        }
        cout << endl;
        root = root->left;
    }
}

int main() {
    /*
        Construct perfect binary tree:
                  1
                /   \
               2     3
              / \   / \
             4   5 6   7
    */
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n2 = new Node(2, n4, n5, nullptr);
    Node* n3 = new Node(3, n6, n7, nullptr);
    Node* n1 = new Node(1, n2, n3, nullptr);

    Solution sol;
    Node* root = sol.connect(n1);

    cout << "Next pointers after connecting:" << endl;
    printNextPointers(root);

    return 0;
}

/*
    Key Insights:
    ----------------------------------
    - Cross-parent connection allows O(1) extra space.
    - Recursive solution starts **top-down** to ensure right pointers for lower levels.
    - Only internal nodes are connected; leaves have NULL next automatically.
    - Perfect tree property is crucial; otherwise cross-parent link may not exist.

    Dry Run Notes:
    - Node 2 connects 2->3
    - Node 4 connects 4->5
    - Node 5 connects 5->6
    - Node 6 connects 6->7
    - Node 7 connects 7->NULL

    Variants:
    - Non-perfect tree → 117. Next Right Pointers II → BFS / prev pointer solution
    - BFS level-order → simpler but uses O(n) extra space
    - Recursive cross-parent → optimal for perfect binary trees
*/
