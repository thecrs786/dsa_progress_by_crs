#include <iostream>
#include <vector>
#include <memory> // optional, for smart pointers if you ever use them

using namespace std;

/*
Problem (brief):
Given the root of a Binary Search Tree (BST) and an integer key,
return a vector of two integers: {inorder_predecessor, inorder_successor} 
for the key in the BST.

- If predecessor or successor doesn't exist, return -1 in its place.
- If the key is NOT present in the BST, this implementation returns the
  predecessor and successor as if the key were inserted (i.e., the nearest
  smaller and nearest larger elements). (If you need an empty vector when
  key is absent, adapt the code with a `found` flag—explained later.)

Examples (in comments):
1) For BST:
         50
        /  \
      30    70
     / \   / \
    20 40 60 80

- key = 30  -> predecessor = 20, successor = 40  => {20, 40}
- key = 50  -> predecessor = 40, successor = 60  => {40, 60}
- key = 65  (not present) -> predecessor = 60, successor = 70 => {60, 70}
- key = 20  -> predecessor = -1, successor = 30 => {-1, 30}
- key = 80  -> predecessor = 70, successor = -1 => {70, -1}

Approach name:
Iterative BST search maintaining candidate predecessor (IP) and successor (IS);
if the node is found, refine IP and IS using node's left/right subtrees.

Time complexity: O(h) where h = height of BST (O(log n) average, O(n) worst)
Space complexity: O(1) extra space (iterative, constant extra memory)

Is this optimal?
- This is optimal in time for a BST if you only have parentless nodes and want O(h) time.
- Uses constant extra space, so it's optimal for iterative approach.
- Will be accepted on online judges (LeetCode / GFG) if they expect the predecessor/successor values.
- No TLE or MLE for typical BST sizes when implemented correctly.
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    // constructors (LeetCode-style)
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Returns {inorder_predecessor, inorder_successor}
    // If predecessor / successor doesn't exist, returns -1 in that slot.
    // Note: if key is not present, this returns the predecessor and successor
    // that would be neighbors if the key were inserted into the BST.
    vector<int> getIPandIS(TreeNode* root, int key) {
        vector<int> ans;

        TreeNode* IP = nullptr; // candidate inorder predecessor (largest < key)
        TreeNode* IS = nullptr; // candidate inorder successor   (smallest > key)
        TreeNode* curr = root;

        // Iterative BST search:
        // - while going left, current node is a candidate successor (IS)
        // - while going right, current node is a candidate predecessor (IP)
        while (curr != nullptr) {
            if (curr->val == key) {
                // If key node is found, refine predecessor and successor
                // using left and right subtrees respectively.
                if (curr->left) {
                    // Predecessor is rightmost node of left subtree
                    TreeNode* temp = curr->left;
                    while (temp->right != nullptr) temp = temp->right;
                    IP = temp;
                }
                if (curr->right) {
                    // Successor is leftmost node of right subtree
                    TreeNode* temp = curr->right;
                    while (temp->left != nullptr) temp = temp->left;
                    IS = temp;
                }
                break; // found the node; done
            }
            else if (curr->val > key) {
                // current node value is greater than key:
                // it could be the successor of key, go left to find closer candidate
                IS = curr;
                curr = curr->left;
            }
            else { // curr->val < key
                // current node value is less than key:
                // it could be the predecessor of key, go right to find closer candidate
                IP = curr;
                curr = curr->right;
            }
        }

        // Return results:
        // If you prefer to return empty vector when key not found, add a `found` flag
        // and only push results when found == true.
        ans.push_back(IP ? IP->val : -1);
        ans.push_back(IS ? IS->val : -1);
        return ans;
    }
};

/*
Detailed logic / explanation (READ CAREFULLY — inline step-by-step)

Goal: For a given key, find the nodes that would come immediately before
(inorder predecessor) and immediately after (inorder successor) the key in
an inorder traversal of the BST.

Key facts about BST inorder traversal:
- Inorder traversal: left -> node -> right
- For any node:
  - All nodes in left subtree have smaller values.
  - All nodes in right subtree have larger values.

Two main cases to consider:
1) Node with value == key exists in tree:
   - Predecessor (IP): if node has a left subtree, it's the rightmost node
     (maximum) in that left subtree.
     Reason: in left subtree, the maximum is the last node visited before the node.
   - Successor (IS): if node has a right subtree, it's the leftmost node
     (minimum) in that right subtree.
     Reason: in right subtree, the minimum is the first node visited after the node.

   Example: node 50 with left subtree ... -> predecessor = max(left)
            node 50 with right subtree ... -> successor = min(right)

2) Node with value == key does NOT exist:
   - Imagine we search for the key in the BST and we end up at a null leaf.
   - While searching, we maintain candidates:
     - When we go left (because current.val > key), current might be the smallest
       node > key we have seen so far. So set IS = current.
     - When we go right (because current.val < key), current might be the largest
       node < key we have seen so far. So set IP = current.
   - At the end of search (if not found), IP and IS are the immediate neighbors
     where the key would be inserted between IP and IS.

Why this single traversal covers both cases:
- While searching, we always maintain closest ancestor candidates.
- If we find the node, we refine using its subtrees (because actual in-order
  neighbors might be inside its subtrees).
- If we don't find the node, the maintained candidates are correct.

Edge cases:
- Key is less than all nodes -> predecessor = -1, successor = smallest node >= all.
- Key is greater than all nodes -> predecessor = largest node <= all, successor = -1.
- Node has only left subtree -> successor must come from ancestors (or be -1).
- Node has only right subtree -> predecessor must come from ancestors (or be -1).

Why not recursion / parent pointers?
- This iterative method uses no parent pointers and only O(1) extra memory.
- Recursion could also be used, but would use O(h) call stack.

Complexity:
- Time: O(h) where h is height of BST.
- Space: O(1) extra memory.

Now: working main() with multiple test cases and prints.
*/

