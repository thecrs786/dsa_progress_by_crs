#include <bits/stdc++.h>
using namespace std;

/*
Problem 496: Next Greater Element I (LeetCode)
------------------------------------------------
Given two integer arrays nums1 and nums2 where nums1 is a subset of nums2, 
find the next greater number for each element in nums1 in the array nums2.

Next greater number of a number x in nums2 is the first greater number to its right in nums2. 
If it does not exist, return -1 for this number.

Example:
--------
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation:
- Next greater element for 4 in nums2 is -1 (no greater element to the right)
- Next greater element for 1 in nums2 is 3
- Next greater element for 2 in nums2 is -1

Solution Method: Brute Force using Nested Loops and HashMap
-----------------------------------------------------------
- We traverse nums2 with a nested loop to find the first greater element to the right for each number.
- We store results in an unordered_map for O(1) lookup when processing nums1.
- Finally, we build the answer for nums1 using the map.

Time Complexity: O(n^2) where n = nums2.size() (due to nested loop)
Space Complexity: O(n) for the unordered_map
Optimality: Not the most optimal (stack + map solution is O(n)), but works for given constraints.
Will it be accepted: Yes, LeetCode accepts this and it won't cause TLE or MLE for given constraints.

Key Insights:
-------------
1. Semicolon after if-statement can break logic. Make sure the block follows curly braces.
2. Map allows O(1) lookup for nums1 elements.
3. Nested loop ensures the first greater element to the right is found correctly.
4. Brute force is easy to understand and implement, suitable for small input sizes.
*/

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> m;              // Step 1: Map to store next greater element for each number in nums2
        vector<int> ans(nums1.size());         // Step 2: Prepare answer array for nums1

        // Step 3: Traverse nums2 to find next greater for each element
        for(int i = 0; i < nums2.size(); i++){
            m[nums2[i]] = -1;                  // Default value if no greater element found
            for(int j = i + 1; j < nums2.size(); j++){
                if(nums2[j] > nums2[i]){       // If a greater element is found
                    m[nums2[i]] = nums2[j];   // Store it in the map
                    break;                     // Stop inner loop; we only need the first greater element
                }
            }
        }

        // Step 4: Build the answer for nums1 using the map
        for(int i = 0; i < nums1.size(); i++){
            ans[i] = m[nums1[i]];              // Lookup next greater element in O(1)
        }

        return ans;                             // Step 5: Return the result
    }
};

/*
Function Logic Walkthrough:
---------------------------
1. unordered_map<int,int> m:
   - Purpose: Quickly find next greater element for any nums1 element.
   - Key = element in nums2, Value = its next greater element or -1 if none.

2. Nested loop:
   - Outer loop i: Pick current element nums2[i].
   - Inner loop j: Look rightwards (i+1 to end) for first element greater than nums2[i].
   - If found, store in map and break inner loop.

3. Lookup for nums1:
   - Simply map each nums1 element to its precomputed next greater value.

4. Return vector ans.

Working of the function (example):
---------------------------------
nums1 = [4,1,2], nums2 = [1,3,4,2]
Step 1: Initialize map with defaults: {1:-1,3:-1,4:-1,2:-1}
Step 2: Nested loop processing nums2:
   - i=0, nums2[i]=1 → first greater is 3 → m[1]=3
   - i=1, nums2[i]=3 → first greater is 4 → m[3]=4
   - i=2, nums2[i]=4 → no greater → m[4]=-1
   - i=3, nums2[i]=2 → no greater → m[2]=-1
Step 3: Build answer for nums1: ans = [m[4], m[1], m[2]] = [-1,3,-1]

Important Details & Key Sights:
--------------------------------
- Always use braces {} for if-blocks inside nested loops.
- Using a map avoids recomputation for nums1 elements.
- Brute force works due to small constraints but memorize stack+map for O(n) optimal solution.
*/

// Main function with working example
int main() {
    vector<int> nums1 = {4,1,2};
    vector<int> nums2 = {1,3,4,2};
    Solution sol;
    vector<int> result = sol.nextGreaterElement(nums1, nums2);

    cout << "Next Greater Elements: ";
    for(int x : result){
        cout << x << " ";
    }
    cout << endl;

    /*
    Expected Output:
    Next Greater Elements: -1 3 -1
    */
    return 0;
}
