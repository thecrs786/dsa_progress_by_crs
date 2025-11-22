// ✅ LeetCode Problem: Next Permutation
// 🔹 Question (Brief):
// Given an array of integers 'nums', rearrange the numbers into the lexicographically next greater permutation of numbers.
// If such arrangement is not possible, rearrange it as the lowest possible order (i.e., sorted in ascending order).
// You must do this **in-place** and use only constant extra memory.

// 🔹 Method: nextPermutation()
// 🔹 Time Complexity: O(n)
// 🔹 Space Complexity: O(1) – in-place
// 🔹 Optimality: ✅ Yes, this is the most optimal solution possible
// 🔹 Verdict: ✅ Will get accepted by LeetCode. No risk of TLE or MLE.

// ✅ This is the optimal solution using the well-known "Next Lexicographical Permutation" algorithm.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int pivot = -1, swapidx = n - 1;

        // 🔹 Step 1: Find the pivot point (first index from right where nums[i] < nums[i+1])
        // This identifies the point where the order stops being increasing from the right.
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                pivot = i; // Found the first decreasing element from the end.
                break;
            }
        }

        // 🔹 Step 2: If no such pivot found, array is the last permutation → reverse to lowest.
        if (pivot == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // 🔹 Step 3: Find the smallest element greater than nums[pivot] from the rightmost side
        // Why? Because to make it the next permutation, we want the next bigger number after pivot.
        for (int j = n - 1; j > pivot; j--) {
            if (nums[j] > nums[pivot]) {
                swapidx = j;
                break;
            }
        }

        // 🔹 Step 4: Swap pivot with that next greater element
        swap(nums[pivot], nums[swapidx]);

        // 🔹 Step 5: Reverse the subarray after pivot to get the lowest order (ascending)
        // Why? Because we want the smallest next permutation — the tail must be sorted ascending.
        reverse(nums.begin() + pivot + 1, nums.end());
    }
};



// 🔍 Detailed Explanation of Logic:
/*

The key idea is to generate the **next lexicographical permutation**. Here's how it works:

1️⃣ Pivot Finding:
   - Traverse from the end of the array and find the first element which is **smaller than its next element**.
   - This position marks where the permutation stops being increasing from the right.
   - This element is called the **pivot**.
   - If such a pivot doesn't exist (i.e., the array is in descending order), it's already the last permutation. So we reverse it.

2️⃣ Swap Element Finding:
   - We need to find the **smallest element greater than nums[pivot]**, starting from the right.
   - This ensures we’re increasing the number at the pivot index **just enough** to get the next permutation.

3️⃣ Swapping:
   - We swap the pivot with this next greater element to form a slightly higher permutation.

4️⃣ Reversing:
   - Finally, reverse the subarray after the pivot to ensure the tail is in the **lowest possible order**.
   - This guarantees that the permutation is the **next smallest possible** greater one.

🔥 Why this works:
   - The algorithm ensures that we make the smallest possible increment to the current permutation.
   - All steps run in linear time, and no extra space is used.

*/


// ✅ Example for Running and Testing:

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3}; // Try changing this to [3,2,1] or [1,1,5] for more test cases
    cout << "Original array: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    sol.nextPermutation(nums);

    cout << "Next permutation: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    return 0;
}


/*
🔎 Example Dry Run for Input: [1, 2, 3]
- Step 1: Pivot = index 1 (nums[1] = 2, because 2 < 3)
- Step 2: Find element greater than 2 from right → 3
- Step 3: Swap → [1, 3, 2]
- Step 4: Reverse part after pivot → already [2], so stays same
✅ Output: [1, 3, 2]

Another Case: [3, 2, 1]
- Step 1: No pivot found
- Step 2: Reverse whole array
✅ Output: [1, 2, 3]
*/

