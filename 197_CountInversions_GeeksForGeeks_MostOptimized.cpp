/*
===================================================================
📝 Problem: Inversion Count
-------------------------------------------------------------------
We are given an array "arr" of integers. 
We need to count the number of inversions in the array.

⚡ Definition of Inversion:
A pair (i, j) is an inversion if:
    - i < j
    - arr[i] > arr[j]

Example:
arr = [2, 4, 1, 3, 5]
Inversions = (2,1), (4,1), (4,3) → Total = 3

===================================================================
💡 Solution Method:
-------------------------------------------------------------------
👉 Method Used: "Merge Sort Based Inversion Counting"
- We use the divide-and-conquer paradigm of Merge Sort.
- During the merge step, if arr[i] > arr[j], 
  then arr[i..mid] are all greater than arr[j].
- This allows counting inversions in O(n log n).

===================================================================
⏱ Time and Space Complexity:
-------------------------------------------------------------------
- Time Complexity: O(n log n)
    (because merge sort divides the array and merges in O(n))
- Space Complexity: O(n)
    (extra array `temp` is used during merging)

===================================================================
⚠️ Is this Optimal?
-------------------------------------------------------------------
✅ Yes, this is the most optimal approach.
- Brute force: O(n^2) → TLE on large inputs
- Merge sort modification: O(n log n) → Accepted on LeetCode/GFG
- Will NOT cause MLE (uses only O(n) extra memory)

===================================================================
🔑 Key Insights:
-------------------------------------------------------------------
1. Merge Sort not only sorts, but while merging, we can **count inversions**.
2. Functions are of `int` type because they return the count of inversions 
   found in their segment of recursion.
3. In `mergesort`, we return:
       leftcount + rightcount + invCount
   - leftcount = inversions in left half
   - rightcount = inversions in right half
   - invCount = inversions formed across left & right
   Summing them gives total inversions.
4. Backtracking in recursion: mergesort divides array into halves, 
   then after recursive calls, merges back results (sort + count).
5. Sorting ensures each merge step is efficient and inversion counts 
   are correctly accumulated.

===================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 🔹 Merge function: merges two sorted halves & counts inversions
    int merge(vector<int> &arr, int st, int mid, int end) {
        vector<int> temp; // temporary array to store merged result
        int count = 0;    // counts inversions

        int i = st, j = mid + 1;

        // Compare both halves
        while (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) {
                // If left element <= right element, no inversion
                temp.push_back(arr[i]);
                i++;
            } else {
                // If left element > right element:
                // arr[i..mid] all are greater than arr[j]
                count += (mid - i + 1);
                temp.push_back(arr[j]);
                j++;
            }
        }

        // Copy remaining left half
        while (i <= mid) {
            temp.push_back(arr[i]);
            i++;
        }

        // Copy remaining right half
        while (j <= end) {
            temp.push_back(arr[j]);
            j++;
        }

        // Copy back merged sorted part into original array
        for (int idx = 0; idx < temp.size(); idx++) {
            arr[st + idx] = temp[idx];
        }

        return count; // return inversion count found in this merge
    }

    // 🔹 MergeSort function: recursively splits, counts & merges
    int mergesort(vector<int> &arr, int st, int end) {
        if (st < end) {
            int mid = st + (end - st) / 2;

            // Count inversions in left half
            int leftcount = mergesort(arr, st, mid);

            // Count inversions in right half
            int rightcount = mergesort(arr, mid + 1, end);

            // Count inversions across left and right
            int invCount = merge(arr, st, mid, end);

            // Total inversions = sum of all three
            return leftcount + rightcount + invCount;
        }

        return 0; // base case: no inversions in a single element
    }

    // 🔹 Public function: called externally
    int inversionCount(vector<int> &arr) {
        return mergesort(arr, 0, arr.size() - 1);
    }
};

/*
===================================================================
📊 Dry Run Example
-------------------------------------------------------------------
Input: arr = [2, 4, 1, 3, 5]

Step 1: Divide into halves until single elements
Step 2: Start merging
    - Merge [2,4] and [1,3,5]
    - While merging, find:
        (2,1), (4,1), (4,3) → total = 3
Step 3: Array becomes sorted as a side effect.
Output = 3

===================================================================
🔑 Conceptual Link with Merge Sort
-------------------------------------------------------------------
- Normal merge sort → just sorts the array.
- Modified merge sort → counts inversions during merge step.
- Why possible?
  Because when arr[i] > arr[j] during merging,
  then ALL elements from arr[i..mid] will also be > arr[j].
  This allows counting in bulk, instead of pair by pair.

===================================================================
*/

int main() {
    vector<int> arr = {2, 4, 1, 3, 5};

    Solution obj;
    int ans = obj.inversionCount(arr);

    cout << "Array after sorting: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTotal Inversions = " << ans << endl;

    /*
    Expected Output:
    Array after sorting: 1 2 3 4 5
    Total Inversions = 3
    */
    return 0;
}

/*
===================================================================
✨ Final Notes
-------------------------------------------------------------------
- Merge Sort helps here by naturally dividing the problem into 
  smaller parts and merging while also counting inversions.
- Functions return int because each returns the number of inversions 
  in its segment.
- We return leftcount + rightcount + invCount because inversions can 
  occur inside left, inside right, and across them.
- Concept uses recursion (divide and conquer) and backtracking (merging).
- Sorting ensures correctness, counting ensures we solve the problem.

This solution is optimal → O(n log n), accepted by LeetCode/GFG.
===================================================================
*/
