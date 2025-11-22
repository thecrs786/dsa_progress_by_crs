/*
LeetCode 239 - Sliding Window Maximum

QUESTION:
Given an integer array 'nums' and a sliding window of size 'k', you are required to find the maximum element in each sliding window as it moves from left to right across the array.

EXAMPLES:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window positions:
[1, 3, -1] → max is 3
[3, -1, -3] → max is 3
[-1, -3, 5] → max is 5
[-3, 5, 3] → max is 5
[5, 3, 6] → max is 6
[3, 6, 7] → max is 7

CONSTRAINTS:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length

APPROACH:
Optimized Sliding Window using Deque
We use a double-ended queue (deque) to keep track of indices of potential maximum elements for the current window.
- Elements in the deque are stored in decreasing order.
- The front always holds the index of the maximum element in the current window.
- Elements are removed from the back if they are smaller than the current element.
- Elements are removed from the front if they are outside the current window.

TIME COMPLEXITY:
✔ O(n), where n is the length of 'nums'.
Each element is added and removed at most once from the deque.

SPACE COMPLEXITY:
✔ O(k), where k is the window size.
The deque stores indices of elements in the current window only.

IS THIS THE MOST OPTIMAL SOLUTION?
✅ Yes, this is the optimal approach for this problem.

WILL IT BE ACCEPTED ON LEETCODE?
✅ It will be accepted for all inputs without TLE or MLE.

SIMILAR QUESTIONS:
- Sliding Window Minimum
- Maximum of all subarrays of size k
- Problems involving Monotonic Queues
- Problems optimized using stacks or two pointers
*/

/*-------------------- CODE STARTS HERE --------------------*/
#include <iostream>
#include <vector>
#include <deque> // Using deque for double-ended access
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans; // Stores the maximum of each window
        deque<int> d;    // Stores indices of potential max elements in decreasing order

        // 1. Process the first 'k' elements to initialize the deque
        for(int i = 0; i < k; i++) {
            // Remove all elements from the back that are smaller than the current element
            while(!d.empty() && nums[d.back()] <= nums[i])
                d.pop_back();
            d.push_back(i); // Add current element index to the back
        }
        // Add the maximum of the first window to the result
        ans.push_back(nums[d.front()]);

        // 2. Process the rest of the elements in the array
        for(int i = k; i < nums.size(); i++) {
            // Remove elements from the front if they are out of the current window
            while(!d.empty() && d.front() <= i - k)
                d.pop_front();

            // Remove all elements from the back that are smaller than the current element
            while(!d.empty() && nums[d.back()] <= nums[i])
                d.pop_back();

            // Add the current element's index to the back
            d.push_back(i);

            // The front of the deque holds the index of the max element for the current window
            ans.push_back(nums[d.front()]);
        }

        return ans; // Return the final list of maximums
    }
};

/*---------------- LOGIC & EXPLANATION -------------------*/

/*
WHY DEQUE AND NOT A QUEUE?
- A normal queue allows removal from the front only, but in this problem, we need to remove smaller elements from the back efficiently.
- A deque allows us to remove from both ends in constant time.
- We need to maintain decreasing order, so smaller elements at the back should be removed when a larger element arrives.

WHY STORE INDICES IN THE DEQUE?
- We need to check if an element at the front is out of the current window range by comparing its index to 'i - k'.
- Storing values makes it harder to track which elements are outdated.

WHY ACCESS FRONT BUT REMOVE FROM BACK?
- The front always holds the index of the largest element in the current window → this is the result.
- Elements at the back that are smaller than the incoming element cannot be the maximum anymore → we remove them.

IN WHAT ORDER ARE ELEMENTS STORED?
- Elements are stored in decreasing order of their values.
- If the current element is larger than some elements at the back, those elements are removed because they won't be useful anymore.

WHAT DOES EACH LOOP DO?
1. The first loop initializes the deque for the first 'k' elements, ensuring it holds potential maximums in order.
2. The second loop:
   - Removes outdated indices from the front.
   - Removes smaller elements from the back.
   - Adds the new element's index to the back.
   - Records the current maximum from the front.

WORKING EXAMPLE:
nums = [1,3,-1,-3,5,3,6,7], k = 3
Initial deque after first window: holds index of 3 → [1]
Result after first window: [3]
Process remaining elements by updating deque and recording max at each step
Final output: [3,3,5,5,6,7]
*/

/*-------------------- MAIN FUNCTION --------------------*/
int main() {
    Solution sol;

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> result = sol.maxSlidingWindow(nums, k);

    cout << "Sliding window maximums are: ";
    for(int val : result){
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*------------------ IMPORTANT DETAILS ------------------*/

/*
✅ KEY INSIGHTS:
- Deque allows efficient insertion and deletion from both ends.
- The maximum element is always at the front of the deque.
- Storing indices lets us check window bounds easily.
- Every element is pushed and popped at most once → O(n) total operations.

⚠ WARNINGS:
- Using a normal queue will not work because it can't remove elements from the back.
- Storing actual values instead of indices will lead to incorrect window management.
- Not removing outdated elements from the front will cause wrong results.

📌 SIMILAR QUESTIONS:
- Sliding Window Minimum
- Finding maximum/minimum in subarrays using monotonic queues
- Optimizations using stacks, two pointers, or heaps

🔑 APPROACH COMPARISON:
- Brute force → O(nk), scans each window individually
- Optimized → O(n), uses deque to maintain order and eliminate useless elements
- This pattern appears in problems requiring efficient window management or maintaining order dynamically
*/
