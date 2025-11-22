/*
LeetCode Question: 24. Swap Nodes in Pairs
Brief: 
    Given a linked list, swap every two adjacent nodes and return its head. 
    You must solve the problem without modifying the values in the list’s nodes (i.e., only nodes themselves may be changed).
Examples:
    Input: head = [1,2,3,4]
    Output: [2,1,4,3]

    Input: head = []
    Output: []

    Input: head = [1]
    Output: [1]

Solution provided below is a recursive approach that essentially reverses nodes in pairs, 
which is a special case of the more general "Reverse Nodes in k-Group" problem (LeetCode 25).
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
    /*
    Method Name: Recursive Pair Reversal
    Approach:
        1. Check if the list has less than 2 nodes. If yes, return head as is.
        2. Identify the next 2 nodes to reverse using 'temp'.
        3. Reverse the 2 nodes using standard iterative reversal logic.
        4. Recurse for the remaining list starting from temp.
        5. Link the reversed pair to the result of recursion.
        6. Return 'prev' as the new head of the reversed pair.

    Time Complexity: O(n) - each node is visited exactly once.
    Space Complexity: O(n) - recursion stack (can be optimized with iterative approach).
    Optimality: Acceptable and will be accepted on LeetCode. No MLE or TLE for reasonable input sizes.
    */
    ListNode* swapPairs(ListNode* head) {
        if(!head) return head; // Base case: empty list

        // Step 1: Check if there are at least 2 nodes to reverse
        ListNode* temp = head;
        for(int count = 0; count < 2; count++) {
            if(temp == NULL) return head; // Less than 2 nodes, return as is
            temp = temp->next;
        }

        // Step 2: Initialize pointers for reversal
        ListNode* prev = NULL;   
        ListNode* curr = head;   
        ListNode* next = NULL;   

        // Step 3: Reverse exactly 2 nodes
        while(curr != temp) {
            next = curr->next;   // Save next node
            curr->next = prev;   // Reverse current node's pointer
            prev = curr;         // Move prev forward
            curr = next;         // Move curr forward
        }

        // Step 4: Recursive call for the remaining list
        head->next = swapPairs(temp); 

        // Step 5: Return new head of this reversed pair
        return prev;
    }
};

/*
Function Explanation:

- Base Case: If list is empty or has less than 2 nodes, no swap is needed.
- Using 'temp', we check if there are 2 nodes available for swapping.
- 'prev', 'curr', 'next' pointers perform iterative reversal for exactly 2 nodes.
- After reversing, 'head' (original first node) points to the result of recursion.
- 'prev' becomes the new head of this reversed pair.
- The recursion ensures all pairs in the list are swapped.
- This is effectively a special case of "Reverse Nodes in k Groups" where k=2.

Important Details & Key Sights:
- Reversal logic: iterative reversal inside a fixed-size window (here k=2).
- Recursion ensures the next part of the list is handled seamlessly.
- Return type must be ListNode* because head changes after reversal.
- Connection to reverseKGroup: This is exactly reverseKGroup with k=2.
- Linking: Each original 'head' becomes the tail after reversal of current k-group.

Working Example:
    Input List: 1 -> 2 -> 3 -> 4
    Step 1: Reverse first pair 1 & 2 -> 2 -> 1
    Step 2: Recurse on 3 -> 4
    Step 3: Reverse next pair 3 & 4 -> 4 -> 3
    Step 4: Link: 1->next = 4
    Output List: 2 -> 1 -> 4 -> 3
*/

// Helper function to print list
void printList(ListNode* head) {
    while(head) {
        cout << head->val;
        if(head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// Main function for testing
int main() {
    // Creating linked list: 1 -> 2 -> 3 -> 4
    ListNode* n4 = new ListNode(4);
    ListNode* n3 = new ListNode(3, n4);
    ListNode* n2 = new ListNode(2, n3);
    ListNode* n1 = new ListNode(1, n2);

    cout << "Original list: ";
    printList(n1);

    Solution sol;
    ListNode* swappedHead = sol.swapPairs(n1);

    cout << "After swapPairs: ";
    printList(swappedHead);

    return 0;
}

/*
Output:
Original list: 1 -> 2 -> 3 -> 4
After swapPairs: 2 -> 1 -> 4 -> 3
*/
