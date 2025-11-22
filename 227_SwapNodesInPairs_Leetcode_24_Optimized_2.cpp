/*
Problem Summary:
----------------
Given a singly-linked list, swap every two adjacent nodes and return its head.
You may not modify the values in the list's nodes; only nodes themselves may be changed.

Example:
Input:  1->2->3->4
Output: 2->1->4->3

Solution Name/Method:
---------------------
Iterative approach using pointer manipulation (O(1) space)

Time Complexity: O(n) 
- We traverse the list once, swapping pairs.

Space Complexity: O(1)
- No recursion or extra data structures used.

Optimality:
------------
- This is optimal in terms of space (iterative) and acceptable in time.
- Recursive solutions are more elegant but use O(n) stack space.
- Will be accepted by LeetCode; will not cause MLE or TLE.

Key Idea:
---------
- Use 4 pointers:
  1. prev   : points to the node before the current pair
  2. first  : first node of the current pair
  3. sec    : second node of the current pair
  4. third  : node after the current pair (next pair start)
- Swap first and sec, update pointers to continue the loop.
- Update head if swapping the first pair.

*/

#include <iostream>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {

        // Base case: empty list or single node -> nothing to swap
        if(head == NULL || head->next == NULL) return head;

        // Initialize pointers
        ListNode* prev = NULL;   // Will track node before current pair
        ListNode* first = head;  // First node of current pair
        ListNode* sec = head->next; // Second node of current pair

        // Loop through list as long as we have a pair to swap
        while(first != NULL && sec != NULL) {

            ListNode* third = sec->next; // Node after the current pair

            // Swap the current pair
            sec->next = first;
            first->next = third;

            // Connect previous pair to current swapped pair
            if(prev != NULL) {
                prev->next = sec;
            } else {
                // If this is the first pair, update head
                head = sec;
            }

            // Move prev to end of current swapped pair
            prev = first;

            // Move to the next pair
            first = third;
            if(third != NULL) {
                sec = third->next;
            }
        }

        // Return new head after all swaps
        return head;
    }
};

/*
Function Working & Step-by-Step Explanation:
-------------------------------------------
1. Base case check: If list is empty or only one node, no swaps needed.
2. Initialize:
   - prev = NULL (no node before first pair)
   - first = head
   - sec = head->next
3. Loop condition: first != NULL && sec != NULL ensures a valid pair exists.
4. Inside loop:
   - Store third = sec->next (next pair starting node)
   - Swap first and sec:
       sec->next = first
       first->next = third
   - Connect previous pair to this swapped pair:
       - If prev exists, prev->next = sec
       - Else, head = sec (first swap changes head)
   - Move prev to end of current pair: prev = first
   - Move first to start of next pair: first = third
   - Update sec to next node if exists: sec = third->next
5. Repeat until all pairs are swapped.
6. Return head.

Pointer Journey:
----------------
- first  : travels node-by-node as the first of current pair
- sec    : always first->next, second node of current pair
- third  : keeps reference to node after pair to continue loop
- prev   : connects last swapped pair to current pair, ensuring continuity

Edge Cases:
-----------
- Empty list -> returns NULL
- Single node -> returns same node
- Odd number of nodes -> last node remains unswapped
- Even number of nodes -> all nodes swapped

Working Example in Main:
------------------------
Input: 1->2->3->4->5
Output: 2->1->4->3->5

*/

int main() {
    // Create list: 1->2->3->4->5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution sol;
    ListNode* newHead = sol.swapPairs(head);

    // Print swapped list
    cout << "Swapped List: ";
    while(newHead != nullptr) {
        cout << newHead->val;
        if(newHead->next != nullptr) cout << "->";
        newHead = newHead->next;
    }
    cout << endl;

    return 0;
}

/*
Expected Output:
----------------
Swapped List: 2->1->4->3->5

Key Takeaways / Insights:
-------------------------
1. Iterative solution avoids recursion, O(1) space.
2. Always track 4 pointers to manage swapping and connections:
   prev, first, sec, third.
3. Loop carefully: only continue if a valid pair exists.
4. Always update head for the first swap.
5. Edge handling: last node remains untouched if odd number of nodes.
6. This method is safe for large lists; avoids stack overflow.
7. This is the most practical way for production-level code.
*/

