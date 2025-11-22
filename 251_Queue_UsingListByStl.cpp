// QUEUE using LINKED LIST
// Already covered STL QUEUE (113)

#include<iostream>  // For input/output operations
#include<list>      // For using std::list as the underlying container
using namespace std;

/*
==========================
LIST OF METHODS USED IN THIS QUEUE IMPLEMENTATION
==========================

1. push_back(val)
   - Adds 'val' at the end of the list.
   - Uses value only; no iterator or index required.
   - Time complexity: O(1)

2. pop_front()
   - Removes the first element.
   - Uses no iterator or index.
   - Time complexity: O(1)

3. empty()
   - Checks if the queue is empty.
   - Uses no iterator or index.
   - Time complexity: O(1)

4. size()
   - Returns the number of elements.
   - Uses no iterator or index.
   - Time complexity: O(1)

5. front()
   - Accesses the first element.
   - Uses no iterator or index.
   - Time complexity: O(1)

6. back()
   - Accesses the last element.
   - Uses no iterator or index.
   - Time complexity: O(1)

7. begin(), end()
   - Provides iterators to traverse the list.
   - Used in the 'display()' method.
   - Time complexity: O(1) to get iterator, O(n) to traverse.

8. push_front(val) [variation]
   - Adds 'val' at the beginning.
   - Time complexity: O(1)

9. pop_back() [variation]
   - Removes the last element.
   - Time complexity: O(1)

10. erase(iterator) [variation]
    - Removes the element at the given iterator position.
    - Requires iterator.
    - Time complexity: O(1)

11. insert(iterator, val) [variation]
    - Inserts 'val' at a specific position.
    - Requires iterator.
    - Time complexity: O(1)

12. clear() [variation]
    - Clears all elements.
    - Time complexity: O(n)

IMPORTANT DETAILS:
- std::list is implemented as a doubly linked list.
- Supports efficient insertion/removal at both ends.
- Does not support direct indexing; traversals need iterators.
- Modifications can be safely done using iterators except where invalidated.
- Good for queue, deque, and other similar structures where order is important.

KEY INSIGHTS:
- Use when you need frequent additions/removals at ends.
- Avoid when you need random access by index.
- Iterators are crucial for advanced manipulations.
- Queue operations like enqueue/dequeue are O(1).
*/

class Queue {
    list<int> ll; // Internal container using std::list to hold queue elements

public:
    // Adds an element at the back of the queue
    void push(int val) {
        ll.push_back(val); // Append 'val' at the end
    }

    // Removes the front element from the queue
    void pop() {
        if(ll.empty()) { // Check if queue is empty before removing
            cout << "Error : Queue is already empty" << endl; // Show error message
        } else {
            ll.pop_front(); // Remove the front element
        }
    }

    // Checks if the queue is empty
    bool empty() {
        return ll.empty(); // Return true if empty, false otherwise
    }

    // Returns the number of elements in the queue
    int size() {
        return ll.size(); // Return current size
    }

    // Returns the element at the front of the queue
    int front() {
        if(ll.empty()) { // Check if queue is empty before accessing
            cout << "Error : Queue is empty" << endl; // Show error message
            return -1; // Return dummy value
        } else {
            return ll.front(); // Return the front element
        }
    }

    // Returns the element at the back of the queue
    int back() {
        if(ll.empty()) { // Check if queue is empty before accessing
            cout << "Error : Queue is empty" << endl; // Show error message
            return -1; // Return dummy value
        } else {
            return ll.back(); // Return the last element
        }
    }

    // Displays all elements from front to back
    void display() {
        if(ll.empty()) { // Check if queue is empty before printing
            cout << "Queue is empty" << endl; // Show empty message
            return; // Exit the function
        }
        cout << "Queue (front->back): "; // Label to show order
        for(auto it = ll.begin(); it != ll.end(); ++it) { // Iterate from front to back
            cout << *it << " "; // Print each element
        }
        cout << endl; // Move to next line after printing
    }

    // Adds an element at the front (variation)
    void push_front(int val) {
        ll.push_front(val); // Insert 'val' at the beginning
    }

    // Removes the last element (variation)
    void pop_back() {
        if(ll.empty()) { // Check if queue is empty before removing
            cout << "Error : Queue is empty, can't pop_back" << endl; // Show error message
        } else {
            ll.pop_back(); // Remove the last element
        }
    }

