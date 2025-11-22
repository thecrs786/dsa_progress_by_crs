/*
────────────────────────────────────────────
📌 Parts of STL:
1. Containers → vector, list, map, set, etc.
2. Iterators  → traverse container elements
3. Algorithms → sort(), reverse(), etc.
4. Functors   → callable objects (not used with vectors much)

────────────────────────────────────────────
✅ STL VECTORS 
📁 Header: #include <vector>
Namespace: using namespace std;

A vector is a **dynamic array** from STL that:
- Automatically resizes
- Stores elements in contiguous memory
- Supports random access like arrays

────────────────────────────────────────────
✅ Syntax – Declaration
vector<int> v;                       // empty vector of int
vector<string> names;               // empty vector of strings

────────────────────────────────────────────
✅ Common Member Functions:

🔹 v.size()           → returns number of elements → O(1)             ✅ index not used                  ⏱ Time: O(1)
🔹 v.capacity()       → current memory allocated → O(1)               ✅ index not used                  ⏱ Time: O(1)
🔹 v.push_back(x)     → adds x to end → O(1) amortized               ✅ index not used                  ⏱ Time: O(1) Amortized
🔹 v.pop_back()       → removes last element → O(1)                  ✅ index not used                  ⏱ Time: O(1)
🔹 v.emplace_back(x)  → constructs x in-place → O(1)                 ✅ index not used                  ⏱ Time: O(1)
🔹 v.at(i)            → element at index i (safe) → O(1)             ✅ ✅ index-based access            ⏱ Time: O(1)
🔹 v[i]               → element at index i (unsafe) → O(1)           ✅ ✅ index-based access            ⏱ Time: O(1)
🔹 v.front()          → first element → O(1)                         ✅ no index                        ⏱ Time: O(1)
🔹 v.back()           → last element → O(1)                          ✅ no index                        ⏱ Time: O(1)
🔹 v.clear()          → removes all elements → O(n)                  ✅ no index                        ⏱ Time: O(n)
🔹 v.empty()          → true if size == 0 → O(1)                     ✅ no index                        ⏱ Time: O(1)
🔹 v.insert(pos, x)   → insert x at pos (⚠️iterator) → O(n)         ❌ index ❌ → ✅ requires iterator   ⏱ Time: O(n)
🔹 v.erase(pos)       → remove element at pos (⚠️iterator) → O(n)   ❌ index ❌ → ✅ requires iterator   ⏱ Time: O(n)
🔹 v.insert(pos, n, x)→ insert `n` copies of `x` at `pos` → O(n)    ✅ needs iterator                   ⏱ Time: O(n)
🔹 v.erase(start, end)→ remove range [start, end) → O(n)            ✅ needs iterator                   ⏱ Time: O(n)

⚠️ Warning:
- Accessing out-of-bounds index via `v[i]` is **undefined behavior**.
- `v.at(i)` throws an exception if index invalid (safe).
- `insert()` and `erase()` take **iterators**, not index values directly.

────────────────────────────────────────────
✅ Internal Memory Growth:

- Vector grows **dynamically**.
- If size == capacity and you insert, the capacity usually **doubles**.
- Involves allocating new memory + copying all old elements (costly).
- That’s why prefer `reserve(n)` if you know the expected size.
────────────────────────────────────────────
*/

#include<iostream>
#include<vector>
using namespace std;

