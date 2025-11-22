/*
LeetCode 239 - Sliding Window Maximum

QUESTION:
Given an integer array 'nums' and an integer 'k', find the maximum element in each sliding window of size 'k' as it moves from left to right across the array.

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

APPROACH USED:
Brute Force Method:
For each window, scan all elements and find the maximum.

TIME COMPLEXITY:
O(n * k), where n is the number of elements in 'nums'.

SPACE COMPLEXITY:
O(n), where n is the number of sliding windows stored in 'ans'.

IS THIS THE MOST OPTIMAL SOLUTION?
❌ No, this is not the optimal approach.

WILL IT BE ACCEPTED ON LEETCODE?
✅ Accepted for small test cases.
❌ Likely to cause TLE (Time Limit Exceeded) for large inputs because of its high time complexity.

SIMILAR QUESTIONS:
- Sliding Window Minimum
- Maximum of all subarrays of size k
- Monotonic Queue (deque) based problems

*/

/*-------------------- CODE STARTS HERE --------------------*/
#include <iostream>
#include <vector>
#include <climits> // For INT_MIN
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans; // To store maximums of each window

        int st = 0;            // Start index of the window
        int end = k - 1;      // End index of the window

        // Slide the window across the array until 'end' reaches the last index
        while(end < nums.size()){
            int m = INT_MIN; // Initialize max to smallest possible integer

            // Find the max value in the current window from 'st' to 'end'
            for(int i = st; i <= end; i++){
                m = max(m, nums[i]); // Update max if a larger element is found
            }
            ans.push_back(m); // Store the max value found for this window

            st++; // Move the window one step forward
            end++; // Move the window one step forward
        }

        return ans; // Return the array containing all window maxes
    }
};

/*---------------- LOGIC & EXPLANATION -------------------*/

/*
LOGIC:
1. We simulate the sliding window using two pointers: 'st' and 'end'.
2. 'st' is the start index, and 'end' is the end index of the current window.
3. For each window, we iterate through all elements from 'st' to 'end' to find the maximum.
4. After computing the max for one window, we move both pointers to the right by one position.
5. We repeat this until the 'end' reaches the last index of 'nums'.
6. All maximums are stored in the 'ans' vector, which is returned at the end.

WHY THESE STEPS?
- Initializing 'm' to 'INT_MIN' ensures that any number in 'nums' will replace it if larger.
- The 'for' loop guarantees we compare all window elements.
- The sliding mechanism ensures each window is considered exactly once.

WORKING OF FUNCTION:
For nums = [1,3,-1,-3,5,3,6,7], k = 3:
1. Window [1,3,-1]: max = 3 → ans = [3]
2. Window [3,-1,-3]: max = 3 → ans = [3,3]
3. Window [-1,-3,5]: max = 5 → ans = [3,3,5]
4. Window [-3,5,3]: max = 5 → ans = [3,3,5,5]
5. Window [5,3,6]: max = 6 → ans = [3,3,5,5,6]
6. Window [3,6,7]: max = 7 → ans = [3,3,5,5,6,7]
Final output: [3,3,5,5,6,7]

*/

/*-------------------- MAIN FUNCTION --------------------*/
int main() {
    Solution sol;

    // Example test case
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
- The brute force method is simple and easy to implement.
- It always scans the entire window since the maximum can be anywhere.
- It's good for learning and understanding sliding window mechanics.

⚠ WARNINGS:
- For large arrays, this approach will likely result in a Time Limit Exceeded (TLE) error.
- Avoid using brute force for high constraint problems unless necessary.

📌 SIMILAR QUESTIONS:
- Sliding Window Minimum
- Finding maximum in subarrays
- Monotonic Queue problems that optimize sliding window computations

🔑 APPROACH COMPARISON:
- Brute force is intuitive but inefficient.
- Optimized methods use data structures like deque to achieve O(n) complexity.
- Understanding both helps build algorithmic thinking.

*/
