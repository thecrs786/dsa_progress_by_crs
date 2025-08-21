/*
────────────────────────────────────────────
📚 STACK (STL): COMPLETE REFERENCE
────────────────────────────────────────────

🔹 What is a Stack?
- Stack is a **LIFO (Last-In First-Out)** data structure.
- The most recent element added is the first to be removed.
- **Only the top element** is accessible — no random access.
- Internally implemented using `deque` by default.
- No iterators, no indexing.
- Useful in: DFS, function calls, expression evaluation, undo operations, etc.

────────────────────────────────────────────
📌 STACK METHODS SUMMARY
────────────────────────────────────────────

| Method         | Description                                  | Index | Iterator | Single/Multiple | Time Complexity |
|----------------|----------------------------------------------|--------|----------|------------------|------------------|
| push(x)        | Push element on top                          | ❌     | ❌       | Single           | O(1)              |
| emplace(x)     | Construct and insert element on top          | ❌     | ❌       | Single           | O(1)              |
| pop()          | Remove the top element                       | ❌     | ❌       | Single           | O(1)              |
| top()          | Access the top element                       | ❌     | ❌       | Single           | O(1)              |
| empty()        | Returns true if stack is empty               | ❌     | ❌       | Single           | O(1)              |
| size()         | Returns number of elements                   | ❌     | ❌       | Single           | O(1)              |
| swap(stack)    | Swaps contents with another stack            | ❌     | ❌       | Multiple         | O(1)              |

────────────────────────────────────────────
🔧 STACK USAGE EXAMPLES
────────────────────────────────────────────
*/

#include<iostream>
#include<vector>
#include<stack>
#include<algorithm> // for reverse()
using namespace std;

int main(){
    // ───────────────────────────────────────────────
    // ✅ INITIALIZATION METHODS
    // ───────────────────────────────────────────────

    stack<int> s1;  // Empty stack
    stack<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);

    stack<int> s3 = s2;  // Copy constructor

    stack<int> s4;
    s4.swap(s2);  // Swaps contents of s2 and s4


    // ───────────────────────────────────────────────
    // ✅ ADD ELEMENTS: push(), emplace()
    // ───────────────────────────────────────────────
    stack<int> st;
    st.push(10);       // Adds 10 at top
    st.push(20);
    st.emplace(30);    // Emplace is same as push for ints

    cout << "Top after pushes: " << st.top() << endl; // 30


    // ───────────────────────────────────────────────
    // ✅ ACCESS ELEMENT: top()
    // ───────────────────────────────────────────────
    cout << "Access top: " << st.top() << endl; // 30


    // ───────────────────────────────────────────────
    // ✅ REMOVE ELEMENT: pop()
    // ───────────────────────────────────────────────
    st.pop();  // Removes 30
    cout << "Top after pop: " << st.top() << endl; // 20


    // ───────────────────────────────────────────────
    // ✅ CHECK EMPTY: empty() + boolalpha
    // ───────────────────────────────────────────────
    // By default, cout prints bools as 1/0
    // Use boolalpha to print "true" or "false"

    cout << "Is stack empty? " << (st.empty() ? true : false) << endl; // prints 0
    
    cout << boolalpha;  // Enables printing bools as "true"/"false"
    cout << "Is stack empty (boolalpha)? " << st.empty() << endl; // prints false

    // Once boolalpha is enabled, all future bools will print as text
    // Use noboolalpha to revert back to 1/0 if needed


    // ───────────────────────────────────────────────
    // ✅ SIZE OF STACK: size()
    // ───────────────────────────────────────────────
    cout << "Stack size: " << st.size() << endl; // 2


    // ───────────────────────────────────────────────
    // ✅ SWAP STACKS: swap()
    // ───────────────────────────────────────────────
    stack<int> s5;
    s5.push(100);
    s5.push(200);

    cout << "Top of s5 before swap: " << s5.top() << endl; // 200
    cout << "Top of st before swap: " << st.top() << endl; // 20

    swap(s5, st);

    cout << "Top of s5 after swap: " << s5.top() << endl; // 20
    cout << "Top of st after swap: " << st.top() << endl; // 200


    // ───────────────────────────────────────────────
    // ✅ THREE WAYS TO PRINT STACK
    // ───────────────────────────────────────────────

    // 1️⃣ Print by popping (destroys stack)
    stack<int> print1 = st;  // create a copy to preserve original
    cout << "Stack (top to bottom by pop): ";
    while (!print1.empty()) {
        cout << print1.top() << " ";
        print1.pop();
    }
    cout << endl;

    // 2️⃣ Copy and print (preserves original)
    stack<int> print2 = st;
    cout << "Stack printed via copy: ";
    while (!print2.empty()) {
        cout << print2.top() << " ";
        print2.pop();
    }
    cout << endl;

    // 3️⃣ Transfer to vector and reverse (prints in push-order)
    stack<int> print3 = st;
    vector<int> v;
    while (!print3.empty()) {
        v.push_back(print3.top());
        print3.pop();
    }
    reverse(v.begin(), v.end());
    cout << "Stack in push order (bottom to top): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    return 0;
}
