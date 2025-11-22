// RUNTIME POLYMORPHISM -> DYNAMIC POLYMORPHISM
/*
Runtime polymorphism in C++ is achieved using inheritance and virtual functions. 
It allows a program to decide **at runtime** which function to invoke, 
based on the actual type of object a base class pointer or reference is pointing to.

Key Points:
1. Achieved using **virtual functions** in base class.
2. Works with **base class pointers/references** to derived objects.
3. Non-virtual functions use compile-time (early) binding.
4. Virtual functions use runtime (late) binding.
5. If a base class pointer points to a derived object, virtual functions ensure
   the derived version is called.
6. Virtual destructors are important to avoid memory leaks when deleting derived objects
   through base class pointers.
*/

#include <iostream>
using namespace std;

// Base class
class Parent {
public:
    // Non-virtual function
    void getinfo() {
        cout << "Parent's getinfo() called (non-virtual)" << endl;
    }

    // Virtual function
    virtual void hello() {
        cout << "Hello from Parent (virtual function)" << endl;
    }

    // Virtual destructor (important for dynamic memory cleanup)
    virtual ~Parent() {
        cout << "Parent destructor called" << endl;
    }
};

// Derived class
class Child : public Parent {
public:
    void getinfo() { // Non-virtual function
        cout << "Child's getinfo() called (non-virtual)" << endl;
    }

    void hello() override { // Virtual function overriding
        cout << "Hello from Child (overridden virtual function)" << endl;
    }

    ~Child() {
        cout << "Child destructor called" << endl;
    }
};

// Another Derived class
class GrandChild : public Child {
public:
    void hello() override { // Overriding virtual function further
        cout << "Hello from GrandChild (overridden virtual function)" << endl;
    }

    ~GrandChild() {
        cout << "GrandChild destructor called" << endl;
    }
};

int main() {
    cout << "--- Direct Object Calls ---\n";
    Parent p;
    Child c;
    GrandChild gc;

    p.getinfo();  // Parent's version
    c.getinfo();  // Child's version
    gc.getinfo(); // GrandChild inherits Child's non-virtual function

    p.hello();  // Parent's version
    c.hello();  // Child's overridden version
    gc.hello(); // GrandChild's overridden version

    cout << "\n--- Base Class Pointer to Derived Objects ---\n";

    Parent* ptr;

    ptr = &p;
    ptr->getinfo(); // ❌ Non-virtual -> calls Parent
    ptr->hello();   // ✅ Virtual -> calls Parent

    ptr = &c;
    ptr->getinfo(); // ❌ Non-virtual -> calls Parent
    ptr->hello();   // ✅ Virtual -> calls Child

    ptr = &gc;
    ptr->getinfo(); // ❌ Non-virtual -> calls Parent
    ptr->hello();   // ✅ Virtual -> calls GrandChild

    cout << "\n--- Base Class Reference to Derived Objects ---\n";
    Parent& ref = gc;

    ref.getinfo(); // ❌ Non-virtual -> Parent
    ref.hello();   // ✅ Virtual -> GrandChild

    cout << "\n--- Dynamic Memory Allocation and Virtual Destructor ---\n";

    Parent* dynPtr = new GrandChild();
    dynPtr->hello(); // ✅ Calls GrandChild hello
    delete dynPtr;   // ✅ Calls GrandChild, then Child, then Parent destructor because destructor is virtual

    return 0;
}

/*
Key Insights and Takeaways:

1. **Virtual Functions**:
   - Allow runtime determination of which function to call.
   - Declared in base class using `virtual` keyword.
   - Always use `override` in derived class (optional, but safer).

2. **Non-Virtual Functions**:
   - Resolved at compile-time (early binding).
   - Base class pointer calling a non-virtual function always calls base's version.

3. **Base Class Pointer / Reference**:
   - Can point to any derived class object.
   - Key to achieving runtime polymorphism.

4. **Destructor Behavior**:
   - Always declare base class destructor `virtual` if you plan to delete derived objects via base class pointers.
   - Prevents memory leaks.

5. **Multi-Level Runtime Polymorphism**:
   - Works across multiple levels of inheritance.
   - GrandChild overriding Child's virtual function works seamlessly.

6. **Pure Virtual Functions and Abstract Classes**:
   - You can create an abstract base class with `virtual void func() = 0;`
   - Forces derived classes to implement the function.
   - Base class cannot be instantiated.

7. **Important Notes**:
   - Static functions cannot be virtual.
   - Constructors cannot be virtual.
   - Runtime polymorphism slightly slows execution due to vtable lookup (negligible in most cases).

This example demonstrates **all crucial aspects** of runtime polymorphism in C++ in a clear, practical manner.
*/
