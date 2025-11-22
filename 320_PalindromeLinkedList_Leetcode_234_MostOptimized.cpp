#include <iostream>
using namespace std;

/*
====================================================================================
🔹 LeetCode 234 — Palindrome Linked List (In-place O(1) space approach)
====================================================================================

Problem (brief):
Given the head of a singly-linked list, determine if the list is a palindrome.
Return true if it reads the same forward and backward, else false.

------------------------------------------------------------------------------------
💡 Examples:

Example 1:
Input:  head = [1,2,2,1]
Output: true
Explanation: Reading forward (1→2→2→1) and backward (1→2→2→1) are same.

Example 2:
Input:  head = [1,2,3,2,1]
Output: true
Explanation: Odd number of nodes; middle element (3) is ignored while comparing halves.

Example 3:
Input:  head = [1,2,3]
Output: false
Explanation: Forward (1→2→3), backward (3→2→1) are not same.

Example 4:
Input:  head = [1]
Output: true
Explanation: Single node is trivially palindrome.

Example 5:
Input:  head = [1,2]
Output: false
Explanation: Forward = 1→2, backward = 2→1, not same.

------------------------------------------------------------------------------------

Key constraints:
- You must do it in O(n) time and O(1) extra space (in-place) for the optimal solution.
- Common accepted strategy: find middle, reverse second half, compare, restore.

This file contains:
- Your implementation (in-place, reverse-second-half, compare, restore)
- Full detailed commentary explaining every pointer and step
- Working examples in main() showing both even and odd cases and that the list is restored

Complexities:
- Time: O(n)
- Space: O(1) (only a few pointers)

Will this be accepted on LeetCode?
- ✅ Yes. This is the standard optimal approach (O(n) time, O(1) space).
- ⚠️ Be careful with null/one-node list edge-cases (code handles them properly).

====================================================================================
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

    // Reverse linked list helper — standard iterative reverse.
    // Returns new head (prev) of the reversed list.
    ListNode* reverse(ListNode* head){
        ListNode* prev = NULL;
        ListNode* next = NULL;
        ListNode* curr = head;

        while(curr!=NULL){
            next = curr->next;
            curr->next = prev;

            prev = curr;
            curr = next;
        }

        return prev;
    }

    // Main function: in-place palindrome check
    bool isPalindrome(ListNode* head) {
        // Edge cases: empty list or single node is palindrome
        if(!head || !head->next) return true;

        // Pointers for finding middle
        ListNode* slow = head;   // moves 1 step
        ListNode* fast = head;   // moves 2 steps
        ListNode* prev = NULL;   // will point to end of first half (or middle for odd case)

        // 1) Find middle using slow/fast.
        //    After loop:
        //    - if fast == NULL  => even length, slow is start of second half (the "right middle")
        //    - if fast != NULL  => odd length, slow is the middle node
        while(fast!=NULL && fast->next!=NULL){
            prev = slow;            // keep previous of slow (tail of first half)
            slow = slow->next;
            fast = fast->next->next;
        }

        // Explanation of positions:
        // - EVEN length (e.g., 4 nodes): fast becomes NULL after the loop.
        //   slow points to the node at index n/2 + 1 (the first node of the *second half*).
        //   prev points to the last node of the first half.
        // - ODD length (e.g., 5 nodes): fast is not NULL (fast points to last node),
        //   slow points to the exact middle node.
        //   prev points to the node just before the middle (end of first half).

        ListNode* st1 = head;   // pointer to traverse first half from start
        ListNode* st2 = NULL;   // start of the second half that we will reverse and compare

        // 2) Choose start of second half to reverse:
        //    - even length: reverse starting from slow (slow is beginning of second half)
        //    - odd length: reverse starting from slow->next (skip the exact middle element)
        //
        // Your specific choice: when odd, you set prev = slow (so prev becomes middle) and
        // st2 = slow->next (start after middle). This makes prev point to the middle node,
        // which you later use to relink restored list correctly.
        if(fast==NULL) {
            // EVEN number of nodes
            // slow is the start of second half
            st2 = slow;
            // prev already points to the last node of first half (correct)
        } else {
            // ODD number of nodes
            // slow is the exact middle node; we must skip it when comparing
            // set prev = slow so prev will later be used to relink (prev->next = restored second half)
            prev = slow;
            st2 = slow->next;
        }

        // 3) Reverse the second half (in-place).
        //    The reversed half ends with NULL, which makes comparing and relinking simple.
        st2 = reverse(st2);

        // 4) Compare: traverse the reversed second half (st2) and the first half (st1).
        //    We only need to run as long as the reversed half has nodes (temp != NULL).
        //    This handles both even and odd lists because:
        //      - For even: both halves have same length => full comparison covers whole list.
        //      - For odd: reversed half is shorter by one, compare only reversed nodes; middle is ignored.
        ListNode* temp = st2;
        while(temp!=NULL){
            if(st1->val != temp->val){
                // Not palindrome — restore the list before returning false.
                prev->next = reverse(st2);   // reverse again to restore original second half then relink
                return false;
            }
            st1 = st1->next;
            temp = temp->next;
        }

        // 5) If all matched, restore the second half back into original order and relink.
        prev->next = reverse(st2);

        // 6) Return result — true because all comparisons passed.
        return true;
    }
};

/*
====================================================================================
LOGIC / WALKTHROUGH (detailed, step-by-step — includes why each pointer exists)
====================================================================================

Pointers:
- head : start of list
- slow : walker that moves one step per loop (used to find middle)
- fast : runner that moves two steps per loop (used to find middle / detect odd/even)
- prev : the node that ends the first half (for even) OR the middle node (for odd).
         Used later to relink the restored second half.
- st1  : pointer traversing the first half from the head during comparison.
- st2  : start of the second half to reverse (and later compare).
- temp : traversal pointer for the reversed second half during comparison.

Why this partitioning works (concise):
- Inorder to compare the list forwards and backwards without extra memory,
  reverse the second half and compare node-by-node with first half.
- For EVEN length: both halves are same length, slow ends at start of second half.
- For ODD length: middle node isn't part of either half to compare; we skip it.
- We define the reversed half's traversal boundary as the reversed list itself (temp != NULL).
  That allows the first half to be one node longer in odd case — no problem.

Why prev is assigned differently for odd & even:
- After the slow/fast loop finishes:
  - For EVEN: prev points to the last node of the first half — correct for relinking.
  - For ODD: slow points to the middle — we set prev = slow so prev becomes the middle node,
    because relinking will reattach the restored second half after the middle node.
  This keeps relinking logic unified:
    prev->next = reverse(st2); // works for both cases

Why comparing only reversed half is enough:
- The reversed half length is the shorter (or equal) half.
- If every element in the reversed half matches the corresponding prefix of the list,
  the list is palindrome. No need to continue beyond reversed half — the remainder has no counterpart.

Restoring the list:
- We reverse the second half back before returning to keep input unchanged.
- prev->next = reverse(st2) puts the restored tail back in place (prev is set appropriately).

====================================================================================
DRY-RUN (EVEN LENGTH example: [1,2,2,1])
------------------------------------------------------------------------------------
Initial: head -> 1 -> 2 -> 2 -> 1
Step: slow=head(1), fast=head(1), prev=NULL

Loop iterations:
1) prev=1, slow=2(first 2), fast=2 (third node)
2) next iteration fast->next is NULL? fast is at third node (value 2) and fast->next->next =>
   fast->next is last node (1), fast->next->next is NULL, so fast becomes NULL; loop exits.
After loop:
- fast == NULL => EVEN
- slow points to node 3 (value 2) — start of second half
- prev points to node 2 (value 2) — end of first half

st2 = slow (node 3)
st2 = reverse(st2) => reversed second half: 1 -> 2 -> NULL

Compare:
st1 (head)=1, temp(st2)=1 => match
st1->next=2, temp->next=2 => match
temp becomes NULL => matched entire reversed half

Restore:
prev->next = reverse(st2) => prev (node2) -> next becomes original second half 2->1

Return true.

====================================================================================
DRY-RUN (ODD LENGTH example: [1,2,3,2,1])
------------------------------------------------------------------------------------
Initial: 1 -> 2 -> 3 -> 2 -> 1
Loop iterations:
1) prev=1, slow=2, fast=3
2) next iteration: prev=2, slow=3, fast moves to NULL? fast->next->next from 3 -> NULL; loop stops.
After loop:
- fast != NULL (fast points to last node) => ODD
- slow points to middle node 3
- prev = slow assigned below for odd case (so prev points to middle node)
st2 = slow->next => node with value 2 (start of second half)

st2 = reverse(st2) => reversed second half = 1 -> 2 -> NULL

Compare:
st1=head=1 vs temp=1 => match
st1=2 vs temp=2 => match
temp becomes NULL => done

Restore:
prev->next = reverse(st2) => prev is middle node (3), so 3->next becomes restored 2->1

Return true.

====================================================================================
IMPORTANT DETAILS, WARNINGS, AND KEY INSIGHTS
====================================================================================
- Always use fast = fast->next->next inside the loop — otherwise mid detection fails.
- prev is used for relinking; in odd length you intentionally set prev=slow (middle) so
  relinking attaches the restored half after the middle node.
- Reverse returns an independent list ending with NULL; relinking uses prev->next = reverse(st2).
- Comparing only the reversed half (temp != NULL) is correct and efficient; it avoids extra checks.
- Restore the list before returning (especially if your environment runs subsequent tests on same list).
- This method is optimal: O(n) time and O(1) auxiliary space.
- Be careful with extremely short lists (0,1 nodes) — this code returns true quickly.

====================================================================================
SIMILAR QUESTIONS & RELATED APPROACHES:
- LeetCode 234 — Palindrome Linked List (this problem)
- LeetCode 206 — Reverse Linked List (helper reverse used here)
- Variants:
    * Use a stack to store first half values (O(n) space) — simpler but not optimal.
    * Copy values into an array and two-pointer check (O(n) space) — simpler.
====================================================================================
*/

