/*
QUEUE IMPLEMENTATION USING LINKED LIST

Already covered STL Queue (113)

This program demonstrates how to implement a queue data structure using a singly linked list.

Key points about queue:
- Queue is a linear data structure that follows the FIFO (First-In-First-Out) principle.
- Insertions happen at the rear (tail) and deletions happen from the front (head).
- Using linked list avoids the fixed size limitation of array-based queues.
- Operations like push, pop, front, back, empty, and size are implemented in constant time O(1).

--- METHODS LIST ---
1. push(int data)
   - Description: Adds an element at the tail of the queue.
   - Uses single value.
   - Does not use iterator or index.
   - Time Complexity: O(1)

2. pop()
   - Description: Removes an element from the head of the queue.
   - Alters multiple values (head pointer, possibly tail pointer).
   - Does not use iterator or index.
   - Time Complexity: O(1)

3. front()
   - Description: Returns the value at the front of the queue.
   - Uses single value.
   - Does not use iterator or index.
   - Time Complexity: O(1)

4. back()
   - Description: Returns the value at the rear (tail) of the queue.
   - Uses single value.
   - Does not use iterator or index.
   - Time Complexity: O(1)

5. empty()
   - Description: Checks whether the queue is empty.
   - Uses single value.
   - Does not use iterator or index.
   - Time Complexity: O(1)

6. getSize()
   - Description: Returns the current number of elements in the queue.
   - Uses single value.
   - Does not use iterator or index.
   - Time Complexity: O(1)

7. display()
   - Description: Prints all elements from front to rear.
   - Uses multiple values while traversing the linked list.
   - Uses iterator-like traversal (via while loop and pointer).
   - Does not use index.
   - Time Complexity: O(n), where n is the number of elements in the queue.

--- IMPORTANT DETAILS ---
✔ Handles empty queue cases gracefully in pop(), front(), and back().
✔ Resets tail when the queue becomes empty.
✔ Uses dynamic memory allocation for nodes.
✔ Avoids fixed-size limitation of array-based queues.
✔ Constant time operations due to head/tail pointers for most methods.
✔ Key insight: A linked list-based queue is more flexible in memory usage than arrays.

*/

#include <iostream>
using namespace std;

// Node structure for the linked list
class Node {
public:
    int data;      // Stores the value of the node
    Node* next;    // Pointer to the next node

    Node(int val) {
        data = val;  // Initialize the data
        next = NULL; // Initialize next to NULL
    }
};

// Queue implemented using linked list
class Queue {
    Node* head;    // Pointer to the front of the queue
    Node* tail;    // Pointer to the rear of the queue
    int size;      // Tracks the number of elements in the queue

public:
    // Constructor: Initializes an empty queue
    Queue() {
        head = tail = NULL;
        size = 0;
    }

    // Push operation: Insert data at the tail of the queue
    void push(int data) {
        Node* newNode = new Node(data); // Create a new node

        if(head == NULL) {
            // Queue is empty, both head and tail point to the new node
            head = tail = newNode;
        } else {
            // Queue is not empty, append at the tail
            tail->next = newNode; // Link current tail to new node
            tail = newNode;       // Update tail pointer
        }
        size++; // Increase size counter
    }

    // Pop operation: Remove the front element from the queue
    void pop() {
        if(head == NULL) {
            // Queue is empty, cannot pop
            cout << "Error: Queue is already empty" << endl;
        } else {
            Node* temp = head;    // Store current head for deletion
            head = head->next;   // Move head to next node
            if(head == NULL) {
                // If queue becomes empty after popping, reset tail
                tail = NULL;
            }
            delete temp; // Free memory of removed node
            size--;      // Decrement size counter
        }
    }

    // Front operation: Return the value at the front of the queue
    int front() {
        if(head == NULL) {
            // Queue is empty, print error and return invalid value
            cout << "Error: Queue is empty" << endl;
            return -1;
        } else {
            return head->data; // Return front element
        }
    }

    // Back operation: Return the value at the rear of the queue
    int back() {
        if(tail == NULL) {
            // Queue is empty, print error and return invalid value
            cout << "Error: Queue is empty" << endl;
            return -1;
        } else {
            return tail->data; // Return rear element
        }
    }

    // Empty operation: Check if the queue is empty
    bool empty() {
        return head == NULL;
    }

    // Size operation: Return the number of elements in the queue
    int getSize() {
        return size;
    }

    // Display operation: Prints all elements in the queue from front to rear
    void display() {
        if(head == NULL) {
            cout << "Queue is empty" << endl;
        } else {
            cout << "Queue (front -> rear): ";
            Node* current = head;
            while(current != NULL) {
                cout << current->data << " "; // Print data
                current = current->next;      // Move to next node
            }
            cout << endl;
        }
    }
    ~Queue() {
    // Loop through the linked list and delete all nodes
    while(head != NULL) {
        Node* temp = head;  // Store current head
        head = head->next;  // Move head to next node
        delete temp;        // Delete previous head
    }
    tail = NULL;           // Ensure tail pointer is null
    size = 0;              // Reset size
}

};

// Main function to demonstrate queue operations
int main() {
    Queue q; // Create an empty queue

    cout << "Initially, is queue empty? " << (q.empty() ? "Yes" : "No") << endl;

    // Push elements into the queue
    cout << "\nPushing elements into queue..." << endl;
    q.push(10); // Insert 10
    q.push(20); // Insert 20
    q.push(30); // Insert 30
    q.push(40); // Insert 40

    // Display queue after insertions
    q.display();

    // Access front element
    cout << "\nFront element: " << q.front() << endl;

    // Access back element
    cout << "Back element: " << q.back() << endl;

    // Check size
    cout << "Queue size: " << q.getSize() << endl;

    // Pop elements from queue
    cout << "\nPopping elements from queue..." << endl;
    q.pop(); // Removes 10
    q.display(); // Check current queue
    cout << "Front element after pop: " << q.front() << endl;
    cout << "Back element after pop: " << q.back() << endl;
    cout << "Queue size after pop: " << q.getSize() << endl;

    // Demonstrate popping all elements and accessing back element
    q.pop(); // Removes 20
    q.pop(); // Removes 30
    q.pop(); // Removes 40

    cout << "\nAfter popping all elements:" << endl;
    q.display();
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;
    cout << "Queue size: " << q.getSize() << endl;

    // Accessing back element when queue is empty
    cout << "\nTrying to access back of empty queue..." << endl;
    q.back(); // Should show error

    return 0;
}
