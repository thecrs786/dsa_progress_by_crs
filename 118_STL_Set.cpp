// SET in C++ STL (Also uses self balancing tree)
/*
────────────────────────────────────────────
📦 HEADER:           #include<set>
📁 Namespace:        using namespace std;
📌 Structure:        Balanced BST (Red-Black Tree)
📌 Properties:
   - Stores only UNIQUE elements.
   - Stores elements in **sorted order** (ascending by default).
   - No random access (no indexing like s[0]).
   - All operations take O(log N) time.

────────────────────────────────────────────
🔧 COMMONLY USED METHODS (with time complexities):

1. insert(x)         → Inserts x if not present        → O(log N)     ✅ single only
2. emplace(x)        → Faster version of insert        → O(log N)     ✅ single only
3. erase(x)          → Removes a specific value        → O(log N)     ✅ single only
4. erase(it)         → Removes using iterator          → O(1)         ✅ single only
5. erase(start, end) → Removes a range [start, end)    → O(K)         ✅ multiple (K elements)
6. find(x)           → Returns iterator to x if found  → O(log N)     ✅ uses iterator
7. count(x)          → Returns 1 if present, 0 if not  → O(log N)     ✅ returns int
8. size()            → Number of elements              → O(1)
9. empty()           → Checks if set is empty          → O(1)
10. clear()          → Erases all elements             → O(N)

────────────────────────────────────────────
✅ INSERT  | ❌ INDEXING  | ✅ ITERATOR SUPPORT
────────────────────────────────────────────
*/

#include<iostream>
#include<set>
using namespace std;

int main(){

    // ───────────────────────────────────────────────
    // 🔰 1. Initialization
    set<int> s1;  // empty set

    set<int> s2 = {10, 5, 20, 5, 30};  // duplicates ignored → {5, 10, 20, 30}

    set<int> s3(s2);  // copy constructor

    // ───────────────────────────────────────────────
    // 🔰 2. Inserting Elements
    s1.insert(7);          // O(log N)
    s1.emplace(5);         // preferred over insert for performance
    s1.emplace(1);
    s1.insert(8);          // even if inserted in middle, sorted order maintained

    cout << "\n🔹 Current set s1:\n";
    for(int val : s1){ cout << val << " "; }  // Output: 1 5 7 8
    cout << "\n";

    // ───────────────────────────────────────────────
    // 🔰 3. Using Iterators
    cout << "\n🔹 First element via iterator: " << *s1.begin() << "\n";
    cout << "🔹 Last element via iterator: " << *prev(s1.end()) << "\n";  // returns iterator of last element
     
    // *(s1.end()-1) can't be used here because '-' is invalid for iterators. so, *prev(s1.end()) is used  

    // ───────────────────────────────────────────────
    // 🔰 4. Modifying Set (no direct modify)
    // → Sets don't allow modification via index.
    // → To modify: erase + insert

    s1.erase(5);       // remove value
    s1.insert(6);      // insert new one

    cout << "\n🔹 Modified set (5 removed, 6 added):\n";
    for(int val : s1){ cout << val << " "; }  // Output: 1 6 7 8
    cout << "\n";

    // ───────────────────────────────────────────────
    // 🔰 5. count(x) → returns 1 if exists, else 0
    cout << "\n🔹 Count of 6: " << s1.count(6) << "\n";   // 1
    cout << "🔹 Count of 5: " << s1.count(5) << "\n";     // 0

    // ───────────────────────────────────────────────
    // 🔰 6. find(x) → returns iterator
    auto it = s1.find(7);
    if(it != s1.end()){
        cout << "\n🔹 Element found: " << *it << "\n";
    } else {
        cout << "🔹 Element not found\n";
    }

    // ───────────────────────────────────────────────
    // 🔰 7. erase(x), erase(it), erase(range)
    s1.erase(6);  // removes the value 6
    s1.erase(s1.find(7));  // removes element at iterator (7)

    // Insert more to demonstrate range erase
    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(40);

    // Erase range [10, end)
    auto start = s1.find(10);
    auto end = s1.end();
    s1.erase(start, end);

    cout << "\n🔹 Set after erasing from 10 to end:\n";
    for(int val : s1){ cout << val << " "; }  // Output: 1 8
    cout << "\n";

    // ───────────────────────────────────────────────
    // 🔰 8. Other Methods
    cout << "\n🔹 Size: " << s1.size() << "\n";
    cout << "🔹 Is Empty: " << (s1.empty() ? "Yes" : "No") << "\n";

    s1.clear();  // removes all
    cout << "🔹 After clear(), is Empty: " << (s1.empty() ? "Yes" : "No") << "\n";

    return 0;
}
