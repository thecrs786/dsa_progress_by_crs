/*
Question (LeetCode 75 - Sort Colors):
Given an array `nums` with n objects colored red, white, or blue (represented by 0, 1, 2), sort them in-place so that objects of the same color are adjacent, with the colors in the order red (0), white (1), and blue (2).

Method: Dutch National Flag (DNF) Algorithm
Time Complexity: O(n)  // single pass through the array
Space Complexity: O(1) // constant extra space
Optimal?: Yes, this is the most optimal solution for in-place one-pass sorting.
LeetCode Acceptance: Will be accepted within time/memory limits (no TLE or MLE).
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
    sortColors(): sorts `arr` of 0s,1s,2s in one pass.
    low (boundary for 0s), mid (current index), high (boundary for 2s).
    Partitions:
      [0 .. low-1]   : all 0s
      [low .. mid-1] : all 1s
      [mid .. high]  : unknown
      [high+1 .. end]: all 2s
    */
    void sortColors(vector<int>& arr) {
        int low = 0;
        int mid = 0;
        int high = arr.size() - 1;

        // Process elements until mid > high (unknown region empty)
        while (mid <= high) {
            if (arr[mid] == 0) {
                // Case 0: swap with `low` boundary, extend 0-region
                swap(arr[low], arr[mid]);
                // Move both low and mid forward, as swapped-in element at mid is already processed
                low++;
                mid++;
            }
            else if (arr[mid] == 1) {
                // Case 1: correct region (middle), just move mid forward
                mid++;
            }
            else { // arr[mid] == 2
                // Case 2: swap with `high` boundary, extend 2-region
                swap(arr[mid], arr[high]);
                // Only decrease high; do NOT move mid, because swapped-in element at mid is unprocessed
                high--;
            }
        }
    }
};
/*
LOGIC:

We create three pointers: low, mid, and high.
Initially, all are empty or uninitialized for sorting, and we partition the array into four parts:

- 0s are filled in nums from index 0 to low-1 (first partition).
- 1s are placed from low to mid-1 (second partition).
- 2s are placed from high+1 to n-1 (last partition).
- The unsorted part (initially the whole array) is from mid to high.

We run a loop while (mid <= high):
- As we process elements, the sorted part increases and the unsorted part shrinks.

Initial conditions:
- mid = 0, high = n - 1, low = 0
- So mid = low = 0, low-1 = -1, and mid-1 = -1 → no sorted elements at the start.

We now check the value at nums[mid] each iteration:

(1) If nums[mid] == 0:
- Swap nums[low] and nums[mid].
- Why? Because 0 should go in the first partition.
- We assume the segment from 0 to low-1 is already filled with sorted 0s.
- Now nums[mid] = 0 → swap with nums[low] because low is the first 1.
- After swap, 0s go from index 0 to low, and 1s are maintained from low+1 to mid.
- Adjust the pointers: low++, mid++

(2) If nums[mid] == 1:
- We do nothing, just move mid++.
- Because 1 already fits in the middle partition.
- Since it lies immediately after the last 1 (at mid-1), it automatically becomes part of the sorted 1s.

(3) If nums[mid] == 2:
- Swap nums[mid] and nums[high].
- Because 2 should go in the last partition.
- We swap it with the last unsorted element at nums[high].
- We don't increment mid yet, because the new element at mid (from nums[high]) is still unknown and might be 0 or 1, which must be processed.
- So only decrement high.

At the end of the loop, the unsorted part vanishes and the entire array is sorted.
*/


/*
Explanation of Steps:
1. Initialize three pointers: low=0, mid=0, high=n-1.
2. Loop while mid <= high to process every element exactly once.
3. If current element is 0:
   - Swap arr[mid] with arr[low], because 0 belongs to the beginning.
   - Increment low and mid to grow the 0-partition and move past processed element.
4. If current element is 1:
   - It's already in correct (middle) partition; just mid++.
5. If current element is 2:
   - Swap arr[mid] with arr[high], because 2 belongs to the end.
   - Decrement high to shrink unknown region; do not mid++ to re-evaluate swapped-in element.
6. At loop end, all partitions sorted: [0s][1s][2s].

Logic Comparison:
- User's logic: Identical, with correct pointer management and partition assumptions.
- Added fix: Do not increment mid after swapping with high (crucial to avoid skipping).
*/

int main() {
    Solution sol;
    vector<int> nums = {2, 0, 2, 1, 1, 0};  // Example input

    cout << "Before sorting: ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    sol.sortColors(nums);

    cout << "After sorting:  ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    return 0;
}

/*
Working Example Output:
Before sorting: 2 0 2 1 1 0
After sorting:  0 0 1 1 2 2
*/