// ✅ Utility function to print vector
void printVec(const vector<int>& vec) {
    cout << "Vector : [";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> vec;

    // ✅ Initial state
    cout << "Initial size: " << vec.size() << endl;
    cout << "Initial capacity: " << vec.capacity() << endl;

    // ✅ Adding elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    printVec(vec); // [10, 20, 30]

    // ✅ Size vs Capacity
    cout << "Size: " << vec.size() << endl;
    cout << "Capacity: " << vec.capacity() << endl;

    // ✅ Removing last element
    vec.pop_back(); // Removes 30
    printVec(vec);  // [10, 20]

    // ✅ Accessing elements using index
    cout << "Element at index 0 using []: " << vec[0] << endl;
    cout << "Element at index 1 using at(): " << vec.at(1) << endl;

    // ✅ Front and Back
    cout << "Front element: " << vec.front() << endl;
    cout << "Back element: " << vec.back() << endl;

    // ✅ Emplace Back
    vec.emplace_back(99); 
    printVec(vec); // [10, 20, 99]

    // ✅ Insert at position 1 (using iterator)
    vec.insert(vec.begin() + 1, 42);  
    printVec(vec); // [10, 42, 20, 99]

    // ✅ Erase element at index 2 (iterator form)
    vec.erase(vec.begin() + 2);
    printVec(vec); // [10, 42, 99]

    // ✅ Insert multiple copies at once
    vec.insert(vec.begin() + 1, 3, 7); // Insert 3 copies of 7 at pos 1
    printVec(vec); // [10, 7, 7, 7, 42, 99]

    // ✅ Erase a range (elements at index 1 to 3)
    vec.erase(vec.begin() + 1, vec.begin() + 4); 
    printVec(vec); // [10, 42, 99]

    // ✅ Clear all elements
    vec.clear();
    cout << "After clear, size: " << vec.size() << endl;
    cout << "Is vector empty? " << (vec.empty() ? "Yes" : "No") << endl;

    /*
    ────────────────────────────────────────────
    ✅ Vector Initialization Methods:
    */

    // 1. Empty vector
    vector<int> v1;
    printVec(v1);  // []

    // 2. Fixed size with default value (0 for int)
    vector<int> v2(5);
    printVec(v2);  // [0, 0, 0, 0, 0]

    // 3. Fixed size with custom value
    vector<int> v3(4, -1);
    printVec(v3);  // [-1, -1, -1, -1]

    // 4. Initializer list
    vector<int> v4 = {1, 2, 3};
    printVec(v4);  // [1, 2, 3]

    // 5. Copy constructor
    vector<int> v5 = v3;
    printVec(v5);  // [-1, -1, -1, -1]

    // 6. Range constructor using iterators
    vector<int> v6(v4.begin(), v4.begin() + 2);
    printVec(v6);  // [1, 2]

    // 7. Move constructor
    vector<int> temp = {5, 6, 7};
    vector<int> v7 = move(temp);
    printVec(v7);   // [5, 6, 7]
    printVec(temp); // [] – moved-from

    return 0;
}

/*
────────────────────────────────────────────
✅ Time Complexity Summary:

Operation               | Time
------------------------|--------
push_back / emplace_back| O(1) amortized
pop_back                | O(1)
at(i) / [i]             | O(1)
insert(pos, x)          | O(n)
insert(pos, n, x)       | O(n)
erase(pos)              | O(n)
erase(start, end)       | O(n)
clear                   | O(n)
size / capacity         | O(1)
front / back            | O(1)

────────────────────────────────────────────
✅ Pro Tips:
- `reserve(n)` → pre-allocate memory if size known
- `shrink_to_fit()` → request vector to release extra capacity
- `emplace_back()` preferred for complex objects
- For frequent middle insertions/deletions → prefer `list`

────────────────────────────────────────────
✅ Index vs Iterator: What's the Difference?

🔹 Index:
- Integer position like `v[3]`
- Works with `[]`, `at()`, loops
- Can only be used with containers like vector, array (random access)

🔹 Iterator: pointers for vectors, arrays, and deque
- Pointer-like object that "points" to an element
- Needed for functions like `insert()`, `erase()`, `begin()`, `end()`
- Use `vec.begin() + i` if you want iterator at index `i`

⚠️ STL functions that **modify** the container (like `insert()` and `erase()`) always require **iterators**, not indexes.

🔹 Use Index:
  - When accessing/modifying individual elements directly
  - Prefer when using loops and random access

🔹 Use Iterator:
  - When calling STL algorithms or member functions
  - When working with containers like list, set, map that don’t support index access

────────────────────────────────────────────
✅ Summary:

If a function needs to **modify structure** (insert/erase), it wants **iterator**.  
If you're **just accessing or looping**, index is fine (if container allows it).
*/
