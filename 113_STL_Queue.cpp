/*
────────────────────────────────────────────
📚 QUEUE (STL): COMPLETE REFERENCE
────────────────────────────────────────────

🔹 What is a Queue?
- Queue is a **FIFO** (First-In First-Out) data structure.
- Elements are added at the **back**, removed from the **front**.
- No indexing, no iterator-based traversal.
- Internally backed by `deque` in C++ STL.
- Useful in BFS, task scheduling, order processing, etc.

🔸 Access: Only front/back via `front()`, `back()`
🔸 Modification: Only through `push()`, `pop()`, and `swap()`
🔸 No random access. No iterators like in vector or list.

⚠️ Can't use range-based `for` loops or iterators directly.
To print or traverse, you must `pop()` or copy into another container.

────────────────────────────────────────────
📌 QUEUE METHODS SUMMARY + TIME COMPLEXITY
────────────────────────────────────────────

| Method         | Description                                     | Complexity | Notes                         |
|----------------|-------------------------------------------------|------------|-------------------------------|
| push(x)        | Push element at back                            | O(1)       | Adds at end                   |
| emplace(x)     | Construct element in-place at back              | O(1)       | Efficient for complex objects |
| pop()          | Remove front element                            | O(1)       | Removes from front            |
| front()        | Access front element                            | O(1)       | No removal                    |
| back()         | Access last (back) element                      | O(1)       | No removal                    |
| empty()        | Check if queue is empty                         | O(1)       | Returns bool                  |
| size()         | Number of elements in the queue                 | O(1)       | Returns int                   |
| swap(queue)    | Swap contents with another queue                | O(1)       | Swaps internals               |

────────────────────────────────────────────
🔧 IMPLEMENTATION WITH EXAMPLES
────────────────────────────────────────────
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm> // for reverse() if needed
using namespace std;

int main(){
    // ───────────────────────────────────────────────
    // ✅ INITIALIZATION METHODS
    // ───────────────────────────────────────────────

    queue<int> q1;  // Empty queue
    queue<int> q2;
    q2.push(1);
    q2.push(2);
    q2.push(3);

    queue<int> q3 = q2;  // Copy constructor
    queue<int> q4;
    q4.swap(q2);  // Swaps contents of q2 and q4


    // ───────────────────────────────────────────────
    // ✅ ADD ELEMENTS: push(), emplace()
    // ───────────────────────────────────────────────
    queue<int> q;
    q.push(10);       // Adds 10 at back
    q.push(20);
    q.emplace(30);    // Emplace is same as push for ints

    cout << "Back after pushes: " << q.back() << endl; // 30


    // ───────────────────────────────────────────────
    // ✅ ACCESS ELEMENTS: front(), back()
    // ───────────────────────────────────────────────
    cout << "Front: " << q.front() << endl; // 10
    cout << "Back: " << q.back() << endl;   // 30


    // ───────────────────────────────────────────────
    // ✅ REMOVE ELEMENT: pop()
    // ───────────────────────────────────────────────
    q.pop();  // Removes 10
    cout << "Front after pop: " << q.front() << endl; // 20


    // ───────────────────────────────────────────────
    // ✅ CHECK EMPTY: empty() + boolalpha
    // ───────────────────────────────────────────────
    // By default, cout prints bools as 1/0
    // Use boolalpha to print "true"/"false"

    cout << "Is queue empty? " << (q.empty() ? true : false) << endl; // prints 0
    
    cout << boolalpha;  // Enables printing bools as "true"/"false"
    cout << "Is queue empty (boolalpha)? " << q.empty() << endl; // prints false

    // Once boolalpha is enabled, all future bools will print as text
    // Use noboolalpha to revert back to 1/0 if needed


    // ───────────────────────────────────────────────
    // ✅ SIZE OF QUEUE: size()
    // ───────────────────────────────────────────────
    cout << "Queue size: " << q.size() << endl; // 2


    // ───────────────────────────────────────────────
    // ✅ SWAP QUEUES: swap()
    // ───────────────────────────────────────────────
    queue<int> q5;
    q5.push(100);
    q5.push(200);

    cout << "Front of q5 before swap: " << q5.front() << endl; // 100
    cout << "Front of q before swap: " << q.front() << endl;   // 20

    swap(q5, q);

    cout << "Front of q5 after swap: " << q5.front() << endl; // 20
    cout << "Front of q after swap: " << q.front() << endl;   // 100


    // ───────────────────────────────────────────────
    // ✅ THREE WAYS TO PRINT QUEUE
    // ───────────────────────────────────────────────

    // 1️⃣ Print by popping (destroys queue)
    queue<int> print1 = q;  // create a copy to preserve original
    cout << "Queue (front to back by pop): ";
    while (!print1.empty()) {
        cout << print1.front() << " ";
        print1.pop();
    }
    cout << endl;

    // 2️⃣ Copy and print (preserves original)
    queue<int> print2 = q;
    cout << "Queue printed via copy: ";
    while (!print2.empty()) {
        cout << print2.front() << " ";
        print2.pop();
    }
    cout << endl;

    // 3️⃣ Transfer to vector (preserves push order naturally)
    queue<int> print3 = q;
    vector<int> v;
    while (!print3.empty()) {
        v.push_back(print3.front());
        print3.pop();
    }
    cout << "Queue in push order (front to back): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    return 0;
}

/*
────────────────────────────────────────────
🔍 IMPORTANT NOTES
────────────────────────────────────────────
- STL `queue` is adapter over `deque`, not a standalone container.
- No indexing like q[0] — use front()/back().
- No iterator support — can’t use range-based for loop.
- boolalpha: modifies cout to show bools as true/false instead of 1/0.
────────────────────────────────────────────
*/
