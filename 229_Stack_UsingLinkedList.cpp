/*

STACKS IN STL ALEADY DISCUSSED BEFORE (112_STL_Stack.cpp)

Stack in C++ Using STL List
---------------------------
A stack is a linear data structure that follows the Last In First Out (LIFO) principle.
The last element inserted is the first to be removed.

Key Operations:
1. push(x)   : Insert element x on top of the stack
2. pop()     : Remove the top element
3. top()     : Access the top element
4. empty()   : Check if the stack is empty
5. size()    : Get number of elements
6. display() : Visualize stack elements

Example:
Initial Stack: empty
Operation: push(10) -> Stack: 10
Operation: push(20) -> Stack: 20->10
Operation: pop()     -> Stack: 10
Operation: top()     -> Returns 10
*/

#include <iostream>
#include <list>
using namespace std;

class Stack {
    list<int> ll; // Using STL list

public:
    // Push element onto stack
    void push(int val){
        ll.push_front(val); // Insert at front for O(1) top access
    }

    // Pop element from stack
    void pop(){
        if(ll.empty()){ // Check if stack is empty
            cout << "Error: Stack is already empty" << endl;
        } else {
            ll.pop_front(); // Remove top element
        }
    }

    // Return top element
    int top(){
        if(ll.empty()){ // Check if empty before accessing
            cout << "Error: Stack is empty" << endl;
            return -1; // Sentinel value
        } else {
            return ll.front(); // Return front element (top)
        }
    }

    // Check if stack is empty
    bool empty(){
        return ll.empty();
    }

    // Return size of stack
    int size(){
        return ll.size();
    }

    // Display stack elements from top to bottom
    void display(){
        if(ll.empty()){
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top->bottom): ";
        for(auto it = ll.begin(); it != ll.end(); ++it){
            cout << *it << " ";
        }
        cout << endl;
    }
};

int main(){
    Stack s;

    // Example 1: Push elements
    s.push(10); // Stack: 10
    s.push(20); // Stack: 20->10
    s.push(30); // Stack: 30->20->10
    s.display(); // Output: 30 20 10

    // Example 2: Access top element
    cout << "Top element: " << s.top() << endl; // 30

    // Example 3: Pop top element
    s.pop(); // Removes 30, Stack: 20->10
    s.display(); // Output: 20 10

    // Example 4: Check if stack is empty
    cout << "Is stack empty? " << (s.empty() ? "Yes" : "No") << endl; // No

    // Example 5: Get stack size
    cout << "Stack size: " << s.size() << endl; // 2

    // Example 6: Pop all elements
    s.pop(); // Removes 20
    s.pop(); // Removes 10
    s.display(); // Output: Stack is empty

    // Example 7: Pop from empty stack
    s.pop(); // Error message

    // Example 8: Access top of empty stack
    cout << "Top element: " << s.top() << endl; // Error + -1

    // Example 9: Push again after emptying
    s.push(50);
    s.display(); // Output: 50

    return 0;
}

/*
Summary of Methods:
-------------------
1. push(val)    -> Adds element to top (front of list)
2. pop()        -> Removes top element safely with empty check
3. top()        -> Returns top element, warns if empty
4. empty()      -> Checks if stack is empty
5. size()       -> Returns number of elements
6. display()    -> Prints stack from top to bottom

Key Insights:
-------------
- Using STL list allows O(1) insertion/removal at front
- Always check for empty stack before pop/top
- Sentinel return values help avoid undefined behavior
- Display method visualizes stack for debugging and understanding
- LIFO principle maintained naturally by push_front/pop_front
- This stack works perfectly for integer data, but can be extended to templates for generic data types
*/
