/*

STACKS IN STL ALEADY DISCUSSED BEFORE (112_STL_Stack.cpp)

Stack in C++ (Using Vector)
---------------------------
A stack is a linear data structure which follows a Last In First Out (LIFO) principle. 
The last element added to the stack will be the first one to be removed.

Common operations:
1. push(x)  : Insert element x on top of the stack
2. pop()    : Remove the top element from the stack
3. top()    : Access the top element without removing it
4. empty()  : Check if the stack is empty
5. size()   : Get the number of elements in the stack

Example:
Stack: Top -> [3, 2, 1] Bottom
Operation: push(4)
Stack becomes: Top -> [4, 3, 2, 1] Bottom
Operation: pop()
Stack becomes: Top -> [3, 2, 1] Bottom
*/

#include <iostream>
#include <vector>
using namespace std;

class Stack {
    vector<int> v; // Internal container using vector

public:
    // Push element onto stack
    void push(int val){
        v.push_back(val); // Add element at the end (top of stack)
    }

    // Pop element from stack
    void pop(){
        if(v.empty()) 
            cout<<"Error : Stack is already empty"<<endl; // Cannot pop from empty stack
        else 
            v.pop_back(); // Remove last element (top)
    }

    // Return the top element
    int top(){
        if(!v.empty()){
            return v.back(); // Access the last element
        } else {
            cout<<"Error : Stack is empty"<<endl; // Warning for empty stack
            return -1; // Sentinel value indicating error
        }
    }

    // Check if stack is empty
    bool empty(){
        return v.empty(); // True if vector is empty
    }

    // Return size of stack (number of elements)
    int size(){
        return v.size();
    }

    // Display the stack elements (from top to bottom)
    void display(){
        if(v.empty()){
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top->bottom): ";
        for(int i=v.size()-1; i>=0; i--){
            cout << v[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    Stack s;

    // Example 1: Push elements onto stack
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

    return 0;
}

/*
Summary of Methods:
-------------------
1. push(val)    -> Adds element at top
2. pop()        -> Removes top element safely
3. top()        -> Returns top element, warns if empty
4. empty()      -> Returns true if stack is empty
5. size()       -> Returns number of elements
6. display()    -> Prints stack contents from top to bottom

Key Insights:
-------------
- Vector is used internally for dynamic resizing and efficient top access.
- Stack follows LIFO: last pushed, first popped.
- Sentinel values (-1) or messages help prevent undefined behavior on empty stack.
- display() helps visualize stack, important for debugging or learning.
*/
