// 🔥 UNORDERED MAP - STL Reference with Explanations

/*
────────────────────────────────────────────
📌 unordered_map - Key Points

✅ Stores data as key-value pairs
✅ Keys must be unique (no duplicates)
✅ Uses **Hash Table** internally
✅ Keys are **not sorted** — no order is guaranteed
✅ Average Time Complexity for insert, erase, find: O(1)
   ⛔ Worst-case: O(N) if many collisions

📁 Header: #include <unordered_map>
Namespace: using namespace std;

🧠 Comparison:
- map             → sorted, uses Red-Black Tree
- unordered_map   → unsorted, uses Hash Table
────────────────────────────────────────────
*/

#include <iostream>
#include <unordered_map>  // Required for unordered_map
using namespace std;

int main() {

    unordered_map<string, int> m;

    // ✅ Inserting using emplace
    m.emplace("tv", 100);      // Inserts "tv" with value 100
    m.emplace("tv", 150);      // ❌ No effect, "tv" already exists

    // ✅ Modifying values using [ ] syntax
    m["tv"] = 120;             // Value updated to 120

    // ✅ Inserting using [ ] as well
    m["laptop"] = 50;          // Inserts new key "laptop"

    /*
    ⚠️ [ ] inserts default value if key doesn't exist.
    This means:
    m["phone"];  // Inserts "phone" with value 0
    */

    // ✅ Traversing (No guaranteed order!)
    cout << "Key-value pairs:\n";
    for (auto& it : m) {
        cout << it.first << " : " << it.second << endl;
    }

    // ✅ Other Common Methods (Same as map)
    cout << "\nDoes 'tv' exist? " << (m.count("tv") ? "Yes" : "No") << "\n";
    cout << "Value for 'tv': " << m["tv"] << "\n";

    m.erase("tv");  // Removes the key "tv"

    cout << "\nAfter erasing 'tv':\n";
    for (auto& p : m) {
        cout << p.first << " : " << p.second << endl;
    }

    return 0;
}

/*
────────────────────────────────────────────
📌 Important Notes:
- No iterators or indexing by number: m[0] ❌, use m["key"]
- Traversal is **unordered**, don't expect same output order
- Collisions can degrade performance → O(N)
────────────────────────────────────────────

🧠 Use unordered_map when:
- You don't need sorting
- Speed is your priority
- You're okay with unpredictable order

🛑 Avoid unordered_map when:
- You need sorted keys
- You have custom key types (like pairs or structs) but no hash function

*/
