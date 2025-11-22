// ✅ LeetCode 75 – Sort Colors
// 📌 Question (Brief):
// You are given an array 'nums' containing only 0s, 1s, and 2s.
// Your task is to sort the array in-place so that all 0s come first,
// then all 1s, then all 2s.
// ✅ Constraints:
// - Do not use any sorting library function.
// - Must use constant space and solve in linear time if possible.

// 🕒 Time Complexity: O(n) → Two passes over the array (counting + rewriting)
// 📦 Space Complexity: O(1) → Only uses three integer counters

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        // 🔢 Step 1: Initialize counters
        // We will count how many 0s, 1s, and 2s are in the array
        int zeroes = 0;  // Number of 0s
        int ones = 0;    // Number of 1s
        int twos = 0;    // Number of 2s

        // 📏 Step 2: Get the size of the array
        int size = nums.size();

        // 🔁 Step 3: First pass – count each number
        // We loop through each element and increment the appropriate counter
        for (int i = 0; i < size; i++) {
            if (nums[i] == 0) {
                zeroes++;   // If element is 0, increment zeroes count
            }
            else if (nums[i] == 1) {
                ones++;     // If element is 1, increment ones count
            }
            else {
                twos++;     // If element is 2, increment twos count
            }
        }

        // 🧹 Step 4: Second pass – overwrite original array
        // We now place 0s, then 1s, then 2s using the counts

        // 🔁 4a: Place all 0s at the start
        for (int i = 0; i < zeroes; i++) {
            nums[i] = 0;  // Fill first 'zeroes' slots with 0
        }

        // 🔁 4b: Place all 1s after the 0s
        // Since we already placed 'zeroes' number of 0s,
        // we start from index 'zeroes' and go till 'zeroes + ones - 1'
        // ✅ Alternatively, you can use (i < size - twos) because:
        //     zeroes + ones == size - twos (based on total size relation)
        for (int i = zeroes; i < size - twos; i++) {
            nums[i] = 1;  // Fill next 'ones' slots with 1
        }

        // 🔁 4c: Place all 2s in the remaining part of the array
        // Remaining part starts from 'size - twos' till end of array
        for (int i = size - twos; i < size; i++) {
            nums[i] = 2;  // Fill final 'twos' slots with 2
        }
    }
};


/* 
🧠 Full Logic Summary:

- This is a variation of Counting Sort for fixed range {0, 1, 2}
- Step 1: Count how many of each number using three counters
- Step 2: Overwrite the original array based on those counts:
    - First fill with 'zeroes' number of 0s
    - Then fill with 'ones' number of 1s
    - Finally fill with 'twos' number of 2s
- This ensures all 0s come before 1s, and 1s before 2s

🕒 Time Complexity: O(n) → Two linear passes over the array
📦 Space Complexity: O(1) → No extra space used except 3 integers

*/

int main() {
    // ✅ Sample input array
    vector<int> nums = {2, 0, 2, 1, 1, 0};

    // 🎯 Call the sorting function
    Solution obj;
    obj.sortColors(nums);

    // 📤 Print the sorted output
    cout << "Sorted array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


