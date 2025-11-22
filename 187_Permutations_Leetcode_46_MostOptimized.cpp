/*******************************************************
 * PROBLEM (LeetCode 46: Permutations)
 * -----------------------------------------------------
 * Given an array nums of distinct integers, return all
 * possible permutations of nums. The order does not matter.
 *
 * EXAMPLE :
 * Input:  nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],
 *          [2,3,1],[3,1,2],[3,2,1]]
 *
 * METHOD USED : "Swap + Backtracking"
 * -----------------------------------------------------
 * - At each recursion level, we FIX the current index `idx`.
 * - To fix it, we try every candidate from idx..end of nums.
 * - After fixing, recursion takes care of the remaining indexes.
 * - Backtracking (swap-back) restores the state for the next choice.
 *
 * ANALOGY TO MATH :
 * - In math, when listing permutations, we say:
 *   "Put each possible number at position 1, then permute the rest."
 * - That’s exactly what the for-loop and recursion are doing:
 *   - Loop = choosing who sits at the current index.
 *   - Recursion = solve the smaller subproblem (remaining indexes).
 *
 * TIME COMPLEXITY :
 * - O(n * n!)
 *   - There are n! permutations.
 *   - Each costs O(n) to copy into the result.
 *
 * SPACE COMPLEXITY :
 * - O(n) recursion depth (excluding result storage).
 * - O(n * n!) space to store the output.
 *
 * OPTIMALITY :
 * - Generating n! permutations cannot be done faster than O(n*n!).
 *   This method is optimal.
 *
 * LEETCODE FEASIBILITY :
 * - Absolutely accepted, no TLE/MLE. n is small (≤ 6–8).
 *******************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * getpermutations:
     * nums = the array we are permuting
     * ans  = stores all generated permutations
     * idx  = the current index we are trying to fix
     */
    void getpermutations(vector<int>& nums,
                         vector<vector<int>>& ans,
                         int idx) {
        // BASE CASE:
        // If idx == nums.size(), all positions are fixed.
        // This means we found a complete permutation.
        if (idx == nums.size()) {
            ans.push_back(nums); // copy current permutation
            return;
        }

        // CHOICE LOOP:
        // For the current index `idx`, we try every element
        // from nums[idx] to nums[end] as the candidate.
        for (int i = idx; i < (int)nums.size(); i++) {
            // Step 1: Fix nums[i] at position idx by swapping
            swap(nums[idx], nums[i]);

            // Step 2: Recursively fix the next index (idx+1)
            getpermutations(nums, ans, idx + 1);

            // Step 3: Backtrack — undo the swap to restore
            // nums to its previous state for the next iteration.
            swap(nums[i], nums[idx]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        getpermutations(nums, ans, 0); // Start fixing from index 0
        return ans;
    }
};

/**********************
 * WORKING EXAMPLE
 * -------------------
 * We'll test nums = [1,2,3] and print the recursion tree.
 **********************/
static void printPermutations(const vector<vector<int>>& perms) {
    cout << "Total permutations: " << perms.size() << "\n";
    cout << "[\n";
    for (const auto& v : perms) {
        cout << "  [";
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i] << (i + 1 < v.size() ? ", " : "");
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums = {1,2,3};
    auto res = sol.permute(nums);

    cout << "Case: nums = [1,2,3]\n";
    printPermutations(res);

    return 0;
}

/**************************************************************
 * DETAILED LOGIC WALKTHROUGH
 * ------------------------------------------------------------
 * nums = [1,2,3]
 *
 * Step 1: idx=0
 * - Loop i=0 → swap(0,0) → nums=[1,2,3]
 *   → Recurse with idx=1
 *
 * Step 2: idx=1
 * - Loop i=1 → swap(1,1) → nums=[1,2,3]
 *   → Recurse with idx=2
 *
 * Step 3: idx=2
 * - Loop i=2 → swap(2,2) → nums=[1,2,3]
 *   → Recurse with idx=3 → BASE CASE → push [1,2,3]
 * - Backtrack swaps restore.
 *
 * Back to idx=1:
 * - i=2 → swap(1,2) → nums=[1,3,2]
 *   → Recurse idx=2 → produce [1,3,2]
 * - Backtrack to [1,2,3].
 *
 * Back to idx=0:
 * - i=1 → swap(0,1) → nums=[2,1,3]
 *   → Recurse into idx=1 → generate [2,1,3], [2,3,1]
 *   → Backtrack to [1,2,3]
 *
 * - i=2 → swap(0,2) → nums=[3,2,1]
 *   → Recurse into idx=1 → generate [3,2,1], [3,1,2]
 *   → Backtrack to [1,2,3]
 *
 * FINAL RESULT = 6 permutations.
 *
 * ------------------------------------------------------------
 * KEY INSIGHT ABOUT LOOP VS RECURSION :
 * - The for-loop decides WHO will sit at the current index.
 *   (just like in math: "pick someone for position idx")
 * - The recursive call says:
 *   "Now that current index is fixed, let's do the same
 *    process for the remaining indexes."
 *
 * - Backtracking (swap-back) ensures independence of choices.
 *   Without it, previous choices would leak into the next branch.
 *
 * TREE VIEW (for nums = [1,2,3]):
 * idx=0
 *   ├── i=0 → [1, _, _]
 *   │      ├── i=1 → [1,2,_] → i=2 → [1,2,3]
 *   │      └── i=2 → [1,3,_] → i=2 → [1,3,2]
 *   ├── i=1 → [2, _, _]
 *   │      ├── i=1 → [2,1,_] → i=2 → [2,1,3]
 *   │      └── i=2 → [2,3,_] → i=2 → [2,3,1]
 *   └── i=2 → [3, _, _]
 *          ├── i=1 → [3,2,_] → i=2 → [3,2,1]
 *          └── i=2 → [3,1,_] → i=2 → [3,1,2]
 *
 * TOTAL = 6 leaves → 6 permutations.
 **************************************************************/
