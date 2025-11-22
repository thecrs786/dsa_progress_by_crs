#include <bits/stdc++.h>
using namespace std;

/*
// LeetCode 430: Flatten a Multilevel Doubly Linked List
//
// Problem Brief:
// Given a multilevel doubly linked list where each node has a next, prev, and optional child pointer,
// flatten it into a single-level doubly linked list. Child lists may have their own children.
//
// Approach / Solution:
// We use a recursive approach. At each node:
// 1. If it has no child, move forward to next node.
// 2. If it has a child, flatten that child list recursively.
// 3. Connect the flattened child list to current node.
// 4. Traverse to the tail of the child list and reconnect to the saved next pointer.
// 5. Continue until the end of the current level.
// This preserves doubly linked structure (prev pointers) and recursively handles multiple levels.
//
// Method Name: Recursive flattening
//
// Time Complexity: O(n)
//  - Each node is visited exactly once.
// Space Complexity: O(d) where d is the maximum depth of recursion (due to call stack).
// Optimal?: Functionally optimal for this problem. Tail-finding loop is linear per child, but avoids extra data structures.
// Will it be accepted?: Yes, no TLE or MLE expected.
//
// Key insights:
// - Use of prev: child head prev must point back to parent node.
// - Use of next: store the original next before splicing child, then reconnect tail.
// - Base case: if head is NULL, return immediately to avoid dereferencing.
// - Tail tracking: after flattening child, move curr to child’s tail to reconnect properly.
// - Each curr is always tracked; after child handling, curr points to last flattened node of that branch.
//
*/

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
public:
    Node* flatten(Node* head) {
        // Base case: empty list
        if(!head) return head;

        Node* curr = head; // Start traversing from head

        while(curr != NULL) {
            if(curr->child != NULL) {
                Node* next = curr->next;          // Save original next node
                curr->next = flatten(curr->child); // Flatten child list recursively
                curr->next->prev = curr;          // Maintain doubly linked prev
                curr->child = NULL;               // Remove child pointer after flattening

                // Move curr to the tail of the flattened child
                while(curr->next != NULL) {
                    curr = curr->next;
                }

                // Reconnect saved next node after child
                curr->next = next;
                if(next) next->prev = curr;
            }
            else {
                curr = curr->next; // No child, just move to next node
            }
        }

        return head; // Return the head of flattened list
    }
};

/*
Logic Walkthrough:

- curr starts at head.
- Loop through each node:
    - If curr has no child: simply move to next node.
    - If curr has a child:
        1. Save curr->next to reconnect later.
        2. Flatten child recursively and attach it after curr.
        3. Set child->prev = curr to maintain doubly linkage.
        4. Set curr->child = NULL because it's now flattened.
        5. Move curr to the tail of the flattened child list.
        6. Reconnect saved next node after the tail.
- Continue until curr reaches NULL.
- Return head, which is now the flattened list.

Base Cases:

- Empty list (head == NULL): return NULL.
- Single node without child: loop moves curr to NULL, return head.
- Single node with child: recursion flattens child, reconnects next, returns head.

Tracking Pointers:

- curr: current node in traversal.
- next: original next node before flattening child.
- prev: maintains doubly linked structure.
- child: used to attach flattened child list, then set to NULL.

Key Details:

- Always flatten child before moving forward.
- Always reconnect tail to saved next.
- Always maintain prev pointers.
- Avoid dereferencing NULL by checking head at start.
- Handles multiple nested children correctly.

*/

// Working Example
int main() {
    // Create nodes manually for testing
    Node* n1 = new Node(); n1->val = 1;
    Node* n2 = new Node(); n2->val = 2;
    Node* n3 = new Node(); n3->val = 3;
    Node* n7 = new Node(); n7->val = 7;
    Node* n8 = new Node(); n8->val = 8;

    // Setup next pointers
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;

    // Setup child pointers
    n2->child = n7;
    n7->next = n8; n8->prev = n7;

    Solution sol;
    Node* flatHead = sol.flatten(n1);

    // Print flattened list
    cout << "Flattened list: ";
    Node* curr = flatHead;
    while(curr != NULL) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    return 0;
}

/*
Expected Output:

Flattened list: 1 2 7 8 3

Explanation:

- Start at 1 → no child, move to 2.
- 2 has child 7 → flatten 7-8 list → attach after 2.
- Move curr to tail of child (8) → reconnect next (3).
- Final flattened order: 1-2-7-8-3
- prev pointers maintained correctly.
*/