int main() {
    // Build sample BST used in examples:
    //
    //          50
    //         /  \
    //       30    70
    //      / \   /  \
    //     20 40 60  80
    //
    TreeNode* n20 = new TreeNode(20);
    TreeNode* n40 = new TreeNode(40);
    TreeNode* n60 = new TreeNode(60);
    TreeNode* n80 = new TreeNode(80);
    TreeNode* n30 = new TreeNode(30, n20, n40);
    TreeNode* n70 = new TreeNode(70, n60, n80);
    TreeNode* n50 = new TreeNode(50, n30, n70);

    Solution sol;

    // Utility lambda to print result vectors
    auto printResult = [](int key, const vector<int>& res) {
        cout << "key = " << key << " => ";
        if (res.empty()) {
            cout << "[] (key not present and code set to return empty)\n";
            return;
        }
        cout << "IP = " << res[0] << ", IS = " << res[1] << '\n';
    };

    // Test cases
    vector<int> keys = {30, 50, 65, 20, 80, 10, 90}; // includes non-existent keys 65, 10, 90
    for (int k : keys) {
        vector<int> ans = sol.getIPandIS(n50, k);
        printResult(k, ans);
    }

    // Clean up allocated nodes (optional but good habit)
    delete n20;
    delete n40;
    delete n60;
    delete n80;
    delete n30;
    delete n70;
    delete n50;

    return 0;
}

/*
Key insights, warnings, and similar problems (study notes):

Important details & warnings:
- This implementation returns predecessor/successor even if key is absent.
  If the problem requires returning an empty vector (or -1s only if node exists),
  add a boolean `found` flag that becomes true only when curr->val == key,
  and only construct the answer when found == true. (You already experimented
  with that earlier.)
- Use nullptr instead of NULL (modern C++).
- Always check for nulls when traversing subtrees.
- If tree is extremely skewed (linked-list like), height h = n and time becomes O(n).
- Memory: iterative approach uses constant extra memory (O(1)). If you used recursion,
  the stack would cost O(h).

Why this won't TLE / MLE on typical online judges:
- Each node is visited at most once along the search path, so O(h) operations.
- No extra large allocations or recursion stack, so no risk of MLE here.

Possible pitfalls:
- Accidentally using curr->left when you meant curr->right (common bug) — double-check.
- Forgetting to `break` after finding the node; then candidates may be overwritten.
- Returning values in wrong order; always return {predecessor, successor}.

Similar problems & variations:
- "Find inorder successor of a given node in BST" (single value return).
- "Find inorder predecessor of a given node in BST".
- "Given a node pointer (with parent pointers available), find successor/predecessor" (different methods).
- "Insert key in BST and return predecessor & successor" — similar idea but with insertion.
- "Convert BST to Doubly Linked List" — related to inorder sequence.
- Problems involving floor/ceil in BST or nearest values queries: same candidate-tracking idea.

Approaches for similar tasks:
- Maintain candidate while searching (this file's approach).
- Use inorder traversal and keep previous/next pointers (O(n) time, O(1) space with Morris).
- If parent pointers exist, climbing to ancestors is easier to find predecessor/successor.

Final thought (teacher advice, short & blunt):
This is the correct, clean, and optimal (in normal conditions) approach for the stated problem. Keep both variants in your toolkit: (A) returning neighbors for non-existing key (this one), and (B) returning empty vector or special behavior when key absent. Both are asked in different problems — read problem statement carefully before coding.

*/
