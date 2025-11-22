#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Problem 496: Next Greater Element I
--------------------------------------------

Problem Summary:
- Given two integer arrays nums1 and nums2, where nums1 is a subset of nums2.
- For each element in nums1, find the **next greater element** in nums2.
- Next greater element = first element to the right in nums2 that is greater than current element.
- If no greater element exists, return -1 for that element.

Example:
--------
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation:
- Next greater element for 4 is -1 (no greater element to the right)
- Next greater element for 1 is 3
- Next greater element for 2 is -1

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]

Solution Name/Method: **Monotonic Stack + HashMap**
---------------------------------------------------
- Use a stack to track potential “next greater elements” in nums2.
- Traverse nums2 from **right to left**.
- Pop smaller elements from stack to maintain **monotonic decreasing stack**.
- Use unordered_map to store next greater element for each number in nums2.
- Lookup map for nums1 to build answer.

Time Complexity: O(n + m)
- n = nums2.size(), m = nums1.size()
- Each element in nums2 is pushed/popped at most once.

Space Complexity: O(n)
- Stack + unordered_map

Optimality:
- This is the **most optimal solution** in terms of time complexity.
- Brute force O(n^2) is slower for large inputs.

Will it be accepted by LeetCode?
- ✅ Yes.  
- No TLE or MLE.

Key Insights & Points of Confusion:
-----------------------------------
1. **Why popping from the stack is safe:**
   - When we pop smaller elements than nums2[i], they can never be the next greater element for any previous element (on the left).
   - The previous element (nums2[i-1]) will either find a greater element already on the stack, or nums2[i] itself is its next greater element.
   - So popping smaller elements does not lose information — it actually discards useless candidates.
   
2. Stack always stores elements in **monotonic decreasing order** from top to bottom.
3. Map allows O(1) lookup for nums1 elements.
4. Always pre-allocate answer array for efficiency.

*/

// Optimized Stack + Map Solution
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans(nums1.size());          // Pre-allocate answer vector
        unordered_map<int, int> m;              // Map to store next greater element for each number
        stack<int> s;                           // Stack to keep track of next greater candidates

        // Traverse nums2 from right to left
        for(int i = nums2.size()-1; i >= 0; i--){
            // Pop elements smaller or equal to nums2[i]
            while(!s.empty() && s.top() <= nums2[i]){
                s.pop();  // Smaller elements cannot be next greater for current or any left element
            }

            // If stack is empty → no greater element to the right
            if(s.empty()){
                m[nums2[i]] = -1;
            }
            else {
                m[nums2[i]] = s.top();  // Top of stack is next greater element
            }

            s.push(nums2[i]);  // Push current element to stack as potential next greater for left elements
        }

        // Build answer for nums1 using map
        for(int i = 0; i < nums1.size(); i++){
            ans[i] = m[nums1[i]];  // O(1) lookup
        }

        return ans;
    }
};

// Main function with working example
int main() {
    vector<int> nums1 = {4,1,2};   // Example input subset
    vector<int> nums2 = {1,3,4,2}; // Full array

    Solution sol;
    vector<int> result = sol.nextGreaterElement(nums1, nums2);

    cout << "Next Greater Elements: ";
    for(int x : result){
        cout << x << " ";          // Output each next greater element
    }
    cout << endl;

    /*
    Expected Output:
    Next Greater Elements: -1 3 -1

    Explanation Line-by-Line:
    ---------------------------------
    nums2 traversal (right to left):
    - i=3, nums2[i]=2, stack empty → map[2]=-1, push 2 → stack=[2]
    - i=2, nums2[i]=4, pop 2 (2<=4), stack empty → map[4]=-1, push 4 → stack=[4]
    - i=1, nums2[i]=3, stack top=4 > 3 → map[3]=4, push 3 → stack=[4,3]
    - i=0, nums2[i]=1, stack top=3 > 1 → map[1]=3, push 1 → stack=[4,3,1]

    Build answer for nums1:
    - ans[0]=map[4]=-1
    - ans[1]=map[1]=3
    - ans[2]=map[2]=-1
    */

    return 0;
}
