// ✅ LeetCode Problem: 88. Merge Sorted Array
// 📌 Question (Brief):
// You are given two sorted integer arrays nums1 and nums2, with lengths m and n respectively.
// Merge nums2 into nums1 as one sorted array **in-place**.
// The final sorted array should be stored inside nums1.

// 🚀 Solution Name: In-place Merge from End
// ✅ Time Complexity: O(m + n) — we visit every element at most once.
// ✅ Space Complexity: O(1) — no extra space used (modifying nums1 in-place).
// ✅ Is it Optimal? YES — this is the most optimal in-place solution for merging two sorted arrays.
// ✅ Will it be accepted on LeetCode? YES — No TLE/MLE issues since it's efficient and uses constant space.

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // ✅ Main function to merge nums2 into nums1
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        // 🧠 Start filling nums1 from the back (highest index), because we don't want to overwrite its valid values
        int idx = m + n - 1;  // Index to place the next largest number
        int i = m - 1;        // Last valid element in nums1
        int j = n - 1;        // Last element in nums2

        // 🔁 While both arrays have elements to compare
        while (i >= 0 && j >= 0) {
            if (nums1[i] >= nums2[j]) {
                nums1[idx] = nums1[i];  // Place nums1[i] at idx
                i--;
            } else {
                nums1[idx] = nums2[j];  // Place nums2[j] at idx
                j--;
            }
            idx--;
        }

        // 🔁 If nums2 still has elements left, copy them
        while (j >= 0) {
            nums1[idx] = nums2[j];
            j--;
            idx--;
        }

        // 🟨 No need to copy nums1's remaining elements (i >= 0), because they are already in place
    }
};

/*
====================================================
💡 Logic and Explanation:

- We're given two sorted arrays:
  - `nums1` has size `m + n`, where the first `m` elements are valid and the rest are zero-filled placeholders.
  - `nums2` has `n` valid sorted elements.

- If we merged from the front of `nums1`, we would **overwrite its valid elements**.
  👉 So we start from the end (index `m + n - 1`) and insert the largest element from the back of either array.

- We compare `nums1[i]` and `nums2[j]`:
    - If `nums1[i]` is greater, place it at index `idx` and move `i` and `idx` one step left.
    - Otherwise, place `nums2[j]` at index `idx` and move `j` and `idx` one step left.

- 🔁 This continues until either `i < 0` or `j < 0`.

🔍 What happens when `j < 0` (nums2 exhausted)?
    ✅ No problem at all. It means all elements from nums2 are merged and the remaining nums1 elements are already in place (sorted).
    Example: nums1 = [1,2,3,0,0,0], nums2 = [1,2,3] → fully merged after loop.

🔍 What if `i < 0` (nums1 exhausted)?
    ⚠️ Can be a problem. It means all original elements from nums1 have been used.
    But if `j >= 0`, we must still copy the remaining elements from nums2 to nums1, because they are smaller and must appear at the beginning.
    That's why we have the second loop: `while(j >= 0)`.

✳️ We **do not need** a loop for `i >= 0` because if elements in `nums1` are remaining, they are already in their correct position.

====================================================
🧪 Example for Testing:
*/

int main() {
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {2, 5, 6};
    int n = 3;

    Solution sol;
    sol.merge(nums1, m, nums2, n);

    cout << "Merged Array: ";
    for (int num : nums1) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}

/*
Expected Output:
Merged Array: 1 2 2 3 5 6

Explanation:
- Start comparing from the back:
  nums1: [1,2,3,_,_,_]  i=2
  nums2: [2,5,6]        j=2
  → compare 3 and 6 → 6 goes to last

Step-by-step:
1. Compare 3 (nums1[2]) vs 6 (nums2[2]) → 6 is larger → nums1[5] = 6
2. Compare 3 vs 5 → 5 is larger → nums1[4] = 5
3. Compare 3 vs 2 → 3 is larger → nums1[3] = 3
4. Compare 2 vs 2 → tie → nums1[2] = 2
5. Compare 2 vs 1 → 2 is larger → nums1[1] = 2
6. nums2[0] = 1 → nums1[0] = 1

Final: [1,2,2,3,5,6]
*/

