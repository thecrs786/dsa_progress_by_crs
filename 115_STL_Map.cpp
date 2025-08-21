//────────────────────────────────────────────
// 📚 C++ STL MAP COMPLETE NOTES
//────────────────────────────────────────────

/*
────────────────────────────────────────────
🔸 What is a map?

A `map` in STL is a container that stores **key-value pairs**. It is implemented using a **Red-Black Tree (self-balancing BST)**.

🔹 Properties:
- Keys are **unique**
- Sorted in **ascending order by default**
- Logarithmic time for insertion, deletion, search (O(log n))

────────────────────────────────────────────
🔹 VARIANTS:

1. map              → Sorted by keys (default: ascending)
2. unordered_map    → Not sorted, faster average time (uses hash table)
3. multimap         → Allows duplicate keys

────────────────────────────────────────────
🔹 HEADER:
#include <map>

────────────────────────────────────────────
📋 METHOD SUMMARY

| Method           | Purpose                            | Affects Multiple? | Uses Iterator | Uses Index | Time Complexity |
|------------------|-------------------------------------|--------------------|----------------|-------------|------------------|
| insert({k,v})    | Insert one pair                    | No                 | Yes            | No          | O(log n)         |
| emplace(k,v)     | Insert (in-place)                  | No                 | Yes            | No          | O(log n)         |
| erase(key/it)    | Remove by key or iterator          | Yes (if range)     | Yes            | No          | O(log n)         |
| find(key)        | Returns iterator to key            | No                 | Yes            | No          | O(log n)         |
| count(key)       | Returns 1 if key exists, else 0     | No                 | No             | No          | O(log n)         |
| size()           | Number of elements                 | No                 | No             | No          | O(1)             |
| empty()          | Checks if map is empty             | No                 | No             | No          | O(1)             |
| clear()          | Erase all contents                 | Yes                | No             | No          | O(n)             |
| operator[key]    | Access/Modify value by key         | No                 | No             | Yes         | O(log n)         |

────────────────────────────────────────────
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {

    //────────────────────────────────────────────
    // 🔸 1. INITIALIZATION METHODS
    //────────────────────────────────────────────

    map<string, int> m1;  // Empty map (string -> int)

    map<int, string> m2 = {
        {1, "apple"},
        {2, "banana"},
        {3, "cherry"}
    };

    map<int, string> m3(m2.begin(), m2.end()); // Copy constructor
    map<string, int> m4(m1);                 // Another copy

    //────────────────────────────────────────────
    // 🔸 2. INSERTION METHODS
    //────────────────────────────────────────────

    m1.insert({"tv", 50});             // insert using pair
    m1.emplace("ac", 40);              // emplace is faster, constructs in-place , no need to pass with { }
    m1["fan"] = 25;                    // operator[] also inserts if key not present

    //────────────────────────────────────────────
    // 🔸 3. ACCESS & MODIFYING ELEMENTS
    //────────────────────────────────────────────

    cout << "m1[\"tv\"] = " << m1["tv"] << "\n";   // access
    m1["tv"] = 60;                                // modify
    cout << "After modifying, m1[\"tv\"] = " << m1["tv"] << "\n";

    //────────────────────────────────────────────
    // 🔸 4. TRAVERSING THE MAP
    //────────────────────────────────────────────

    cout << "\nAll key-value pairs:\n";
    for (auto& pair : m1) { // & not necessary here
        cout << pair.first << " : " << pair.second << "\n";  // pair.first = key , pair.second = value
    }

    //────────────────────────────────────────────
    // 🔸 5. FINDING & COUNTING KEYS
    //────────────────────────────────────────────

    // if found, iterator is returned. if key value pair not found then m.end() is returned

    if (m1.count("ac")) {
        cout << "\nKey 'ac' found with value: " << m1["ac"] << "\n";
    } else {
        cout << "Key 'ac' not found.\n";
    }

    auto it = m1.find("fan");  // returns iterator to key or m1.end()
    if (it != m1.end()) {
        cout << "Found: " << it->first << " : " << it->second << "\n"; // -> used to acces key and pair from iterator as first and second
    }

    //────────────────────────────────────────────
    // 🔸 6. ERASE ELEMENTS
    //────────────────────────────────────────────

    m1.erase("fan");                   // erase by key
    if (m1.find("fan") == m1.end())
        cout << "'fan' successfully erased.\n";

    // erase using iterator
    auto iter = m1.find("ac");
    if (iter != m1.end()) {
        m1.erase(iter);
        cout << "'ac' erased using iterator.\n";
    }

    //────────────────────────────────────────────
    // 🔸 7. SIZE, EMPTY, CLEAR
    //────────────────────────────────────────────

    cout << "\nSize of map: " << m1.size() << "\n";
    cout << boolalpha << "Is map empty? " << m1.empty() << "\n";

    m1.clear();  // removes all key-value pairs
    cout << "After clearing, is map empty? " << m1.empty() << "\n";

    return 0;
}

/*
────────────────────────────────────────────
✅ SAMPLE OUTPUT:

m1["tv"] = 50  
After modifying, m1["tv"] = 60  

All key-value pairs:  
ac : 40  
fan : 25  
tv : 60  

Key 'ac' found with value: 40  
Found: fan : 25  
'fan' successfully erased.  
'ac' erased using iterator.  

Size of map: 1  
Is map empty? false  
After clearing, is map empty? true
────────────────────────────────────────────
*/
