// LeetCode 2 - Add Two Numbers (NOTES STYLE)
// ------------------------------------------------------------
// Problem (brief):
// Given two non-empty singly-linked lists representing two non-negative integers.
// The digits are stored in **reverse order** (least significant digit first).
// Each node contains a single digit. Add the two numbers and return the sum as a linked list.
//
// IMPORTANT: Input lists are reversed. You must RETURN the sum in the SAME reversed format.
//
// Examples:
// 1) l1 = [2 -> 4 -> 3], l2 = [5 -> 6 -> 4]  // 342 + 465
//    Output: [7 -> 0 -> 8]  // 807 (reversed as [7,0,8])
//
// 2) l1 = [5 -> 2 -> 2]  (225), l2 = [3 -> 4 -> 5 -> 4 -> 3 -> 2] (234543)
//    Output: [8 -> 6 -> 7 -> 4 -> 3 -> 2]  // 234768 (reversed)
//
// What to return (explicit):
// - Return the sum as a linked list whose digits are stored in reverse order
//   (i.e., least significant digit first), the same format as the inputs.
//
// ------------------------------------------------------------
// User's provided approach (the code you pasted earlier) — summary & why it fails:
// - You attempted to convert each linked list to an integer (num1, num2) by multiplying by 10,
//   then added them and converted to string to build the output list.
//
// Fatal problems with that approach:
// 1) **Overflow**: linked lists can be very long (up to 100+ digits). Can't store in int/long long.
// 2) **Wrong digit order handling**: you multiplied by 10 each step but lists are in reversed order.
// 3) **Pointer bug**: you used `n1->val` inside second loop (should be n2), causing wrong reads/crash.
// 4) **Char -> int bug**: casting `char '7'` to int yields ASCII 55; you must subtract '0'.
// 5) **List construction bug**: you never advanced the temp pointer, and you didn't handle next properly.
// 6) **Inevitable MLE/TLE/WA**: beyond simple logic bugs, the approach is conceptually wrong for constraints.
//
// Bottom line: **do not attempt to convert the whole list into a native integer/string and add**.
// Use digit-by-digit addition with carry (like hand addition). That's O(n) and safe.


// ------------------------------------------------------------
// Solution name / method:
// Digit-by-digit addition using a dummy head ("newHead") and a tail pointer ("temp").
// Maintain a carry variable and iterate while either list or carry remains.

// Time complexity: O(max(n, m)) where n and m are lengths of l1 and l2.
// Space complexity: O(max(n, m)) for the returned linked list (we allocate new nodes).
// - Extra auxiliary space beyond the output: O(1).
// Is it optimal? Yes in time (you must visit all digits). The space for output is optimal because output size
// is at least max(n,m) (possibly +1).
// Will it be accepted on LeetCode? Yes. No TLE or MLE for valid inputs. It's the standard accepted approach.
//
// Small note: you can slightly optimize by reusing nodes of the longer list to avoid allocating new nodes,
// but that complicates the code and isn't required for acceptance.

#include <bits/stdc++.h>
using namespace std;

// ---------------------- Linked list node ----------------------
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *nxt) : val(x), next(nxt) {}
};

// ---------------------- Solution class ------------------------
class Solution {
public:
    // addTwoNumbers
    // - builds the result list in reversed order directly (least significant digit first)
    // - uses a dummy head called "newHead" and a moving pointer "temp" to append nodes.
    //
    // Key idea: iterate while l1 || l2 || carry. At each iteration:
    //   sum = carry + (l1? l1->val : 0) + (l2? l2->val : 0)
    //   create node with value (sum % 10)
    //   carry = sum / 10
    // Move l1/l2 and temp accordingly.
    //
    // Why dummy "newHead"?
    // - It simplifies appending nodes: you never need a separate case to initialize head.
    // - newHead->next will be the real start of the resulting list.
    //
    // Why "temp"?
    // - temp is the tail pointer where we append the next digit node.
    // - We move temp forward after appending; newHead stays pointing to the dummy.
    //
    // Why return newHead->next?
    // - newHead is a dummy node (value unused). newHead->next points to the first real node of the sum.
    // - Returning newHead->next returns the result list without including the dummy node.
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* newHead = new ListNode(0); // dummy node — simplifies edge cases
        ListNode* temp = newHead;            // tail pointer to build the list
        int carry = 0;

        // Loop until both lists are exhausted and there's no carry left
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry; // start with carry from previous digit

            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next; // advance l1
            }

            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next; // advance l2
            }

            carry = sum / 10;
            int digit = sum % 10;

            // append new node with computed digit
            temp->next = new ListNode(digit);
            temp = temp->next; // move tail forward
        }

        // The real head of the result is newHead->next
        ListNode* result = newHead->next;

        // Optional: delete dummy node to avoid tiny memory leak (safe on LeetCode to skip).
        delete newHead;

        return result;
    }
};

// -------------------- Helper utilities for testing --------------------

// Create a reversed linked list from a string number in natural order.
// e.g. input "225" -> returns list [5 -> 2 -> 2]
ListNode* createListFromStringReverse(const string &numStr) {
    if (numStr.empty()) return nullptr;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int i = (int)numStr.size() - 1; i >= 0; --i) {
        char c = numStr[i];
        if (c < '0' || c > '9') continue; // ignore any non-digit
        int d = c - '0';
        ListNode* node = new ListNode(d);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }
    return head;
}

