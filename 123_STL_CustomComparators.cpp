#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
────────────────────────────────────────────────────────────
🔹 CUSTOM COMPARATOR FUNCTION

This function tells the sort() function **how** to sort the pairs.

sort(vec.begin(), vec.end(), comparator);
- `comparator(p1, p2)` returns `true` if p1 should come before p2.

We're building logic to:
- First, sort based on the second element (ascending).
- If the second elements are **equal**, sort based on the first element (ascending).
────────────────────────────────────────────────────────────
*/
bool comparator(pair<int, int> p1, pair<int, int> p2) {
    // Primary condition: sort by second element
    if (p1.second < p2.second) return true;
    if (p1.second > p2.second) return false;

    // Secondary condition: if second elements are equal, sort by first element
    if (p1.first < p2.first) return true;
    else return false;
}

int main() {

    // Vector of pairs (unsorted)
    vector<pair<int, int>> vec = {
        {5, 4}, {3, 8}, {4, 8},
        {2, 6}, {1, 0}, {12, 9}, {10, 4}
    };

    /*
    🔹 Default sorting with sort(vec.begin(), vec.end());
    This sorts based on the **first element** of the pair (ascending).
    If two pairs have the same first element, then it checks second element.
    */
    sort(vec.begin(), vec.end());

    cout << "🔸 Sorted by FIRST element (default):\n";
    for (auto pair : vec) {
        cout << "[" << pair.first << " : " << pair.second << "] ";
    }
    cout << "\n\n";

    /*
    🔹 Custom sorting using comparator
    Now we sort based on second element, and break tie with first element.
    */
    sort(vec.begin(), vec.end(), comparator);

    cout << "🔸 Sorted by SECOND element (custom comparator):\n";
    for (auto pair : vec) {
        cout << "[" << pair.first << " : " << pair.second << "] ";
    }
    cout << "\n\n";

    /*
    🔹 Another example: Sorting in descending order based on FIRST element
    We can also use lambda functions (inline) instead of writing a separate comparator function
    */
    vector<pair<int, int>> anotherVec = {
        {3, 5}, {1, 9}, {6, 0}, {4, 4}, {6, 7}
    };

    sort(anotherVec.begin(), anotherVec.end(),
        [](pair<int, int> a, pair<int, int> b) {
            return a.first > b.first; // descending order of first element
        });

    cout << "🔸 Sorted by FIRST element (descending):\n";
    for (auto pair : anotherVec) {
        cout << "[" << pair.first << " : " << pair.second << "] ";
    }
    cout << "\n";

    return 0;
}

/*
────────────────────────────────────────────────────────────
📌 EXPLANATION — VECTOR OF PAIRS SORTING IN C++

👉 A `pair<int, int>` is a data type which holds two values:
   - pair.first
   - pair.second

👉 By default, `sort()` on a vector of pairs uses:
   - First: compares `first` of the pair
   - If `first` is same: compares `second`

🔹 Syntax:
   sort(vec.begin(), vec.end());                ➤ default: based on .first
   sort(vec.begin(), vec.end(), comparator);    ➤ custom logic

────────────────────────────────────────────
📌 COMPARATOR FUNCTION RULE

Comparator must return a `bool`. It should return:
   ➤ `true` if `p1` should come before `p2`
   ➤ `false` otherwise

➤ For example: Sort by second element ascending
    if(p1.second < p2.second) return true;

➤ To break ties with first element:
    if(p1.second == p2.second)
        return p1.first < p2.first;

────────────────────────────────────────────
📌 WHY AUTO WORKS FOR PAIR

In range-based loops:

    for (auto p : vec) { ... }

`auto` deduces the type as `pair<int, int>` — so we can access:
   - `p.first`
   - `p.second`

Unlike vectors of `int`, a pair doesn’t use indices like `p[0]`, `p[1]`.

────────────────────────────────────────────
📌 LAMBDA COMPARATOR

You can also use anonymous lambda function:

    sort(vec.begin(), vec.end(), [](pair<int,int> a, pair<int,int> b){
        return a.second < b.second;
    });

Lambdas are short, inline, and readable for small logic.
────────────────────────────────────────────
*/
