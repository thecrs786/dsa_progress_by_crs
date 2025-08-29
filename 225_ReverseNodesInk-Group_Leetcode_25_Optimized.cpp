#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 25: Reverse Nodes in k-Group

Problem Brief:
- Given a singly linked list, reverse the nodes of the list k at a time and return the modified list.
- If the number of nodes is not a multiple of k, the remaining nodes should stay as-is.
- Must change node connections, cannot just swap values.

Solution Name / Method:
- Recursive reversal of k-sized segments in a linked list.
- Track the first k nodes, reverse them, recursively process the rest, and connect.

Time Complexity:
- O(n), each node is visited exactly once.

Space Complexity:
- O(n/k) due to recursion stack; can be optimized to O(1) with iterative solution.

Optimality:
- Optimized for readability and correctness.
- Iterative solution can avoid recursion stack for extremely large lists, but asymptotic complexity is same.
- Will be accepted by LeetCode, no TLE/MLE under normal constraints.

Key Points:
1. `prev`, `curr`, `next` are used to reverse k nodes.
2. `head` becomes tail after reversal, used to connect to the next segment.
3. Base case: fewer than k nodes left → return head as-is.
4. Recursive call ensures remaining nodes are processed similarly.
5. Works correctly for all edge cases including empty list, k=1, and list length not multiple of k.
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {

        if(!head) return head; // Base case: empty list

        // Step 1: Check if there are at least k nodes to reverse
        ListNode* curr = head;
        for(int i = 0; i < k; i++) {
            if(curr == NULL) return head; // Less than k nodes, return as-is
            curr = curr->next;
        }

        // Step 2: Reverse first k nodes
        ListNode* prev = NULL;       // Previous pointer for reversal
        ListNode* temp = head;       // Current pointer, start of segment
        ListNode* next = NULL;       // Temporary pointer to store next node

        while(temp != curr) {        // Reverse exactly k nodes
            next = temp->next;       // Store next node
            temp->next = prev;       // Reverse link
            prev = temp;             // Move prev forward
            temp = next;             // Move temp forward
        }

        // Step 3: Connect reversed segment with the rest of the list
        head->next = reverseKGroup(curr, k); // head is now tail after reversal

        // Step 4: Return new head of this segment
        return prev;
    }
};

/*
Function Logic Explanation:

1. Check if there are at least k nodes left; otherwise, return head.
2. Reverse exactly k nodes using standard linked list reversal logic:
    - prev tracks previous node
    - temp tracks current node
    - next stores next node temporarily
3. After reversal:
    - prev points to new head of reversed segment
    - original head becomes tail of reversed segment
4. Recursively call reverseKGroup on the remaining nodes (curr) and connect to tail.
5. Return prev as new head of the segment.
6. This process continues recursively until the list is fully processed.

Edge Cases Handled:
- Empty list → returns NULL
- k = 1 → list remains unchanged
- List length < k → last segment remains unchanged
- List length multiple of k → all nodes reversed properly
*/

void printList(ListNode* head) {
    while(head) {
        cout << head->val;
        if(head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Working Example
    // Input: 1 -> 2 -> 3 -> 4 -> 5, k = 2
    // Output: 2 -> 1 -> 4 -> 3 -> 5
    ListNode* n5 = new ListNode(5);
    ListNode* n4 = new ListNode(4, n5);
    ListNode* n3 = new ListNode(3, n4);
    ListNode* n2 = new ListNode(2, n3);
    ListNode* n1 = new ListNode(1, n2);

    cout << "Original List: ";
    printList(n1);

    Solution sol;
    int k = 2;
    ListNode* newHead = sol.reverseKGroup(n1, k);

    cout << "After reversing in k-groups (k=" << k << "): ";
    printList(newHead);

    return 0;
}
