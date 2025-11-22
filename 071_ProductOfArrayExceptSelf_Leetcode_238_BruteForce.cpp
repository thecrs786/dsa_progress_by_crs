// ✅ LeetCode 238 - Product of Array Except Self (Brute Force Approach)
// 🚀 Time Complexity: O(n^2)
// ❌ Not optimal, but valid and handles edge cases like zero correctly.

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();

        for(int i = 0; i < n; i++) {
            int prod = 1;

            for(int j = 0; j < n; j++) {
                if(i == j) continue;       // skip the current index
                prod *= nums[j];          // multiply all other elements
            }

            ans.push_back(prod);          // store result for current index
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // 🔢 Example input
    vector<int> nums = {1, 2, 3, 4};

    // 🧮 Expected Output: [24, 12, 8, 6]
    vector<int> result = sol.productExceptSelf(nums);

    // 📤 Print result
    for(int x : result) {
        cout << x << " ";
    }

    return 0;
}

/*
📘 Explanation:

For each index i in the input array:
    - Skip the element at index i.
    - Multiply all other elements.
    - Push the product to the answer vector.

Example:
Input: [1, 2, 3, 4]
For i=0: multiply [2,3,4] = 24
For i=1: multiply [1,3,4] = 12
For i=2: multiply [1,2,4] = 8
For i=3: multiply [1,2,3] = 6
Output: [24, 12, 8, 6]

✅ Edge Cases Handled:
- If there's exactly one 0 → only the index containing 0 will be non-zero.
- If there are two or more 0s → entire output becomes 0.
- No use of division, so safe from divide-by-zero errors.

⚠️ Drawback:
- Time complexity is O(n^2), so it will TLE (Time Limit Exceeded) for large inputs (up to 10^5 elements).

🎯 Use only for learning and understanding logic. Prefer O(n) solution for production.
*/
