//============================================================================
// 📌 Problem 21. Merge Two Sorted Lists (LeetCode)
//
// ❓ Problem Summary:
// Given two sorted linked lists, merge them into one sorted linked list 
// and return its head. The merged list should be made by splicing together
// the nodes of the first two lists (without creating new nodes).
//
// ⚡ Example:
// Input: list1 = [1,2,4], list2 = [1,3,4]
// Output: [1,1,2,3,4,4]
//============================================================================

#include <bits/stdc++.h>
using namespace std;

//============================================================================
// 🔑 Definition of a Linked List Node
//============================================================================
struct ListNode {
    int val;
    ListNode *next;

    // Constructors
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//============================================================================
// 🚀 Solution Class
// Method: Recursive Merge
//============================================================================
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
        // Base Case 1: If first list is empty → return second
        if (head1 == NULL) return head2;

        // Base Case 2: If second list is empty → return first
        if (head2 == NULL) return head1;

        // Step 1: Compare values of current nodes
        // Step 2: Pick the smaller one as "current node" of merged list
        // Step 3: Recursively merge remaining part of lists
        if (head1->val <= head2->val) {
            head1->next = mergeTwoLists(head1->next, head2);
            return head1;  // head1 is chosen, return it upward
        } 
        else {
            head2->next = mergeTwoLists(head1, head2->next);
            return head2;  // head2 is chosen, return it upward
        }
    }
};

//============================================================================
// 📘 Detailed Explanation of Logic
//============================================================================
/*
1. Base Case:
   - If one list is empty → just return the other list, because merging 
     with an empty list doesn't change the result.

2. Recursion:
   - Compare head1->val and head2->val
   - Suppose head1->val <= head2->val:
        - head1 must be the next node in the merged list.
        - But we still need to merge the rest:
              mergeTwoLists(head1->next, head2)
        - That gives us the merged list of remaining elements.
        - Attach it to head1->next.
   - Return head1 (since it's chosen as the smaller node).

   - Similarly for head2 if head2->val < head1->val.

3. Key Insight:
   - We’re not creating new nodes, only re-wiring existing `next` pointers.
   - This ensures O(1) extra space (ignoring recursion stack).

4. Recursion Tree Example:
   Let head1 = [1,3,5], head2 = [2,4,6]
   
   merge(1,2):
      1 < 2 → take 1 → link 1->merge(3,2)
         merge(3,2):
             3 > 2 → take 2 → link 2->merge(3,4)
                merge(3,4):
                    3 < 4 → take 3 → link 3->merge(5,4)
                        merge(5,4):
                            5 > 4 → take 4 → link 4->merge(5,6)
                                merge(5,6):
                                    5 < 6 → take 5 → link 5->merge(NULL,6)
                                        base → return 6
   Final merged list = 1->2->3->4->5->6

5. Time Complexity:
   - Each node is processed exactly once → O(n+m), where n and m are lengths of two lists.

6. Space Complexity:
   - No extra data structures used, but recursion depth = O(n+m) stack space.
   - ⚠️ Important: In worst-case very long lists, recursion can cause stack overflow.
     Iterative solution is safer in real systems.

7. Optimality:
   - Yes, time O(n+m) is optimal (you must touch all nodes at least once).
   - Space O(n+m) due to recursion stack is not strictly optimal.
   - Iterative solution achieves O(1) space.

8. LeetCode Acceptance:
   ✅ This solution will be accepted.
   - No TLE (time is linear).
   - No MLE (memory is fine for typical list sizes).
   - But iterative version is recommended if constraints are huge.
*/

//============================================================================
// 🛠️ Working Example (Test Code in main)
//============================================================================
int main() {
    // Creating first sorted list: [1,2,4]
    ListNode* a = new ListNode(1);
    a->next = new ListNode(2);
    a->next->next = new ListNode(4);

    // Creating second sorted list: [1,3,4]
    ListNode* b = new ListNode(1);
    b->next = new ListNode(3);
    b->next->next = new ListNode(4);

    Solution sol;
    ListNode* merged = sol.mergeTwoLists(a, b);

    cout << "Merged List: ";
    while (merged != NULL) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    return 0;
}

/*
============================================================================
💡 Key Takeaways:
- Recursive merge works by "choosing the smaller head and recursing".
- Each recursive call reduces problem size by 1 node.
- The recursion builds a "decision tree" but only one path executes fully.
- Links are re-wired, not new nodes created → efficient.
- Stack depth = n+m (watch out for huge lists).
============================================================================
*/
