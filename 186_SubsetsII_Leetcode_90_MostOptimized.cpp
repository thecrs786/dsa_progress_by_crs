/*******************************************************
 * PROBLEM (LeetCode 90: Subsets II) — BRIEF
 * -----------------------------------------------------
 * Given a vector<int> nums that may contain duplicates,
 * return ALL possible subsets (the power set) WITHOUT
 * DUPLICATES. The order of subsets doesn't matter.
 *
 * KEY CHALLENGE: Handling duplicate elements so that
 * logically identical subsets (e.g., [1,2] from picking
 * the first '2' vs. the second '2') appear only once.
 *
 * METHOD NAME (This file): "Include-then-Skip-Run Exclude"
 * ---------------------------------------------------------
 * - Sort nums.
 * - At index i:
 *    1) INCLUDE nums[i] -> recurse i+1
 *    2) BACKTRACK (pop the include)
 *    3) EXCLUDE the entire run of duplicates starting at i+1
 *       (i.e., jump idx forward over all equal nums[idx]==nums[idx-1])
 *       -> recurse from the first index after that run.
 *
 * WHY THIS WORKS :
 * - When you exclude nums[i], you MUST also skip all of its
 *   identical twins at this recursion depth; otherwise, you
 *   can pick an indistinguishable twin later and produce a
 *   duplicate subset (same multiset content).
 *
 * TIME COMPLEXITY :
 * - O(n log n) for sort + O(n * 2^n) to generate/copy subsets.
 *   (Each subset copy costs up to O(n), total subsets ≤ 2^n.)
 *
 * SPACE COMPLEXITY :
 * - O(n) recursion depth + O(total output) to store answers.
 *
 * OPTIMALITY :
 * - Enumerating all unique subsets is Θ(#answers). You cannot
 *   asymptotically beat O(#answers). This solution is optimal.
 *
 * LEETCODE FEASIBILITY (No BS):
 * - LeetCode 90 typically has n ≤ 10. This solution is easily
 *   accepted. No TLE, no MLE. If n were ~20–25, still fine.
 *
 * WHY NOT "exclude->recurse, then include->recurse WITHOUT pop"?
 * --------------------------------------------------------------
 * 1) Backtracking requires restoring shared mutable state (vector).
 *    If you push and don't pop, the parent's state is polluted.
 * 2) Even with correct pops, excluding a value and then allowing
 *    its twin at the SAME depth produces duplicates. You must
 *    SKIP the entire run after an exclude at that depth.
 *
 * HOW DUPLICATES FORM (Intuition)
 * --------------------------------
 * Example: nums = [1,2,2] (sorted)
 *
 * Naive recursion (no skipping):
 *                 (start)
 *               /         \
 *           pick 1       skip 1
 *            /  \          /  \
 *        pick 2 skip 2  pick 2 skip 2
 *         / \    / \     / \    / \
 *       p2 s2  p2 s2   p2 s2  p2 s2
 *
 * Focus on producing subset [1,2]:
 * - pick 1, pick first 2, skip second 2 -> [1,2]
 * - pick 1, skip first 2, pick second 2 -> [1,2]  (DUPLICATE!)
 *
 * Both 2's are indistinguishable. To avoid this, when we choose to
 * EXCLUDE the first '2' at this depth, we must SKIP all subsequent
 * 2's at the SAME depth. That’s exactly what the idx-jump does.
 *
 * ASCII TREE (showing the SKIP after EXCLUDE):
 *
 * Suppose nums = [1, 2, 2, 2, 3]
 *
 * At i pointing to the first '2' (say i=1):
 *   INCLUDE path explores counts of 2's:
 *       include 2 at i=1 -> (i=2)
 *           include next 2 -> (i=3)
 *               include next 2 -> (i=4) -> ...
 *           ... (also tries partial counts)
 *
 *   EXCLUDE path must jump over the entire '2'-run:
 *       i=1 exclude -> idx jumps to first non-2 (idx=4 where nums[4]=3)
 *       recurse from idx=4, i.e., we never start a subset that first
 *       includes a later '2' after having excluded the earlier '2' at
 *       the SAME decision level — preventing duplicates like:
 *         (include second 2 / exclude first 2) vs
 *         (include first 2 / exclude second 2)
 *
 * POP_BACK IS NON-NEGOTIABLE (STATE RESTORE):
 * -------------------------------------------
 * We pass 'ans' by reference for performance. Each choice mutates it.
 * After returning from a branch where we pushed, we MUST pop to restore
 * the exact state the sibling branch expects. Otherwise, pollutants
 * leak into siblings and the whole tree is wrong.
 *
 *******************************************************/

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    void getallsubsets(vector<int>& nums,
                       vector<int>& ans,
                       vector<vector<int>>& allsubsets,
                       int i) {
        // BASE CASE: If we've considered all elements, record the subset.
        if (i == (int)nums.size()) {
            // Make a copy of the current path 'ans' and store it.
            allsubsets.push_back(ans);
            return;
        }

        /************ CHOICE 1: INCLUDE nums[i] ************
         * We always attempt the "include" branch first.
         * This path will allow selecting multiple copies if available
         * because subsequent indices can include the next identical numbers.
         ***************************************************/
        ans.push_back(nums[i]);                // choose nums[i]
        getallsubsets(nums, ans, allsubsets, i + 1);  // dive deeper with it
        ans.pop_back();                        // backtrack (restore 'ans')

        /************ CHOICE 2: EXCLUDE nums[i] ************
         * Critical duplicate handling:
         * If we exclude nums[i], then at THIS recursion depth we must
         * skip all identical twins of nums[i] so we don’t start a subset
         * with a later twin that would be indistinguishable from starting
         * with nums[i]. That would create duplicate subsets.
         *
         * We jump idx forward over the entire run equal to nums[i].
         ***************************************************/
        int idx = i + 1;
        while (idx < (int)nums.size() && nums[idx] == nums[idx - 1]) {
            // Skip over duplicates of nums[i] at the SAME depth.
            idx++;
        }

        // Now recurse from the first index after this run of duplicates.
        getallsubsets(nums, ans, allsubsets, idx);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // STEP 0: Sort to cluster duplicates; required for correct skipping.
        sort(nums.begin(), nums.end());

        vector<int> ans;                // current path
        vector<vector<int>> allsubsets; // collector
        getallsubsets(nums, ans, allsubsets, 0);
        return allsubsets;
    }
};

