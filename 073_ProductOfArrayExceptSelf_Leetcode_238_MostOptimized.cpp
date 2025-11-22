// ✅ LeetCode 238: Product of Array Except Self
// 🔥 Fully optimized O(n) time, O(1) extra space (excluding output)
// 💡 Prefix product is built in ans[], suffix is tracked using a single variable

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);  // Initialize ans with all 1s

        // 🔹 Step 1: Build prefix product in ans[]
        for(int i = 1; i < n; i++) {
            ans[i] = ans[i-1] * nums[i-1];
        }

        // 🔹 Step 2: Apply suffix product from the end, updating ans in-place
        int suffix = 1;
        for(int i = n-1; i >= 0; i--) {
            ans[i] *= suffix;
            suffix *= nums[i];  // Move suffix product backward
        }

        return ans;
    }
};

/*
🔎 Example:

Input:  nums = [1, 2, 3, 4]

Prefix in ans: [1, 1, 2, 6]
Suffix:         ×24 ×12 ×4 ×1
Final ans:     [24, 12, 8, 6]

💡 Explanation:
- ans[0] = 1 * 24 = 24
- ans[1] = 1 * 12 = 12
- ans[2] = 2 * 4 = 8
- ans[3] = 6 * 1 = 6
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
📌 KEY NOTES:
1. Time Complexity: O(n)
2. Space Complexity: O(1) extra space (ans[] is output, allowed by problem)
3. No division used, so handles 0s safely.
4. Elegant in-place prefix + suffix approach.
5. This is the **most efficient solution** — clean, readable, and scalable.

✨ Pattern Mastery:
- Left pass for prefix
- Right pass for suffix
- Multiply both in the same array
*/
