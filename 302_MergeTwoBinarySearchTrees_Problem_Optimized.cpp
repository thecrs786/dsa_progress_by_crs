#include <iostream>
#include <vector>
using namespace std;

/*
    Question (Brief):

    Given two Binary Search Trees (BSTs), merge them and return a balanced BST.
    The resulting BST should contain all nodes from both BSTs and remain height-balanced.

    Examples:
    BST1:        2
                / \
               1   3
    BST2:          7
                   / \
                  6   8
    Merged Balanced BST (inorder traversal):
    [1, 2, 3, 6, 7, 8] 
    Balanced BST example:
            3
           / \
          2   7
         /   / \
        1   6   8

    Approach:
    1. Perform inorder traversal of both BSTs (results in two sorted arrays).
    2. Merge these two sorted arrays (similar to merge step in merge sort).
    3. Construct a balanced BST from the merged sorted array by picking the middle element recursively.

    Time Complexity: 
        - O(n1 + n2) where n1 and n2 are the number of nodes in the two BSTs.
        - Inorder traversal: O(n1 + n2)
        - Merge arrays: O(n1 + n2)
        - Construct balanced BST: O(n1 + n2)
    
    Space Complexity:
        - O(n1 + n2) for storing inorder arrays.
        - O(h1 + h2) recursion stack during inorder traversal.
        - O(log(n1 + n2)) recursion stack while building balanced BST.

    Notes on Optimality:
        - This is an efficient and accepted approach for online platforms.
        - Memory usage is linear due to storing inorder arrays.
        - Will not cause TLE as all operations are linear.
        - Could be optimized further using in-place merging techniques (Morris Traversal + BST to DLL merge), but this is simple, readable, and safe.

*/

struct Node {
    int val;       // Node value
    Node* left;    // Left child pointer
    Node* right;   // Right child pointer

    Node(int data) {
        val = data;
        left = right = nullptr;
    }
};

class Solution {

    // Function: getInorder
    // Purpose: Perform inorder traversal of BST and store elements in a vector.
    // Reason: Inorder traversal of BST gives sorted elements, which can later be merged.
    void getInorder(Node* root, vector<int>& ans){
        if(root == nullptr) return;

        getInorder(root->left, ans);   // Traverse left subtree first (smaller values)
        ans.push_back(root->val);      // Visit root
        getInorder(root->right, ans);  // Traverse right subtree (larger values)
    }

    // Function: mergeTwovectors
    // Purpose: Merge two sorted vectors into one sorted vector.
    // Reason: Merging two BST inorder lists is like merging two sorted arrays.
    vector<int> mergeTwovectors(vector<int>& v1, vector<int>& v2){
        vector<int> ans;
        int i = 0, j = 0;

        // Merge step similar to merge sort
        while(i < v1.size() && j < v2.size()){
            if(v1[i] <= v2[j]){
                ans.push_back(v1[i++]);
            } else {
                ans.push_back(v2[j++]);
            }
        }

        // Append remaining elements if any
        while(i < v1.size()) ans.push_back(v1[i++]);
        while(j < v2.size()) ans.push_back(v2[j++]);

        return ans;
    }

    // Function: helper
    // Purpose: Construct a balanced BST from a sorted array.
    // Logic: Pick middle element as root to ensure balance; recursively do same for left and right subarrays.
    Node* helper(vector<int>& nums, int st, int end){
        if(st > end) return nullptr;  // Base case: no element to process

        int mid = st + (end - st) / 2; // Middle element for balance
        Node* root = new Node(nums[mid]);

        root->left  = helper(nums, st, mid - 1);   // Build left subtree
        root->right = helper(nums, mid + 1, end);  // Build right subtree

        return root;
    }

public:
    // Function: mergetwoBST
    // Purpose: Merge two BSTs and return balanced BST.
    Node* mergetwoBST(Node* root1, Node* root2) {
        vector<int> v1, v2;

        getInorder(root1, v1);  // Step 1: Get inorder of BST1 (sorted array)
        getInorder(root2, v2);  // Step 1: Get inorder of BST2 (sorted array)

        vector<int> nums = mergeTwovectors(v1, v2); // Step 2: Merge the two sorted arrays

        // Step 3: Build balanced BST from sorted merged array
        return helper(nums, 0, nums.size() - 1);
    }

};

/*
    Logic Explanation:

    1. Why Inorder Traversal:
       - Inorder traversal of BST produces sorted elements.
       - This allows easy merging with another sorted array.
    
    2. Merge Two Sorted Arrays:
       - Analogous to merge step in merge sort.
       - Guarantees combined sorted list of all BST nodes.

    3. Construct Balanced BST:
       - Pick middle element as root to minimize height.
       - Recursively apply same logic to left and right subarrays.
       - Ensures resulting BST is balanced, height = O(log(n1+n2)).

    4. Relation to "Merge Two Sorted Arrays":
       - Each BST's inorder is a sorted array.
       - Merging two BSTs reduces to merging two sorted arrays, then forming balanced BST.

    5. Why It Works:
       - Preserves BST property (left < root < right) because merged array is sorted.
       - Balanced because we pick middle element as root at each step.

    Key Insight:
    - This is a common pattern: BST → Sorted Array → Merge → Balanced BST.
*/

void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {

    // Create first BST
    Node* root1 = new Node(2);
    root1->left = new Node(1);
    root1->right = new Node(3);

    // Create second BST
    Node* root2 = new Node(7);
    root2->left = new Node(6);
    root2->right = new Node(8);

    Solution obj;
    Node* mergedRoot = obj.mergetwoBST(root1, root2);

    cout << "Inorder of merged balanced BST: ";
    printInorder(mergedRoot);  // Expected: 1 2 3 6 7 8
    cout << endl;

    return 0;
}

/*
    Important Details, Warnings, Key Insights:

    - Do NOT forget to mark mergetwoBST() as public, otherwise main() cannot access it.
    - Always use inorder traversal to convert BST to sorted array; otherwise, merge fails.
    - Merging two arrays is O(n), much more efficient than inserting nodes one by one.
    - Constructing balanced BST requires picking middle element recursively.
    - Edge cases: One or both BSTs can be empty; code handles it correctly.
    - Memory usage: Storing inorder arrays is linear (O(n1+n2)); recursion stack adds extra O(log n) for balanced BST creation.

    Similar Questions / Approaches:

    1. Merge two sorted arrays → Build balanced BST (exactly what we did)
    2. Merge two linked lists → Build balanced BST
    3. Flatten BST to sorted DLL → Merge → Build BST
    4. Convert sorted array to balanced BST
    5. K-way merge for multiple BSTs (generalization)

    Key takeaway: Merging BSTs efficiently relies on the property that inorder traversal produces a sorted list.
*/