// Print list in human-readable reversed order "[5 -> 2 -> 2]"
void printList(const ListNode* head) {
    cout << "[";
    const ListNode* cur = head;
    bool first = true;
    while (cur) {
        if (!first) cout << " -> ";
        cout << cur->val;
        first = false;
        cur = cur->next;
    }
    cout << "]";
}

// Convert result list to a normal-order number string (most significant digit first).
// e.g. list [8 -> 6 -> 7 -> 4 -> 3 -> 2] -> "234768"
string listToNumberString(const ListNode* head) {
    if (!head) return "0";
    vector<char> digits;
    const ListNode* cur = head;
    while (cur) {
        digits.push_back(char('0' + cur->val));
        cur = cur->next;
    }
    reverse(digits.begin(), digits.end()); // because list is reversed
    return string(digits.begin(), digits.end());
}

// Free list memory
void deleteList(ListNode* head) {
    while (head) {
        ListNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

// ----------------------------- MAIN ---------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Working example requested: add 225 and 234543
    string s1 = "225";
    string s2 = "234543";

    // Create lists in the format LeetCode expects (reversed)
    ListNode* l1 = createListFromStringReverse(s1); // [5 -> 2 -> 2]
    ListNode* l2 = createListFromStringReverse(s2); // [3 -> 4 -> 5 -> 4 -> 3 -> 2]

    cout << "Input l1 (reversed) = "; printList(l1); cout << "  (represents " << s1 << ")\n";
    cout << "Input l2 (reversed) = "; printList(l2); cout << "  (represents " << s2 << ")\n\n";

    Solution sol;
    ListNode* result = sol.addTwoNumbers(l1, l2);

    cout << "Result list (reversed) = "; printList(result); cout << "\n";
    cout << "Result number (normal order) = " << listToNumberString(result) << "\n\n";

    // Expected:
    // Result list (reversed) = [8 -> 6 -> 7 -> 4 -> 3 -> 2]
    // Result number (normal order) = 234768

    // Cleanup
    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    return 0;
}


/*
---------------------- DETAILED STEP-BY-STEP WALKTHROUGH (explain each line of addTwoNumbers) ----------------------

1) ListNode* newHead = new ListNode(0);
   - Create a dummy node ("newHead") to anchor the result list.
   - Avoids special-case logic for the first appended node.

2) ListNode* temp = newHead;
   - temp is a moving tail pointer. When we append a node, we do "temp->next = newNode" and then "temp = temp->next".
   - This preserves newHead as the starting anchor so we can return newHead->next later.

3) int carry = 0;
   - carry stores the carry from adding two digits (0 or 1 for decimal digits, but could be larger if base was different).

4) while (l1 != nullptr || l2 != nullptr || carry != 0)
   - Continue as long as there are digits to process in either list OR there is a non-zero carry.
   - This handles different-length lists automatically, and also handles a final carry (e.g., 5 + 5 -> [0 -> 1]).

5) int sum = carry;
   - Start with the previous carry, then add digits from l1 and l2 if present.

6) if (l1 != nullptr) { sum += l1->val; l1 = l1->next; }
   - Add the next digit from l1 (or 0 if l1 is exhausted). Advance l1.

7) if (l2 != nullptr) { sum += l2->val; l2 = l2->next; }
   - Add the next digit from l2 (or 0 if l2 is exhausted). Advance l2.

8) carry = sum / 10;
   - Compute carry for next iteration (integer division). For decimals this is either 0 or 1.

9) int digit = sum % 10;
   - The current digit to store in the result node.

10) temp->next = new ListNode(digit); temp = temp->next;
   - Append a new node with the computed digit and move the tail pointer.

11) After loop, ListNode* result = newHead->next;
   - The first real node is after the dummy. Return that.

12) delete newHead;
   - Free the dummy node (optional). The returned list remains valid.

--------------------------------------------------------------------------------
KEY INSIGHTS & IMPORTANT DETAILS:
- You DO NOT reverse the result separately because the inputs are reversed by contract.
- Loop condition MUST include 'carry' to handle cases where final carry creates a new digit.
- Treat missing digits (when one list is shorter) as 0 — the while condition + null checks accomplish this.
- Converting the whole list to an integer is unsafe (overflow) and unnecessary.
- Memory: We allocate O(k) nodes for the answer where k = max(n,m) or max(n,m)+1.
- This approach is canonical and will pass typical LeetCode constraints.

EDGE CASES:
- l1 or l2 is a single node.
- Sum produces an additional digit (e.g., 999 + 1 = 1000).
- Inputs include zeros (e.g., [0] + [0]).
- Very long numbers (handled as we operate digit-by-digit).

VARIANT / NOTE:
- LeetCode 445 ("Add Two Numbers II") stores digits in forward order (most significant first). That problem requires either reversing lists first or using stacks to add from right to left. Don't confuse the two problems.

--------------------------------------------------------------------------------
If you want: I can also produce a *one-page* condensed flashcard version of this (shorter), or a version that **reuses existing nodes** to reduce allocations (in-place), but the above is the cleanest and most standard form for learning and submission.
*/
