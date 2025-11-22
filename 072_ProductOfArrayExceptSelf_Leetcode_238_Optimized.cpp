// ✅ LeetCode Problem 238: Product of Array Except Self
// 🔥 Optimized O(n) solution using prefix and suffix arrays
// 🔧 Constraints handled: No division used, space efficient (excluding output array)

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        // 🔹 Step 1: Initialize prefix and suffix product arrays of size n
        vector<int> prefix(n);
        vector<int> suffix(n);
        vector<int> ans(n); // This will store the final result

        // 🔹 Step 2: Build the prefix product array
        // prefix[i] will hold the product of all elements to the left of index i
        prefix[0] = 1; // Nothing to the left of index 0
        for(int i = 1; i < n; i++) {
            prefix[i] = prefix[i-1] * nums[i-1];
        }

        // 🔹 Step 3: Build the suffix product array
        // suffix[i] will hold the product of all elements to the right of index i
        suffix[n-1] = 1; // Nothing to the right of last index
        for(int i = n-2; i >= 0; i--) {
            suffix[i] = suffix[i+1] * nums[i+1];
        }

        // 🔹 Step 4: Final result is product of prefix[i] * suffix[i]
        for(int i = 0; i < n; i++) {
            ans[i] = prefix[i] * suffix[i];
        }

        return ans;
    }
};

/*
🔎 Example:

Input: nums = [1, 2, 3, 4]
prefix:       [1, 1, 2, 6]
suffix:       [24, 12, 4, 1]
ans:          [24,12,8,6]

🔁 Explanation:
- For index 0: product = 1 (left) * 24 (right) = 24
- For index 1: product = 1 (left) * 12 (right) = 12
- For index 2: product = 2 (left) * 4 (right) = 8
- For index 3: product = 6 (left) * 1 (right) = 6
*/

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 4};
    vector<int> result = sol.productExceptSelf(nums);

    cout << "Product of array except self: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

/*
📌 Key Points:
1. Time Complexity: O(n) — Each loop runs once through the array.
2. Space Complexity: O(n) — Due to extra prefix and suffix arrays (can be optimized to O(1) if allowed).
3. This avoids division, so it's safe when nums contains 0.
4. Works for both positive and negative integers in input.

📌 Space Optimization Tip:
If allowed, you can compute prefix in-place and reuse the result array for final output and suffix tracking.
*/
