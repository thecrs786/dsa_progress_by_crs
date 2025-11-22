/*
🎯 LeetCode #33: Search in Rotated Sorted Array

📝 Context:
You are given a **rotated sorted array with distinct elements** (e.g., [4,5,6,7,0,1,2]).
You must find the index of a given `target` in **O(log n)** time, or return -1 if not found.

✅ Array is strictly increasing but rotated.
✅ No duplicates exist.
✅ Problem demands binary search-based logic.

📈 Time Complexity: O(log n)
📦 Space Complexity: O(1)
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int st = 0;
        int end = nums.size() - 1;

        // 🚀 Begin binary search
        while (st <= end) {
            // ✅ Calculate mid to avoid overflow
            int mid = st + (end - st) / 2;

            // 🎯 If target found at mid, return the index
            if (nums[mid] == target) return mid;

            /*
            🔍 Step 1: Decide which half is sorted

            There are always two halves:
            - One of them is strictly sorted
            - The other is rotated

            We use this to decide where to search
            */

            if (nums[st] <= nums[mid]) {
                // 🧭 Left half is sorted

                // ✅ Now check if target lies within this sorted half
                if (nums[st] <= target && target <= nums[mid]) {
                    // 🎯 Target is in the left sorted half
                    end = mid - 1;
                } else {
                    // 🔄 Target must be in right half
                    st = mid + 1;
                }
            }

            else {
                // 🧭 Right half is sorted

                // ✅ Now check if target lies within the right half
                if (nums[mid] <= target && target <= nums[end]) {
                    // 🎯 Target is in the right sorted half
                    st = mid + 1;
                } else {
                    // 🔄 Target must be in left half
                    end = mid - 1;
                }
            }
        }

        // ❌ Element not found
        return -1;
    }
};

// 🧪 Example run
int main() {
    Solution sol;

    // Rotated sorted array
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    int result = sol.search(nums, target);

    if (result != -1) {
        cout << "Target " << target << " found at index: " << result << endl;
    } else {
        cout << "Target " << target << " not found." << endl;
    }

    return 0;
}

/*
🔍 Dry Run of Example:
nums = [4, 5, 6, 7, 0, 1, 2], target = 0

1. mid = 3 → nums[3] = 7 → left half [4,5,6,7] is sorted
2. 0 is not in [4,7] → search right → st = 4
3. mid = 5 → nums[5] = 1 → right half [1,2] is sorted
4. 0 is less than 1 → move left → end = 4
5. mid = 4 → nums[4] = 0 → ✅ match!

Result: index 4
*/
