/**************************************************************************************
 *  Problem Summary:
 *  ----------------
 *  Implement the QuickSort algorithm on an array using the "Lomuto Partition Scheme".
 *  
 *  QuickSort is a Divide & Conquer algorithm:
 *  - It selects a pivot element.
 *  - Partitions the array around the pivot (smaller elements left, larger right).
 *  - Recursively sorts the left and right partitions.
 *  
 *  -----------------------------------------------------------------------------------
 *  Method Used: QuickSort (Divide & Conquer, Lomuto Partition Scheme)
 *  
 *  Time Complexity:
 *    - Best Case: O(n log n)  -> when pivot divides array evenly each time
 *    - Average Case: O(n log n)
 *    - Worst Case: O(n^2)     -> when pivot chosen is always smallest/largest element
 *  
 *  Space Complexity:
 *    - O(log n) recursion stack (best/avg case)
 *    - O(n) recursion stack (worst case, skewed recursion tree)
 *  
 *  Optimality:
 *    - This is the standard QuickSort implementation using the last element as pivot.
 *    - Not guaranteed to be optimal in worst-case scenarios (e.g., sorted arrays).
 *    - Still accepted widely in practice and educational sites (GeeksforGeeks, LeetCode).
 *  
 *  Will it be accepted on GFG/LeetCode?
 *    - ✅ Yes, this is the correct and accepted implementation.
 *    - ⚡ No risk of MLE (Memory Limit Exceeded) as it only uses O(log n) extra stack.
 *    - ⚡ Possible TLE only if input arrays are very large AND unlucky pivot choices 
 *      repeatedly give O(n^2). Otherwise efficient.
 *  
 **************************************************************************************/

#include <bits/stdc++.h>
using namespace std;

//NOTE: To arrange in decreasing order, use >= instead of <= in line 68

class Solution {
  public:

    /***************************************************************************
     * partition():
     * ------------
     * - Rearranges the array so that:
     *      - All elements <= pivot are placed before the pivot.
     *      - All elements > pivot are placed after the pivot.
     * - Returns the final index of the pivot after partitioning.
     * 
     * Why do we take `idx = st - 1`?
     *   - We start `idx` one position before the start. This is a marker for 
     *     the "boundary" of the smaller elements region.
     *   - Every time we find arr[j] <= pivot, we increment idx and swap arr[idx] with arr[j],
     *     thus expanding the "smaller elements region".
     * 
     * Why choose pivot = arr[end]?
     *   - A simple and common choice for Lomuto scheme.
     *   - Always consistent and avoids complex logic.
     ***************************************************************************/
    int partition(vector<int>& arr, int st, int end) {
        
        int idx = st - 1;        // boundary index for <= pivot region
        int pivot = arr[end];    // pivot value (last element)
        
        for (int j = st; j < end; j++) {  // iterate from st to end-1 OR IERATE TO end to avoid extra swap in line 75 & 76
            if (arr[j] <= pivot) {        // if current element <= pivot  NOTE : use >= for decreasing order
                idx++;                    // expand boundary
                swap(arr[idx], arr[j]);   // place element into <= region
            }
        }

        // Place pivot in its correct sorted position (idx+1) OR JUST USE j<=end in line 67
        idx++;
        swap(arr[idx], arr[end]);

        return idx;   // return final pivot index
    }
  
    /***************************************************************************
     * quickSort():
     * ------------
     * - Core recursive function.
     * - Divides array into subproblems around a pivot.
     * 
     * Base Case: st >= end (0 or 1 element) → already sorted.
     * Recursive Case:
     *   1. Partition the array around pivot.
     *   2. Recursively call quickSort on left subarray.
     *   3. Recursively call quickSort on right subarray.
     * 
     * This is the "divide & conquer" + backtracking:
     *   - At each step, array is divided into left/right partitions.
     *   - Recursion "backtracks" after finishing sorting left and right partitions.
     ***************************************************************************/
    void quickSort(vector<int>& arr, int st, int end) {
        if (st < end) {
            int pivIdx = partition(arr, st, end); // get pivot's final index
            quickSort(arr, st, pivIdx - 1);       // sort left of pivot
            quickSort(arr, pivIdx + 1, end);      // sort right of pivot
        }
    }

}; // end of class


/**************************************************************************************
 * Example Walkthrough:
 * --------------------
 * Input: [10, 7, 8, 9, 1, 5]
 * 
 * Step 1: Choose pivot = 5 (last element)
 *         Partition -> [1, 5, 8, 9, 10, 7]  pivot index = 1
 * 
 * Step 2: Recurse left [1] (already sorted)
 *         Recurse right [8, 9, 10, 7]
 * 
 * Step 3: Choose pivot = 7
 *         Partition -> [1, 5, 7, 9, 10, 8]  pivot index = 2
 * 
 * Step 4: Left [ ] (empty)
 *         Right [9, 10, 8]
 *         Pivot = 8
 *         Partition -> [1, 5, 7, 8, 10, 9]  pivot index = 3
 * 
 * Step 5: Left [] (empty)
 *         Right [10, 9]
 *         Pivot = 9
 *         Partition -> [1, 5, 7, 8, 9, 10] pivot index = 4
 * 
 * Final Sorted Array = [1, 5, 7, 8, 9, 10]
 **************************************************************************************/


int main() {
    Solution sol;

    // Example array
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    sol.quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array:   ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}


/**************************************************************************************
 * Key Insights & Important Details:
 * ---------------------------------
 * 1. QuickSort is recursive → must always define base case (st < end).
 * 2. Partition logic is the heart of QuickSort.
 * 3. Choosing a "bad pivot" repeatedly leads to O(n^2).
 *    - E.g., already sorted arrays with last-element pivot.
 *    - Can be improved by randomized pivot or median-of-three pivot.
 * 4. QuickSort is NOT a stable sort (relative order of equal elements may change).
 * 5. Despite worst-case O(n^2), it's one of the fastest sorts in practice because:
 *    - Good cache performance.
 *    - In-place sorting (no extra array needed).
 * 6. Backtracking: after partitioning, recursion "unwinds" once both subarrays are sorted.
 * 
 * Backtracking Example:
 *   - quickSort keeps branching into left & right.
 *   - Once smallest subarrays are solved, recursion returns (backtracks).
 *   - Final result is achieved when recursion stack fully unwinds.
 **************************************************************************************/
