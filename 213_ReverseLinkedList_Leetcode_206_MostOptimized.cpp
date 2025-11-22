// ============================================================================
// LeetCode 206: Reverse Linked List
// ============================================================================
//
// 📌 Problem Statement (in brief):
// Given the head of a singly linked list, reverse the list and return the new head.
//
// Example:
// Input:  1 -> 2 -> 3 -> 4 -> 5 -> NULL
// Output: 5 -> 4 -> 3 -> 2 -> 1 -> NULL
//
// ============================================================================
// ✅ Approach Used: Iterative Linked List Reversal
// ============================================================================
//
// - We will use three pointers: prev, curr, and next.
// - prev → tracks the already reversed part
// - curr → tracks the current node we are processing
// - next → temporarily stores curr->next so we don't lose the remaining list
//
// ============================================================================
// ⏱️ Time Complexity: O(n)
//    - We visit each node exactly once and reverse its pointer.
// 💾 Space Complexity: O(1)
//    - We only use a constant number of extra pointers (prev, curr, next).
//
// ✅ Optimality: This is the most optimal approach for linked list reversal.
// - No extra space needed
// - Only single pass required
//
// ✅ Will it be accepted by LeetCode? 
// Yes. It’s efficient, no TLE (Time Limit Exceeded), no MLE (Memory Limit Exceeded).
//
// ============================================================================

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list (provided by LeetCode).
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// ============================================================================
// Solution Class
// ============================================================================
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // Step 1: Initialize three pointers
        ListNode *prev = NULL;   // initially reversed part is empty
        ListNode *curr = head;   // start with the head of list
        ListNode *next = NULL;   // will be used to store next node

        // Step 2: Traverse the list until curr becomes NULL
        while(curr != NULL) {
            // Save the next node before breaking the link
            next = curr->next;

            // Reverse the current node's pointer
            curr->next = prev;

            // Move prev and curr one step forward
            prev = curr;
            curr = next;
        }

        // Step 3: prev will be the new head of the reversed list
        return prev;
    }
};

// ============================================================================
// Explanation of Logic (Detailed)
// ============================================================================
//
// 1. We need to reverse the "arrows" of the linked list.
//    For example: head: 1 -> 2 -> 3 -> NULL
//    After reversal: 3 -> 2 -> 1 -> NULL
//
// 2. Why three pointers?
//    - curr : points to the node we are currently reversing.
//    - prev : keeps track of the already reversed portion.
//    - next : temporarily stores curr->next so we don't lose the rest of the list.
//
// 3. Step-by-step for input [1,2,3]:
//
// Initial state:
// prev = NULL, curr = head(1)
//
// Iteration 1:
// next = curr->next (2)
// curr->next = prev (1->NULL)
// prev = curr (prev=1)
// curr = next (curr=2)
//
// Iteration 2:
// next = 3
// curr->next = prev (2->1)
// prev = 2
// curr = 3
//
// Iteration 3:
// next = NULL
// curr->next = prev (3->2)
// prev = 3
// curr = NULL (end loop)
//
// Now prev points to new head = 3.
//
// ============================================================================
// Key Insights:
// - If you swap the order of assignments (e.g., move curr=next before changing curr->next),
//   you will LOSE the link and list will break.
// - Order must always be:
//   1. Save next
//   2. Reverse pointer
//   3. Advance prev and curr
//
// ============================================================================
// Working Example in main()
// ============================================================================

int main() {
    // Build linked list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "Original List: ";
    ListNode* temp = head;
    while(temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    // Apply reversal
    Solution sol;
    ListNode* newHead = sol.reverseList(head);

    cout << "Reversed List: ";
    temp = newHead;
    while(temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    return 0;
}

/*
===============================================================================
✔ OUTPUT:
Original List: 1 2 3 4 5 
Reversed List: 5 4 3 2 1 

===============================================================================
*/
