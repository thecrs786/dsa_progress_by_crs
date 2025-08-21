// LISTS : Complete std::list Reference with Examples and Explanations

#include <iostream>
#include <list>  // Required for LISTS
#include <iterator>   // for std::advance()
using namespace std;

/*
──────────────────────────────────────────────────────────────
🧾 STL LIST: Complete Reference Guide with Full Explanations
──────────────────────────────────────────────────────────────

📦 Header:         <list>
📚 Type:           Doubly Linked List (NOT indexable)
⚡️ Strength:       Fast insertion/deletion anywhere — O(1) with iterators
🚫 Weakness:       No random access — ❌ no indexing ([]), ❌ no at(i)

──────────────────────────────────────────────────────────────
📌 FUNCTION REFERENCE TABLE
──────────────────────────────────────────────────────────────

| Function         | Description                                 | Iterator Needed | Time Complexity       | Notes & Behavior                                |
|------------------|---------------------------------------------|------------------|------------------------|--------------------------------------------------|
| push_back()      | Add element at end                          | ❌               | O(1)                   |                                                  |
| push_front()     | Add element at front                        | ❌               | O(1)                   |                                                  |
| emplace_back()   | Construct element at end                    | ❌               | O(1)                   | More efficient: constructs in-place              |
| emplace_front()  | Construct element at front                  | ❌               | O(1)                   |                                                  |
| pop_back()       | Remove element from end                     | ❌               | O(1)                   |                                                  |
| pop_front()      | Remove element from front                   | ❌               | O(1)                   |                                                  |
| front()          | Access first element                        | ❌               | O(1)                   |                                                  |
| back()           | Access last element                         | ❌               | O(1)                   |                                                  |
| insert()         | Insert at position                          | ✅               | O(1)                   | Requires iterator; insert before `it`            |
| erase()          | Remove element or range                     | ✅               | O(1) for single, O(n)  | Needs iterator; range version O(distance)        |
| remove(val)      | Remove ALL elements == val                  | ❌               | O(n)                   | No iterator required                             |
| remove_if(fn)    | Remove by condition (lambda/predicate)      | ❌               | O(n)                   |                                                  |
| clear()          | Remove all elements                         | ❌               | O(n)                   |                                                  |
| size()           | Returns number of elements                  | ❌               | O(1) (C++11 onward)    | Earlier implementations were O(n)                |
| empty()          | Check if list is empty                      | ❌               | O(1)                   |                                                  |
| assign(n, val)   | Replace contents with n copies              | ❌               | O(n)                   |                                                  |
| assign(range)    | Replace with range from another container   | ❌               | O(n)                   |                                                  |
| assign({list})   | Replace with initializer list               | ❌               | O(n)                   |                                                  |
| unique()         | Remove consecutive duplicates               | ❌               | O(n)                   | Use `sort()` before to remove all duplicates     |
| sort()           | Sorts entire list in ascending order        | ❌               | O(n log n)             | Uses merge sort (stable)                         |
| reverse()        | Reverses the list                           | ❌               | O(n)                   |                                                  |
| splice(pos, l2)  | Move all of l2 into current list at pos     | ✅               | O(1)                   | No copy, just pointer manipulation               |
| begin(), end()   | Get start and end iterators                 | ✅               | O(1)                   | Required for iteration and many operations       |
| rbegin(), rend() | Reverse iterators                           | ✅               | O(1)                   |                                                  |
| advance(it, n)   | Move iterator n steps forward/backward      | ✅               | O(n)                   | Used to position iterators                       |

──────────────────────────────────────────────────────────────
🧠 Notes:
- ✅ Use `auto it = list.begin()` for iterator-based operations.
- ❗ insert/erase **require** a valid iterator — don’t use index.
- STL list is a **doubly linked list** → stable sort, fast splice
- `splice()` transfers nodes — **constant time** no matter how large
- Avoid using `std::list` when frequent random access is required — use `vector` or `deque` instead
──────────────────────────────────────────────────────────────
*/


