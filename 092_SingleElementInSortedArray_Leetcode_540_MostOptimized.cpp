/*
💡 Question: LeetCode 540 - Single Element in a Sorted Array

Given a sorted array where every element appears exactly twice except for one element
which appears only once, find that single non-duplicate element in O(log n) time and O(1) space.

The array will always have an odd number of elements (2x pairs + 1 single).

Constraints:
- The array is sorted.
- Only one element occurs once; all others occur twice.
- Must use binary search.

🧪 Example:
Input:  nums = [1,1,2,2,3,3,4,8,8]
Output: 4
Explanation: All elements appear twice except 4.
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int st = 1;
        int end = n - 2;

        // Handle small edge cases directly
        if (n == 1) return nums[0];
        if (nums[0] != nums[1]) return nums[0];
        if (nums[n - 1] != nums[n - 2]) return nums[n - 1];

        while (st <= end) {
            int mid = st + (end - st) / 2;

            // Check if nums[mid] is the single element
            if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]) {
                return nums[mid];
            }

            // Duplicate of nums[mid] is on the left side
            if (nums[mid] == nums[mid - 1]) {
                // Check if number of elements on left side is even or odd
                if (mid % 2 == 0) {
                    // Even-sized left side: single element lies on the left
                    end = mid - 2;
                } else {
                    // Odd-sized left side: single element lies on the right
                    st = mid + 1;
                }
            }
            // Duplicate of nums[mid] is on the right side
            else if (nums[mid] == nums[mid + 1]) {
                if (mid % 2 == 0) {
                    // Even-sized left side: single element lies on the right
                    st = mid + 2;
                } else {
                    // Odd-sized left side: single element lies on the left
                    end = mid - 1;
                }
            }
        }

        return -1; // Default return, should never be reached
    }

    /*
    🧠 Explanation:

    - Since all elements appear in pairs except one, the total size is always odd.
    - Before the single element, elements will appear in pairs: [x,x], and so will they after.
    - So the array can be split evenly on both sides of the single element.

    - If nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1] -> this is the single element.

    - If nums[mid] == nums[mid - 1]:
        → Check if mid is even:
            • If yes: left side has even elements excluding the current pair → single lies on the left → end = mid - 2
            • If no: left side has odd elements → single lies on the right → st = mid + 1

    - If nums[mid] == nums[mid + 1]:
        → Check if mid is even:
            • If yes: left side has even elements → single lies on the right → st = mid + 2
            • If no: left side has odd elements → single lies on the left → end = mid - 1

    - This binary search continues until we isolate the single element.
    - Time Complexity: O(log n)
    - Space Complexity: O(1)
    */
};

int main() {
    // Test Case
    vector<int> nums = {1, 1, 2, 2, 3, 3, 4, 8, 8};

    Solution obj;
    int result = obj.singleNonDuplicate(nums);

    cout << "The single non-duplicate element is: " << result << endl;

    /*
    🧪 Output:
    The single non-duplicate element is: 4
    */

    return 0;
}