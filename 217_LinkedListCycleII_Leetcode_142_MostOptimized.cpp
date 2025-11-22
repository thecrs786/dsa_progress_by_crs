#include <bits/stdc++.h>
using namespace std;

/*
  LEETCODE - 142 -  LINKED LIST II
================================================================================
🚩 Problem Summary:
Given the head of a linked list, detect if the list has a cycle. 
If a cycle exists:
  1. Find the starting node of the cycle. (ONLY LEETCODE PART)
  2. Break the cycle by setting the "last node of cycle's next" to NULL. 
  3. Return the starting node of the cycle.
If no cycle exists, return NULL.

================================================================================
📌 Method: Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
- Step 1: Detect cycle using two pointers (slow moves 1 step, fast moves 2 steps).
- Step 2: If cycle exists, find the starting node of cycle. (LEETCODE PART)
- Step 3: Traverse cycle once to find last node and break the cycle. (NOT LEETCODE PART)

================================================================================
⏱️ Time Complexity:
- O(N), where N = number of nodes in the list.
  (Cycle detection = O(N), finding start of cycle = O(N), breaking cycle = O(N)).
- Still linear.

💾 Space Complexity:
- O(1) (constant extra space, no extra DS used).

✅ LeetCode Acceptance:
- This is the most optimal cycle detection/removal method.
- It won’t cause TLE (linear time).
- It won’t cause MLE (constant space).
- Fully acceptable.

================================================================================
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // ============================================================
        // Step 1: Detect cycle using Floyd's Tortoise & Hare algorithm
        // ------------------------------------------------------------
        // If no cycle: fast will reach NULL or fast->next == NULL.
        // If cycle exists: slow and fast will eventually meet inside cycle.
        // WHY will they meet?
        //   - Relative speed = 1 step per iteration (fast - slow).
        //   - They are bound to meet in circular track (like runners in race).
        // ============================================================
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;         // move 1 step
            fast = fast->next->next;   // move 2 steps
            if (slow == fast) break;   // cycle detected
        }

        if (fast == NULL || fast->next == NULL) 
            return NULL;  // no cycle present

        // ============================================================
        // Step 2: Find start of the cycle
        // ------------------------------------------------------------
        // Once slow and fast meet inside the cycle:
        //   - Place slow back at head.
        //   - Move slow and fast both 1 step each time.
        //   - They will meet at the cycle start node.
        // WHY?
        //   - Math proof: distance from head to start = distance from meeting point to start.
        //   - So both pointers synchronized will meet at cycle start.
        // ============================================================
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next; // notice here we move both by 1 step only
        }

        // At this point, slow == fast == start of cycle

        // ============================================================
        // Step 3: Break the cycle
        // ------------------------------------------------------------
        // Traverse the cycle starting from "slow" until we find the node
        // whose next = slow (that means it’s the last node in the cycle).
        // Then set its next = NULL to break the cycle.
        // ============================================================
        ListNode* ptr = slow;
        while (ptr->next != slow) {
            ptr = ptr->next;
        }
        ptr->next = NULL;  // break the cycle

        return slow; // returning start of cycle (before breaking, it was the cycle start)
    }
};

/*
================================================================================
🔑 Key Insights:
1. Two pointer speeds (1 and 2) guarantee meeting if cycle exists (relative velocity idea).
2. Why we reset slow to head and then move both by 1 step?
   - Because the distance from head to start of cycle == distance from meeting point to start.
   - Mathematical proof ensures they will meet at start.
3. Why second traversal for breaking cycle?
   - We must find the last node of cycle (node whose next points to cycle start).
   - Only then we can set last->next = NULL to break.
4. Importance of "fast != NULL && fast->next != NULL" check:
   - Prevents segmentation fault (fast may jump off end in acyclic list).
5. Entire process is linear time, constant space → optimal.

================================================================================
⚙️ Example Walkthrough:
List: 1 → 2 → 3 → 4 → 5
                 ↑     ↓
                 8 ←  6 ← 7
Cycle starts at node 3.

Step 1: slow=1, fast=1
   slow=2, fast=3
   slow=3, fast=5
   slow=4, fast=7
   slow=5, fast=3
   slow=6, fast=5
   slow=7, fast=7 (meeting point found inside cycle)

Step 2: Reset slow=head (1), keep fast=7.
   slow=1, fast=7 → not equal
   slow=2, fast=8 → not equal
   slow=3, fast=3 → equal (start of cycle found!)

Step 3: Traverse cycle to find last node (8).
   Set 8->next = NULL.

Final list becomes: 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → NULL
Cycle removed successfully.

================================================================================
*/

int main() {
    // Example demonstration
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next->next = new ListNode(8);

    // Creating a cycle: node 8 points back to node 3
    head->next->next->next->next->next->next->next->next = head->next->next;

    Solution sol;
    ListNode* cycleStart = sol.detectCycle(head);

    if (cycleStart != NULL)
        cout << "Cycle started at node with value: " << cycleStart->val << endl;
    else
        cout << "No cycle detected" << endl;

    // Print final list after breaking cycle
    cout << "Final Linked List after cycle removal: ";
    ListNode* temp = head;
    while (temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    return 0;
}
