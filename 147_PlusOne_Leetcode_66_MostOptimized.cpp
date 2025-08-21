// ✅ Problem: LeetCode – Plus One
// 🔹 You're given a non-empty array of digits representing a non-negative integer.
// 🔹 Each element in the array contains a single digit (0–9).
// 🔹 The digits are stored such that the most significant digit is at the start.
// 🔹 You must add one to this number and return the resulting array of digits.

// ✅ Approach Name: "Traverse from End, Carry-over 9s"
// ✅ Time Complexity: O(n) – Worst case if all digits are 9 (e.g., [9,9,9,...])
// ✅ Space Complexity: O(1) – In-place modification (except insert at front adds 1 element)
// ✅ Optimized: YES, this is the most optimal approach possible
// ✅ Will it get accepted by LeetCode? YES ✅
// 🔴 Any chance of MLE or TLE? NO ❌ – Input size is small (max 100), and space is minimal

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        // Step 1: Start from the last digit (rightmost position)
        int i = digits.size() - 1;

        // Step 2: Traverse backwards while digits[i] == 9
        // Because adding 1 to 9 results in 0 and a carry to the left
        while(i >= 0 && digits[i] == 9){
            digits[i] = 0; // Set current 9 to 0
            i--;           // Move to previous digit
        }

        // Step 3: If we found a digit that is not 9 (i >= 0), just add 1 and we're done
        if(i != -1){
            digits[i] += 1;
        } 
        // Step 4: If all digits were 9 (i == -1), we need to insert 1 at the front
        // Example: [9,9,9] → [1,0,0,0]
        else {
            digits.insert(digits.begin(), 1);
        }

        // Step 5: Return the updated digits array
        return digits;
    }
};

/*
🧠 LOGIC EXPLAINED:

We simulate how we manually add 1 to a number. Start from the right:
- If the digit is < 9, just add 1 and you're done.
- If it's 9, it becomes 0 and we carry over to the left.

Example: [1, 2, 9]
- 9 becomes 0, carry to 2
- 2 becomes 3 → result is [1, 3, 0]

Example: [9, 9, 9]
- All 9s become 0
- Insert 1 at front → [1, 0, 0, 0]

Edge Case: [0]
- Becomes [1]

This method is better than converting to int/long (risk of overflow), and better than using extra arrays.

*/

// ✅ Working Example to Test It
int main() {
    Solution sol;

    vector<int> digits = {9, 9, 9}; // Try changing to {1,2,3}, {4,3,2,1}, {0}, etc.
    vector<int> result = sol.plusOne(digits);

    cout << "Result after plus one: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
