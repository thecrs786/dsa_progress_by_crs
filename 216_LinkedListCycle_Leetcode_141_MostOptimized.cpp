// ============================================================
// 🔹 LeetCode 141 - Linked List Cycle
// ============================================================
// ❓ Question in brief:
// You are given the head of a linked list. Determine if the 
// linked list has a cycle in it.
// A cycle exists if some node in the list can be reached again 
// by continuously following the next pointer.
//
// Example:
// Input: head = [3,2,0,-4], pos = 1 (tail connects to node index 1)
// Output: true (because tail links back, forming a loop)
//
// ------------------------------------------------------------
// ✅ Solution name: Floyd’s Cycle Detection Algorithm 
//    (a.k.a. Tortoise & Hare Algorithm)
// ------------------------------------------------------------
// 🔹 Idea:
// Use two pointers: 
// - slow pointer moves one step at a time.
// - fast pointer moves two steps at a time.
// If there is a cycle, fast will eventually "lap" slow and 
// they will meet. If there is no cycle, fast will reach NULL.
// ------------------------------------------------------------
// ⏱ Time Complexity: O(n)
// - Each node visited at most once by slow/fast.
// 
// 💾 Space Complexity: O(1)
// - Only two pointers are used.
//
// 🔹 Is it optimal? 
// Yes. This is the most optimal cycle detection method known.
// 
// 🔹 Will it be accepted by LeetCode?
// Yes ✅. No chance of TLE or MLE.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        // Initialize both pointers at the head
        ListNode* slow = head;
        ListNode* fast = head;

        // Traverse while fast and fast->next are not NULL
        // (if there is no cycle, one of these will eventually hit NULL)
        while(fast != NULL && fast->next != NULL) {
            // slow moves one step
            slow = slow->next;

            // fast moves two steps
            fast = fast->next->next;

            // If slow and fast meet, there is a cycle
            if(slow == fast) return true;
        }

        // If fast reached NULL, no cycle exists
        return false;
    }
};

// ============================================================
// 🧠 Logic explained step by step:
// ------------------------------------------------------------
// 1. Why two pointers?
//    - Slow moves 1 step, fast moves 2 steps.
//    - If there’s a cycle, fast will eventually "lap" slow 
//      (they must meet at some node in the cycle).
//    - If there’s no cycle, fast will eventually reach NULL.
//
// 2. Why check (fast != NULL && fast->next != NULL)?
//    - Because if fast hits the end, accessing fast->next 
//      would cause a crash. It also signals no cycle.
//
// 3. The "lap" concept:
//    - Imagine a circular race track of length k.
//    - Slow moves 1 step per round, fast moves 2.
//    - Relative speed = (2 - 1) = 1 step per iteration.
//    - Therefore, fast reduces the gap by 1 each time, 
//      and will meet slow within at most k steps.
//
// 4. Why return NULL when no cycle?
//    - In a proper singly linked list, the tail ends with NULL.
//    - So, if fast ever reaches NULL, it means no cycle exists.
//
// ------------------------------------------------------------
// 🔑 Key insights:
// - If a cycle exists, collision (slow == fast) is inevitable.
// - If no cycle, loop ends naturally with fast == NULL.
// - This algorithm is the foundation of more advanced problems 
//   like "find start of cycle" (LeetCode 142).
// ============================================================

// ============================================================
// 🎯 Working Example
// ============================================================
int main() {
    // Example 1: Cycle present
    ListNode* head1 = new ListNode(3);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(0);
    ListNode* node4 = new ListNode(-4);

    head1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node2; // cycle created here

    Solution sol;
    cout << "Cycle present in list 1? " 
         << (sol.hasCycle(head1) ? "Yes" : "No") << endl;

    // Example 2: No cycle
    ListNode* head2 = new ListNode(1);
    ListNode* nodeB = new ListNode(2);
    head2->next = nodeB; // 1 -> 2 -> NULL

    cout << "Cycle present in list 2? " 
         << (sol.hasCycle(head2) ? "Yes" : "No") << endl;

    // Example 3: Single node cycle
    ListNode* head3 = new ListNode(5);
    head3->next = head3; // points to itself

    cout << "Cycle present in list 3? " 
         << (sol.hasCycle(head3) ? "Yes" : "No") << endl;

    // Example 4: Empty list
    ListNode* head4 = NULL;
    cout << "Cycle present in list 4? " 
         << (sol.hasCycle(head4) ? "Yes" : "No") << endl;

    return 0;
}

// ============================================================
// 📊 Output:
// Cycle present in list 1? Yes
// Cycle present in list 2? No
// Cycle present in list 3? Yes
// Cycle present in list 4? No
// ============================================================

// 🎓 Final note:
// Floyd’s cycle detection is not just about linked lists — 
// it's a powerful technique used in many cycle-detection 
// problems in mathematics and graph theory.
// ============================================================
