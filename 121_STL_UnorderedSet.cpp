/*
────────────────────────────────────────────
📌 UNORDERED_SET IN C++
────────────────────────────────────────────
🔹 Header: #include <unordered_set>
🔹 Allows Duplicates: ❌ NO
🔹 Sorted: ❌ NO (No ordering guaranteed)
🔹 Underlying structure: Hash Table
🔹 Iterator: ✅ Supported (but no ordering)
🔹 Indexing: ❌ Not allowed
🔹 All operations: Average O(1), Worst O(n) due to collisions

🔸 Use unordered_set when:
    - You don’t care about order
    - You want faster average insert/find/erase
────────────────────────────────────────────
🔸 UNORDERED_SET COMMON METHODS (C++ STL)
────────────────────────────────────────────
| Method                | Description                               | Avg TC  | Worst TC |
|-----------------------|-------------------------------------------|---------|----------|
| insert(x)/emplace(x)  | Insert element if not already present     | O(1)    | O(n)     |
| erase(x)              | Removes element by value                  | O(1)    | O(n)     |
| erase(iterator)       | Removes element at given iterator         | O(1)    | O(1)     |
| find(x)               | Returns iterator to x if present          | O(1)    | O(n)     |
| count(x)              | Returns 1 if x exists, else 0             | O(1)    | O(n)     |
| size()                | Returns number of elements                | O(1)    | O(1)     |
| empty()               | Checks if container is empty              | O(1)    | O(1)     |
| clear()               | Removes all elements                      | O(n)    | O(n)     |
────────────────────────────────────────────
📌 Notes:
- All average cases are O(1) due to hash table usage.
- Worst-case O(n) occurs due to poor hashing/collisions.
- For guaranteed O(log n) operations, use `set`.
────────────────────────────────────────────
🔸 NOT AVAILABLE:
    ❌ lower_bound()
    ❌ upper_bound()
    ❌ equal_range()
    ❌ Multivalue duplicates (use unordered_multiset instead)
────────────────────────────────────────────
*/

#include<iostream>
#include<unordered_set>
using namespace std;

int main() {
    // 🔸 Initialization
    unordered_set<int> uset = {100, 200, 300};

    // 🔹 Insert
    uset.insert(400);     // Insert 400
    uset.emplace(500);    // Faster, avoids copy if possible

    // 🔹 Insert duplicates (will be ignored)
    uset.insert(300);
    uset.insert(500);

    // 🔹 Print (unordered!)
    cout << "Unordered Set elements: ";
    for (int x : uset) cout << x << " ";
    cout << "\n";

    // 🔹 size()
    cout << "Size: " << uset.size() << "\n";  // Unique count only

    // 🔹 count(x)
    cout << "Count of 100: " << uset.count(100) << "\n"; // 1 if exists, else 0
    cout << "Count of 700: " << uset.count(700) << "\n"; // Output: 0

    // 🔹 find(x)
    if (uset.find(200) != uset.end()) {
        cout << "200 is present in the set.\n";
    } else {
        cout << "200 not found.\n";
    }

    // 🔹 erase(x)
    uset.erase(300);  // Removes 300 if present
    cout << "After erasing 300: ";
    for (int x : uset) cout << x << " ";
    cout << "\n";

    // 🔹 erase(iterator)
    auto it = uset.find(500);
    if (it != uset.end()) uset.erase(it);  // Removes one element at iterator
    cout << "After erasing 500 using iterator: ";
    for (int x : uset) cout << x << " ";
    cout << "\n";

    // 🔹 empty()
    cout << "Is empty? " << (uset.empty() ? "Yes" : "No") << "\n";

    // 🔹 clear()
    uset.clear();
    cout << "After clear(): Size = " << uset.size() << ", Is empty? " 
         << (uset.empty() ? "Yes" : "No") << "\n";

    return 0;
}
