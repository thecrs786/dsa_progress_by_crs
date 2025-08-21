#include <iostream>
#include <vector>
using namespace std;

/*
    ✅ LEETCODE 78. SUBSETS
    ---------------------------------
    🎯 PROBLEM BRIEF:
    - Given a vector `nums` of distinct integers, return all possible subsets (the power set).
    - A subset can be empty or contain any number of elements.
    - The order of subsets does not matter.

    Example:
      Input: nums = [1,2,3]
      Output: [[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]]

    ---------------------------------
    📌 SOLUTION NAME:
    Backtracking (Recursive Approach)

    ---------------------------------
    ⏱️ TIME COMPLEXITY:
    - There are 2^n subsets for n elements.
    - Each subset can take O(n) to copy into `allsubsets`.
    - Total = O(2^n * n).

    💾 SPACE COMPLEXITY:
    - O(2^n * n) for storing all subsets.
    - O(n) recursion depth for the call stack.
    - Overall: O(2^n * n).

    ---------------------------------
    ⚡ OPTIMALITY:
    - This is the most optimal solution for generating all subsets.
    - You cannot do better than O(2^n * n), since the output itself is that large.
    - This solution is fully accepted by LeetCode.
    - No risk of TLE/MLE for constraints (n ≤ 10–20 on LeetCode).

    ---------------------------------
    🔑 KEY INSIGHTS:
    1. At each index `i`, we have 2 choices:
       - INCLUDE nums[i]
       - EXCLUDE nums[i]
       This binary decision tree generates all 2^n subsets.
    
    2. Why `allsubsets.push_back(ans)` works:
       - `ans` is a vector representing the current subset (partial path).
       - At base case, when `i == nums.size()`, we have a *complete* subset.
       - `push_back(ans)` makes a **copy** of `ans` and stores it into `allsubsets`.
       - Without copy, we’d lose subsets when `ans` changes (due to backtracking).
       - `{ans}` is redundant, `push_back(ans)` is enough.

    3. Backtracking ensures we “undo” the include step before exploring the exclude path.
       - This is why `ans.pop_back()` is essential.

    ---------------------------------
    🚀 FUNCTION LOGIC (Step by Step):
    getallsubsets(nums, ans, allsubsets, i):
    - Base Case:
        If i == nums.size():
            → All decisions made, subset `ans` is complete.
            → Store it in allsubsets using push_back(ans).
            → Return to backtrack.
    - Recursive Case:
        1. INCLUDE nums[i]:
            → ans.push_back(nums[i])
            → Recurse with i+1
        2. BACKTRACK:
            → ans.pop_back() to undo
        3. EXCLUDE nums[i]:
            → Recurse with i+1 (without adding nums[i])

    ---------------------------------
*/

class Solution {
public:
    void getallsubsets(vector<int>& nums, vector<int> &ans, vector<vector<int>> &allsubsets, int i) {
        // ✅ Base case: all elements processed
        if(i == nums.size()) {
            allsubsets.push_back({ans} ); // store current subset (COPY of ans)
            return;
        }

        // ---------- INCLUDE CASE ----------
        ans.push_back(nums[i]);                 // choose nums[i]
        getallsubsets(nums, ans, allsubsets, i+1);  // recurse with it included

        // ---------- BACKTRACK ----------
        ans.pop_back();                         // undo choice

        // ---------- EXCLUDE CASE ----------
        getallsubsets(nums, ans, allsubsets, i+1);  // recurse without nums[i]
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> ans;               // temporary subset being built
        vector<vector<int>> allsubsets; // stores all subsets
        getallsubsets(nums, ans, allsubsets, 0); // start recursion
        return allsubsets;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};

    // Call subsets() to generate all subsets
    vector<vector<int>> result = sol.subsets(nums);

    // Print the result for analysis
    cout << "All subsets of [1,2,3] are:" << endl;
    for(auto &subset : result) {
        cout << "[";
        for(int j = 0; j < subset.size(); j++) {
            cout << subset[j];
            if(j != subset.size()-1) cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}

/*
    ---------------------------------
    🧠 WORKING EXAMPLE: nums = [1,2]
    
    Call Tree:
    
    getallsubsets(nums, [], allsubsets, 0)
      → INCLUDE 1
        getallsubsets(nums, [1], allsubsets, 1)
          → INCLUDE 2
            getallsubsets(nums, [1,2], allsubsets, 2) 
              → Base case → store [1,2]
          → BACKTRACK (remove 2)
          → EXCLUDE 2
            getallsubsets(nums, [1], allsubsets, 2)
              → Base case → store [1]
      → BACKTRACK (remove 1)
      → EXCLUDE 1
        getallsubsets(nums, [], allsubsets, 1)
          → INCLUDE 2
            getallsubsets(nums, [2], allsubsets, 2)
              → Base case → store [2]
          → BACKTRACK (remove 2)
          → EXCLUDE 2
            getallsubsets(nums, [], allsubsets, 2)
              → Base case → store []
    
    Final allsubsets = [[1,2], [1], [2], []]

    ---------------------------------
    🔑 KEY DETAIL ABOUT STORAGE:
    - At base case, we do allsubsets.push_back(ans).
    - ans is passed by reference, BUT push_back copies it.
    - Example:
        If ans = [1,2] at base case, 
        push_back stores a snapshot [1,2].
        Later backtracking removes 2 → ans=[1], 
        but the snapshot [1,2] remains in allsubsets.
    - This is how we safely collect all subsets.
    ---------------------------------
*/
