#include <iostream>
#include <stack>
using namespace std;

/*
LeetCode 232: Implement Queue using Stacks

Problem in brief:
-----------------
Implement a first-in-first-out (FIFO) queue using only two standard stacks.
You need to implement the following operations of a queue:
- push(x) -- Push element x to the back of the queue.
- pop() -- Removes the element from the front of the queue and returns it.
- peek() -- Get the front element.
- empty() -- Return whether the queue is empty.

Example:
--------
Input:
MyQueue* obj = new MyQueue();
obj->push(1);
obj->push(2);
int front = obj->peek(); // returns 1
int popped = obj->pop(); // returns 1
bool isEmpty = obj->empty(); // returns false

Constraints:
-------------
- You may only use standard operations of a stack: push to top, peek/pop from top, size, and is empty.
- All operations are valid.

Solution Approach:
------------------
Method Name: Push-heavy two-stack implementation
- We maintain two stacks: s (main stack) and helper (temporary stack).
- push(x): O(n)
  - Move all elements from s to helper.
  - Push x into s.
  - Move all elements back from helper to s.
  - This ensures the **front of the queue is always at the top of s**, simulating queue behavior.
- pop(): O(1)
  - Remove s.top() since it holds the front element.
- peek(): O(1)
  - Return s.top() without removing it.
- empty(): O(1)
  - Return s.empty().

Time Complexity:
----------------
- push(): O(n)
- pop(): O(1)
- peek(): O(1)
- empty(): O(1)

Space Complexity:
-----------------
- O(n) for storing n elements in s and helper (temporarily).

Optimality:
------------
- This is one of the **two standard most optimized two-stack implementations**.
- Push-heavy approach favors O(1) pop/peek at the cost of push.
- Will be accepted by LeetCode; no TLE or MLE for reasonable constraints.

*/

class MyQueue {
public:
    stack<int> s;       // main stack storing elements in "queue order" (top = front)
    stack<int> helper;  // helper stack for rearranging elements during push

    // Constructor
    MyQueue() {
        // stacks are automatically initialized empty
    }
    
    // Push element x to the back of queue (push-heavy approach)
    void push(int x) {
        // Step 1: Move all elements from s to helper
        while(!s.empty()){
            helper.push(s.top()); // transfer older elements
            s.pop();              // remove from main stack
        }

        // Step 2: Push new element x into s
        s.push(x); // this element will be at bottom if we visualize, but top of stack represents front

        // Step 3: Move all elements back from helper to s
        while(!helper.empty()){
            s.push(helper.top()); // restore older elements on top of new element
            helper.pop();
        }
    }
    
    // Removes the element from front of queue and returns it
    int pop() {
        // s.top() always contains the front element due to push-heavy reordering
        int x = s.top();
        s.pop(); // remove it
        return x; // return the popped element
    }
    
    // Get the front element
    int peek() {
        return s.top(); // s.top() always holds the front
    }
    
    // Return whether the queue is empty
    bool empty() {
        return s.empty();
    }
};

/*
Logic & Explanation:
--------------------
1. Why we use two stacks:
   - s stores elements in "queue order" (top = front of queue). 
   - helper temporarily holds elements to rearrange them so that newly pushed element is at the bottom of s.
2. How push achieves FIFO:
   - Move all elements to helper -> s is empty.
   - Push new element -> becomes bottom if visualized as queue, but top of s holds front logically.
   - Move back older elements from helper -> they go on top of new element.
   - This ensures s.top() always contains the front of the queue.
3. How pop works:
   - Simply remove s.top() since it represents front of queue.
4. How peek works:
   - s.top() always points to front due to push arrangement.
5. How empty works:
   - Just check if s is empty.
6. Key insights:
   - Only push is O(n); pop/peek are O(1).
   - Push-heavy approach; alternative is pop-heavy.
   - Using helper avoids complicated rotations inside a single stack.
7. Important warnings:
   - stack::pop() returns void; must use top() first to get value.
   - while(!helper.empty()), not while(helper.empty()).
*/

int main() {
    // Example usage and testing
    MyQueue* obj = new MyQueue();

    obj->push(10);
    obj->push(20);
    obj->push(30);

    cout << "Front element: " << obj->peek() << endl; // Expected: 10
    cout << "Popped element: " << obj->pop() << endl; // Expected: 10
    cout << "Front element now: " << obj->peek() << endl; // Expected: 20
    cout << "Is empty? " << (obj->empty() ? "Yes" : "No") << endl; // Expected: No

    obj->pop();
    obj->pop();
    cout << "Is empty after popping all? " << (obj->empty() ? "Yes" : "No") << endl; // Expected: Yes

    return 0;
}

/*
Key Insights, Warnings & Similar Questions:
-------------------------------------------
1. Key Insights:
   - s.top() always stores the front element due to push-heavy reordering.
   - helper stack is only temporary during push; after push, helper is empty.
   - FIFO behavior achieved on top of LIFO container by moving older elements on top after pushing new one.
2. Warnings:
   - Do not forget to use !helper.empty() in while loop.
   - stack::pop() returns void; must retrieve top() first.
3. Similar Questions & Approaches:
   - LeetCode 225: Implement Stack using Queues (inverse problem)
   - Single-stack queue implementation: push O(n), pop/peek O(1)
   - Pop-heavy approach with two stacks: push O(1), pop/peek O(n)
   - Can be generalized to other FIFO implementations using LIFO containers
*/