    // Erases element at a specific index (variation)
    void erase_element_at(int index) {
        if(index < 0 || index >= ll.size()) { // Validate index
            cout << "Invalid index for erase" << endl; // Show error message
            return;
        }
        auto it = ll.begin(); // Get iterator at beginning
        advance(it, index); // Move iterator to desired position
        ll.erase(it); // Erase element at that position
    }

    // Inserts an element at a specific index (variation)
    void insert_at(int index, int val) {
        if(index < 0 || index > ll.size()) { // Validate index
            cout << "Invalid index for insert" << endl; // Show error message
            return;
        }
        auto it = ll.begin(); // Get iterator at beginning
        advance(it, index); // Move iterator to desired position
        ll.insert(it, val); // Insert 'val' at the position
    }

    // Clears the entire queue (variation)
    void clear() {
        ll.clear(); // Remove all elements
    }
};

int main() {
    // Initialization examples for list container
    cout << "Initialization Examples:" << endl;

    list<int> l1; // Empty list
    list<int> l2 = {1, 2, 3}; // List initialized with values
    list<int> l3(l2); // Copy of another list
    list<int> l4(3, 50); // List of 3 elements, each initialized to 50
    int arr[] = {4, 5, 6};
    list<int> l5(arr, arr + 3); // List initialized from an array

    // Print elements of list l2
    cout << "l2 elements: ";
    for(auto x : l2) cout << x << " ";
    cout << endl;

    // Print elements of list l3
    cout << "l3 elements (copy of l2): ";
    for(auto x : l3) cout << x << " ";
    cout << endl;

    // Print elements of list l4
    cout << "l4 elements (3 times 50): ";
    for(auto x : l4) cout << x << " ";
    cout << endl;

    // Print elements of list l5
    cout << "l5 elements (from array): ";
    for(auto x : l5) cout << x << " ";
    cout << endl << endl;

    // Queue implementation examples
    cout << "Queue Implementation Using Linked List:" << endl;
    Queue q; // Create queue object

    // Push elements into queue
    q.push(10); // Add 10 at the back
    q.push(20); // Add 20 at the back
    q.push(30); // Add 30 at the back

    cout << "After pushing 10, 20, 30:" << endl;
    q.display(); // Show queue contents

    // Access front and back elements
    cout << "Front element: " << q.front() << endl; // Should print 10
    cout << "Back element: " << q.back() << endl;   // Should print 30

    // Pop an element from the queue
    q.pop(); // Removes the front element (10)

    cout << "After popping one element:" << endl;
    q.display(); // Show queue contents

    // Check if queue is empty and print size
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl; // Should print No
    cout << "Queue size: " << q.size() << endl; // Should print 2

    // Pop all elements to make queue empty
    q.pop(); // Removes 20
    q.pop(); // Removes 30

    cout << "After popping all elements:" << endl;
    q.display(); // Should show empty queue

    // Attempt to pop from empty queue
    q.pop(); // Should show error message

    // Push into empty queue
    q.push(100); // Add 100 to queue
    cout << "After pushing 100:" << endl;
    q.display(); // Show queue contents

    // Using additional variation methods
    cout << endl << "Using Variations:" << endl;

    // Insert at front
    q.push_front(50); // Insert 50 at front
    cout << "After push_front(50):" << endl;
    q.display();

    // Insert at back
    q.push(200); // Insert 200 at back
    cout << "After push(200):" << endl;
    q.display();

    // Remove from back
    q.pop_back(); // Removes last element (200)
    cout << "After pop_back():" << endl;
    q.display();

    // Insert at specific index
    q.insert_at(1, 150); // Inserts 150 at index 1
    cout << "After insert_at(1, 150):" << endl;
    q.display();

    // Erase element at specific index
    q.erase_element_at(1); // Removes element at index 1
    cout << "After erase_element_at(1):" << endl;
    q.display();

    // Clear the queue
    cout << "Queue size before clear: " << q.size() << endl;
    q.clear(); // Removes all elements
    cout << "After clear():" << endl;
    q.display(); // Should show empty queue
    cout << "Queue size after clear: " << q.size() << endl; // Should print 0

    return 0;
}
