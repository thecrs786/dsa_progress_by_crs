// Static Keyword in C++

/*
There are two main uses of the `static` keyword in C++:

1. Static Variables
2. Static Members (static objects/members in a class)
*/

#include <iostream>
using namespace std;

// 1. Static Variables in a function
void demoStaticVariable() {
    static int count = 0; // initialized only once
    count++;              // retains value across function calls
    cout << "Count = " << count << endl;
}

// 2. Static Members in a class
class Demo {
public:
    static int objectCount; // declared inside class, shared among all objects

    Demo() {
        objectCount++; // increment whenever object is created
    }

    static void showCount() { // static member function
        cout << "Object Count = " << objectCount << endl;
    }
};

// Static members must be defined outside the class
int Demo::objectCount = 0;

int main() {
    cout << "Function Static Variable Example:\n";
    demoStaticVariable(); // Count = 1
    demoStaticVariable(); // Count = 2
    demoStaticVariable(); // Count = 3

    cout << "\nStatic Member Example:\n";
    Demo d1;
    Demo d2;
    Demo d3;

    Demo::showCount(); // Object Count = 3

    return 0;
}

/*
Important Notes:

1. Static variables inside functions:
   - Initialized only once.
   - Lifetime = entire program execution.
   - Scope = local to function.
   - Stored in data segment (not stack).

2. Static class members:
   - Shared among all objects.
   - Only one copy exists.
   - Can be accessed using class name or object.
   - Static member functions can only access static members.
   - Useful for counting objects, shared configurations, etc.

3. Static keyword can also be used:
   - At global level (limits visibility to the current file — internal linkage).
   - Inside a class, for both variables and functions.
*/