// Utility function to print the contents of a list
void printList(const list<int>& lst) {
    cout << "List: ";
    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    // ✅ Basic Construction
    list<int> l; // creates an empty list

    // ✅ push_back & push_front
    // Adds elements at the back and front respectively
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_front(2);
    l.push_front(1);
    printList(l); // List: 1 2 3 4 5

    // ✅ emplace_back & emplace_front
    // Constructs elements in-place at front/back (faster than push_back/push_front for complex types)
    l.emplace_back(6);
    l.emplace_front(0);
    printList(l); // List: 0 1 2 3 4 5 6

    // ✅ front() & back()
    cout << "Front: " << l.front() << endl;  // 0
    cout << "Back: "  << l.back() << endl;   // 6

    // ✅ size() & empty()
    cout << "Size: " << l.size() << endl;              // 7
    cout << "Empty? " << boolalpha << l.empty() << endl; // false

    // ✅ pop_back & pop_front
    l.pop_back();   // Removes 6
    l.pop_front();  // Removes 0
    printList(l);   // List: 1 2 3 4 5

    // ✅ Access with iterator (list does not support random access with [])
    // std::advance moves the iterator forward (or backward) by 'n' steps from current position
    auto it = l.begin();      // points to first element (1)
    advance(it, 2);           // moves iterator to 3rd element (0-based index)
    cout << "Element at index 2: " << *it << endl; // 3

    // ✅ insert (single element)
    it = l.begin();
    advance(it, 2);           // move to position before element 3
    l.insert(it, 99);         // insert 99 before 3
    printList(l); // List: 1 2 99 3 4 5

    // ✅ insert (multiple elements from another list)
    list<int> extra = {7, 8, 9};
    it = l.begin();
    advance(it, 4); // move to element 4
    l.insert(it, extra.begin(), extra.end());
    printList(l); // List: 1 2 99 3 7 8 9 4 5

    // ✅ erase (single element)
    it = l.begin();
    advance(it, 2); // points to 99
    l.erase(it);
    printList(l); // List: 1 2 3 7 8 9 4 5

    // ✅ erase (range)
    auto start = l.begin();
    advance(start, 2); // points to 3
    auto end = start;
    advance(end, 3);   // points to 4 (3 steps ahead)
    l.erase(start, end); // removes 3, 7, 8
    printList(l); // List: 1 2 9 4 5

    // ✅ clear(): removes all elements
    l.clear();
    cout << "After clear(), is empty? " << l.empty() << endl; // true

    // ✅ begin(), end(), rbegin(), rend() usage
    list<int> demo = {10, 20, 30, 40};

    cout << "Forward iteration: ";
    for (auto it = demo.begin(); it != demo.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "Reverse iteration: ";
    for (auto rit = demo.rbegin(); rit != demo.rend(); ++rit)
        cout << *rit << " ";
    cout << endl;

    // ✅ More Methods to Know:

    // assign(): replaces current contents
    list<int> l2;
    l2.assign(5, 100); // assigns five 100s
    printList(l2); // List: 100 100 100 100 100

    // remove(): removes elements by value
    l2.remove(100); // removes all 100s
    printList(l2);  // List: (empty)

    // remove_if(): removes elements that satisfy a condition
    list<int> nums = {1, 2, 3, 4, 5, 6};
    nums.remove_if([](int x){ return x % 2 == 0; }); // remove even numbers
    printList(nums); // List: 1 3 5

    // unique(): removes consecutive duplicates (only works if duplicates are adjacent)
    list<int> dups = {1, 1, 2, 2, 2, 3, 3, 4};
    dups.unique();
    printList(dups); // List: 1 2 3 4

    // sort(): sorts the list
    list<int> unsorted = {5, 2, 9, 1};
    unsorted.sort();
    printList(unsorted); // List: 1 2 5 9

    // reverse(): reverses the order
    unsorted.reverse();
    printList(unsorted); // List: 9 5 2 1

    // splice(): transfers elements from one list to another
    list<int> a = {1, 2, 3};
    list<int> b = {4, 5};
    auto pos = a.begin();
    advance(pos, 1); // move to 2
    a.splice(pos, b); // move all elements from b into a before 2
    printList(a); // List: 1 4 5 2 3
    printList(b); // List: (empty)

    // ✅ All Major Initialization Techniques for std::list

    list<int> l3; // Empty list

    list<int> l4(5); 
    // Creates list of 5 default-initialized elements (0s for int)

    list<int> l5(4, 10); 
    // Creates list: 10 10 10 10

    list<int> l6 = {1, 2, 3, 4};
    // Direct list initialization with initializer list

    list<int> l7(l6);
    // Copy constructor (makes a copy of l6)

    list<int> l8(l6.begin(), l6.end());
    // Initialize from another container's iterator range

    printList(l4); // 0 0 0 0 0
    printList(l5); // 10 10 10 10
    printList(l6); // 1 2 3 4
    printList(l7); // 1 2 3 4
    printList(l8); // 1 2 3 4

    return 0;
}
