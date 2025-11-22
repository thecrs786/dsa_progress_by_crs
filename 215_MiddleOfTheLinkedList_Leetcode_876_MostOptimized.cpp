// ===============================
// LeetCode 876: Middle of the Linked List
// ===============================
//
// 📝 Question in brief:
// Given the head of a singly linked list, return the middle node.
// If there are two middle nodes, return the second middle node.
//
// Example:
// Input: 1 -> 2 -> 3 -> 4 -> 5
// Output: Node with value 3
//
// Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6
// Output: Node with value 4 (second middle)
//
// ===============================
// ✅ Solution Name / Method:
// Slow and Fast Pointer Approach (a.k.a Tortoise and Hare)
//
// ✅ Time Complexity: O(n)  [We traverse the list only once]
// ✅ Space Complexity: O(1) [No extra space, just two pointers]
// ✅ Optimality: This is the most optimal solution available.
// ✅ Will it be accepted? Yes, 100% accepted. No MLE (Memory Limit Exceeded), 
//    No TLE (Time Limit Exceeded).
// ===============================

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // Initialize two pointers, both starting at head
        ListNode* slow = head;
        ListNode* fast = head;

        // Move fast by 2 steps and slow by 1 step
        // until fast reaches the end of the list
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;           // slow moves one step
            fast = fast->next->next;     // fast moves two steps
        }

        // When loop ends:
        // - If list length is odd, slow is at the middle node.
        // - If list length is even, slow is at the SECOND middle node (as required).
        return slow;
    }
};

// ===============================
// 🔎 Detailed Explanation of Steps
// ===============================
//
// 1. We use two pointers:
//    - slow: moves one step at a time
//    - fast: moves two steps at a time
//
// 2. Why two pointers?
//    Because when fast reaches the end, slow will have reached the middle naturally.
//
// 3. The while condition (fast != NULL && fast->next != NULL) ensures:
//    - We don’t go out of bounds
//    - Loop runs only while fast has 2 steps to take
//
// 4. When loop breaks, slow is at the middle node.
//    This satisfies both odd and even length cases.
//
// ===============================
// 🔑 Important Details & Key Insights
// ===============================
// - If the list is empty (head = NULL), function safely returns NULL.
// - If there is only 1 node: fast and slow start at head, 
//   while loop never runs, so we return head itself (correct).
// - If there are 2 nodes: loop runs once, slow moves to 2nd node, fast reaches NULL,
//   so function returns the 2nd node (LeetCode requires the second middle).
// - This pattern of "fast moves 2, slow moves 1" is not just for this problem.
//   It is a **classic linked list technique** used in many problems:
//     → Detecting cycles (Floyd’s Cycle Detection)
//     → Finding cycle start
//     → Splitting linked list into halves
//   So mastering this approach is very important for future linked list problems.
//
// ===============================
// 💡 Dry Run Examples
// ===============================
//
// Case 1: [1]
// slow = 1, fast = 1
// Loop doesn't run (fast->next is NULL).
// Return slow = 1 ✅
//
// Case 2: [1 -> 2]
// slow = 1, fast = 1
// Loop runs once: slow = 2, fast = NULL
// Return slow = 2 ✅ (second middle)
//
// Case 3: [1 -> 2 -> 3 -> 4 -> 5]
// slow moves: 1 → 2 → 3
// fast moves: 1 → 3 → 5
// Return slow = 3 ✅
//
// Case 4: [1 -> 2 -> 3 -> 4 -> 5 -> 6]
// slow moves: 1 → 2 → 3 → 4
// fast moves: 1 → 3 → 5 → NULL
// Return slow = 4 ✅ (second middle)
//
// ===============================
// 🚀 Working Example with main()
// ===============================

int main() {
    // Create linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);

    Solution sol;
    ListNode* mid = sol.middleNode(head);

    cout << "Middle node value: " << mid->val << endl;

    // Expected Output: 4
    // Because for even length, we return the SECOND middle.
    return 0;
}

//
// ===============================
// END OF NOTES
// ===============================
//
