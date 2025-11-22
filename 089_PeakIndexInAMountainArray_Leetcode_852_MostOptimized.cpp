// Problem: Find the peak index in a mountain array.
// A mountain array increases to a peak, then decreases.
// For example: a = [0, 2, 4, 3, 1] → Peak is at index 2 (value = 4)

// Binary Search Approach (Optimized):
// Time Complexity: O(log n) - much faster than linear scan
// Space Complexity: O(1) - no extra space used

// Note:
// - 0th and last index can NEVER be the peak in a valid mountain array.
// - So we always start search from index 1 to size-2
// - Avoid checking a[mid-1] or a[mid+1] at invalid indices

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& a) {

        // Start from index 1 and end at size-2
        // Because 0 and n-1 are never peak elements in a valid mountain array
        int st = 1;
        int end = a.size() - 2;

        while (st <= end) {

            // Calculate mid safely to avoid integer overflow
            int mid = st + (end - st) / 2;

            // If a[mid] is greater than both neighbors, it's the peak
            if (a[mid] > a[mid - 1] && a[mid] > a[mid + 1]) {
                return mid;
            }

            // If right side is increasing, move right
            else if (a[mid] < a[mid + 1]) {
                st = mid + 1;
            }

            // Else move left
            else {
                end = mid - 1;
            }
        }

        // Should never reach here in a valid mountain array
        return -1;
    }
};

int main() {
    Solution sol;

    // Working Example
    vector<int> arr = {0, 3, 5, 7, 6, 2, 1};

    // Call the function and store the peak index
    int peakIndex = sol.peakIndexInMountainArray(arr);

    // Output the result
    cout << "Peak Index: " << peakIndex << endl;
    cout << "Peak Element: " << arr[peakIndex] << endl;

    return 0;
}

/*
🔍 Example Run:
Input array: [0, 3, 5, 7, 6, 2, 1]
Peak Index: 3
Peak Element: 7

🧠 Why it works:
- Binary search eliminates half each time:
  - If mid < mid+1 → move right (still climbing)
  - If mid > mid+1 → move left (already descending)

✅ Time: O(log n)
✅ Space: O(1)


🧠 Key Observations:
- Peak will always lie between index 1 and n-2
- Don't access a[mid+1] or a[mid-1] at edges, it causes runtime error
- Binary search works here because:
    - One side is strictly increasing
    - Other side is strictly decreasing
    - So we can eliminate one half every time
*/



