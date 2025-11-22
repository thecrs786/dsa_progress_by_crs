#include <iostream>
#include <queue>
using namespace std;

/*
LeetCode 225: Implement Stack using Queues

Problem in brief:
-----------------
Implement a last-in-first-out (LIFO) stack using only two standard queues.
You need to implement the following operations of a stack:
- push(x) -- Push element x onto stack.
- pop() -- Removes the element on top of the stack and returns it.
- top() -- Get the top element.
- empty() -- Return whether the stack is empty.

Example:
--------
Input:
MyStack* obj = new MyStack();
obj->push(1);
obj->push(2);
int topElement = obj->top(); // returns 2
int poppedElement = obj->pop(); // returns 2
bool isEmpty = obj->empty(); // returns false

Constraints:
-------------
- You may only use standard operations of a queue: push to back, peek/pop from front, size, and is empty.
- You can assume all operations are valid.

Solution Approach:
------------------
Method Name: Push-heavy two-queue implementation
- We maintain two queues: q (main queue) and helper (temporary queue).
- push(x): O(n)
  - Move all elements from q to helper.
  - Push x into q.
  - Move all elements back from helper to q.
  - This ensures the **last pushed element is always at the front of q**, simulating stack behavior.
- pop(): O(1)
  - Remove q.front() since it holds the most recently pushed element.
- top(): O(1)
  - Return q.front() without removing it.
- empty(): O(1)
  - Return q.empty().

Time Complexity:
----------------
- push(): O(n)
- pop(): O(1)
- top(): O(1)
- empty(): O(1)

Space Complexity:
-----------------
- O(n) for storing n elements in q and helper (temporarily).

Optimality:
------------
- This is one of the **two standard most optimized two-queue implementations**.
- Push-heavy approach favors O(1) pop/top at the cost of push.
- Will be accepted by LeetCode; no TLE or MLE for reasonable constraints.

*/

class MyStack {
public:
    queue<int> q;      // main queue storing elements in "stack order" (front = top)
    queue<int> helper; // helper queue for rearranging elements during push

    // Constructor
    MyStack() {
        // queues are automatically initialized empty
    }
    
    // Push element x onto stack (push-heavy approach)
    void push(int x) {
        // Step 1: Move all existing elements from q to helper
        while(!q.empty()){
            helper.push(q.front()); // transfer oldest elements
            q.pop();                // remove from main queue
        }

        // Step 2: Push new element x into q
        q.push(x); // this element will be at the front of q, representing "top of stack"

        // Step 3: Move all elements back from helper to q
        while(!helper.empty()){
            q.push(helper.front()); // restore older elements behind the new element
            helper.pop();
        }
    }
    
    // Removes the element on top of the stack and returns it
    int pop() {
        // q.front() always contains the last inserted element due to push rearrangement
        int x = q.front(); 
        q.pop(); // remove it
        return x; // return the popped element
    }
    
    // Get the top element
    int top() {
        // q.front() holds the top element
        return q.front();
    }
    
    // Return whether the stack is empty
    bool empty() {
        return q.empty();
    }
};

/*
Logic & Explanation:
--------------------
1. Why we use two queues:
   - q holds elements in "stack order" (front = top). 
   - helper temporarily holds elements to rearrange them so that the newly pushed element is always at the front.
2. How push achieves LIFO:
   - Move all elements to helper -> q is empty.
   - Push new element -> becomes front of q.
   - Move back older elements from helper -> they go behind the new element.
   - This ensures that q.front() always contains the most recent element.
3. How pop works:
   - Simply remove q.front() since it represents top of stack.
4. How top works:
   - q.front() always points to top due to push arrangement.
5. Why this simulates a stack using FIFO queues:
   - By moving all older elements behind the new one on every push, we maintain LIFO order.
6. Key insights:
   - Only push is O(n); other operations are O(1).
   - This is push-heavy; alternative is pop-heavy.
   - Using helper avoids complicated rotations inside a single queue.
7. Important warnings:
   - Do NOT use q.pop() directly to return a value — queue::pop() returns void.
   - Always fetch value with q.front() first.
*/

int main() {
    // Example usage and testing
    MyStack* obj = new MyStack();

    obj->push(1);
    obj->push(2);
    obj->push(3);

    cout << "Top element: " << obj->top() << endl; // Expected: 3
    cout << "Popped element: " << obj->pop() << endl; // Expected: 3
    cout << "Top element now: " << obj->top() << endl; // Expected: 2
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
   - q.front() always stores the top element due to push-heavy reordering.
   - helper queue is only temporary to rearrange elements; after push, helper is empty.
   - LIFO behavior achieved on top of FIFO container by moving older elements behind new one.
2. Warnings:
   - Do not forget to use !helper.empty() in while loop, not helper.empty().
   - queue::pop() does not return value; must use front() first.
3. Similar Questions & Approaches:
   - LeetCode 232: Implement Queue using Stacks (inverse problem)
   - Single-queue stack implementation: push O(n), pop/top O(1)
   - Pop-heavy approach with two queues: push O(1), pop/top O(n)
   - Can be generalized to other LIFO implementations using other FIFO containers
*/
