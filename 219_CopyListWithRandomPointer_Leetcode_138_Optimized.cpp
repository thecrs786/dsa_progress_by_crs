#include <bits/stdc++.h>
using namespace std;

/*
==================================================
📌 Problem Summary (LeetCode 138: Copy List with Random Pointer)
--------------------------------------------------
We are given a linked list where each node has:
1. `val`    → integer data
2. `next`   → pointer to the next node
3. `random` → pointer to ANY random node in the list (or NULL)

Task: 
Make a **deep copy** of this list, meaning:
- Create completely new nodes (no shared memory with original list).
- Both `next` and `random` pointers must be correctly assigned.

Constraints:
- Length of list: up to 1000 nodes.
- Node values: any integer.
==================================================
*/

/*
// Definition of a Node in this problem
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    /*
    ==================================================
    📌 Method Name: HashMap-based Deep Copy
    --------------------------------------------------
    Idea:
    - Use a hashmap (unordered_map) to keep a mapping between 
      original nodes and their corresponding newly created copies.
    - Step 1: Copy all nodes (values) and build `next` pointers.
    - Step 2: Traverse again and assign correct `random` pointers
              using the hashmap.

    Time Complexity  : O(N)  (two passes, each visiting all nodes)
    Space Complexity : O(N)  (extra hashmap storing mapping)
    Optimality       : ✔ Accepted by LeetCode
                       ✘ Not the most optimal in space (O(1) solution exists
                         using "node weaving" technique).
    Will it TLE/MLE? : ❌ No. (N <= 1000, so O(N) time and O(N) memory are safe)
    ==================================================
    */
    Node* copyRandomList(Node* head) {
        if (head == NULL) return NULL; // edge case: empty list

        // Hashmap: original node -> copied node
        unordered_map<Node*, Node*> m;

        // Step 1: Copy the head node
        Node* newHead = new Node(head->val); // new node created with same value
        Node* oldTemp = head->next;          // traversal pointer for original list
        Node* newTemp = newHead;             // traversal pointer for new list
        m[head] = newHead;                   // store mapping of original head -> new head

        // Step 2: Traverse original list and copy the rest of the nodes
        while (oldTemp != NULL) {
            Node* copyNode = new Node(oldTemp->val); // copy node with same value
            m[oldTemp] = copyNode;                   // map original -> copy
            newTemp->next = copyNode;                // link the new node in new list

            // advance both pointers
            oldTemp = oldTemp->next;
            newTemp = newTemp->next;
        }

        // Step 3: Traverse again to copy random pointers
        oldTemp = head;
        newTemp = newHead;
        while (oldTemp != NULL) {
            // oldTemp->random may be NULL, in which case m[NULL] is also NULL
            newTemp->random = m[oldTemp->random];
            oldTemp = oldTemp->next;
            newTemp = newTemp->next;
        }

        // Finally return the head of the deep copied list
        return newHead;
    }
};

/*
==================================================
📌 Key Concepts and Pointer Roles
--------------------------------------------------
- newHead : the starting pointer of the new (copied) list. Permanent reference.
- oldTemp : traversal pointer for the original list (used for scanning).
- newTemp : traversal pointer for the new list (used for attaching new nodes).
- copyNode: freshly created node that copies the value of an original node.
- m       : unordered_map (hashmap) that stores mapping:
            original_node_address -> copy_node_address
            This allows us to easily find the "corresponding" copy of any
            original node (for setting random pointers).

==================================================
📌 Why this Works
--------------------------------------------------
1. We must copy both `val`, `next`, and `random`.
2. Problem: when copying nodes, the `random` target might not yet exist!
3. Solution: use a hashmap to store mappings so we can easily find the copy.
4. Do two passes:
   - Pass 1: Copy nodes, build `next` pointers, fill hashmap.
   - Pass 2: Use hashmap to assign `random` pointers.

==================================================
📌 Important Insights
--------------------------------------------------
- Without hashmap, we cannot resolve random pointers unless we do
  the "O(1) weaving trick" (more complex but space-efficient).
- Always keep a permanent pointer to head (`newHead`),
  never lose it by advancing it during traversal.
- Careful: `m[oldTemp->random]` works even if `random == NULL`,
  because `unordered_map` allows `NULL` as a key and returns NULL.

==================================================
*/

// ==========================
// 📌 Working Example (Main)
// ==========================

int main() {
    // Manually create a small linked list:
    // Node1(val=7) -> Node2(val=13) -> Node3(val=11)
    // Random pointers set arbitrarily

    Node* node1 = new Node(7);
    Node* node2 = new Node(13);
    Node* node3 = new Node(11);

    // Build the "next" chain
    node1->next = node2;
    node2->next = node3;

    // Assign random pointers
    node1->random = NULL;    // node1 random -> NULL
    node2->random = node1;   // node2 random -> node1
    node3->random = node2;   // node3 random -> node2

    // Make a deep copy using our function
    Solution sol;
    Node* copiedHead = sol.copyRandomList(node1);

    // Print both original and copied list to verify
    cout << "Original list:" << endl;
    Node* temp = node1;
    while (temp != NULL) {
        cout << "Node val: " << temp->val;
        if (temp->random) cout << ", Random val: " << temp->random->val;
        else cout << ", Random val: NULL";
        cout << endl;
        temp = temp->next;
    }

    cout << "\nCopied list:" << endl;
    temp = copiedHead;
    while (temp != NULL) {
        cout << "Node val: " << temp->val;
        if (temp->random) cout << ", Random val: " << temp->random->val;
        else cout << ", Random val: NULL";
        cout << endl;
        temp = temp->next;
    }

    return 0;
}

/*
==================================================
📌 Example Walkthrough
--------------------------------------------------
Original List:
    node1(7) -> node2(13) -> node3(11)
    random: node1->NULL, node2->node1, node3->node2

After copy:
    newNode1(7) -> newNode2(13) -> newNode3(11)
    random: newNode1->NULL, newNode2->newNode1, newNode3->newNode2

Both lists are separate (different memory), but structure + random
connections are identical.

==================================================
*/
