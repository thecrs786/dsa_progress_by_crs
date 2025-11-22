// LeetCode Problem 503: Next Greater Element II
// Problem Summary:
// Given a circular array nums, for each element find the next greater element.
// The next greater element of a number x is the first greater number traversed forward.
// If none exists, assign -1.
//
// Example:
// Input: nums = [1, 2, 1]
// Output: [2, -1, 2]
// Explanation: For the first 1 → next greater is 2;
// for 2 → no greater → -1;
// for the last 1 → wrap around → next greater is 2.
//
// Time Complexity: O(n), because each element is pushed and popped from the stack at most once.
// Space Complexity: O(n), as we use a stack and answer array of size n only.
// Approach Used: Optimized stack-based approach using modulo (%) to handle circular traversal.
// Is it the most optimal? ✅ Yes, both in time and space complexity this is optimal.
// Will it be accepted? ✅ Yes, this solution will pass all test cases without TLE or MLE.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n); // Stores the final answers for each index
        stack<int> s;       // Stack to hold indices of potential next greater elements

        // We traverse from 2n - 1 to 0 to simulate going through the array twice
        for(int i = (2 * n) - 1; i >= 0; i--) {
            int idx = i % n; // Map the index to the original array using modulo

            // Pop elements from the stack that are smaller or equal to nums[idx]
            while(!s.empty() && nums[idx] >= nums[s.top()]) {
                s.pop();
            }

            // If the stack is empty, there's no greater element → assign -1
            // Otherwise, assign the top element as the next greater element
            
            ans[idx] = s.empty() ? -1 : nums[s.top()];
            
            // OR
            /*if(s.empty()) ans[idx] = -1;
            else ans[idx] = nums[s.top()];*/


            // Push the current index onto the stack for future comparisons
            s.push(idx);
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Example Test Case
    vector<int> nums = {1, 2, 1};
    vector<int> result = sol.nextGreaterElements(nums);

    cout << "Next Greater Elements: ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Logic Explanation and Working of the Function:

1. Problem Handling:
   - The array is circular, meaning after the last element we wrap to the first.
   - We need to find the next greater element for each index, considering this circularity.

2. Optimization from Previous Version:
   - Instead of physically copying and extending the array (which costs extra space),
     we logically simulate going through the array twice by traversing from 2n - 1 to 0.
   - Modulo (%) is used to map indices back to the original array.

3. Use of idx and i:
   - 'i' goes from 2n - 1 to 0 → simulates two passes over the array.
   - 'idx = i % n' maps any index in this extended iteration back to the correct position in nums.

4. Stack Usage:
   - The stack stores indices of elements that might be the next greater element for future elements.
   - We pop elements that are smaller or equal to the current element because they can't be the next greater for anyone after.

5. Filling ans:
   - If the stack is empty after popping → no next greater → assign -1.
   - If not empty → the top element of the stack is the next greater → assign accordingly.
   - We assign the answer for idx during every iteration, ensuring even wrap-around cases are handled.

6. Traversing Twice:
   - Circular nature requires considering elements at the start after reaching the end.
   - By traversing from 2n - 1 to 0 and using modulo, we efficiently simulate this without extra space.

7. Final Assignment:
   - The answer array is filled while we traverse from the end.
   - Every element's next greater is assigned exactly once because earlier assignments are overwritten only when necessary.
   - The modulo ensures that the correct position is updated.

Important Details and Key Insights:
✔ Modulo (%) is key to mapping indices from extended traversal back to original positions.
✔ Traversing twice covers wrap-around cases without copying the array.
✔ Stack helps efficiently manage and find the next greater element.
✔ Avoids extra space → truly optimal solution in both time and space.
✔ Every element is processed only once → ensures O(n) efficiency.
✔ This is the version to use in interviews or real-world applications where space matters.

Example Walkthrough (for nums = [1, 2, 1]):
- Extended logical view: [1, 2, 1, 1, 2, 1]
- We process indices from 5 down to 0.
- At each step, we compare and pop from the stack as needed, assigning answers based on the top element or assigning -1 if the stack is empty.

Final Output:
Next Greater Elements: 2 -1 2
*/

