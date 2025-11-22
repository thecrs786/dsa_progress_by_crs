#include <iostream>
using namespace std;

/*
CIRCULAR QUEUE IMPLEMENTATION USING DYNAMIC ARRAY
-------------------------------------------------
A circular queue is a linear data structure that follows FIFO (First-In-First-Out) principle but efficiently reuses empty spaces at the beginning of the array after elements are removed. This avoids the "wasting space" problem in a simple linear queue.

Key points:
- Uses a dynamically allocated array to store elements.
- Front (f) and Rear (r) pointers track the start and end positions.
- Modulo operator (%) is used to wrap around the array indices when reaching the end.
- All operations (push, pop, front, back, empty, size) are O(1).
- Dynamic memory allows specifying capacity at runtime.

--- METHODS LIST ---
1. push(int val)
   - Adds an element to the rear.
   - Uses index manipulation (+1 and % capacity).
   - Does not use iterators.
   - Time Complexity: O(1)
   - Space: O(1)

2. pop()
   - Removes element from the front.
   - Uses index manipulation (+1 and % capacity).
   - Time Complexity: O(1)

3. front()
   - Returns element at the front.
   - Uses index access.
   - Time Complexity: O(1)

4. back()
   - Returns element at the rear.
   - Uses index access.
   - Time Complexity: O(1)

5. empty()
   - Checks if the queue is empty.
   - Returns a boolean.
   - Time Complexity: O(1)

6. getsize()
   - Returns current number of elements.
   - Time Complexity: O(1)

--- IMPORTANT DETAILS AND KEY INSIGHTS ---
✔ We dynamically created the array using `arr = new int[capacity];` which allocates contiguous memory on the heap for 'capacity' elements. The pointer `arr` points to the first element.
✔ Using `% capacity` ensures circular behavior. When rear or front reaches the end, it wraps back to index 0.
✔ Using `+1` in `(index + 1) % capacity` moves the index forward by one while respecting the circular nature.
✔ This implementation prevents overflow if elements are popped and added repeatedly.
✔ `currSize` is used to differentiate between full and empty states.
✔ Unlike linked list implementation, this uses contiguous memory (better cache locality).
✔ Destructor must free dynamic memory to prevent memory leaks.
*/

class Circularqueue{
    int* arr;       // Pointer to dynamically allocated array
    int capacity;   // Maximum capacity of queue
    int f, r;       // Indices for front and rear

    public:
    int currSize;   // Current number of elements in queue

    // Constructor: Initialize queue
    Circularqueue(int c){
        capacity = c;
        currSize = 0;
        arr = new int[capacity]; // created a dynamic array
        f = 0;
        r = -1;
    }

    // Push method: Add element at rear
    void push(int val){
        if(currSize==capacity){
            cout<<"Error : Circular Queue is full"<<endl;
            return;
        }

        r = (r+1)%capacity;   // Move rear forward circularly
        arr[r] = val;         // Insert value at new rear
        currSize++;           // Increment size
    }

    // Pop method: Remove element from front
    void pop(){
        if(currSize==0){
            cout<<"Error : Circular Queue is already empty"<<endl;
            return;
        }

        f = (f+1)%capacity;   // Move front forward circularly
        currSize--;           // Decrement size
    }

    // Front method: Access element at front
    int front(){
        if(currSize==0){
            cout<<"Error : Circular Queue is empty"<<endl;
            return -1;
        }
        return arr[f];        // Return element at front
    }

    // Back method: Access element at rear
    int back(){
        if(currSize==0){
            cout<<"Error : Circular Queue is empty"<<endl;
            return -1;
        }
        return arr[r];        // Return element at rear
    }

    // Empty method: Check if queue is empty
    bool empty(){
        return currSize==0;   // True if no elements
    }

    // Get size method
    int getsize(){
        return currSize;      // Return current number of elements
    }

    // Destructor: Free dynamic memory
    ~Circularqueue(){
        delete[] arr;         // Prevent memory leak
    }
};

int main(){
    // Create a circular queue with capacity 5
    Circularqueue cq(5);

    // Push elements
    cq.push(10);
    cq.push(20);
    cq.push(30);

    // Access front and back
    cout << "Front element: " << cq.front() << endl; // 10
    cout << "Back element: " << cq.back() << endl;   // 30

    // Pop one element
    cq.pop(); // Removes 10

    // Check front and back again
    cout << "Front after pop: " << cq.front() << endl; // 20
    cout << "Back after pop: " << cq.back() << endl;   // 30

    // Push more elements to demonstrate circular behavior
    cq.push(40);
    cq.push(50);

    // Back after pushing more elements
    cout << "Back after pushing 40 and 50: " << cq.back() << endl; // 50

    // Push to wrap around
    cq.push(60); // Rear wraps around to beginning
    cout << "Back after pushing 60 (wrap-around): " << cq.back() << endl; // 60

    return 0;
}
