// 🔍 LeetCode 540: Single Element in a Sorted Array
// 📝 Problem:
// You are given a sorted array where every element appears exactly twice,
// except for one element which appears only once.
// Find that single element in O(n) time using brute force.
// 🔒 Constraints: Exactly one such unique element always exists.

/*
🧪 Example:
Input:  [1,1,2,2,3,4,4,5,5]
Output: 3
Explanation:
- All elements appear twice except 3.
- 1, 1 ✅
- 2, 2 ✅
- 3 ❌ unmatched
- 4, 4 ✅
- 5, 5 ✅
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();

        // If the array has only one element, it's the answer
        if (n == 1) return nums[0];

        for (int i = 0; i < n; i++) {
            // Case: first element is unique
            if (i == 0 && nums[i] != nums[i + 1]) {
                return nums[i];
            }
            // Case: last element is unique
            else if (i == n - 1 && nums[i] != nums[i - 1]) {
                return nums[i];
            }
            // Case: middle element is unique (not equal to neighbors)
            else if (i > 0 && i < n - 1 && nums[i] != nums[i - 1] && nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }

        // If somehow no element is found (though problem guarantees one), return -1
        return -1;
    }
};

// 🔁 Sample Test Run
int main() {
    Solution sol;
    vector<int> arr = {1,1,2,2,3,4,4,5,5};

    cout << "Single Non-Duplicate Element: " << sol.singleNonDuplicate(arr) << endl;
    return 0;
}
