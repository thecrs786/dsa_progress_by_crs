#include <iostream>
#include <vector>
using namespace std;

/*
====================================================================================
🔹 LeetCode 234 — Palindrome Linked List (Array / Vector Approach)
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
Explanation: Palindrome with odd length; center element ignored when comparing.

Example 3:
Input:  head = [1,2,3]
Output: false

Example 4:
Input:  head = [1]
Output: true

Example 5:
Input:  head = [1,2]
Output: false

------------------------------------------------------------------------------------
Approach / Method (this file):
- Copy all node values into a dynamic array / vector.
- Use two indices (start, end) to perform a two-pointer palindrome check on the vector.
- Simple, direct, easy to implement.

Complexities:
- Time Complexity: O(n) — one pass to build vector + one pass to compare (combined O(n)).
- Space Complexity: O(n) — vector stores all node values.

Is this the most optimal?
- No in terms of space. The optimal approach uses O(1) extra space (reverse second half).
- This vector approach is simpler and fast enough for typical constraints.

Will it be accepted on LeetCode?
- ✅ Yes. It passes LeetCode constraints for this problem.
- ❗ Not optimal for memory-critical or huge lists, but LeetCode limits make it acceptable.
- No chance of TLE (O(n) time). MLE only when list size exceeds available memory (rare for LeetCode constraints).

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
    // --------------------
    // Vector-based method:
    // 1) Dump values into vector<int> l
    // 2) Two-pointer check from both ends
    // --------------------
    bool isPalindrome(ListNode* head) {
        vector<int> l;

        // copy node values into vector
        ListNode* temp = head;
        while(temp != nullptr){
            l.push_back(temp->val);
            temp = temp->next;
        }

        // two-pointer palindrome check on vector
        int st = 0;
        int end = (int)l.size() - 1;

        while(st <= end){
            if(l[st] != l[end]) return false;
            st++;
            end--;
        }

        return true;
    }
};

/*
====================================================================================
LOGIC / DETAILED EXPLANATION (step-by-step, fully explicit)
------------------------------------------------------------------------------------

Why this works:
- A palindrome list reads the same forwards and backwards.
- If we copy the values into an array, palindrome-check reduces to comparing
  the array with its reverse — which can be done with two pointers in O(n).

Step-by-step:
1) Traverse the linked list once (linear scan) and push each node's value to a vector<int>.
   - Purpose: provide random access and index-based two-pointer comparison.
   - Complexity: O(n) time, O(n) extra memory.

2) Initialize two integer pointers:
   - st = 0 (index of first element)
   - end = l.size() - 1 (index of last element)

3) While st <= end:
   - Compare l[st] and l[end].
   - If not equal → list is not a palindrome → return false immediately.
   - Else move st++ and end-- to check the next pair.

4) If loop finishes without mismatch → all mirrored pairs matched → return true.

Why st <= end (not st < end)?
- Either choice works (st < end or st <= end) because when st == end we compare the center element with itself (always equal).
- Using st <= end is safe and simple.

Edge cases handled:
- Empty list (head == nullptr): vector empty → st = 0, end = -1 → loop skipped → returns true.
- Single node: vector size 1 → st = 0, end = 0 → compares element with itself → returns true.
- Even and odd lengths both handled naturally.

Memory / Performance notes:
- Vector size is proportional to number of nodes; large lists require more memory.
- But vector operations and comparisons are cache-friendly and fast.

====================================================================================
*/

 // ---------------------------
 // Helper functions for testing
 // ---------------------------
void printList(ListNode* head) {
    ListNode* cur = head;
    while(cur) {
        cout << cur->val;
        if(cur->next) cout << " -> ";
        cur = cur->next;
    }
    cout << '\n';
}

ListNode* buildList(initializer_list<int> vals) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int v : vals) {
        ListNode* node = new ListNode(v);
        if (!head) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    return head;
}

void freeList(ListNode* head) {
    while(head) {
        ListNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

// ---------------------------
// Working examples (main)
// ---------------------------
int main() {
    Solution sol;

    // Example 1: even-length palindrome [1,2,2,1]
    ListNode* a = buildList({1,2,2,1});
    cout << "List A: "; printList(a);
    cout << "isPalindrome(A)? " << (sol.isPalindrome(a) ? "true" : "false") << '\n';
    freeList(a);
    cout << '\n';

    // Example 2: odd-length palindrome [1,2,3,2,1]
    ListNode* b = buildList({1,2,3,2,1});
    cout << "List B: "; printList(b);
    cout << "isPalindrome(B)? " << (sol.isPalindrome(b) ? "true" : "false") << '\n';
    freeList(b);
    cout << '\n';

    // Example 3: not a palindrome [1,2,3]
    ListNode* c = buildList({1,2,3});
    cout << "List C: "; printList(c);
    cout << "isPalindrome(C)? " << (sol.isPalindrome(c) ? "true" : "false") << '\n';
    freeList(c);
    cout << '\n';

    // Example 4: single node [7]
    ListNode* d = buildList({7});
    cout << "List D: "; printList(d);
    cout << "isPalindrome(D)? " << (sol.isPalindrome(d) ? "true" : "false") << '\n';
    freeList(d);
    cout << '\n';

    // Example 5: large-ish test (works fine)
    ListNode* e = buildList({1,1,1,1,1,1});
    cout << "List E: "; printList(e);
    cout << "isPalindrome(E)? " << (sol.isPalindrome(e) ? "true" : "false") << '\n';
    freeList(e);
    cout << '\n';

    return 0;
}

/*
====================================================================================
IMPORTANT DETAILS, WARNINGS, AND KEY SIGHTS
------------------------------------------------------------------------------------
1. Simplicity: This method is very simple to implement and reason about.
2. Space tradeoff: uses O(n) extra memory — not optimal but acceptable in most contest/LeetCode settings.
3. When to prefer this:
   - Quick implementation, debugging, or when memory isn't tight.
   - Interview when time is limited and interviewer allows O(n) extra space.
4. When to avoid this:
   - If you are explicitly required to use O(1) extra space.
   - Very large lists where memory usage could be an issue.
5. Alternatives:
   - Optimal O(1) space: find middle, reverse second half, compare, restore. (More pointers, trickier.)
   - Stack-based: push first half values on stack then compare with second half (O(n) space).
6. Performance:
   - Time: linear traversal operations; no hidden heavy constants.
   - Memory: vector allocation/resizing overhead — reserve(n) could be used if n known.

====================================================================================
SIMILAR QUESTIONS & RELATED APPROACHES:
- LeetCode 234: Palindrome Linked List (optimal method uses O(1) space)
- LeetCode 206: Reverse Linked List (helper for O(1) solution)
- Using array copy vs reverse-half-inplace: tradeoff is simplicity vs space
====================================================================================
*/
