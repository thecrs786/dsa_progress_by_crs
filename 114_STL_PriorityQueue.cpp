//────────────────────────────────────────────
// 📚 C++ STL PRIORITY_QUEUE COMPLETE NOTES
//────────────────────────────────────────────

/*
────────────────────────────────────────────
🔸 What is a priority_queue?

A `priority_queue` is a container adaptor that provides constant-time access to the element with the highest priority.
By default, it is implemented using a **Max Heap** (largest element at the top).

📦 Internally backed by a **vector** and uses heap functions like:
    - push_heap
    - pop_heap
    - make_heap

It is part of the STL `<queue>` header.

────────────────────────────────────────────
🔹 No iterator or index-based access:
You cannot use:
    - `begin()` / `end()` 
    - Access via index like `pq[i]`
Because it is implemented as a heap (not a linear structure).

────────────────────────────────────────────
🔹 Time Complexities of Common Operations:

| Method           | Type         | Time Complexity |
|------------------|--------------|------------------|
| push(x)          | Insert       | O(log n)         |
| emplace(x)       | Insert       | O(log n)         |
| top()            | Access max   | O(1)             |
| pop()            | Remove max   | O(log n)         |
| size()           | Inspect      | O(1)             |
| empty()          | Inspect      | O(1)             |
| swap(q2)         | Bulk modify  | O(1)             |

────────────────────────────────────────────
*/

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // for std::greater
using namespace std;

int main() {

    //────────────────────────────────────────────
    // 🔸 METHODS OF INITIALIZATION
    //────────────────────────────────────────────

    // 1. Default max heap (int)
    priority_queue<int> pq1;

    // 2. Min heap (int)
    priority_queue<int, vector<int>, greater<int>> pq2;  // greater<int> is a functor.

    // 3. Initialize with existing vector (max heap)
    vector<int> vec = {4, 1, 8, 2, 5};
    priority_queue<int> pq3(vec.begin(), vec.end()); // automatically heapified

    // 4. Initialize min heap from vector
    priority_queue<int, vector<int>, greater<int>> pq4(vec.begin(), vec.end());

    // 5. Using pairs with custom comparator (see below)

    //────────────────────────────────────────────
    // 🔸 INSERTION METHODS (ONLY WAY TO ADD)
    //────────────────────────────────────────────

    pq1.push(10);   // O(log n)
    pq1.push(30);
    pq1.push(5);
    pq1.emplace(20);  // More efficient when element is constructed in-place

    //────────────────────────────────────────────
    // 🔸 ACCESS & INSPECTION
    //────────────────────────────────────────────

    cout << "Top element (max): " << pq1.top() << endl;  // 30
    cout << "Size: " << pq1.size() << endl;
    cout << boolalpha << "Is pq1 empty? " << pq1.empty() << endl;

    //────────────────────────────────────────────
    // 🔸 PRINTING A PRIORITY_QUEUE (Without Destroying)
    //────────────────────────────────────────────

    // NOTE: You must copy the queue and pop from the copy

    cout << "Printing pq1 (Max-Heap): ";
    priority_queue<int> temp1 = pq1;
    while (!temp1.empty()) {
        cout << temp1.top() << " ";
        temp1.pop();
    }
    cout << "\n";

    cout << "Printing pq4 (Min-Heap): ";
    priority_queue<int, vector<int>, greater<int>> temp2 = pq4;
    while (!temp2.empty()) {
        cout << temp2.top() << " ";
        temp2.pop();
    }
    cout << "\n";

    //────────────────────────────────────────────
    // 🔸 REMOVAL
    //────────────────────────────────────────────

    pq1.pop(); // removes the highest element (30)
    cout << "After pop, top: " << pq1.top() << endl; // Now 20

    //────────────────────────────────────────────
    // 🔸 SWAP TWO PRIORITY_QUEUES
    //────────────────────────────────────────────

    priority_queue<int> a, b;
    a.push(100); a.push(200);
    b.push(1); b.push(2);

    cout << "\nBefore swap:\nA top: " << a.top() << " | B top: " << b.top() << endl;
    a.swap(b);
    cout << "After swap:\nA top: " << a.top() << " | B top: " << b.top() << endl;

    //────────────────────────────────────────────
    // 🔸 CUSTOM COMPARATOR EXAMPLE (PAIR SORTING)
    //────────────────────────────────────────────

    struct CompareSecond {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second; // Min-heap based on second value
        }
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> customPQ;
    customPQ.push({1, 100});
    customPQ.push({2, 50});
    customPQ.push({3, 75});

    cout << "\nCustom Comparator (pair<int,int> based on second):\n";
    while (!customPQ.empty()) {
        auto p = customPQ.top();
        cout << "{" << p.first << ", " << p.second << "} ";
        customPQ.pop();
    }
    cout << "\n";

    return 0;
}

/*
────────────────────────────────────────────
✅ SAMPLE OUTPUT:

Top element (max): 30  
Size: 4  
Is pq1 empty? false  
Printing pq1 (Max-Heap): 30 20 10 5  
Printing pq4 (Min-Heap): 1 2 4 5 8  
After pop, top: 20  

Before swap:  
A top: 200 | B top: 2  
After swap:  
A top: 2 | B top: 200  

Custom Comparator (pair<int,int> based on second):  
{2, 50} {3, 75} {1, 100}
────────────────────────────────────────────
*/
