/*
🔁 ITERATORS in VECTORS:

→ vec.begin()   → points to the 0th index (first element)  
→ vec.end()     → points to index n (one past the last element)  

→ vec.rbegin()  → points to index n-1 (last element)  
→ vec.rend()    → points to the memory **just before** index 0 (i.e., one *before* the first element)


⚠️ Note:
vec.end() DOES NOT point to the last element.
It points to the memory **just after** the last valid element.

🧠 Range Syntax:
  - (vec.begin(), vec.end()) defines a **half-open range**
  - Meaning: [vec.begin(), vec.end())
  - Includes the first, excludes the last → covers full vector safely

✅ So: for (auto it = v.begin(); it != v.end(); ++it) → iterates the entire vector.
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    // Print first element
    cout << *(nums.begin()) << endl;   // 1

    // Print last element
    cout << *(nums.end() - 1) << endl; // 5

    // ❌ DO NOT do this:
    // cout << *(nums.end()) << endl;
    // → This is undefined behavior. It accesses memory outside the vector.

    return 0;
}
