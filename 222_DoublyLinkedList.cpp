/*
    Doubly Linked List (DLL) - Introduction

    1. Definition:
       - A Doubly Linked List is a type of linked list in which each node contains:
            a) Data (the value it stores)
            b) A pointer to the previous node (prev)
            c) A pointer to the next node (next)
       - Unlike a singly linked list, nodes can be traversed in both directions.

    2. Structure of a Node:
       class Node {
           int val;
           Node* next; // Pointer to the next node
           Node* prev; // Pointer to the previous node
       };

    3. Characteristics:
       - Bi-directional traversal: head -> tail and tail -> head
       - Dynamic size: memory allocated as needed
       - Insertions and deletions can be done efficiently at both ends (O(1) if head/tail pointers are maintained)
       - Requires extra memory per node for the prev pointer

    4. Advantages over Singly Linked List:
       - Easy backward traversal
       - Easier deletion of a given node without needing to traverse from head
       - Supports complex data structures like deques and some types of LRU caches

    5. Disadvantages:
       - Slightly more memory usage (prev pointer)
       - More pointer manipulation required during insertions/deletions

    6. Typical Operations:
       - push_front(val): Insert at the beginning
       - push_back(val): Insert at the end
       - pop_front(): Delete from the beginning
       - pop_back(): Delete from the end
       - insert_after(node, val): Insert after a given node
       - delete_node(node): Delete a specific node
*/


#include <iostream>
using namespace std;

// Node class represents a single node in a doubly linked list
class Node {
public:
    int val;      // data stored in the node
    Node* next;   // pointer to next node
    Node* prev;   // pointer to previous node

    // Constructor: initializes a node with given data
    Node(int data) {
        val = data;      // set value
        next = NULL;     // initially, no next node
        prev = NULL;     // initially, no previous node
    }
};

// Doubly linked list class
class List {
    Node* head;  // pointer to the first node of the list
    Node* tail;  // pointer to the last node of the list
    int size;    // number of nodes in the list

public:
    // Constructor: initializes an empty list
    List() {
        head = tail = NULL; // empty list has no head or tail
        size = 0;           // size is 0
    }

    // Print the list from head to tail
    void print() {
        Node* temp = head;           // temp pointer to traverse without moving head
        if (head == NULL) {          // check for empty list
            cout << "[Empty]" << endl;
            return;
        }
        cout << "[";                 // start display
        while (temp != NULL) {       // traverse until end
            cout << temp->val;       // print current node value
            temp = temp->next;       // move to next node
            if (temp != NULL)
                cout << " -> ";      // print arrow if not last node
            else
                cout << "]" << endl; // close bracket at end
        }
    }

    // PUSH_FRONT
    // Insert a node at the front of the list

    void push_front(int val) {
        Node* newNode = new Node(val); // create new node

        if (head == NULL) {            // if list is empty
            head = tail = newNode;     // head and tail point to new node
            size++;                    // increment size
            return;                    // return as insertion is done
        }

        // If list is non-empty
        newNode->next = head;          // new node points to current head
        head->prev = newNode;          // current head's prev points back to new node
        head = newNode;                // update head to new node
        size++;                        // increment size
    }
    
    // PUSH_BACK
    // Insert a node at the end of the list

    void push_back(int val) {
        Node* newNode = new Node(val); // create new node

        if (head == NULL) {            // if list is empty
            head = tail = newNode;     // head and tail point to new node
            size++;                    // increment size
            return;
        }

        // If list is non-empty
        tail->next = newNode;          // old tail points to new node
        newNode->prev = tail;          // new node points back to old tail
        tail = newNode;                // update tail to new node
        size++;                        // increment size
    }
    
    // POP_FRONT
    // Remove a node from the front of the list

    void pop_front() {
        if (head != NULL) {            // check if list is non-empty
            Node* temp = head;         // store old head for deletion

            if (head == tail) {        // single-node case
                head = tail = NULL;    // list becomes empty
            } else {                   // multiple nodes
                head = head->next;     // move head forward
                head->prev = NULL;     // new head's prev becomes NULL
              // temp->next = NULL  optional because we're deleteing temp anyway  
            }

            delete temp;               // free memory of removed node
            size--;                    // decrement size
        } else {
            cout << "Error: List is already empty" << endl;
        }
    }
    
    // POP_BACK
    // Remove a node from the end of the list

    void pop_back() {
        if (head != NULL) {            // check if list is non-empty
            Node* temp = tail;         // store old tail for deletion

            if (head == tail) {        // single-node case
                head = tail = NULL;    // list becomes empty
            } else {                   // multiple nodes
                tail = tail->prev;     // move tail backward
                tail->next = NULL;     // new tail's next becomes NULL
              // temp->next = NULL  optional because we're deleteing temp anyway  
            }

            delete temp;               // free memory of removed node
            size--;                    // decrement size
        } else {
            cout << "Error: List is already empty" << endl;
        }
    }

    // Return the current size of the list
    int get_size() {
        return size;
    }
};

/*
Summary of how the doubly linked list works:

- Each node contains a value, a pointer to the next node, and a pointer to the previous node.
- The List class maintains head (first node), tail (last node), and size.
- push_front inserts a node at the beginning; push_back inserts at the end.
- pop_front removes from the beginning; pop_back removes from the end.
- All operations update head, tail, prev/next pointers correctly to maintain list integrity.
- Memory is explicitly freed using delete to prevent leaks.
- print() traverses from head to tail and displays values neatly.
*/

int main() {
    List l;                        // create empty list

    cout << "Initial list: ";
    l.print();                     // [Empty]

    // Testing push_back
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    cout << "After push_back 1,2,3: ";
    l.print();                     // [1 -> 2 -> 3]

    // Testing push_front
    l.push_front(0);
    cout << "After push_front 0: ";
    l.print();                     // [0 -> 1 -> 2 -> 3]

    // Testing pop_front
    l.pop_front();
    cout << "After pop_front: ";
    l.print();                     // [1 -> 2 -> 3]

    // Testing pop_back
    l.pop_back();
    cout << "After pop_back: ";
    l.print();                     // [1 -> 2]

    // Testing get_size
    cout << "Current size: " << l.get_size() << endl; // 2

    // Testing pop until empty
    l.pop_back();
    l.pop_front();
    cout << "After removing all elements: ";
    l.print();                     // [Empty]

    // Testing pop on empty list
    l.pop_back();                   // Error message
    l.pop_front();                  // Error message

    return 0;
}
