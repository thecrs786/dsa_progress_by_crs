#include <iostream>
using namespace std;

/*
====================================================================================
📌 LeetCode 203 — Remove Linked List Elements
====================================================================================

📝 Problem (Brief):
-------------------
Given the head of a singly linked list and an integer `val`, remove all nodes 
that have `Node.val == val` and return the new head of the list.

🔹 Examples:

Example 1:
Input: head = [1,2,6,3,4,5,6], val = 6
Output: [1,2,3,4,5]

Example 2:
Input: head = [], val = 1
Output: []

Example 3:
Input: head = [7,7,7,7], val = 7
Output: []

====================================================================================
💡 Approach / Method:
---------------------
Iterative Approach using a Dummy Node:
- Create a dummy node pointing to head to handle head removal easily.
- Use two pointers: `prev` (tracks last node kept) and `curr` (current node).
- Traverse the list:
    - If `curr->val == val`, remove node by `prev->next = curr->next`.
    - Else, move `prev` to `curr`.
- Move `curr` to next node each iteration.
- Return `dummy->next` as the new head.

====================================================================================
⏱ Time Complexity: O(N)
   - Each node is visited exactly once.

📌 Space Complexity: O(1)
   - Iterative solution, constant extra memory.

✔ Optimality:
- This is the most optimal iterative solution for this problem.
- Will be accepted on LeetCode; no risk of TLE or MLE for normal constraints.
- Preferred over recursion for very long lists to avoid stack overflow.

====================================================================================
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // Step 1: Create a dummy node before head
        // This ensures removal of head node is handled seamlessly
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        // Step 2: Initialize pointers
        ListNode* prev = dummy;  // Last node kept in the list
        ListNode* curr = head;   // Current node to examine

        // Step 3: Traverse the list
        while(curr != nullptr) {
            if(curr->val == val) {
                // Remove current node by skipping it
                prev->next = curr->next;
            } else {
                // Keep current node, move prev forward
                prev = curr;
            }
            // Move to next node in the list
            curr = curr->next;
        }

        // Step 4: Return the new head (may be different from original head)
        return dummy->next;
    }
};

/*
====================================================================================
📌 LOGIC / FUNCTION WORKING:
------------------------------------------------------------------------------------
1. **Dummy Node**:
   - Handles the special case when the head node itself has the target value.
   - Avoids separate if-statement for head removal.

2. **Pointers**:
   - `prev` tracks the last node that should remain in the list.
   - `curr` scans each node to check its value.

3. **Removal Logic**:
   - If `curr->val == val`, link `prev->next` to `curr->next` → node is skipped.
   - Else, move `prev` to `curr` → node is kept.

4. **Traversal**:
   - `curr` always moves to next node.
   - Iterative, so space is O(1).

5. **Return**:
   - `dummy->next` is the new head after removals.
   - Handles empty lists and full removals correctly.

🔹 Dry Run Example:
Input: [1,2,6,3,4,5,6], val = 6
- dummy->0->1->2->6->3->4->5->6
- curr=1 → keep → prev=1
- curr=2 → keep → prev=2
- curr=6 → remove → prev->next=3
- curr=3 → keep → prev=3
- curr=4 → keep → prev=4
- curr=5 → keep → prev=5
- curr=6 → remove → prev->next=null
Output: [1,2,3,4,5]
====================================================================================
*/

int main() {
    // Construct example list: [1,2,6,3,4,5,6]
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(6);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next->next = new ListNode(6);

    int val = 6;

    Solution sol;
    ListNode* newHead = sol.removeElements(head, val);

    // Print output
    cout << "Updated List: ";
    ListNode* curr = newHead;
    while (curr) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    return 0;
}

/*
====================================================================================
📌 IMPORTANT DETAILS, WARNINGS, AND KEY INSIGHTS:
------------------------------------------------------------------------------------
1. Dummy node simplifies head removal and avoids extra conditional checks.
2. Always update prev->next when skipping nodes.
3. Iterative method is preferred over recursion for very long lists (O(1) space).
4. Handles all edge cases: empty list, all nodes removed, head removed.

====================================================================================
🔹 SIMILAR QUESTIONS & APPROACHES:
------------------------------------------------------------------------------------
1. LeetCode 19 — Remove N-th node from end of list.
2. LeetCode 82 — Remove duplicates from sorted list.
3. LeetCode 203 — Recursive version (O(N) space, stack recursion).
4. Approach variants: recursion vs iteration, using dummy nodes to simplify operations.
====================================================================================
*/
