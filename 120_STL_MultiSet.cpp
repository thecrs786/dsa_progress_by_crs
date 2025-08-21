/*
────────────────────────────────────────────
📌 MULTISET IN C++
────────────────────────────────────────────
🔹 Header: #include <set>
🔹 Allows Duplicates: ✅ YES
🔹 Sorted: ✅ YES (ascending by default)
🔹 Underlying structure: Balanced BST (Red-Black Tree)
🔹 Iterator: ✅ Used extensively
🔹 Indexing: ❌ Not allowed
🔹 All operations: O(log n)

────────────────────────────────────────────
🔸 Methods & Time Complexities
────────────────────────────────────────────
🔸 insert(x) / emplace(x)      → O(log n)         → Adds an element
🔸 erase(x)                    → O(log n)         → Removes ALL instances of x
🔸 erase(iterator)             → O(1)             → Removes ONE element at given iterator
🔸 find(x)                     → O(log n)         → Returns iterator to first x (if exists)
🔸 count(x)                    → O(log n)         → Returns number of times x occurs
🔸 size()                      → O(1)             → Number of total elements
🔸 empty()                     → O(1)             → true if size==0
🔸 clear()                     → O(n)             → Removes all elements
🔸 lower_bound(x)              → O(log n)         → First element >= x
🔸 upper_bound(x)              → O(log n)         → First element > x
🔸 equal_range(x)              → O(log n)         → pair<lower_bound(x), upper_bound(x)>
────────────────────────────────────────────
*/

#include<iostream>
#include<set>
using namespace std;

int main() {
    // Initialization
    multiset<int> ms = {10, 20, 20, 30, 30, 30};

    // 🔹 Print all elements
    cout << "Initial multiset: ";
    for (int x : ms) cout << x << " ";  // Output: 10 20 20 30 30 30
    cout << "\n";

    // 🔹 insert() or emplace()
    ms.insert(20);  // adds another 20
    ms.emplace(10); // adds another 10

    cout << "After insertions: ";
    for (int x : ms) cout << x << " ";  // Output: 10 10 20 20 20 30 30 30
    cout << "\n";

    // 🔹 count(x)
    cout << "Count of 20: " << ms.count(20) << "\n"; // Output: 3
    cout << "Count of 10: " << ms.count(10) << "\n"; // Output: 2

    // 🔹 erase(x) → removes all occurrences of x
    ms.erase(30);
    cout << "After erase(30): ";
    for (int x : ms) cout << x << " ";  // Output: 10 10 20 20 20
    cout << "\n";

    // 🔹 erase(it) → removes only one element
    auto it = ms.find(20);  // returns iterator to first 20
    if (it != ms.end()) ms.erase(it);  // removes ONE 20
    cout << "After erasing one 20 using iterator: ";
    for (int x : ms) cout << x << " ";  // Output: 10 10 20 20
    cout << "\n";

    // 🔹 find(x)
    if (ms.find(10) != ms.end()) cout << "10 is found in multiset\n";

    // 🔹 lower_bound(x) → first ≥ x
    auto lb = ms.lower_bound(15);  // returns iterator to 20
    if (lb != ms.end()) cout << "Lower bound of 15 is " << *lb << "\n";

    // 🔹 upper_bound(x) → first > x
    auto ub = ms.upper_bound(20);  // returns iterator to end
    if (ub != ms.end()) cout << "Upper bound of 20 is " << *ub << "\n";
    else cout << "Upper bound of 20 not found (end)\n";

    // 🔹 equal_range(x) → pair of (lower_bound, upper_bound)
    ms.insert(50);
    ms.insert(50);
    auto range = ms.equal_range(50);
    cout << "All elements equal to 50: ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << " ";  // Output: 50 50
    }
    cout << "\n";

    // 🔹 size() and empty()
    cout << "Size: " << ms.size() << "\n";    // Output: total number of elements
    cout << "Is empty? " << (ms.empty() ? "Yes" : "No") << "\n";

    // 🔹 clear()
    ms.clear();
    cout << "After clear(), is empty? " << (ms.empty() ? "Yes" : "No") << "\n";

    return 0;
}
