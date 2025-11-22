// DEQUE : Complete std::deque Reference with Examples and Explanations

#include <iostream>
#include <deque> // Required for DEQUE
#include <iterator>   // for std::advance
using namespace std;

/*
────────────────────────────────────────────
📘 STL DEQUE — COMPLETE REFERENCE (WITH TC)
────────────────────────────────────────────
🔹 Header: <deque>
🔹 Type: Double-ended queue — allows fast insert/delete from both ends.
🔹 Supports random access like vector (with O(1) access).
🔹 Good alternative to vector when frequent front operations are needed.

────────────────────────────────────────────
📌 INITIALIZATION
────────────────────────────────────────────
| Expression                            | Description                          | TC      |
|--------------------------------------|--------------------------------------|---------|
| deque<int> d;                        | Empty deque                          | O(1)    |
| deque<int> d(n);                     | n elements of 0                      | O(n)    |
| deque<int> d(n, val);                | n elements of val                    | O(n)    |
| deque<int> d = {a, b, c};            | Initializer list                     | O(n)    |
| deque<int> d2(d1);                   | Copy constructor                     | O(n)    |
| deque<int> d3(d1.begin(), d1.end()); | Range constructor                    | O(n)    |

────────────────────────────────────────────
📌 ELEMENT ACCESS
────────────────────────────────────────────
| Expression         | Description              | TC      |
|-------------------|--------------------------|---------|
| d[i]              | Access index i           | O(1)    |
| d.at(i)           | Access with bound check  | O(1)    |
| d.front()         | First element            | O(1)    |
| d.back()          | Last element             | O(1)    |

────────────────────────────────────────────
📌 CAPACITY
────────────────────────────────────────────
| Expression        | Description        | TC      |
|------------------|--------------------|---------|
| d.size()         | Number of elements | O(1)    |
| d.empty()        | Is empty or not    | O(1)    |

────────────────────────────────────────────
📌 INSERTION
────────────────────────────────────────────
| Expression                          | Description                            | TC (avg) |
|------------------------------------|----------------------------------------|----------|
| d.push_back(val)                   | Insert at end                          | O(1)     |
| d.push_front(val)                  | Insert at front                        | O(1)     |
| d.emplace_back(val)               | Efficient back insertion               | O(1)     |
| d.emplace_front(val)              | Efficient front insertion              | O(1)     |
| d.insert(pos, val)                | Insert before pos                      | O(n)     |
| d.insert(pos, n, val)             | Insert n copies before pos             | O(n)     |
| d.insert(pos, first, last)        | Insert range                           | O(n)     |

────────────────────────────────────────────
📌 DELETION
────────────────────────────────────────────
| Expression              | Description                          | TC (avg) |
|------------------------|--------------------------------------|----------|
| d.pop_back()           | Remove from end                      | O(1)     |
| d.pop_front()          | Remove from front                    | O(1)     |
| d.erase(pos)           | Erase element at pos                 | O(n)     |
| d.erase(start, end)    | Erase range [start, end)             | O(n)     |
| d.clear()              | Erase all elements                   | O(n)     |

────────────────────────────────────────────
📌 OTHER MODIFIERS
────────────────────────────────────────────
| Expression                | Description                              | TC     |
|--------------------------|------------------------------------------|--------|
| d.resize(n)              | Resize to n (fill 0 if expand)           | O(n)   |
| d.resize(n, val)         | Resize with val instead of 0             | O(n)   |
| d.assign(n, val)         | Assign n copies                          | O(n)   |
| d.assign(first, last)    | Assign from range                        | O(n)   |
| d.assign({a, b, c})      | Assign initializer list                  | O(n)   |
| d.swap(d2)               | Swap with another deque                  | O(1)   |

────────────────────────────────────────────
📌 ITERATORS
────────────────────────────────────────────
| Expression       | Description            | TC      |
|-----------------|------------------------|---------|
| d.begin()       | Iterator to front      | O(1)    |
| d.end()         | Iterator to back+1     | O(1)    |
| d.rbegin()      | Reverse iterator start | O(1)    |
| d.rend()        | Reverse iterator end   | O(1)    |

────────────────────────────────────────────
📎 NOTES
────────────────────────────────────────────
🔹 Better than vector for operations on both ends.
🔹 Slightly less cache-friendly than vector for random access.
🔹 Use emplace when you want to construct in-place (avoids copy).
🔹 Internally implemented as a segmented array — not contiguous like vector.
🔹 Avoid excessive mid-insertions — expensive (O(n)).

*/

