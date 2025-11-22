// ✅ STL PAIR – Utility component for storing two values
// 📌 Defined in <utility> header and part of STL Utilities (not a container)
//    Can store two elements of ANY type (not necessarily same type)
// 📁 Header: #include<utility>
// 📁 Namespace: using namespace std;

#include<iostream>
#include<vector>
#include<utility>
#include<tuple> // required for tie()
using namespace std;

/*
────────────────────────────────────────────
📚 STL PAIR: COMPLETE REFERENCE
────────────────────────────────────────────

🔸 A `pair` is a container to store two heterogeneous values together.
    - Header: <utility>
    - Default underlying structure: struct with two fields: `.first` and `.second`
    - Commonly used in maps, priority queues, coordinate problems, etc.

────────────────────────────────────────────
📌 METHODS, ACTIONS & DETAILS
────────────────────────────────────────────

| ✅ Category        | ✅ Operation/Example                        | ⏱️ Time Complexity | 🔁 Iterator | 🧩 Single/Multiple |
|-------------------|---------------------------------------------|--------------------|-------------|--------------------|
| Initialization    | `pair<int, int> p = {a, b};`                | O(1)               | ❌          | Single             |
|                   | `make_pair(a, b)`                           | O(1)               | ❌          | Single             |
|                   | `pair<T1,T2> p(a, b);`                      | O(1)               | ❌          | Single             |
|                   | `pair<T1,T2> q = p;` (copy init)            | O(1)               | ❌          | Single             |
|                   | `pair<int, pair<int,int>> p` (nested)       | O(1)               | ❌          | Single             |
| Access            | `p.first`, `p.second`                       | O(1)               | ❌          | Single             |
| Modify            | `p.first = val`, `p.second = val`           | O(1)               | ❌          | Single             |
| Compare           | `p1 < p2`, `p1 == p2`                        | O(1)               | ❌          | Single             |
| Swap              | `swap(p1, p2)`                              | O(1)               | ❌          | Pair vs Pair       |
| Unpack (C++11)    | `tie(a, b) = p;`                            | O(1)               | ❌          | Single             |
| Ignore (C++11)    | `tie(a, ignore) = p;`                       | O(1)               | ❌          | Single             |
| Unpack (C++17)    | `auto [a, b] = p;`                          | O(1)               | ❌          | Single             |
| Nested Access     | `p.second.first`, `p.second.second`         | O(1)               | ❌          | Single             |
| Pair in Container | `vector<pair<int, int>> vp;`                | O(1) insert        | ✅ Loop     | Multiple           |
| Access in loop    | `for (auto &pr : vp) pr.first/second`       | O(n) total         | ✅ Required | Multiple           |
| Modify in loop    | `auto &pr = vp[i]; pr.first = ...`          | O(1) per element   | ✅ Required | Multiple           |

────────────────────────────────────────────
📎 EXTRA NOTES
────────────────────────────────────────────
🔹 Comparison follows lexicographical order:
    pair(a1, b1) < pair(a2, b2) means:
        → if a1 < a2 OR (a1 == a2 AND b1 < b2)

🔹 `tie()` is often used in sorting, structured bindings, or comparisons.

🔹 Works great with `map`, `set`, and containers of pairs.
    Example: `map<string, pair<int, int>> studentMarks;`

🔹 Structured binding (`auto [a, b]`) needs C++17 or above.

🔹 Prefer `auto` to avoid long template declarations when looping over containers of pairs.

────────────────────────────────────────────
*/


int main() {

    // ─────────────────────────────────────────────────────────────
    // ✅ 1. INITIALIZATION METHODS
    // ─────────────────────────────────────────────────────────────

    // a) Direct brace initialization
    pair<int, int> p1 = {10, 20};

    // b) Constructor style
    pair<char, int> p2('A', 100);

    // c) make_pair() – Useful when types are long/complex
    pair<string, double> p3 = make_pair("CRS", 3.14);

    // d) Copy initialization
    pair<int, int> p4 = p1;  // p4 = {10, 20}

    // e) Uniform initialization with nested pair
    pair<int, pair<int, int>> p5 = {1, {2, 3}}; // Nested pair

    // ─────────────────────────────────────────────────────────────
    // ✅ 2. ACCESSING ELEMENTS
    // ─────────────────────────────────────────────────────────────

    cout << "p1.first = " << p1.first << endl;     // 10
    cout << "p1.second = " << p1.second << endl;   // 20

    cout << "Nested p5: " << p5.first << ", " 
         << p5.second.first << ", " 
         << p5.second.second << endl;              // 1, 2, 3

    // ─────────────────────────────────────────────────────────────
    // ✅ 3. MODIFYING VALUES
    // ─────────────────────────────────────────────────────────────

    p1.first = 99;
    p1.second = 100;
    cout << "Modified p1: " << p1.first << ", " << p1.second << endl;

    // ─────────────────────────────────────────────────────────────
    // ✅ 4. COMPARISON
    // ─────────────────────────────────────────────────────────────

    pair<int, int> a = {1, 2};
    pair<int, int> b = {1, 3};

    if (a < b) cout << "a < b\n";  // Lexicographical compare: first then second

    // ─────────────────────────────────────────────────────────────
    // ✅ 5. SWAPPING PAIRS
    // ─────────────────────────────────────────────────────────────

    swap(a, b);  // Now a = {1, 3}, b = {1, 2}
    cout << "a: " << a.first << "," << a.second << endl;

    // ─────────────────────────────────────────────────────────────
    // ✅ 6. tie() – UNPACK pair elements into variables
    // 📌 Used when you want to extract both elements separately
    // 📌 Available via <tuple>
    // 📌 Can also ignore values using std::ignore
    // ─────────────────────────────────────────────────────────────

    int x; string y;
    pair<int, string> info = {42, "crs"};
    tie(x, y) = info;

    cout << "Unpacked x: " << x << ", y: " << y << endl;

    // Ignoring one of the values:
    tie(x, ignore) = info;  // only get x

    // ─────────────────────────────────────────────────────────────
    // ✅ 7. Structured Bindings (C++17)
    // 📌 Cleaner unpacking of pair using auto [a, b] syntax
    // ─────────────────────────────────────────────────────────────

    auto [id, name] = info;
    cout << "Structured Bindings -> id: " << id << ", name: " << name << endl;

    // ─────────────────────────────────────────────────────────────
    // ✅ 8. Nested Pairs Example
    // ─────────────────────────────────────────────────────────────

    pair<string, pair<int, int>> student = {"CRS", {18, 99}};
    cout << "Name: " << student.first 
         << ", Age: " << student.second.first 
         << ", Marks: " << student.second.second << endl;

    // ─────────────────────────────────────────────────────────────
    // ✅ 9. Pair in container (array/vector)
    // ─────────────────────────────────────────────────────────────

    pair<int, int> arr[3];
    arr[0] = {1, 2};
    arr[1] = {3, 4};
    arr[2] = {5, 6};

    for (int i = 0; i < 3; i++) {
        cout << arr[i].first << ", " << arr[i].second << endl;
    }

    vector<pair<int, int>> vec = {{1, 10}, {2, 20}, {3, 30}};
    for (auto &pr : vec) { // & not required here, but required when modifying
        cout << "(" << pr.first << ", " << pr.second << ") ";
    }cout<<endl;

    for (auto &pr : vec) {
    pr.second *= 2;  // This modifies the actual vector elements
}

    for (auto pr : vec) { // printing withour &
    cout << "(" << pr.first << ", " << pr.second << ") ";
}


    return 0;
}
