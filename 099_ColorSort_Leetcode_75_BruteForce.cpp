// ✅ LeetCode Problem: Sort Colors
// --------------------------------------
// 🔸 Problem Brief:
// Given an array 'nums' with only 0s, 1s, and 2s (representing colors),
// sort the array in-place such that all 0s come first, followed by all 1s, and all 2s.
//
// 🔸 Input: nums = [2,0,2,1,1,0]
// 🔸 Output: [0,0,1,1,2,2]
//
// 🔸 Constraint for optimal solution (NOT followed here):
// Do not use library sort function. Solve in one pass with constant space.
//
// 🔸 This solution uses STL sort (not optimal, but accepted)

// Time Complexity : O(nlogn)

// Space complexity : O(1)

#include <iostream>
#include <vector>
#include <algorithm> // Required for sort()
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        // STL sort is used to sort the array in ascending order
        // Time complexity: O(n log n)
        // Space complexity: O(1) (in-place sort for vectors)

        sort(nums.begin(), nums.end());
        // We sort the vector using built-in quicksort-based function
        // Since the values are only 0, 1, 2 — it still works, though not optimal
    }
};

/*
🔍 LOGIC AND WORKING:
-----------------------------
This approach simply calls C++ STL's `sort()` function on the input vector.

1. `nums.begin()` returns an iterator to the start of the vector.
2. `nums.end()` returns an iterator to the end of the vector.
3. `sort(nums.begin(), nums.end())` sorts the entire vector in-place.

✅ This works correctly since it sorts 0s, 1s, and 2s in increasing order.
❌ But it is not optimal as it takes O(n log n) time, violating the "one-pass" requirement.

📌 This solution is acceptable only when constraints are relaxed and efficiency is not a concern.

*/

int main() {
    Solution obj;
    vector<int> nums = {2, 0, 2, 1, 1, 0};

    cout << "Original array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    obj.sortColors(nums); // Apply the sorting function

    cout << "Sorted array:   ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

/*
💻 OUTPUT:
---------------------
Original array: 2 0 2 1 1 0 
Sorted array:   0 0 1 1 2 2

📌 You can see the array is sorted correctly.
But remember: This is not optimal and wouldn't be acceptable
in interviews or strict one-pass constraint problems.
*/