// Utility function to print the contents of a deque
void printDeque(const deque<int>& dq) {
    cout << "Deque: ";
    for (int val : dq) cout << val << " ";
    cout << endl;
}

int main() {
    // ✅ Initialization Techniques
    deque<int> d1;                     // Empty deque
    deque<int> d2(5);                  // 5 default-initialized ints (0)
    deque<int> d3(4, 10);              // 4 elements, each 10
    deque<int> d4 = {1, 2, 3, 4};      // initializer_list
    deque<int> d5(d4);                 // copy constructor
    deque<int> d6(d4.begin(), d4.end()); // range constructor

    printDeque(d1); // 
    printDeque(d2); // 0 0 0 0 0
    printDeque(d3); // 10 10 10 10
    printDeque(d4); // 1 2 3 4
    printDeque(d5); // 1 2 3 4
    printDeque(d6); // 1 2 3 4

    // ✅ Element Access Methods
    // operator[]: unchecked access
    cout << "d4[2]: " << d4[2] << endl;  // 3
    // at(): bounds-checked access (throws out_of_range)
    try {
        cout << "d4.at(3): " << d4.at(3) << endl; // 4
        // cout << d4.at(4); // would throw
    } catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    // front() & back()
    cout << "front: " << d4.front() << endl;  // 1
    cout << "back: "  << d4.back() << endl;   // 4

    // ✅ Capacity
    cout << "size: " << d4.size() << endl;
    cout << "empty? " << boolalpha << d4.empty() << endl;

    // ✅ Modifiers: Insertion
    deque<int> dq;
    // push_back / push_front
    dq.push_back(3);    // {3}
    dq.push_front(2);   // {2,3}
    dq.push_back(4);    // {2,3,4}
    dq.push_front(1);   // {1,2,3,4}
    printDeque(dq);

    // emplace_back / emplace_front
    dq.emplace_back(5); // more efficient in-place
    dq.emplace_front(0);
    printDeque(dq); // {0,1,2,3,4,5}

    // insert single element
    auto it = dq.begin();
    advance(it, 3);    // point at element '3'
    dq.insert(it, 99); // insert before '3'
    printDeque(dq);

    // insert multiple copies
    dq.insert(dq.end(), 2, 77); // two 77s at end
    printDeque(dq);

    // insert range from another deque
    deque<int> extra = {8,9};
    dq.insert(dq.begin(), extra.begin(), extra.end());
    printDeque(dq);

    // ✅ Modifiers: Removal
    // pop_back / pop_front
    dq.pop_back();    // removes last
    dq.pop_front();   // removes first
    printDeque(dq);

    // erase single element
    it = dq.begin();
    advance(it, 2);
    dq.erase(it);     // erase 2nd index
    printDeque(dq);

    // erase range [first, last)
    auto first = dq.begin();
    advance(first, 1);
    auto last  = first;
    advance(last, 3);
    dq.erase(first, last);
    printDeque(dq);

    // clear: remove all
    dq.clear();
    cout << "After clear, empty? " << dq.empty() << endl;

    // resize: change size, new elements default-initialized or assigned value
    deque<int> rd = {1,2,3};
    rd.resize(5);     // adds two zeros
    printDeque(rd);
    rd.resize(2);     // removes extra elements
    printDeque(rd);
    rd.resize(4, 9);  // adds two 9s
    printDeque(rd);

    // swap: exchange contents
    deque<int> a = {1,2,3}, b = {4,5};
    a.swap(b);
    printDeque(a); // {4,5}
    printDeque(b); // {1,2,3}

    // assign: replace contents
    deque<int> as;
    as.assign(3, 42);           // {42,42,42}
    printDeque(as);
    as.assign(extra.begin(), extra.end()); // from range
    printDeque(as);
    as.assign({7,8,9});         // initializer_list
    printDeque(as);

    // ✅ Iterators
    deque<int> di = {10,20,30,40};
    cout << "Forward iter: "; for(auto i=di.begin(); i!=di.end(); ++i) cout<<*i<<" "; cout<<endl;
    cout << "Reverse iter: "; for(auto r=di.rbegin(); r!=di.rend(); ++r) cout<<*r<<" "; cout<<endl;

    return 0;
}
