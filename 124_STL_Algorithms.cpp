// OTHER ALGORITHMS + STL UTILITY FUNCTIONS

/*
────────────────────────────────────────────
// ✅ REVERSE
// → reverse(start_iterator, end_iterator)
// → Reverses the elements in the range [start, end)
// → Works with: vector, array, deque, string, etc.
// → Pass iterators: container.begin(), container.end()
// → Time Complexity: O(n)

// ✅ NEXT PERMUTATION
// → next_permutation(start_iterator, end_iterator)
// → Rearranges elements into lexicographically next greater permutation
// → Returns true if such permutation exists, else false
// → Works with containers like vector, array (random-access)
// → Pass iterators: container.begin(), container.end()
// → Time Complexity: O(n)

// ✅ SORT
// → sort(start_iterator, end_iterator)
// → Sorts the range [start, end) in ascending order
// → Pass iterators: container.begin(), container.end()
// → Time Complexity: O(n log n)

// ✅ SWAP
// → swap(a, b)
// → Swaps the values of a and b
// → Works with: variables, pointers, iterators, container elements
// → Time Complexity: O(1)
// → Examples: swap(x, y), swap(vec[i], vec[j]), swap(it1, it2)

// ✅ MIN / MAX
// → min(a, b), max(a, b)
// → Return the smaller/larger of two values
// → Works with: int, float, char, etc.
// → Time Complexity: O(1)

// ✅ MIN_ELEMENT / MAX_ELEMENT
// → min_element(start_iterator, end_iterator)
// → max_element(start_iterator, end_iterator)
// → Returns iterator to min/max element in the range [start, end)
// → Pass iterators: container.begin(), container.end()
// → Use *it to access value
// → Time Complexity: O(n)

// ✅ BINARY_SEARCH
// → binary_search(start_iterator, end_iterator, value)
// → Returns true if value exists in sorted range [start, end)
// → Works with: vector, array, etc. (requires sorted data)
// → Pass iterators: container.begin(), container.end()
// → Time Complexity: O(log n)

// ✅ __builtin_popcount(n), __builtin_popcountll(n)
// → GCC built-in to count number of set bits (1s) in integer
// → __builtin_popcount(n): for int
// → __builtin_popcountll(n): for long long
// → Time Complexity: O(1)

// ✅ std::popcount(n) → C++20 only
// → Requires: #include <bit> and -std=c++20
// → Returns number of set bits (1s) in unsigned number
// → Works with: unsigned int, long, long long
// → Time Complexity: O(1)

// ✅ Popcountl (for long integers)

// ✅ Popcount ll (for long long integers)

────────────────────────────────────────────
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <bit> // for std::popcount (C++20)
using namespace std;

int main() {
    // ───────────────────────────────────────────────
    // Basic reverse and partial reverse

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "Original Vector: ";
    for (int val : vec) cout << val << " "; cout << endl;

    reverse(vec.begin(), vec.end());
    cout << "Reversed Vector: ";
    for (int val : vec) cout << val << " "; cout << endl;

    reverse(vec.begin()+3, vec.end()-2); 
    // '+' and '-' work because vec.begin() is a random-access iterator
    // advance and distance can be used for general iterators like auto itr

    cout << "Partial Reversal [3, end-2): ";
    for (int val : vec) cout << val << " "; cout << endl;

    sort(vec.begin(), vec.end()); // Restore order

    // ───────────────────────────────────────────────
    // Next Permutation

    vector<int> v1 = {1, 2, 3, 4, 5};
    next_permutation(v1.begin(), v1.end());
    cout << "Next Permutation: ";
    for (int val : v1) cout << val << " "; cout << endl;

    // ───────────────────────────────────────────────
    // swap, min, max with variables

    int a = 12, b = 14;
    cout << "Max: " << max(a, b) << " and Min: " << min(a, b) << endl;
    cout << "Before Swap → a = " << a << ", b = " << b << endl;
    swap(a, b);
    cout << "After Swap → a = " << a << ", b = " << b << endl;

    // ───────────────────────────────────────────────
    // swap with vector elements (using iterators)

    vector<int> vv = {10, 20, 30, 40};
    swap(vv[0], vv[2]); // Swap elements by index
    cout << "Swapped Elements [0,2]: ";
    for (int val : vv) cout << val << " "; cout << endl;

    // OR using iterators:
    swap(*(vv.begin()), *(vv.begin()+2));

    // ───────────────────────────────────────────────
    // swap arrays, vectors entirely

    array<int, 3> arr1 = {1, 2, 3}, arr2 = {4, 5, 6};
    swap(arr1, arr2); // swaps full array
    cout << "Swapped Arrays: ";
    for (int val : arr1) cout << val << " "; cout << endl;

    vector<int> va = {100, 200}, vb = {300, 400};
    swap(va, vb); // swaps full vectors
    cout << "Swapped Vectors: ";
    for (int val : va) cout << val << " "; cout << endl;

    // ───────────────────────────────────────────────
    // min_element and max_element   dereference the iterator

    vector<int> v = {15, 3, 9, 42, 7};
    auto min_it = min_element(v.begin(), v.end());
    auto max_it = max_element(v.begin(), v.end());

    cout << "Min Element = " << *min_it << ", Max Element = " << *max_it << endl;

    // ───────────────────────────────────────────────
    // Binary Search (returns bool)

    vector<int> sorted_vec = {2, 4, 6, 8, 10, 12};
    cout<<boolalpha;
    cout << "Is 6 present? " << binary_search(sorted_vec.begin(), sorted_vec.end(), 6) << endl;
    cout << "Is 7 present? " << binary_search(sorted_vec.begin(), sorted_vec.end(), 7) << endl;

    // ───────────────────────────────────────────────
    // Built-in Popcount (count set bits)

    int x = 13; // binary: 1101
    cout << "Set Bits in 13: " << __builtin_popcount(x) << endl;

    long long y = 123456789123456;
    cout << "Set Bits (long long): " << __builtin_popcountll(y) << endl;

    // C++20 style (if supported)
    // cout << "std::popcount(13): " << std::popcount(13) << endl;

    return 0;
}

/*
Example Output:

Original Vector: 1 2 3 4 5 6 7 8 9 
Reversed Vector: 9 8 7 6 5 4 3 2 1 
Partial Reversal [3, end-2): 9 8 7 2 3 4 5 6 1 
Next Permutation: 1 2 3 5 4 
Max: 14 and Min: 12
Before Swap → a = 12, b = 14
After Swap → a = 14, b = 12
Swapped Elements [0,2]: 30 20 10 40 
Swapped Arrays: 4 5 6 
Swapped Vectors: 300 400 
Min Element = 3, Max Element = 42
Is 6 present? 1
Is 7 present? 0
Set Bits in 13: 3
Set Bits (long long): 30
*/
