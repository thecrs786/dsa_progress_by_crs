// =======================================================================================
// 3Sum — Detailed, copy-paste C++ file with full "book-style" comments
// =======================================================================================
// Problem (brief):
//    Given an integer array nums, return all unique triplets [a, b, c] such that
//    a + b + c == 0. Each triplet must consist of elements from distinct indices.
//    The output must not contain duplicate triplets (triplets are unique by values).
//
// Method implemented:
//    Sort the array, then for each i use the two-pointer pattern on the subarray (i+1..n-1).
//    This is the canonical O(n^2) algorithm for 3Sum.
//
// This file contains:
//  - The two-pointer implementation (your approach) with small, safe improvements.
//  - Exhaustive inline comments: complexity, why sort, why j=i+1/k=n-1, duplicate skipping,
//    vector<vector<int>> explanation, overflow note, and practical tips.
//  - Working main() with several tests and printing utilities to inspect output.
//
// =======================================================================================
#include <bits/stdc++.h>
using namespace std;

/*
  Quick note (honest):
  - This two-pointer approach AFTER sorting is the standard accepted solution on LeetCode.
  - It's optimal in time (O(n^2)) and uses O(1) extra space (excluding output).
  - I added minimal safety (long long sum) to avoid overflow on extreme inputs.
*/

// ---------------------------
// Solution class (two-pointer)
// ---------------------------
class Solution {
public:
    // -----------------------
    // threeSum: main function
    // -----------------------
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();

        // Result container: each element is a triplet vector<int> of size 3.
        // Why vector<vector<int>>:
        //  - LeetCode expects this return type.
        //  - It stores triplets compactly and is easy to print/compare.
        vector<vector<int>> ans;

        // Quick guard: fewer than 3 elements -> no triplets
        if (n < 3) return ans;

        // Sort the array.
        // WHY sort?
        //  - Two-pointer method relies on sorted order so we can deterministically move left/right:
        //      if sum < target -> move left forward to increase sum
        //      if sum > target -> move right backward to decrease sum
        //  - Sorting groups duplicates together so we can skip them efficiently and avoid using
        //    extra data structures for deduplication (no set<vector<int>> required).
        sort(nums.begin(), nums.end());

        // Outer loop: fix the first element of the triplet at index i.
        // We only need to run i up to n-3 inclusive (i < n-2).
        for (int i = 0; i < n - 2; ++i) {
            // Skip duplicate 'first' numbers to avoid duplicate triplets.
            // Because the array is sorted, duplicates are adjacent.
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // Two pointers on the subarray [i+1, n-1]
            int j = i + 1;
            int k = n - 1;

            // While left pointer is before right pointer
            while (j < k) {
                // Use long long to avoid overflow when summing three ints.
                // (int ranges up to ~1e9 on LeetCode; sum of three ints can overflow 32-bit)
                long long sum = (long long)nums[i] + nums[j] + nums[k];

                if (sum < 0) {
                    // Sum too small: need larger value -> move left pointer right
                    ++j;
                } else if (sum > 0) {
                    // Sum too large: need smaller value -> move right pointer left
                    --k;
                } else {
                    // Found a valid triplet
                    ans.push_back({nums[i], nums[j], nums[k]});

                    // Move both pointers to continue searching for new pairs.
                    ++j;
                    --k;

                    // Skip duplicates for the second element:
                    // After incrementing j, skip over values equal to the previous nums[j-1].
                    while (j < k && nums[j] == nums[j - 1]) ++j;

                    // Skip duplicates for the third element:
                    // After decrementing k, skip over values equal to the previous nums[k+1].
                   // while (j < k && nums[k] == nums[k + 1]) --k;  no need, because i and j are not repeated. so no way of duplicate triplet
                }
            }
        }

        return ans;
    }
};

