// LOWER_BOUND and UPPER_BOUND in SET

/*
────────────────────────────────────────────────────────────

────────────────────────────────────────────
📌 LOWER_BOUND vs UPPER_BOUND in C++ SET
────────────────────────────────────────────

🔸 Syntax: set.lower_bound(x)
    → Returns an iterator pointing to the **first element ≥ x**
    → If x exists in the set, it returns iterator to x
    → If x doesn't exist, it returns iterator to the first greater element
    → If x is greater than all elements in the set → returns s.end()

🔸 Syntax: set.upper_bound(x)
    → Returns an iterator pointing to the **first element > x**
    → Skips equal elements, finds strictly greater
    → If x is the largest or no element > x exists → returns s.end()

🧪 Examples:
    set = {10, 20, 30, 40, 50};

    set.lower_bound(30) → iterator to 30
    set.lower_bound(25) → iterator to 30
    set.lower_bound(55) → s.end()

    set.upper_bound(30) → iterator to 40
    set.upper_bound(50) → s.end()

🔁 Return type:
    → Returns an iterator (not value!)
    → Must dereference: `*s.lower_bound(x)` or `*s.upper_bound(x)`

⚠️ Don't dereference if the result is s.end(), or you’ll get runtime crash.

────────────────────────────────────────────
✅ Same rules apply to std::map:
    map.lower_bound(key) → iterator to pair with key ≥ given key
    map.upper_bound(key) → iterator to pair with key > given key
    Dereference: `it->first` for key, `it->second` for value
────────────────────────────────────────────


🔸 Works in: set, multiset, map, multimap
    (unordered_ containers do NOT support this)

────────────────────────────────────────────────────────────
🧠 Important Notes:
- Both return iterators (not actual values)
- Must be dereferenced: *it
- Must check for s.end() before dereferencing to avoid runtime error
────────────────────────────────────────────────────────────
*/

#include <iostream>
#include <set>
using namespace std;

int main() {

    set<int> s;

    s.emplace(1);
    s.emplace(2);
    s.emplace(3);
    s.emplace(4);
    s.emplace(5);

    cout << "Set Elements: ";
    for (int x : s) cout << x << " ";
    cout << "\n\n";

    // ----------------- UPPER_BOUND TEST -----------------

    cout << "[UPPER_BOUND tests]\n";

    auto it1 = s.upper_bound(4);  // Should return 5
    if (it1 != s.end()) cout << "Upper bound of 4: " << *it1 << endl;
    else cout << "Upper bound of 4: Not found\n";

    auto it2 = s.upper_bound(5);  // Should return end()
    if (it2 != s.end()) cout << "Upper bound of 5: " << *it2 << endl;
    else cout << "Upper bound of 5: Not found (past last element)\n";

    auto it3 = s.upper_bound(6);  // Beyond greatest
    if (it3 != s.end()) cout << "Upper bound of 6: " << *it3 << endl;
    else cout << "Upper bound of 6: Not found (past last element)\n";


    // ----------------- LOWER_BOUND TEST -----------------

    cout << "\n[LOWER_BOUND tests]\n";

    auto it4 = s.lower_bound(3);  // Should return 3
    if (it4 != s.end()) cout << "Lower bound of 3: " << *it4 << endl;
    else cout << "Lower bound of 3: Not found\n";

    auto it5 = s.lower_bound(1);  // Should return 1
    if (it5 != s.end()) cout << "Lower bound of 1: " << *it5 << endl;
    else cout << "Lower bound of 1: Not found\n";

    auto it6 = s.lower_bound(-5);  // Below smallest → return 1
    if (it6 != s.end()) cout << "Lower bound of -5: " << *it6 << endl;
    else cout << "Lower bound of -5: Not found\n";

    auto it7 = s.lower_bound(6);  // Beyond largest → return end()
    if (it7 != s.end()) cout << "Lower bound of 6: " << *it7 << endl;
    else cout << "Lower bound of 6: Not found (past last element)\n";

    return 0;
}
