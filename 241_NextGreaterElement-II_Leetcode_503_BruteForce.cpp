// LeetCode Problem 503: Next Greater Element II
// Given a circular array nums, for each element find the next greater element.
// The next greater element of a number x is the first greater number to its traversing order.
// If it doesn't exist, output -1 for that element.
//
// Example:
// Input: nums = [1, 2, 1]
// Output: [2, -1, 2]
// Explanation:
// - The next greater for 1 is 2.
// - The next greater for 2 doesn't exist, so -1.
// - The next greater for 1 is 2 (circular array wraps around).

#include <iostream>
#include <vector>
using namespace std;

// Solution provided by user
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();

        for(int i=0; i<n; i++){
            bool found = false;
            for(int j = i+1; j<nums.size(); j++){
                if(nums[j]>nums[i]) {
                    ans.push_back(nums[j]);
                    found = true;
                    break;
                }
            }
            if(found == false) ans.push_back(-1);
            nums.push_back(nums[i]); // simulate circular array by appending current element
        }
        return ans;
    }    
};

/*
Solution Name: Brute-force by extending array every iteration

Time Complexity:
- Worst case: O(n^2), because for each element, we may need to scan up to n elements ahead.
- The inner loop can go through all future elements, and with the array being extended, it grows unnecessarily.

Space Complexity:
- O(n) extra space for the answer array.
- But nums itself grows dynamically, potentially reaching O(n^2) in extreme cases before termination, which is dangerous.

Optimal or not?
- ❌ This is NOT an optimal solution.
- ❌ This method is inefficient and risky because it modifies the input array and may cause excessive memory usage or time delays.

Will it be accepted by LeetCode?
- ❌ This approach may pass small inputs but will likely cause Memory Limit Exceeded (MLE) or Time Limit Exceeded (TLE) errors on larger test cases.

Key observations:
- Circularity is simulated by appending elements, but this approach is flawed because it keeps appending at every iteration.
- We are not controlling the size of nums and hence creating unpredictable resource consumption.
- The correct way would be to either loop with modulo or extend nums only once.

Logic explanation:
- For each element in nums (indexed by i), we scan subsequent elements starting from i+1.
- If a greater element is found, we store it in ans and stop scanning.
- If we don't find any greater element after scanning, we push -1.
- After processing element i, we append it to nums to simulate circular traversal.
- This way, when scanning further elements, the wrap-around is handled by the appended elements.

Working of the function step-by-step:
1. Initialize an empty answer vector ans.
2. Loop over each index i from 0 to n-1.
3. For each i, initialize a boolean flag found as false.
4. Scan the elements from index i+1 to the current size of nums.
5. If any element greater than nums[i] is found:
   - Add that element to ans.
   - Set found = true and break out of the inner loop.
6. After scanning, if no greater element was found, push -1 into ans.
7. Append nums[i] at the end of nums to simulate circular array behavior.
8. Once all elements are processed, return the ans vector.

Why this method is bad and not suitable:
- Every iteration appends an element, increasing nums endlessly.
- This makes the loop boundary unstable and leads to unpredictable run-time behavior.
- Memory usage can spiral out of control, causing MLE.
- For large inputs, the repeated scanning causes TLE.
- It’s hard to reason about the correctness because the array is being modified while being iterated.
- A proper circular traversal should be handled using modulo arithmetic or a single extension of the array.

Important details and key insights:
- Circular arrays should be handled logically, not by extending the container dynamically in every iteration.
- Using a flag to track when a greater element is found is correct, but only if array boundaries are well controlled.
- Always consider worst-case scenarios: sorted decreasing arrays will break naive brute-force approaches.
- Efficient solutions use stacks or pre-processing rather than modifying the input repeatedly. */

int main() {
    Solution sol;

    // Example test case
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
Example run explanation:
- nums = [1, 2, 1]
Iteration details:
1. i = 0, nums[i] = 1
   - Check j = 1 -> nums[1]=2 > 1, so ans[0]=2
   - Append 1 -> nums = [1, 2, 1, 1]

2. i = 1, nums[i] = 2
   - Check j = 2 -> nums[2]=1 < 2
   - Check j = 3 -> nums[3]=1 < 2
   - Not found -> ans[1]=-1
   - Append 2 -> nums = [1, 2, 1, 1, 2]

3. i = 2, nums[i] = 1
   - Check j = 3 -> nums[3]=1 not greater
   - Check j = 4 -> nums[4]=2 > 1, so ans[2]=2
   - Append 1 -> nums = [1, 2, 1, 1, 2, 1]

Final ans = [2, -1, 2]
*/
