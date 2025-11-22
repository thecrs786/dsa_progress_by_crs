// ✅ Difference between push_back() and emplace_back()
// ----------------------------------------------------------------
// Both functions are used to add elements at the end of containers
// like vector, list, deque, etc. But they work differently internally.
//
// 🔹 push_back(): only inserts, Constructs the object separately and then copies or moves it into the container.
//
// 🔹 emplace_back(): in-placce objects create, Constructs the object *in place* inside the container, avoiding extra copy or move.
//
// So, emplace_back is more efficient, especially with complex user-defined types or objects like pair.
// ----------------------------------------------------------------

#include <iostream>
#include <vector>
#include <utility>  // For std::pair
using namespace std;

int main() {
    
    vector<pair<int, int>> vec;

    // 🔸 Using push_back():
    // We have to construct a pair object manually before adding it.
    vec.push_back(make_pair(1, 2));      // OK
    vec.push_back({2, 3});               // Also works (C++11)
    // But internally: this creates a pair, then copies/moves it into the vector.

    // 🔸 Using emplace_back():
    // We directly pass the arguments of the pair — no need to explicitly write make_pair or braces.
    vec.emplace_back(3, 4);              // Preferred
    vec.emplace_back(5, 6);              // Cleaner syntax
    // Internally: constructs pair<int,int> in-place inside the vector — no copy/move.

    // 🔁 Printing the vector of pairs
    cout << "Vector of pairs: ";
    for (const auto& pr : vec) {
        cout << "(" << pr.first << ", " << pr.second << ") ";
    }
    cout << endl;


    return 0;
}