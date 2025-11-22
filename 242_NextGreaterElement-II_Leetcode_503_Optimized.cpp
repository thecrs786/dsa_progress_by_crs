// LeetCode Problem 503: Next Greater Element II
// Question Summary:
// Given a circular array nums, for each element find the next greater element.
// The next greater element is the first greater number traversed forward.
// If none exists, assign -1.
//
// Example:
// Input: nums = [1, 2, 1]
// Output: [2, -1, 2]
// Explanation: For 1 → next greater is 2; for 2 → none → -1; for 1 → wrap → 2.
//
// Time Complexity: O(n), each element is pushed/popped at most once.
// Space Complexity: O(2n), due to duplicating the array once to simulate circularity.
// Approach Used: Stack-based method with array duplication to handle circular behavior.
// Is it the most optimal? ❌ Not the most space optimal because of extra array copy.
// Will it be accepted? ✅ Yes, passes all test cases without TLE or MLE.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> copy(nums); // Copy of the original array to extend for circularity
        int n = nums.size();
        vector<int> ans(n);    // Stores the answer for each index
        stack<int> s;          // Stack to store indices while processing elements

        // Extend the array once by appending the original array to itself
        for(int i = 0; i < n; i++){
            copy.push_back(nums[i]);
        }

        // Traverse from the end of the extended array to the beginning
        for(int i = copy.size() - 1; i >= 0; i--){
            int idx = i % n; // Map the extended array index back to the original index
            
            // Pop smaller or equal elements from the stack
            while(!s.empty() && copy[i] >= copy[s.top()]) {
                s.pop();
            }

            // Assign the next greater element if available, otherwise -1
            if(s.empty()) ans[idx] = -1;
            else ans[idx] = copy[s.top()];

            // Push the current index into the stack for future comparisons
            s.push(i);
        }

        return ans;
    }
};

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
Logic Explanation and Working:

1. The circular nature of the array means that after reaching the end, we need to wrap around to the beginning.
   To handle this easily, we duplicate the array once, so all wrap-around cases can be treated as regular forward traversal.

2. We iterate from the last index to the first in the extended array to ensure that at each step,
   we can efficiently determine the next greater element using a stack.

3. The modulo operator (%) is used to map the extended index 'i' back to the original array's index.
   Example: if i = 4 and n = 3 → 4 % 3 = 1 → refers to index 1 in the original array.

4. We use 'idx = i % n' to ensure that the answers are written in the correct position,
   while 'i' is used to track elements in the extended array.

5. The stack stores indices of elements. When a new element is considered, we pop elements that are smaller or equal,
   because they cannot be the next greater for future elements.

6. After popping, if the stack is empty, it means no next greater element exists → assign -1.
   If the stack is not empty, the element at the top of the stack is the next greater → assign accordingly.

7. We push the current index into the stack, so it can be used for future comparisons when traversing backwards.

8. Traversing twice ensures that every element can access all subsequent elements including those at the start of the array.
   This guarantees that we can find the next greater for every element if one exists.

9. The algorithm runs in O(n) time because each index is pushed and popped at most once.
   Space usage is O(2n) because we store the extended array along with the stack and answer array.

Important Details and Key Insights:
- Circular traversal is handled by duplicating the array → practical but not space-optimal.
- Using % is essential to map indices back to the original array and maintain correctness.
- Stack ensures efficient lookup for next greater elements → avoids nested loops.
- Traversing from the end allows us to always have the needed elements in the stack.
- This method is accepted but can be optimized further by avoiding duplication.
*/