// ---------------------------
// Helper functions for testing
// ---------------------------
void printList(ListNode* head){
    ListNode* cur = head;
    while(cur){
        cout << cur->val;
        if(cur->next) cout << " -> ";
        cur = cur->next;
    }
    cout << '\n';
}

ListNode* buildList(initializer_list<int> vals){
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for(int v : vals){
        ListNode* node = new ListNode(v);
        if(!head){ head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    return head;
}

int main(){
    Solution sol;

    // Example 1: odd-length palindrome [1,2,3,2,1]
    ListNode* a = buildList({1,2,3,2,1});
    cout << "Original A: "; printList(a);
    cout << "isPalindrome(A)? " << (sol.isPalindrome(a) ? "true" : "false") << '\n';
    cout << "Restored A: "; printList(a);
    cout << '\n';

    // Example 2: even-length palindrome [1,2,2,1]
    ListNode* b = buildList({1,2,2,1});
    cout << "Original B: "; printList(b);
    cout << "isPalindrome(B)? " << (sol.isPalindrome(b) ? "true" : "false") << '\n';
    cout << "Restored B: "; printList(b);
    cout << '\n';

    // Example 3: not a palindrome [1,2,3]
    ListNode* c = buildList({1,2,3});
    cout << "Original C: "; printList(c);
    cout << "isPalindrome(C)? " << (sol.isPalindrome(c) ? "true" : "false") << '\n';
    cout << "Restored C: "; printList(c);
    cout << '\n';

    // Example 4: single node [7]
    ListNode* d = buildList({7});
    cout << "Original D: "; printList(d);
    cout << "isPalindrome(D)? " << (sol.isPalindrome(d) ? "true" : "false") << '\n';
    cout << "Restored D: "; printList(d);
    cout << '\n';

    return 0;
}
