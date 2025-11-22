// LeetCode Problem 19: Remove Nth Node From End of List
// Problem Summary:
// Given the head of a linked list, remove the n-th node from the end of the list and return its head.
// The list is singly-linked, and you must handle cases where the node to remove is the head or in the middle.
//
// Example:
// Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
// Explanation: The 2nd node from the end is 4, which is removed.
//
// Edge Case Example:
// Input: head = [1], n = 1
// Output: []
// Explanation: Removing the only node results in an empty list.

// Time Complexity: O(n), where n is the number of nodes in the list.
// Space Complexity: O(1), as no extra data structures are used.
// Approach Used: Two-pass traversal approach.
// - First pass: Count the total number of nodes (size).
// - Second pass: Find the node just before the target node and adjust links.
// Is it the most optimal? ❌ No, it traverses the list twice.
// Will it be accepted by LeetCode? ✅ Yes, it handles all cases efficiently without MLE or TLE.

#include <iostream>
using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int size = 0; // Initialize the size of the list

        // First pass: Traverse the list to calculate its size
        ListNode* temp = head;
        while(temp != nullptr) {
            size++;
            temp = temp->next;
        }

        temp = head; // Reset temp to head for second traversal

        // Edge case: Removing the head node itself
        if(n == size) {
            head = head->next;
            delete temp; // Free memory of the removed node
            return head;
        } else {
            // Find the node just before the node to be removed
            int count = 0;
            while(count < size - n - 1) {
                count++;
                temp = temp->next;
            }

            ListNode* prev = temp;      // Node before the one to remove
            temp = temp->next;          // Node to remove
            ListNode* next = temp->next; // Node after the one to remove

            prev->next = next; // Bypass the node to remove
            delete temp;       // Free memory of the removed node
        }

        return head; // Return the modified list
    }
};

// Utility function to print the list
void printList(ListNode* head) {
    while(head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;

    // Example 1
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "Original List: ";
    printList(head);

    head = sol.removeNthFromEnd(head, 2);

    cout << "Modified List after removing 2nd node from end: ";
    printList(head);

    // Example 2 (edge case: single node)
    ListNode* head2 = new ListNode(1);
    cout << "Original List: ";
    printList(head2);

    head2 = sol.removeNthFromEnd(head2, 1);

    cout << "Modified List after removing 1st node from end: ";
    printList(head2);

    return 0;
}

/*
Logic Explanation and Working of the Function:

1. Edge Case Handling:
   - If n equals the size of the list, we are removing the head node.
   - We directly update the head pointer to head->next and delete the original head.

2. How size works:
   - First pass traverses the list to count all nodes.
   - The size helps us determine how far we need to traverse to reach the node before the one to remove.

3. Traversing to find prev node:
   - We traverse until count reaches size - n - 1.
   - At this point, temp points to the node before the target node.

4. Working with prev, temp, and next:
   - prev is the node before the one to remove.
   - temp is the node to remove.
   - next is the node after the one to remove.
   - We adjust prev->next to point to next, thereby removing temp from the chain.
   - We then delete temp to free memory.

5. Why two passes:
   - The first pass gets the total size.
   - The second pass finds the exact position of the node to delete without storing extra information.

6. Traversal bounds:
   - The loop stops at size - n - 1 to reach the node just before the target node.

Important Details and Key Insights:
✔ Using size allows us to know exactly where the node is without extra space.
✔ Edge cases like removing the head are handled separately to avoid null-pointer errors.
✔ Memory management is handled by deleting the removed node.
✔ This approach is efficient and accepted but not as elegant as the one-pass two-pointer method.
✔ The method scales well for large lists as it's linear in time and constant in space.
✔ Understanding prev, temp, and next pointers is critical for linked list manipulation.

This is a fully optimized version in terms of using minimal space,
but since it requires two passes, it's not the most optimal approach.
In interviews, mentioning the one-pass two-pointer method shows deeper mastery.
*/
