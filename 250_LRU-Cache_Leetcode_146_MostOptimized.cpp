/*
LeetCode Problem 146: LRU Cache

Question Brief:
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
Implement the LRUCache class:

1. LRUCache(int capacity) - Initialize the LRU cache with positive size capacity.
2. int get(int key) - Return the value of the key if the key exists, otherwise return -1.
3. void put(int key, int value) - Update the value of the key if the key exists. 
   Otherwise, add the key-value pair to the cache. If the number of keys exceeds 
   the capacity from this operation, evict the least recently used key.

Example:
Input:
LRUCache cache = new LRUCache(2); // capacity 2
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

Approach/Method:
- Use a doubly linked list to maintain the order of most recently used elements.
- Use a hashmap (unordered_map) for O(1) access to nodes by key.
- Head and tail dummy nodes are used to avoid null checks and simplify operations.

Time Complexity:
- get(): O(1)
- put(): O(1)
- Overall operations: O(1) amortized for both

Space Complexity:
- O(capacity) for the doubly linked list + hashmap storage.

Optimality:
- This is the optimal solution for LRU Cache.
- Will be accepted on LeetCode (no TLE or MLE).

*/

#include <bits/stdc++.h>
using namespace std;

class LRUCache {
public:

    // Node class for doubly linked list
    class Node{
        public:
        int key, val;     // key and value of cache entry
        Node* prev;
        Node* next;

        Node(int k, int v){
            key = k;
            val = v;
            prev = next = NULL;
        }
    };
    
    Node* head = new Node(-1, -1); // dummy head to simplify insertion at front
    Node* tail = new Node(-1, -1); // dummy tail to simplify deletion at end

    unordered_map<int, Node*> m; // hashmap for O(1) access
    int limit; // max capacity of cache

    // Moves an existing node to front (most recently used)
    void moveFront(Node* node){
        // detach node from its current position
        node->prev->next = node->next;
        node->next->prev = node->prev;

        // insert node right after head
        Node* temp = head->next;
        head->next = node;
        node->prev = head;

        node->next = temp;
        temp->prev = node;
    }

    // Deletes a node from the list (used during eviction)
    void deleteNode(Node* node){
        Node* temp = node;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete temp; // free memory
    }

    // Adds a new node to the front of the list and map
    void addNode(int key, int value){
        Node* newNode = new Node(key, value);
        Node* temp = head->next;

        head->next = newNode;
        newNode->prev = head;

        newNode->next = temp;
        temp->prev = newNode;

        m[key]=newNode; // insert into hashmap
    }

    // Constructor initializes cache with capacity
    LRUCache(int capacity) {
        limit = capacity;
        head->next = tail; // initially, head points to tail
        tail->prev = head; // tail points back to head
    }
    
    int get(int key) {
        if(m.find(key)!=m.end()){ // key exists
            moveFront(m[key]);    // move it to front (most recently used)
            return m[key]->val;
        }
        else return -1;           // key not found
    }
    
    void put(int key, int value) {
        if(m.find(key)!=m.end()){ // key exists, update value
            m[key]->val = value;
            moveFront(m[key]);
        }
        /* OR  (Not Recommended)
        if(m.find(key)!=m.end()){
            deleteNode(m[key]);
            m.erase(key);
            addNode(key, value);
        }*/
        else{
            if(m.size()==limit){ // cache full, evict LRU (node before tail)
                m.erase(tail->prev->key); // remove from map
                deleteNode(tail->prev);   // remove from list
            }
            addNode(key, value); // add new node to front
        }
    }
};

/*
Logic & Function Explanation:

1. Node Class:
   - Represents each cache entry with key, value.
   - Has prev and next pointers to form a doubly linked list.

2. Head & Tail Dummy Nodes:
   - Avoids null checks when inserting or deleting nodes.
   - Head->next always points to most recently used node.
   - Tail->prev always points to least recently used node.

3. Hashmap:
   - Stores key -> Node* mapping for O(1) access during get and put.

4. moveFront(Node* node):
   - Detaches the node from its current position.
   - Inserts it right after head to mark it as most recently used.

5. deleteNode(Node* node):
   - Detaches node from list.
   - Frees memory to prevent memory leaks.

6. addNode(int key, int value):
   - Creates a new node and inserts it at the front.
   - Updates hashmap.

7. get(int key):
   - If key exists, move to front (most recently used) and return value.
   - Else return -1.

8. put(int key, int value):
   - If key exists, update value and move to front.
   - If key does not exist:
     - If cache full, remove LRU (node before tail) from map and list.
     - Add new node to front.

Important Details, Warnings, and Key Insights:
- Always maintain head->next and tail->prev correctly.
- Never forget to update both prev and next pointers during move/delete/add.
- Using dummy head/tail simplifies edge cases.
- Do not forget to delete nodes to prevent memory leaks.
- Map ensures O(1) access, list maintains LRU order.
- Optimal for LeetCode 146, will not TLE or MLE.
- Similar questions: LFU Cache, Design a Cache System, Rolling Hash LRU.

*/

int main() {
    // Working example
    LRUCache cache(2); // capacity 2
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;   // 1
    cache.put(3, 3);                // evicts key 2
    cout << cache.get(2) << endl;   // -1
    cache.put(4, 4);                // evicts key 1
    cout << cache.get(1) << endl;   // -1
    cout << cache.get(3) << endl;   // 3
    cout << cache.get(4) << endl;   // 4

    return 0;
}

/*
Key Insights:
- LRU eviction is always at tail->prev (least recently used node).
- Always move accessed nodes to front.
- Doubly linked list + hashmap = O(1) get and put.
- Dummy nodes are crucial to simplify edge cases.
- Never skip updating both prev and next; it breaks the list.
- Memory management: delete evicted nodes.

Similar Questions & Approaches:
1. LFU Cache - requires frequency-based ordering.
2. Design a cache system for file systems - uses map + linked list or heap.
3. Rolling Hash LRU problems in competitive programming.

*/
