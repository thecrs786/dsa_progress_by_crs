#include<iostream>
#include<string>   // Required for using std::string
#include<algorithm>  // Required for std::reverse
using namespace std;

int main(){

    /*
    ──────────────────────────────────────────────────────────────────────────────
    📌 std::string - Most Commonly Used Methods (Access/Modify/Add/Remove)
    ──────────────────────────────────────────────────────────────────────────────

    ░ Method               ░ Description                              ░ Index/Iter ░ Time    ░
    ░─────────────────────░──────────────────────────────────────────░───────────░─────────░
    ░ s.length() / size()  ░ Returns number of characters              ░ No        ░ O(1)     ░
    ░ s[i]                 ░ Access or modify single character         ░ Index     ░ O(1)     ░
    ░ s.at(i)              ░ Bounds-checked access                     ░ Index     ░ O(1)     ░
    ░ s.front()            ░ Returns first character                   ░ No        ░ O(1)     ░
    ░ s.back()             ░ Returns last character                    ░ No        ░ O(1)     ░
    ░ s.push_back(char)    ░ Add character at end                      ░ No        ░ O(1)     ░
    ░ s.pop_back()         ░ Remove last character                     ░ No        ░ O(1)     ░
    ░ s.append("str")      ░ Add string at end                         ░ No        ░ O(N)     ░
    ░ s.insert(pos, "x")   ░ Insert at pos                             ░ Index     ░ O(N)     ░
    ░ s.erase(pos, len)    ░ Erase from pos to pos+len                 ░ Index     ░ O(N)     ░
    ░ s.replace(pos, len, str) ░ Replace substring                     ░ Index     ░ O(N)     ░
    ░ s.clear()            ░ Remove all contents                       ░ No        ░ O(1)     ░
    ░ s.empty()            ░ Check if string is empty                  ░ No        ░ O(1)     ░
    ░ s.find("str")        ░ Find index of first occurrence            ░ No        ░ O(N)     ░
    ░ s.substr(pos, len)   ░ Extract substring                         ░ Index     ░ O(len)   ░
    ░ s.compare("str")     ░ Lexicographical compare                   ░ No        ░ O(N)     ░
    ░ s.c_str()            ░ Convert to C-style string (const char*)   ░ No        ░ O(1)     ░
    ░ std::reverse()       ░ Reverse the contents of the string        ░ Iter      ░ O(N)     ░ 🔹Algorithm
    ──────────────────────────────────────────────────────────────────────────────
    🔸 All functions are member functions of std::string
    🔸 Index: Integer position; Iterator: pointer-like object
    🔸 Time complexity varies mostly based on size of string or substring being worked on
    🔸 std::reverse() is an STL algorithm, not a string member function. It takes iterators.
    */

    string s = "Hello";

    // 1️⃣ LENGTH / SIZE
    cout << "Length: " << s.length() << endl;
    cout << "Size: " << s.size() << endl;

    // 2️⃣ INDEX ACCESS
    cout << "First char: " << s[0] << endl;       // Direct access
    s[0] = 'h';                                   // Modify character
    cout << "Modified: " << s << endl;

    // 3️⃣ at(i)
    cout << "Char at 1 (safe): " << s.at(1) << endl;
    // cout << s.at(100); // Throws runtime error if out of bounds

    // 4️⃣ front() and back()
    cout << "Front: " << s.front() << ", Back: " << s.back() << endl;

    // 5️⃣ push_back() and pop_back()
    s.push_back('!');
    cout << "After push_back: " << s << endl;
    s.pop_back();
    cout << "After pop_back: " << s << endl;

    // 6️⃣ append()
    s.append(" World");
    cout << "After append: " << s << endl;

    // append() adds an entire string (or substring) to the end, while push_back() adds a single character at the end.

    // 7️⃣ insert()
    s.insert(5, ",");
    cout << "After insert: " << s << endl;

    // 8️⃣ erase()
    s.erase(5, 1); // Remove the comma
    cout << "After erase: " << s << endl;

    // 9️⃣ replace()
    s.replace(6, 5, "Universe");  // Replace "World" with "Universe"
    cout << "After replace: " << s << endl;

    // 🔟 substr()
    string part = s.substr(6, 8); // Extract "Universe"
    cout << "Substring: " << part << endl;

    // 1️⃣1️⃣ find()
    int index = s.find("Uni");
    if(index != string::npos) {
        cout << "'Uni' found at index: " << index << endl;
    }

    // 1️⃣2️⃣ compare()
    cout << "Compare with 'hello Universe': " << s.compare("hello Universe") << endl;  // 0 if equal, <0 or >0 otherwise

    // 1️⃣3️⃣ c_str()
    const char* c_style = s.c_str();
    cout << "C-style string: " << c_style << endl;

    // 1️⃣4️⃣ clear() and empty()
    s.clear();
    cout << "After clear, is empty? " << (s.empty() ? "Yes" : "No") << endl;

    /*
    ────────────────────────────────────────────────────────────────────────
    🔁 REVERSE ALGORITHM (std::reverse)
    ────────────────────────────────────────────────────────────────────────
    ▪ Header: <algorithm>
    ▪ Prototype: std::reverse(iterator_begin, iterator_end)
    ▪ Time Complexity: O(N)
    ▪ Space Complexity: O(1)
    ▪ Why iterators?
        ↪ Because algorithms like std::reverse are generic and work on any container type that supports random-access or bidirectional iterators.
        ↪ Strings internally store characters like arrays, so begin() and end() give us positions to reverse in-place.
    ▪ Does not cause TLE or MLE
    ▪ ✅ Accepted by LeetCode and optimal in-place reversal
    */

    // 🔁 Example: Reverse a string using std::reverse
    string rev = "ReverseMe";
    cout << "Before reverse: " << rev << endl;

    // Reverse the entire string
    reverse(rev.begin(), rev.end());

    cout << "After reverse: " << rev << endl;

    return 0;
}
