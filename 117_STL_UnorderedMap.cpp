// 🔥 MULTIMAP - STL Reference with Explanations

/*
────────────────────────────────────────────
📌 multimap - Key Points

✅ Stores key–value pairs (just like map)
✅ Allows **duplicate keys**
✅ Internally uses a **Red-Black Tree** (like map)
✅ Always keeps keys in **sorted order**
✅ No operator[] → must use insert() or emplace()

📁 Header: #include <map>
Namespace: using namespace std;

🧠 Comparison:
- map         → unique keys
- multimap    → duplicate keys allowed
────────────────────────────────────────────
*/

#include <iostream>
#include <map>  // Required for multimap
using namespace std;

int main() {
    
    // ✅ Declaration
    multimap<string, int> m;

    // ✅ Insertion using emplace
    m.emplace("tv", 100);
    m.emplace("tv", 99);
    m.emplace("tv", 50);
    m.emplace("tv", 150);

    cout << "\n🔹 All key-value pairs in multimap:\n";
    for (const auto& pair : m) {
        cout << pair.first << " : " << pair.second << "\n";
    }

    // ✅ Count how many keys named "tv"
    cout << "\n🔸 Count of key \"tv\": " << m.count("tv") << endl;

    // ✅ Erase all instances of a key
    m.erase("tv");

    cout << "\n🔻 After erasing all 'tv' entries:\n";
    for (const auto& pair : m) {
        cout << pair.first << " : " << pair.second << "\n";
    }

    // 🔁 Rebuild map to demonstrate erasing a **single instance**
    multimap<string, int> m1;
    m1.emplace("tv", 100);
    m1.emplace("tv", 99);
    m1.emplace("tv", 50);
    m1.emplace("tv", 150);

    // ✅ Erase only one occurrence of "tv"
    m1.erase(m1.find("tv"));  // Deletes the **first matching "tv"**

    cout << "\n🟡 After erasing one 'tv':\n";
    for (const auto& p : m1) {
        cout << p.first << " : " << p.second << "\n";
    }

    return 0;
}

/*
────────────────────────────────────────────
📌 Additional Notes:
- find(key) returns an iterator to **first** matching key
- erase(it) deletes only that specific instance
- count(key) gives number of duplicates
- insert() also works like emplace()

🧠 Use multimap when:
- You need multiple values per key (e.g., multiple marks for same student)
- You want sorted ordering + duplicates
────────────────────────────────────────────
*/


/*  DIFFERENCE BETWEEN MAP AND UNORDERED MAP

| Feature                       | `map`                                               | `unordered_map`                              |
| ----------------------------- | --------------------------------------------------- | -------------------------------------------- |
| **Ordering**                  | Keys are **sorted** (by default in ascending order) | Keys are **not sorted**, no guaranteed order |
| **Underlying Data Structure** | Red-Black Tree (self-balancing BST)                 | Hash Table                                   |
| **Time Complexity**           | `O(log N)` for insert, find, erase                  | **Average:** `O(1)`, **Worst-case:** `O(N)`  |
| **Duplicates**                | Only **unique keys** allowed                        | Only **unique keys** allowed                 |
| **Access via `[]`**           | ✅ Yes (both insert + modify)                       | ✅ Yes (both insert + modify)                 |
| **Custom Ordering**           | ✅ Yes (via comparator)                             | ❌ Not supported                              |
| **Performance**               | Slower due to balancing + sorting                   | Faster due to hashing (on average)           |
| **Predictable Traversal**     | ✅ Yes, always in key order                          | ❌ No order guaranteed                     |
| **Header File**               | `#include <map>`                                    | `#include <unordered_map>`                   |


*/