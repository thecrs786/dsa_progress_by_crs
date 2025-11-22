// 🔍 LeetCode 540: Single Element in a Sorted Array
// 📝 Problem:
// You are given a sorted array where every element appears exactly twice,
// except for one element that appears only once.
// Find and return the single element in O(n) time using XOR logic.

/*
🧪 Example:
Input:  [1,1,2,2,3,4,4,5,5]
Output: 3

Explanation:
- All elements appear exactly twice except 3.
- XOR cancels out duplicate elements:
    1^1 = 0
    0^2 = 2, 2^2 = 0
    0^3 = 3
    3^4 = 7, 7^4 = 3
    3^5 = 6, 6^5 = 3
- Final result: 3
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int ans = 0;

        // Traverse the entire array and XOR all elements
        // Duplicate elements cancel each other out
        for (size_t i = 0; i < nums.size(); i++) {
            ans ^= nums[i];
        }

        // The result will be the element that did not get cancelled
        return ans;
    }
};

// 🔁 Sample Test Run
int main() {
    Solution sol;
    vector<int> arr = {1,1,2,2,3,4,4,5,5};

    cout << "Single Non-Duplicate Element: " << sol.singleNonDuplicate(arr) << endl;
    return 0;
}