/**********************
 * WORKING EXAMPLE
 * -------------------
 * We'll run on multiple cases (including heavy duplicate runs)
 * and pretty-print output to verify uniqueness and logic.
 **********************/
static void printSubsets(const vector<vector<int>>& subs) {
    cout << "Total subsets: " << subs.size() << "\n";
    cout << "[\n";
    for (const auto& v : subs) {
        cout << "  [";
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i] << (i + 1 < v.size() ? ", " : "");
        }
        cout << "]\n";
    }
    cout << "]\n";
}

/*
 * DIAGNOSTIC NOTE:
 * For a multiset with frequencies f1, f2, ..., fk,
 * number of unique subsets is Π (fi + 1).
 * We'll compute this to sanity-check.
 */
static long long expectedUniqueSubsetsCount(vector<int> nums) {
    sort(nums.begin(), nums.end());
    long long ans = 1;
    for (int i = 0; i < (int)nums.size();) {
        int j = i;
        while (j < (int)nums.size() && nums[j] == nums[i]) j++;
        int freq = j - i;
        ans *= (freq + 1); // choose 0..freq copies
        i = j;
    }
    return ans;
}

/*
 * EXTRA: Why does "exclude-then-include" still require pop_back?
 * ----------------------------------------------------------------
 * Even if you try to recurse exclude first, then include, you MUST
 * pop after the include branch. Otherwise, 'ans' retains the pushed
 * value when returning to parent, corrupting sibling branches.
 *
 * Also, excluding a value at a depth and then including a later twin
 * at the SAME depth causes duplicates; hence the idx-jump is required
 * regardless of the order you explore branches.
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    // TEST 1: From the explanation: [1,2,2]
    {
        vector<int> nums = {1, 2, 2};
        auto res = sol.subsetsWithDup(nums);
        sort(res.begin(), res.end()); // sorting result vectors for stable display
        cout << "Case 1: nums = [1,2,2]\n";
        printSubsets(res);
        cout << "Expected count (product of (freq+1)): "
             << expectedUniqueSubsetsCount(nums) << "\n\n";
    }

    // TEST 2: Heavy duplicate run: [2,2,2,2]
    {
        vector<int> nums = {2, 2, 2, 2};
        auto res = sol.subsetsWithDup(nums);
        sort(res.begin(), res.end());
        cout << "Case 2: nums = [2,2,2,2]\n";
        printSubsets(res);
        cout << "Expected count: " << expectedUniqueSubsetsCount(nums) << "\n\n";
    }

    // TEST 3: Mixed: [1,2,2,2,3]
    {
        vector<int> nums = {1, 2, 2, 2, 3};
        auto res = sol.subsetsWithDup(nums);
        sort(res.begin(), res.end());
        cout << "Case 3: nums = [1,2,2,2,3]\n";
        printSubsets(res);
        cout << "Expected count: " << expectedUniqueSubsetsCount(nums) << "\n\n";
    }

    // TEST 4: All unique: [1,2,3]
    {
        vector<int> nums = {1, 2, 3};
        auto res = sol.subsetsWithDup(nums);
        sort(res.begin(), res.end());
        cout << "Case 4: nums = [1,2,3]\n";
        printSubsets(res);
        cout << "Expected count: " << expectedUniqueSubsetsCount(nums) << "\n\n";
    }

    // TEST 5: Empty input
    {
        vector<int> nums = {};
        auto res = sol.subsetsWithDup(nums);
        sort(res.begin(), res.end());
        cout << "Case 5: nums = [] (empty)\n";
        printSubsets(res);
        cout << "Expected count: " << expectedUniqueSubsetsCount(nums) << "\n\n";
    }

    return 0;
}

/**************************************************************
 * DETAILED STEP-BY-STEP (WHY EACH STEP EXISTS)
 * --------------------------------------------
 * 1) sort(nums):
 *    - Groups equal values contiguously. Essential so that when we
 *      exclude nums[i], we can jump over the entire run of identicals.
 *
 * 2) ans.push_back(nums[i]) -> recurse(i+1) -> ans.pop_back():
 *    - INCLUDE branch: we try taking the current number.
 *    - After recursion returns, we MUST restore 'ans' via pop_back()
 *      so the EXCLUDE branch sees the clean pre-include state.
 *
 * 3) idx = i+1; while (idx < n && nums[idx] == nums[idx-1]) idx++;
 *    - EXCLUDE branch with SKIP : having decided to exclude nums[i],
 *      we now skip all its identical twins at the SAME depth to avoid
 *      generating indistinguishable subsets later.
 *      Example: [1,2,2] — exclude first 2, then if we allow starting with
 *      second 2 at this depth, we’ll recreate every subset that starts with a 2.
 *
 * 4) Recurse from idx after skipping run:
 *    - Now we move to the next different value and continue branching.
 *
 * WHY WE MUST NOT INCLUDE THE "SAME ELEMENT" AFTER EXCLUDING IT ONCE
 * -------------------------------------------------------------------
 * "Same element" here means "same value at the same recursion depth".
 * If you exclude nums[i] = 2 and then, still at this depth, include
 * nums[i+1] = 2, you create subsets that are indistinguishable from
 * those created by including nums[i] and excluding nums[i+1].
 * Since 2’s are identical, the subset contents are identical — duplicates.
 *
 * Concrete duplicate for nums = [1,2,2]:
 * - Path A : include 2 at i=1, exclude 2 at i=2 -> subset [1,2]
 * - Path B : exclude 2 at i=1, include 2 at i=2 -> subset [1,2] (duplicate)
 * The "skip run after exclude" forbids Path B at that depth.
 *
 * ALTERNATIVE PATTERNS (FYI)
 * --------------------------
 * 1) Depth-For-Loop pattern:
 *    - At each level, iterate j from i..n-1, but skip j>i if nums[j]==nums[j-1].
 *    - Also standard and accepted. Same complexity.
 *
 * 2) Counting runs:
 *    - For a run of value v with frequency f, choose k=0..f copies and recurse.
 *    - Also valid and often clean.
 *
 * Bottom line: You cannot avoid the "skip duplicates at the same depth" rule.
 *
 * EDGE CASES & KEY INSIGHTS
 * -------------------------
 * - Empty input -> one subset: [].
 * - All duplicates, e.g., [2,2,2,2] -> f=4 -> (4+1)=5 subsets: choose 0..4 copies.
 * - Negative numbers? Works. Sorting handles order; equality works the same.
 * - Large n? Enumeration is exponential by nature. On LeetCode constraints,
 *   this is comfortably accepted.
 *
 **************************************************************/
