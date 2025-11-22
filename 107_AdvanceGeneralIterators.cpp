// ✅ STL: advance() function with list iterators

#include <iostream>
#include <list>
#include <iterator>  // Required for std::advance()
using namespace std;

int main() {
    // 🔹 Initialize a list
    list<int> l = {10, 20, 30, 40, 50};

    /*
    📌 std::advance(iterator, n):

    → Moves the iterator forward by `n` steps
    → Works with all STL iterators (input, forward, bidirectional, random access)
    → In std::list (which is bidirectional), advance() walks node-by-node, so it's O(n)

    ✅ If n is positive → moves forward
    ✅ If n is negative → moves backward (only in bidirectional or random-access iterators)
    ❌ Going past l.end() leads to undefined behavior
    */

    // 🔹 Move 2 steps forward from begin()
    auto it = l.begin();    // points to 10
    advance(it, 2);         // moves to 30

    cout << "Element at position 2: " << *it << endl;  // Output: 30

    // 🔹 Move 1 step back from current position
    advance(it, -1);        // moves to 20
    cout << "After moving 1 step back: " << *it << endl;  // Output: 20

    // 🔹 Edge Case: Advancing to end()
    auto endcheck = l.begin();
    advance(endcheck, l.size());  // moves to l.end()
    
    // ❗ Cannot dereference end() — would be undefined behavior
    if (endcheck == l.end()) {
        cout << "Iterator now points to end(). Dereferencing is invalid here." << endl;
    }

    return 0;
}