/*
=========================================================================================
DETAILED EXPLANATION — step-by-step and why we did each thing
=========================================================================================
1) Sorting (sort(nums.begin(), nums.end())):
   - Required to apply two-pointer strategy: when array is sorted,
     moving the left pointer right increases the sum, moving right pointer left decreases the sum.
   - Sorting also groups duplicates so we can skip them. This eliminates the need for
     global dedup containers (like set<vector<int>>) and reduces memory and overhead.
   - Cost: O(n log n) — dominated by O(n^2) two-pointer scanning for large n.

2) Outer loop (for i):
   - We fix one element nums[i] and then search for two other numbers that sum to -nums[i].
   - We stop at i < n-2 because we need at least two numbers to the right.
   - Duplicate skip for i: if nums[i] == nums[i-1] we continue; this prevents repeating
     the same triplet first value and is correct because array is sorted.

3) Two-pointer window [j, k] on the remainder:
   - Initialize j = i+1, k = n-1 to consider the entire tail once.
   - For current i, the target two-sum is (-nums[i]).
   - While j < k:
       sum = nums[i] + nums[j] + nums[k]
       If sum < 0 -> j++ (we need a bigger value)
       If sum > 0 -> k-- (we need smaller value)
       If sum == 0 -> record triplet, move both pointers, skip duplicates

4) Duplicate skipping after finding a triplet:
   - After pushing a found triplet, we increment j and decrement k.
   - We then skip over equal values on both sides to ensure we only record unique triplet values.
   - Correctness: Because we incremented/decremented pointers, we compare to the *previous* value
     (nums[j-1] for left, nums[k+1] for right) which is the value we just used in the recorded triplet.
   - Example: nums = [-1, -1, 0, 1, 1]; with i pointing to first -1, we find (-1,0,1).
     Skipping duplicates ensures we don't record (-1,0,1) again when encountering the second 1.

5) Why no std::set<vector<int>> / unordered_set needed here:
   - Sorting + careful duplicate skipping ensures each value-based triplet is generated exactly once.
   - Using a set would work but costs extra memory & log-factor insertions.
   - The two-pointer approach is both simpler and faster in practice.

6) Use of long long for sum:
   - Avoid overflow: if nums elements are near INT_MAX or INT_MIN, sum of three ints may overflow a 32-bit int.
   - Using long long cast for the sum makes the function robust across value ranges.

7) Complexity summary:
   - Time: O(n log n) (sorting) + O(n^2) (two-pointer) => **O(n^2)** dominates.
   - Space: O(1) extra (not counting the output vector). Output may be O(n^2) in pathological cases.

8) Will LeetCode accept this? TLE/MLE risk?
   - This is the canonical solution — yes, it's accepted.
   - TLE: No (O(n^2) is required/expected).
   - MLE: No (we don't maintain large auxiliary structures); memory is dominated by output size.

=========================================================================================
IMPORTANT DETAILS & KEY SIGHTS (TL;DR bullet list)
=========================================================================================
- Sorting is mandatory for two-pointer correctness (and for duplicate-skip strategy).
- Use i < n - 2 for the outer loop — avoids useless iterations.
- Duplicate skip at i prevents repeating triplets that start with the same value.
- After finding a triplet, always move both pointers and skip duplicates on both sides.
- Cast to long long when summing to be safe with big integers.
- Two-pointer + sorted input removes the need for a global set for deduplication.
- Worst-case number of unique triplets T can be O(n^2) — output memory could be large but that's inherent to the problem.
- If you need deterministic order of triplets, you can optionally sort `ans` before returning, but LeetCode doesn't require any particular order.

=========================================================================================
WORKING EXAMPLE (dry-run explanation)
=========================================================================================
Example: nums = [-1, 0, 1, 2, -1, -4]
1) Sort -> nums = [-4, -1, -1, 0, 1, 2]
2) i = 0 -> nums[i] = -4 -> need two-sum 4 -> j=1 (-1), k=5 (2)
   - sum = -4 + (-1) + 2 = -3 < 0 -> j++ (increase sum)
   - move j through until j >= k or found nothing -> no triplet for i=0
3) i = 1 -> nums[i] = -1 -> need two-sum 1 -> j=2 (-1), k=5 (2)
   - sum = -1 + (-1) + 2 = 0 -> record [-1,-1,2]
   - move j->3, k->4; skip duplicates appropriately
   - then find [-1,0,1] later in same i iteration -> record
4) i moves on; duplicate skip prohibits starting on the second -1 again (i=2) because it's equal to nums[1]
Result: [[-1,-1,2], [-1,0,1]]

=========================================================================================
POTENTIAL PITFALLS / GOTCHAS
=========================================================================================
- Forgetting to sort -> algorithm incorrect.
- Not skipping duplicates -> duplicate triplets in output.
- Using int for sum in languages/environments where integer overflow is possible -> wrong answers on extreme inputs.
- Doing while(j<k && nums[k]==nums[k+1]) k-- BEFORE decrementing k after finding a triplet (wrong comparison index) -> bug.
  Correct pattern is: record, then ++j, --k, then compare with nums[j-1] and nums[k+1] respectively.

=========================================================================================
END OF NOTES
=========================================================================================
*/

// ---------------------
// Small printing helper
// ---------------------
static void printTriplets(const vector<vector<int>>& triplets) {
    cout << "[\n";
    for (size_t i = 0; i < triplets.size(); ++i) {
        const auto &t = triplets[i];
        cout << "  [";
        for (size_t j = 0; j < t.size(); ++j) {
            cout << t[j];
            if (j + 1 < t.size()) cout << ", ";
        }
        cout << "]";
        if (i + 1 < triplets.size()) cout << ",";
        cout << "\n";
    }
    cout << "]\n";
}

// ---------------------
// main() — runnable tests
// ---------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> a1 = {-1, 0, 1, 2, -1, -4};
    auto r1 = sol.threeSum(a1);
    cout << "Input 1: [-1, 0, 1, 2, -1, -4]\nResult 1:\n"; printTriplets(r1); cout << "Count: " << r1.size() << "\n\n";

    vector<int> a2 = {0, 0, 0, 0};
    auto r2 = sol.threeSum(a2);
    cout << "Input 2: [0, 0, 0, 0]\nResult 2:\n"; printTriplets(r2); cout << "Count: " << r2.size() << "\n\n";

    vector<int> a3 = {3, -2, -1, 0, 1, 2, -1, -4, 2};
    auto r3 = sol.threeSum(a3);
    cout << "Input 3: [3, -2, -1, 0, 1, 2, -1, -4, 2]\nResult 3:\n"; printTriplets(r3); cout << "Count: " << r3.size() << "\n\n";

    vector<int> a4 = {1, 2, 3, 4};
    auto r4 = sol.threeSum(a4);
    cout << "Input 4: [1, 2, 3, 4]\nResult 4:\n"; printTriplets(r4); cout << "Count: " << r4.size() << "\n\n";

    // Tricky/large-range test to show overflow safety:
    vector<int> a5 = {1000000000, -1000000000, 0};
    auto r5 = sol.threeSum(a5);
    cout << "Input 5: [1000000000, -1000000000, 0]\nResult 5:\n"; printTriplets(r5); cout << "Count: " << r5.size() << "\n\n";

    cout << "Notes:\n - Algorithm: sort + two-pointer -> O(n^2) time, O(1) extra space.\n";
    cout << " - This is the standard accepted solution on LeetCode; no TLE/MLE for reasonable constraints.\n";

    return 0;
}
