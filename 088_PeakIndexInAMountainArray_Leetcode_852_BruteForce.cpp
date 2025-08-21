/*
🎯 LeetCode #852: Peak Index in a Mountain Array
🔗 https://leetcode.com/problems/peak-index-in-a-mountain-array/

📝 Problem Brief:
You are given a **mountain array** (strictly increasing then strictly decreasing).
You need to find and return the **index of the peak element**.

✔️ It is guaranteed that exactly one peak exists.
⚠️ Expected optimal time: O(log n), but this solution is brute force.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        // 🔁 Iterate from second to second-last element
        for (int i = 1; i < arr.size() - 1; i++) {
            /*
            💡 Peak condition:
            The peak element is greater than its neighbors:
                arr[i - 1] < arr[i] > arr[i + 1]

            ✅ Works because mountain array guarantees:
                - strictly increasing part → arr[i - 1] < arr[i]
                - strictly decreasing part → arr[i] > arr[i + 1]
            */
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
                return i;
            }
        }

        // 🔴 Not expected to reach here for valid input
        return -1;
    }
};

/*
🧪 Example
Input: arr = [0, 3, 5, 7, 6, 4, 2]
Output: 3

Explanation:
- Increasing: 0 → 3 → 5 → 7
- Decreasing: 7 → 6 → 4 → 2
- Peak value = 7, at index 3
*/

int main() {
    Solution sol;
    vector<int> arr = {0, 3, 5, 7, 6, 4, 2};
    int result = sol.peakIndexInMountainArray(arr);

    cout << "Peak index is: " << result << endl;
    return 0;
}

/*
📈 Time Complexity: O(n)
📂 Space Complexity: O(1)

⚠️ This is a **brute-force approach**.
- It checks every middle element until the peak is found.
- On large arrays, this may lead to **TLE (Time Limit Exceeded)**.

✅ Correct logic and valid for small inputs.
❌ Not optimal — use **binary search (O(log n))** to meet expected constraints.
*/
