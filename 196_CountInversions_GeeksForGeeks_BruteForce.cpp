/*
===================================================================
📝 Problem Summary (Inversion Count Problem)
-------------------------------------------------------------------
We are given an array "arr" of integers. 
We need to count the number of "inversions" in this array.

⚡ Definition of Inversion:
A pair of indices (i, j) is considered an inversion if:
    - i < j
    - arr[i] > arr[j]

Example:
arr = [2, 4, 1, 3, 5]
Inversions: (2,1), (4,1), (4,3) → Total = 3

===================================================================
💡 Approach Used in This Code
-------------------------------------------------------------------
👉 Method: Brute Force Approach (Naive Method)
We simply use two nested loops:
    - Outer loop fixes one element arr[i]
    - Inner loop checks all arr[j] with j > i
    - If arr[i] > arr[j], we increment count.

===================================================================
⏱ Time Complexity:
    - Outer loop runs (n-1) times
    - Inner loop runs at most (n-1) times
    - Total = O(n^2)

📦 Space Complexity:
    - O(1) → We only use one integer variable (count)

===================================================================
⚠️ Key Notes on Optimality:
    - This brute force solution is NOT optimal.
    - For large n (n up to 10^5 in LeetCode / GFG), this will cause **TLE**.
    - Optimal solution uses "Merge Sort based method" in O(n log n).

===================================================================
✅ Acceptance on Platforms:
    - This brute force code will work for **small inputs** (n <= 5000 approx).
    - On large inputs (like 10^5), it will time out (TLE).
    - No risk of MLE (memory limit exceeded), only TLE.

===================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int inversionCount(vector<int> &arr) {
        int count = 0; // keeps track of total inversions found

        // Outer loop → selects an element arr[i]
        for (int i = 0; i < arr.size() - 1; i++) {

            // Inner loop → checks all elements after i
            for (int j = i + 1; j < arr.size(); j++) {

                // If arr[i] > arr[j], then this is an inversion
                if (arr[i] > arr[j]) 
                    count++; // increment inversion count
            }
        }

        return count; // finally return total inversions
    }
};

/*
===================================================================
🔍 Detailed Logic Walkthrough:
-------------------------------------------------------------------
1. We start with `count = 0`
   → To store how many inversion pairs exist.

2. For each element arr[i]:
   → We need to compare it with every element to its right (arr[j], j > i)

3. If arr[i] > arr[j]:
   → That means this pair (i, j) is an inversion.
   → We increment count.

4. After all pairs are checked:
   → count will store the total inversion count.

===================================================================
📌 Key Insight:
- Brute force checks every possible pair → O(n^2).
- For large n, this is too slow.
- This is mainly useful as a "first try" or conceptual method.

===================================================================
📊 Example Dry Run:
-------------------------------------------------------------------
Input: arr = [2, 4, 1, 3, 5]

Step by step:
i=0 → arr[0]=2, check right side [4,1,3,5]
       Compare (2,4) → no
       Compare (2,1) → inversion ✅ count=1
       Compare (2,3) → no
       Compare (2,5) → no

i=1 → arr[1]=4, check right side [1,3,5]
       Compare (4,1) → inversion ✅ count=2
       Compare (4,3) → inversion ✅ count=3
       Compare (4,5) → no

i=2 → arr[2]=1, check right side [3,5]
       Compare (1,3) → no
       Compare (1,5) → no

i=3 → arr[3]=3, check right side [5]
       Compare (3,5) → no

Final Count = 3

===================================================================
*/

int main() {
    // Example test case
    vector<int> arr = {2, 4, 1, 3, 5};

    Solution obj;
    int ans = obj.inversionCount(arr);

    cout << "Array: ";
    for (int num : arr) cout << num << " ";
    cout << "\nTotal Inversions = " << ans << endl;

    /*
    Expected Output:
    Array: 2 4 1 3 5 
    Total Inversions = 3
    */

    return 0;
}

/*
===================================================================
✨ Final Notes:
-------------------------------------------------------------------
- This code is correct but **NOT optimal**.
- For small arrays, it works fine and gives correct results.
- For large arrays (LeetCode style constraints), it will give **TLE**.
- The optimal method uses a "Merge Sort Modification" with O(n log n).
===================================================================
*/
