#include <iostream>
using namespace std;

/*
====================================================================================
📌 LeetCode 203 — Remove Linked List Elements
====================================================================================

📝 Problem (Brief):
-------------------
Given the head of a singly linked list and an integer `val`, remove all nodes 
that have `Node.val == val`, and return the new head of the list.

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
Recursive Approach:
- Recursively remove all nodes with value `val` from the rest of the list (`head->next`).
- After recursion, decide if the current `head` node should be kept or skipped.
- If `head->val == val` → skip it by returning `head->next`.
- Else → return `head`.

====================================================================================
⏱ Time Complexity: O(N)
   - Each node is visited exactly once.

📌 Space Complexity: O(N)
   - Recursion stack stores at most N calls (N = number of nodes).

✔ Optimality:
- Recursive approach is simple and readable.
- For very long lists, iterative approach is preferred to avoid stack overflow.
- Will be accepted on LeetCode; no TLE/MLE for typical constraints.

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
        // Base Case: if list is empty, return nullptr
        if (!head) return nullptr;

        // Step 1: Recursively remove 'val' from the rest of the list
        head->next = removeElements(head->next, val);

        // Step 2: Decide whether to keep current node
        if (head->val == val) {
            // Skip current node
            return head->next;
        } else {
            // Keep current node
            return head;
        }
    }
};

/*
====================================================================================
📌 LOGIC / FUNCTION WORKING:
------------------------------------------------------------------------------------
1. We process the **tail first**: recursively call removeElements on head->next.
2. Once the rest of the list is cleaned, we check the current node:
   - If it contains the target value, skip it.
   - Otherwise, link it to the cleaned rest of the list.
3. This ensures that all occurrences of 'val' are removed, including the head node.

🔹 Dry Run Example:
Input: [1,2,6,3,4,5,6], val = 6

Step-by-step recursion:
- removeElements([1,2,6,3,4,5,6], 6)
  -> head = 1, recurse on [2,6,3,4,5,6]
- head = 2, recurse on [6,3,4,5,6]
- head = 6, recurse on [3,4,5,6]
- head = 3, recurse on [4,5,6]
- head = 4, recurse on [5,6]
- head = 5, recurse on [6]
- head = 6, recurse on [] -> returns nullptr
Backtracking:
- head = 5, val != 6 -> keep, next = nullptr
- head = 4 -> next = 5
- head = 3 -> next = 4
- head = 6 -> skip -> next = 3
- head = 2 -> next = 3
- head = 1 -> next = 2
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
1. Base Case: always check if head is nullptr.
2. Recursive approach is clean and handles head node removal seamlessly.
3. Be cautious with very long lists; recursion depth may reach N.
4. Iterative approach avoids recursion stack overflow and is O(1) space.

====================================================================================
🔹 SIMILAR QUESTIONS & APPROACHES:
------------------------------------------------------------------------------------
1. LeetCode 203 (this problem) — remove all occurrences of a value.
2. LeetCode 19 — Remove N-th node from end of list.
3. LeetCode 82 — Remove duplicates from sorted list (keep unique).
4. Approach variants: recursion vs iteration, using dummy nodes to simplify head removal.
====================================================================================
*/
