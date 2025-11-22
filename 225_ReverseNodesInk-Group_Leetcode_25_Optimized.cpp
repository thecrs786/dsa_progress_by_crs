/*
LeetCode Problem: 25. Reverse Nodes in k-Group

Problem in brief:
Given a linked list, reverse the nodes of the list k at a time and return its modified list.
- k is a positive integer and is less than or equal to the length of the linked list.
- If the number of nodes is not a multiple of k then left-out nodes in the end should remain as-is.
- You may not alter the values in the nodes, only nodes themselves may be changed.

Example Test Cases:

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
Explanation:
- First k-group: [1,2] -> reversed to [2,1]
- Second k-group: [3,4] -> reversed to [4,3]
- Remaining node [5] has less than k nodes, remains as-is

Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
Explanation:
- First k-group: [1,2,3] -> reversed to [3,2,1]
- Remaining nodes [4,5] have less than k nodes, remain as-is

Example 3:
Input: head = [1,2,3,4,5,6,7,8], k = 4
Output: [4,3,2,1,8,7,6,5]
Explanation:
- First k-group: [1,2,3,4] -> reversed to [4,3,2,1]
- Second k-group: [5,6,7,8] -> reversed to [8,7,6,5]
- All nodes processed, no leftover

Example 4:
Input: head = [1,2], k = 3
Output: [1,2]
Explanation:
- Less than k nodes in list, nothing reversed

Key Takeaways:
- Only reverse exact k nodes
- If remaining nodes < k, leave as-is
- Recursive calls automatically handle connecting segments

Solution provided: Recursive reversal of k nodes at a time

Method/Approach: 
- Recursion + standard linked list reversal of k nodes

Time Complexity: O(n)  // Each node visited exactly once
Space Complexity: O(n/k) recursion stack space
Optimality: Not the most optimal (iterative O(1) space version exists)
Accepted by LeetCode: Yes, will not cause TLE, but recursive stack is extra memory
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
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

        if(!head) return head; 
        // Step 1: Check if there are at least k nodes to reverse
        ListNode* temp = head;
        for(int count = 0; count < k; count++) {
            if(temp == NULL) return head; 
            // If fewer than k nodes, return head as-is. 
            // These nodes remain unreversed.
            temp = temp->next;
        }

        // Step 2: Reverse first k nodes
        ListNode* prev = NULL;   // Previous pointer, used to reverse links
        ListNode* curr = head;   // Current node pointer, start of segment
        ListNode* next = NULL;   // Temporary pointer to store next node

        while(curr != temp) {    // Reverse exactly k nodes
            next = curr->next;   // Store next node before breaking link
            curr->next = prev;   // Reverse current node's pointer
            prev = curr;         // Move prev forward (new head of reversed segment)
            curr = next;         // Move curr forward
        }

        // Step 3: Connect reversed segment with rest of the list
        // Recursive call to reverse the next segment starting from 'temp'
        head->next = reverseKGroup(temp, k); 
        // Explanation:
        // After reversal, original head becomes tail of this segment.
        // Its next should point to the head of the next reversed segment.

        // Step 4: Return new head of this segment
        return prev;
        // prev is the new head of the reversed k-group
    }
};

/*
Logic and Explanation:

1. Use 'temp' to check if there are enough nodes to reverse.
   - If nodes < k, we skip reversal for this part of the list.

2. Reverse exactly k nodes using the standard linked list reversal technique:
   - Maintain three pointers: prev, curr, next
   - Loop until curr reaches temp
   - Reverse the link of each node to point to prev

3. Recursive call:
   - head->next = reverseKGroup(temp, k)
   - Connect the current reversed segment to the next segment.
   - Recursion ensures we process all remaining nodes in k-groups.

4. Return prev:
   - prev becomes the new head after reversing this segment

Key Insights:
- head becomes tail after reversal
- temp acts as a boundary marker for reversal
- Recursion ensures segments are connected correctly
- Works correctly for any number of nodes, including less than k at the end
- Safe for normal constraints but not memory-optimal for huge lists

*/

int main() {
    // Creating a sample linked list: 1->2->3->4->5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 2;

    Solution sol;
    ListNode* newHead = sol.reverseKGroup(head, k);

    // Printing the reversed list in k-groups
    cout << "Reversed list in groups of " << k << ": ";
    ListNode* temp = newHead;
    while(temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    return 0;
}

/*
Expected Output for k=2:
Reversed list in groups of 2: 2 1 4 3 5

Explanation:
- First k-group: 1,2 -> reversed to 2,1
- Second k-group: 3,4 -> reversed to 4,3
- Remaining node 5 < k, stays as-is
- Recursive calls handle connecting the reversed segments
*/
