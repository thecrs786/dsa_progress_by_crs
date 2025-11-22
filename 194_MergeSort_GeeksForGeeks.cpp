/********************************************************************************************
 * 📌 Problem: Implement Merge Sort
 * 
 * 🔹 Method Name: Merge Sort (Divide and Conquer)
 * 🔹 Approach:
 *      - Recursively divide the array into halves until single elements remain.
 *      - Merge those halves in sorted order using a temporary array.
 * 🔹 Type: Divide and Conquer algorithm
 * 🔹 Stability: ✅ Stable (order of equal elements preserved)
 * 🔹 Time Complexity: O(n log n) for Best, Average, and Worst cases
 * 🔹 Space Complexity: O(n) (due to auxiliary temp array)
 * 🔹 Optimality: Yes, this is optimal comparison-based sorting (you can’t do better than O(n log n)).
 * 🔹 GeeksForGeeks Acceptance: ✅ Yes, it will pass all test cases. No TLE (since O(n log n)), no MLE 
 *      (since extra space is O(n), which is acceptable).
 * 🔹 When useful:
 *      - When stability is needed
 *      - When guaranteed performance is required
 *      - When sorting linked lists or external data (files/streams)
 ********************************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

// For arranging in decreasing order, use >= in merge comparison in line 45

class Solution {
public:
    /***********************************************************************************
     * 📌 merge() function:
     *    - Merges two sorted subarrays [st...mid] and [mid+1...end] into one sorted array.
     *    - Uses an auxiliary vector<int> temp to temporarily store merged results.
     * 
     * 🔹 Why we need it?
     *    - After recursive division, left and right halves are individually sorted.
     *    - We need to "combine" them back into sorted order → this step is essential.
     ***********************************************************************************/
    void merge(vector<int> &arr, int st, int mid, int end) {
        vector<int> temp; // Temporary array for merging results
        int i = st;       // Pointer for left half [st...mid]
        int j = mid + 1;  // Pointer for right half [mid+1...end]

        // Traverse both halves simultaneously and pick smaller element
        while (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) {   // use >= instead of <= for descending order
                temp.push_back(arr[i]); // Left element is smaller → keep order
                i++;
            } else {
                temp.push_back(arr[j]); // Right element smaller → pick it
                j++;
            }
        }

        // If elements remain in left half, add them
        while (i <= mid) {
            temp.push_back(arr[i]);
            i++;
        }

        // If elements remain in right half, add them
        while (j <= end) {
            temp.push_back(arr[j]);
            j++;
        }

        // Copy sorted temp back into arr[st...end]
        for (int k = 0; k < temp.size(); k++) {
            arr[st + k] = temp[k]; // Overwrite original array segment
        }
    }

    /***********************************************************************************
     * 📌 mergeSort() function:
     *    - Recursively divides the array into halves.
     *    - Calls itself for left half and right half.
     *    - Then merges the two sorted halves using merge().
     * 
     * 🔹 Why recursion?
     *    - Merge Sort follows "Divide and Conquer".
     *    - Base case: when st >= end (single element array → already sorted).
     * 
     * 🔹 Backtracking insight:
     *    - Function keeps dividing until base case.
     *    - On returning (backtracking), merging happens bottom-up.
     ***********************************************************************************/
    void mergeSort(vector<int> &arr, int st, int end) {
        if (st < end) { // when st=end, single element → base case
            // Find midpoint to divide array into two halves
            int mid = st + (end - st) / 2; // Safe midpoint calculation

            // Recursively sort left half
            mergeSort(arr, st, mid);

            // Recursively sort right half
            mergeSort(arr, mid + 1, end);

            // Merge the two sorted halves
            merge(arr, st, mid, end);
        }
    }
};

/********************************************************************************************
 * 📌 Logic Walkthrough (Example: arr = [38, 27, 43, 3, 9, 82, 10])
 * 
 * Step 1: Split into halves until single elements remain:
 *         [38, 27, 43, 3, 9, 82, 10]
 *             ↓
 *         [38, 27, 43]   [3, 9, 82, 10]
 *             ↓                 ↓
 *         [38] [27, 43]    [3, 9] [82, 10]
 * 
 * Step 2: Merge bottom-up:
 *         [27, 38, 43]   [3, 9, 10, 82]
 * 
 * Step 3: Final merge:
 *         [3, 9, 10, 27, 38, 43, 82]
 * 
 * 🔑 Key Insight: 
 * - "Merging" is the real workhorse, combining two sorted halves in O(n).
 * - Recursion (backtracking) ensures smaller problems are solved first, then combined.
 ********************************************************************************************/

/********************************************************************************************
 * 📌 Key Insights / Important Details:
 * - Merge Sort is deterministic O(n log n) (unlike QuickSort which can degrade to O(n²)).
 * - Stable sort → equal elements retain order.
 * - Requires O(n) extra space (not in-place).
 * - Excellent for linked lists or external memory sorting.
 ********************************************************************************************/

int main() {
    // Working Example
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    Solution sol;
    sol.mergeSort(arr, 0, arr.size() - 1);

    // Output the result
    cout << "Sorted array: [";
    for (auto &x : arr) {
        cout << x << " ";
    }
    cout << "]" << endl;

    return 0;
}

/********************************************************************************************
 * ✅ Output:
 * Sorted array: [3 9 10 27 38 43 82 ]
 * 
 * 📌 Working:
 * - mergeSort keeps dividing array into halves.
 * - On returning from recursion (backtracking), merge() merges the two halves.
 * - Temporary array ensures we can merge smoothly without overwriting elements.
 * - Final result: fully sorted array.
 ********************************************************************************************/
