/**************************************************************************************
🔹 Problem: Combination Sum (LeetCode 39)
Given an array of distinct integers (candidates) and a target integer, find all unique
combinations of candidates where the chosen numbers sum to target. You may use each 
candidate an unlimited number of times. The order of combinations does not matter.

Example:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]

**************************************************************************************

🔹 Approach: Backtracking (DFS)
We recursively explore all possibilities:
1. Include the current candidate (as many times as possible).
2. Skip the current candidate (move to next one).
3. Stop when sum == target (valid combination).
4. Stop when sum > target (invalid path).

We use a "remaining" variable to keep track of what is left to reach target.

**************************************************************************************

🔹 Key Insights:
- Each recursive call represents a decision point: include OR exclude the current number.
- Because numbers can be used multiple times, after including `candidates[i]`, we do NOT
  move to `i+1`. We stay on `i` to allow unlimited reuse.
- Backtracking is done by popping from `ans` after exploring a branch, so the recursion 
  tree can try other possibilities.
- `remaining` ensures we don’t overshoot beyond target.
- Sorting the array is OPTIONAL for correctness, but helps with pruning:
  If `candidates[i] > remaining`, break early → saves recursion calls.

**************************************************************************************

🔹 Time Complexity:
- Worst case: O(2^T) where T ≈ target / min(candidates).
  Because for each candidate, we either include it or exclude it, and recursion depth can 
  go as far as target/minimum value.
- With pruning (sorted + early break), efficiency improves drastically.
- Typical accepted runtime on LeetCode.

🔹 Space Complexity:
- O(T) recursion depth (stack space, max path length = target/min).
- O(#combinations * average length of combination) for storing results.

**************************************************************************************

🔹 Is this optimal?
- Yes. This backtracking approach is the most optimal known for this problem.
- Sorting is not mandatory but increases efficiency (not decreases).
- Accepted by LeetCode, does NOT cause TLE/MLE under constraints.

*************************************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Helper recursive function for backtracking
    void helper(vector<vector<int>> &result,
                vector<int> &candidates,
                vector<int> &ans,
                int sum,
                int remaining,
                int i) {
        
        // ✅ Base Case 1: If remaining == 0 → Found valid combination
        if (remaining == 0) {
            result.push_back(ans);
            return;
        }

        // ❌ Base Case 2: Out of bounds or overshoot
        if (i == candidates.size() || remaining < 0) return;

        // 🔹 Choice 1: Include candidates[i] (multiple times possible)
        ans.push_back(candidates[i]);
        helper(result, candidates, ans, sum + candidates[i], remaining - candidates[i], i);
        ans.pop_back(); // backtrack

        // 🔹 Choice 2: Exclude candidates[i] and move forward
        helper(result, candidates, ans, sum, remaining, i + 1);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> ans;

        // Sorting is OPTIONAL, but helps with pruning
        sort(candidates.begin(), candidates.end());

        helper(result, candidates, ans, 0, target, 0);
        return result;
    }
};

/**************************************************************************************
🔹 Explanation of Important Points:
1. "remaining" variable:
   - Keeps track of how much more is needed to reach target.
   - Each inclusion reduces "remaining".
   - Prevents overshooting and stops recursion early.

2. Infinite inclusion & its limit:
   - By calling helper with same `i` after including candidates[i], we allow unlimited usage.
   - Limit is naturally imposed by "remaining" (cannot go below 0).

3. Three choices:
   - NO inclusion → skip candidate, go to next (helper(..., i+1)).
   - ONE inclusion → include candidate once, then move on in recursion.
   - MULTIPLE inclusion → handled by staying on same `i`.

4. Backtracking:
   - After including candidates[i], we backtrack using ans.pop_back().
   - This ensures the path state is restored for exploring other branches.

5. Sorting necessity:
   - Not mandatory for correctness.
   - With sorting, we can prune: if candidates[i] > remaining, break → avoids useless calls.
   - This improves efficiency, so sorting INCREASES optimality.

**************************************************************************************

🔹 Working Example (step-by-step trace):

Input: candidates = [2,3,6,7], target = 7

Path exploration:
- Pick 2 → remaining=5 → pick 2 → remaining=3 → pick 2 → remaining=1 → pick 2 → remaining=-1 ❌
- Backtrack → try 3 → remaining=0 ✅ [2,2,3]
- Backtrack → try 6 ❌ overshoot
- Backtrack → try 7 → remaining=0 ✅ [7]

Output: [[2,2,3],[7]]

**************************************************************************************/

int main() {
    Solution sol;
    vector<int> candidates = {2,3,6,7};
    int target = 7;

    vector<vector<int>> result = sol.combinationSum(candidates, target);

    cout << "Combinations for target " << target << ":\n";
    for (auto &vec : result) {
        cout << "[ ";
        for (int num : vec) cout << num << " ";
        cout << "]\n";
    }

    return 0;
}
