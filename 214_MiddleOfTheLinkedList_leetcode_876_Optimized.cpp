// ============================================================================
// LeetCode 876 - Middle of the Linked List
// ============================================================================
// Problem (in brief):
// You are given the head of a singly linked list. 
// Return the middle node of the linked list.
// If there are two middle nodes, return the second one.
//
// Example 1: Input: [1,2,3,4,5]   -> Output: node with val=3
// Example 2: Input: [1,2,3,4,5,6] -> Output: node with val=4
//
// ============================================================================
// Solution Method: Two-pass counting approach (YOUR method)
// 1st pass: Traverse the list to count the number of nodes.
// 2nd pass: Move again to reach the middle node and return it.
// 
// Time Complexity  : O(n)  (2 passes → still O(n))
// Space Complexity : O(1)  (only a few variables used)
// Will it be accepted on LeetCode? YES. No TLE/MLE since O(n), O(1).
// Is it the most optimal? NO. Optimal is fast/slow pointers (1 pass).
// But your method is still efficient and completely acceptable.
// ============================================================================

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list (provided by LeetCode).
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}            // default constructor
    ListNode(int x) : val(x), next(nullptr) {}       // constructor with value
    ListNode(int x, ListNode *next) : val(x), next(next) {} // full constructor
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // ----------------------------
        // Step 1: Count total nodes
        // ----------------------------
        ListNode* temp = head;   // pointer to traverse the list
        int len = 0;             // variable to count nodes
        while (temp != nullptr) {
            len++;               // increment count for each node
            temp = temp->next;   // move forward
        }
        // After this loop, len contains total number of nodes in the list.

        // ----------------------------
        // Step 2: Calculate middle index
        // ----------------------------
        // For odd length: middle = len/2 (integer division).
        // For even length: middle = len/2 (this ensures we pick the SECOND middle).
        // Example: len=5 -> 5/2 = 2 (0-based index 2 → 3rd node).
        // Example: len=6 -> 6/2 = 3 (0-based index 3 → 4th node, second middle).
        int middleIndex = len / 2;

        // ----------------------------
        // Step 3: Traverse again to middle
        // ----------------------------
        temp = head; // reset pointer back to start
        for (int i = 0; i < middleIndex; i++) {
            temp = temp->next; // move step by step until reaching middleIndex
        }

        // ----------------------------
        // Step 4: Return the middle node
        // ----------------------------
        return temp;
    }
};

// ============================================================================
// Utility functions for testing
// ============================================================================

// Build a linked list from a vector of ints
ListNode* buildList(const vector<int>& vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (size_t i = 1; i < vals.size(); i++) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

// Print a linked list from a given node
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// ============================================================================
// Main function with working examples
// ============================================================================
int main() {
    Solution sol;

    // Example 1: Odd length list
    vector<int> vals1 = {1,2,3,4,5};
    ListNode* head1 = buildList(vals1);
    cout << "Input list 1: ";
    printList(head1);
    ListNode* mid1 = sol.middleNode(head1);
    cout << "Middle node value (expected 3): " << mid1->val << endl << endl;

    // Example 2: Even length list
    vector<int> vals2 = {1,2,3,4,5,6};
    ListNode* head2 = buildList(vals2);
    cout << "Input list 2: ";
    printList(head2);
    ListNode* mid2 = sol.middleNode(head2);
    cout << "Middle node value (expected 4): " << mid2->val << endl << endl;

    // Example 3: Single node list
    vector<int> vals3 = {10};
    ListNode* head3 = buildList(vals3);
    cout << "Input list 3: ";
    printList(head3);
    ListNode* mid3 = sol.middleNode(head3);
    cout << "Middle node value (expected 10): " << mid3->val << endl << endl;

    return 0;
}

// ============================================================================
// Key Insights & Explanation of Logic
// ============================================================================
// Why do we need two passes?
// 1st pass → to find how many nodes exist (length).
// 2nd pass → to walk exactly to the middle index.
//
// Why return len/2?
// Because integer division automatically gives correct index:
// - Odd length (5) → 5/2 = 2 → index 2 (3rd element).
// - Even length (6) → 6/2 = 3 → index 3 (4th element), which is the second middle.
//
// Why not move pointers differently?
// If you tried to find the middle directly in first loop,
// you’d need two pointers moving at different speeds (fast & slow).
// That’s the more optimal method, but since you chose counting, we stick with it.
//
// Why is this correct?
// Because traversal is linear and deterministic — counting ensures we know
// exactly where the middle is, and the second traversal stops exactly there.
// ============================================================================

