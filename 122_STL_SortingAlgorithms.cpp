//────────────────────────────────────────────────────────────
// 📌 C++ STL SORTING — Complete Reference with Explanation
//
// There are 5 important ways to sort data using `sort()` in STL:
//────────────────────────────────────────────────────────────
//
// (1) sort(arr, arr + n)
//     👉 Sorts a C-style array in ascending order
//     👉 We pass **pointers** (arr is pointer to arr[0])
//
// (2) sort(arr, arr + n, greater<int>())
//     👉 Sorts a C-style array in descending order
//     👉 Comparator: `greater<int>()` from <functional>
//
// (3) sort(v.begin(), v.end())
//     👉 Sorts a vector in ascending order
//     👉 We pass **iterators** (begin() to end())
//
// (4) sort(v.begin(), v.end(), greater<int>())
//     👉 Sorts a vector in descending order
//     👉 Uses comparator just like in arrays
//
// (5) sort(v.rbegin(), v.rend())
//     👉 Also sorts a vector in descending order
//     👉 Uses **reverse iterators** directly
//
// 📌 Sorting a vector of pairs:
//     👉 Pairs are sorted by `first` element by default
//     👉 If `first` is equal, then sorted by `second`
//     👉 Custom comparators can change this behavior
//
// 🧠 STL `sort(start, end)` uses [start, end) — `end` is excluded
//────────────────────────────────────────────────────────────

#include<iostream>
#include<vector>
#include<algorithm>     // for sort()
#include<functional>    // for greater<int>()
using namespace std;

int main() {

    // Data for testing
    int arr[]  = {7, 8, 4, 5, 2, 9, 1, 3, 0, 6};
    int arr2[] = {7, 8, 4, 5, 2, 9, 1, 3, 0, 6};
    int n = 10;

    vector<int> v = {7, 8, 4, 5, 2, 9, 1, 3, 0, 6};

    //────────────────────────────────────────────
    // (1) ✅ SORTING C-ARRAY IN ASCENDING ORDER
    sort(arr, arr + n);
    cout << "Sorted Array (Ascending): ";
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    //────────────────────────────────────────────
    // (2) ✅ SORTING C-ARRAY IN DESCENDING ORDER
    sort(arr2, arr2 + n, greater<int>());
    cout << "Sorted Array (Descending): ";
    for(int i = 0; i < n; i++) cout << arr2[i] << " ";
    cout << endl;

    //────────────────────────────────────────────
    // (3) ✅ SORTING VECTOR IN ASCENDING ORDER
    sort(v.begin(), v.end());
    cout << "Sorted Vector (Ascending): ";
    for(int val : v) cout << val << " ";
    cout << endl;

    //────────────────────────────────────────────
    // (4) ✅ SORTING VECTOR IN DESCENDING ORDER
    sort(v.begin(), v.end(), greater<int>());
    cout << "Sorted Vector (Descending): ";
    for(int val : v) cout << val << " ";
    cout << endl;

    //────────────────────────────────────────────
    // (5) ✅ SORTING VECTOR USING REVERSE ITERATORS
    sort(v.rbegin(), v.rend()); // sorts in descending order
    cout << "Vector (Descending using reverse iterators): ";
    for(int val : v) cout << val << " ";
    cout << endl;

    //────────────────────────────────────────────
    // (6) ✅ SORTING VECTOR OF PAIRS BY FIRST ELEMENT
    //
    // Default behavior:
    //   If first elements are different → sort by .first
    //   If first elements are same      → sort by .second
    //
    //   pair<int, int> sorts lexicographically by default
    //────────────────────────────────────────────
    vector<pair<int, int>> vp = {{3, 9}, {1, 7}, {2, 4}, {3, 5}, {2, 2}};
    
    sort(vp.begin(), vp.end());  // default comparator: sorts by first, then second

    cout << "Sorted Vector of Pairs (by first, then second): ";
    for(auto p : vp) {
        cout << "{" << p.first << "," << p.second << "} ";
    }
    cout << endl;

    return 0;
}
