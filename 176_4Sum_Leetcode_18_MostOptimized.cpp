#include <bits/stdc++.h>
using namespace std;

/*
Question (brief):
- LeetCode 18: 4Sum
- Given nums[] and target, return all unique quadruplets [a,b,c,d] with a<b<c<d and sum == target.

EXAMPLE (walk-through — small & concrete)
nums = {1, 0, -1, 0, -2, 2}, target = 0
Sorted -> {-2, -1, 0, 0, 1, 2}

- i=0 (nums[i] = -2)
  - j=1 (nums[j] = -1) -> p=2 (0), q=5 (2)
    sum = -2 + -1 + 0 + 2 = -1  -> p++
    p=3 (0), q=5 (2) -> sum = -1 -> p++
    p=4 (1), q=5 (2) -> p>=q loop ends
  - j moves to j=2 (nums[j]=0)
    p=3 (0), q=5 (2) -> sum = 0 -> record [-2,0,0,2], move p->4, q->4 -> loop ends
  - etc...
- The algorithm finds unique quadruplets: [-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]

Solution (brief):
- Sort + fix two numbers (i, j) + two-pointer on the remaining (p, q).
- This is the standard O(n^3) approach.
TIME COMPLEXITY
- Sorting: O(n log n).
- Main work: for each i (O(n)) and each j (O(n)), we run a p/q two-pointer scan O(n) -> O(n^3).
- Total worst-case: O(n^3) (sorting is dominated by this).
- Practical: constants and duplicates/pruning often reduce real runtime.

SPACE COMPLEXITY
- Extra auxiliary: O(1) (a few indices, temporaries).
- Output storage: O(k) where k is number of returned quadruplets.
- Sorting uses O(log n) stack for std::sort (implementation dependent).
*/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) { // function signature: input vector and target
        vector<vector<int>> ans; // stores resulting quadruplets
        int n = nums.size(); // cache size to avoid repeated size() calls
        sort(nums.begin(), nums.end()); // sort for two-pointer technique & easy duplicate detection

        for (int i = 0; i < n - 3; i++) { // fix first element; need at least 3 elements after i
            if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicate first elements
            for (int j = i + 1; j < n - 2; j++) { // fix second element; need at least 2 elements after j
                // or remove j++ from above and at the end of this j loop add
                // j++;
                // while(nums[j]==nums[j-1]) j++;
                // this because we want this j loop to run once first then skip dplicae j's/
                if (j > i + 1 && nums[j] == nums[j - 1]) continue; // skip duplicate second elements
                int p = j + 1; // left pointer for the pair search
                int q = n - 1; // right pointer for the pair search

                while (p < q) { // two-pointer loop runs in linear time for fixed i,j
                    long long sum = (long long)nums[i] + (long long)nums[j] + (long long)nums[p] + (long long)nums[q]; // use long long to avoid overflow
                    if (sum < target) p++; // sum too small -> increase by moving left pointer right
                    else if (sum > target) q--; // sum too big -> decrease by moving right pointer left
                    else {
                        ans.push_back({nums[i], nums[j], nums[p], nums[q]}); // record quadruplet when sum matches target
                        p++; q--; // move both pointers to continue searching for other pairs
                        while (p < q && nums[p] == nums[p - 1]) p++; // skip duplicate third elements (avoid duplicate quadruplets)
                        // note: we do not explicitly skip q duplicates here; that's fine (see post-class notes)
                    }
                }
            }
        }
        return ans; // return all unique quadruplets found
    }
};
/* ------------------ end class ------------------ */

/*
POST-CLASS: concise explanations addressing  points 

1) About using `if (j>i+1 && nums[j]==nums[j-1]) continue;` vs manual j++ at end:
   - The `continue` pattern in the for-loop is cleaner and idiomatic: it keeps increment logic in the loop header.
   - It ensures the first j (j==i+1) is processed even if equal to nums[i].
   - Equivalent to your original manual increment + while-skip, but easier to read and less error-prone.

2) Why we skip duplicates for i, j, and p (but not strictly for q):
   - i-skip: prevents repeating entire blocks that start with the same first element.
   - j-skip: prevents repeating second-level choices under a fixed i.
   - p-skip: after finding a match, we increment p then skip equal p values so we don't re-add the same third number.
   - q duplicates are implicitly handled by pointer movement: because we do both p++ and q-- on match and we skip duplicate p, duplicate q values won't produce repeated unique quadruplets. Skipping q explicitly (while(p<q && nums[q]==nums[q+1]) q--;) is symmetric and fine as a micro-optimization, but not required for correctness.

3) Why cast to `long long`:
   - Summing four ints can overflow 32-bit; long long prevents overflow and incorrect comparisons against target.

4) Complexity & acceptance:
   - Time: O(n^3) worst-case (i loop * j loop * p/q sweep). For LeetCode constraints (n ~ 200) this is acceptable.
   - Space: O(1) extra + O(k) for output where k is number of quadruplets.
   - Will be accepted on LeetCode; no TLE or MLE expected under usual constraints.

5) Alternative duplicate-skip for j (the while-version you mentioned):
   - Works: increment j and then while (j < n-2 && nums[j] == nums[j-1]) j++;
   - Drawback: mixes loop increment logic and duplicate-skip across places — easier to make off-by-one mistakes.
   - Recommended: the `if (j>i+1 && ...) continue;` approach you proposed (already in your code).

6) Minor micro-optimizations you can add (optional):
   - Early pruning inside loops:
     * If smallest possible sum with current i (nums[i] + next three) > target -> break outer loop.
     * If largest possible sum with current i (nums[i] + three largest) < target -> continue outer loop.
     * Similar pruning inside j-loop.
   - Symmetric q duplicate-skip after q-- (micro-opt).

7) Why not use set for deduplication:
   - Using a set<vector<int>> would be simpler but slower (log factor on insert) and uses more memory.
   - Preventing duplicates by skipping during generation is faster and preferred.

*/

int main() {
    Solution sol;
    // Example A
    vector<int> a = {1, 0, -1, 0, -2, 2};
    int ta = 0;
    auto ra = sol.fourSum(a, ta);
    cout << "Example A results:\n";
    for (auto &v : ra) {
        cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "]\n";
    }
    cout << "----\n";

    // Example B (duplicates)
    vector<int> b = {0, 0, 0, 0, 0};
    int tb = 0;
    auto rb = sol.fourSum(b, tb);
    cout << "Example B results:\n";
    for (auto &v : rb) {
        cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "]\n";
    }
    cout << "----\n";

    return 0;
}
