// =======================================================================================
// Problem (brief) : 3Sum (LeetCode style)
// ---------------------------------------------------------------------------------------
// Given an integer array nums, return all the unique triplets [nums[i], nums[j], nums[k]]
// such that i, j, and k are distinct indices and nums[i] + nums[j] + nums[k] == 0.
//
// This file contains:
//  - The brute-force O(n^3) implementation you provided (unchanged in logic).
//  - Full "book-style" comments: problem summary, method name, time & space complexity,
//    why certain index choices were made (j = i+1, k = j+1), why we sort triplets,
//    why we used std::set<vector<int>> instead of unordered_set, step-by-step logic,
//    possible LeetCode behavior (TLE/MLE), and suggested better approach.
//  - A working `main()` with a test example and printing utility to analyze output.
// =======================================================================================
#include<iostream>
#include<algorithm>
#include<set>
#include<stdio.h>
#include<vector>
using namespace std;

/*
=========================================================================================
Top-level notes (as requested) - BRUTE FORCE approach
=========================================================================================
Problem summary:
    Find all unique triplets in the array which gives the sum of zero.

Method / Name:
    Brute Force Triple Loop with deduplication using std::set<vector<int>>.
    (You provided this approach: check all combinations (i,j,k), collect those with sum 0,
    canonicalize triplet by sorting it, and use a set to ensure uniqueness.)

Time Complexity:
    - The triple nested loops iterate roughly O(n^3) combinations in the worst case.
    - Each time we find a valid triplet, we sort the small 3-element vector (O(3 log 3) = O(1) constant)
      then insert into std::set which is O(log M) where M is number of distinct triplets found so far.
    - Overall worst-case time: O(n^3 * log M). For complexity discussions it's safely considered O(n^3).
    - For n ~ 3000 (LeetCode constraints), O(n^3) is infeasible (billions of iterations).

Space Complexity:
    - Set to store unique triplets: O(T) where T is number of unique triplets (each triplet size 3).
    - Answer vector stores the triplets as well: O(T).
    - Extra constant space for loop variables and temporary trip vector.
    - Worst-case T can be large (O(n^3) combinations degenerate to many unique triplets in contrived inputs),
      but practically T is often much smaller. Still memory grows with number of unique triplets.

Will LeetCode accept this?
    - In most realistic LeetCode test cases this will TLE (Time Limit Exceeded). LeetCode expects
      an O(n^2) solution (sorting + two-pointer) for typical constraints.
    - This brute-force is correct (returns correct triplets) but not optimal.
    - Not likely to cause MLE before TLE — typically it times out before memory becomes critical,
      but pathological inputs with many valid unique triplets can cause high memory usage.

Key reasons this implementation uses the parts it does:
    - j = i + 1 and k = j + 1:
        -> Ensures i, j, k are distinct and we only consider combinations in one order (i < j < k).
        -> This avoids permuted versions of the same indices (e.g., (i,j,k) vs (j,i,k)).
        -> Example: nums = [1, -1, 0]; i=0 (1), j=1 (-1), k=2 (0) gives sum 0. If we allowed j < i,
           we'd also check j=0,i=1 which is the same indices but different order — duplicates.
        -> Using i<j<k reduces combination count from permutations to combinations (n choose 3).
    - Sorting each found triplet:
        -> Even with i<j<k, values are not ordered by magnitude. Example:
                nums = [2, -1, -1] with indices (0,1,2). Values are [2,-1,-1].
           The triplet as picked is [2,-1,-1]. Another index order might pick the same numbers in a
           different order, so sorting the vector of values produces canonical form [-1,-1,2].
        -> The set requires identical vectors to detect duplicates. Sorting ensures we always insert
           a canonical representation.
    - Why std::set<vector<int>> instead of unordered_set<vector<int>>:
        -> std::set provides ordering and uniqueness out of the box for vector<int> (it uses
           lexicographical comparison). No custom hash needed.
        -> unordered_set<vector<int>> is not available by default because vector<int> has no
           std::hash specialization. You *could* write a custom hash, but that introduces
           complexity (need good hash combining, risk of collisions, and careful handling).
        -> Using std::set keeps code simple and correct; complexity is O(log M) per insertion,
           which is acceptable for a brute-force demonstration but contributes to slower runtime.
        -> If optimizing, one could convert triplets to strings or packs (e.g., pair of longs)
           or implement a custom hash and use unordered_set to reduce average insertion time to O(1).
=========================================================================================
*/

class Solution {
public:
    // ---------------------------
    // Brute-force 3Sum implementation
    // ---------------------------
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();

        // ans: the list of unique triplets returned
        vector<vector<int>> ans;

        // s: ordered set to avoid duplicate triplets. Each triplet is stored in sorted order.
        // Using std::set<vector<int>> gives us uniqueness guarantee without custom hashing.
        set<vector<int>> s;

        // Edge case: if less than 3 numbers, no triplets possible.
        if (n < 3) return ans;

        // Triple nested loop:
        // - i runs from 0 to n-3
        // - j runs from i+1 to n-2  (ensuring j > i)
        // - k runs from j+1 to n-1  (ensuring k > j)
        //
        // Using j = i+1 and k = j+1 ensures indices i, j, k are distinct and avoids permuted duplicates.
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    // Check if these three elements sum to zero
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        // Construct the triplet of values
                        vector<int> trip = {nums[i], nums[j], nums[k]};

                        // Sort the triplet to canonicalize it (so equal multisets become equal vectors)
                        // Example: trip = {2, -1, -1} -> sorted: {-1, -1, 2}
                        sort(trip.begin(), trip.end());

                        // Insert into set if not present (set ensures uniqueness)
                        // We also push_back to ans at the same time to preserve results.
                        if (s.find(trip) == s.end()) {
                            s.insert(trip);
                            ans.push_back(trip);
                        }
                    }
                }
            }
        }

        // Return list of unique triplets
        return ans;
    }
};

/*
=========================================================================================
Detailed explanation of function flow (step-by-step, lengthy)
=========================================================================================
1) Input read and quick guard:
   - We obtain the number of elements n.
   - If n < 3, there is no valid triplet; return empty answer immediately.

2) Data structures:
   - ans: vector<vector<int>> that will hold final unique triplets for return.
   - s: set<vector<int>> used to keep track of triplets we've already added. The reason:
         -> Without a dedup structure, the same combination of values might be discovered
            multiple times via different index combinations (if duplicates exist in the array).
         -> Example: nums = [-1, -1, 2]. Indices (0,1,2) produce [-1,-1,2] once only here because we
            impose i<j<k. But if there are more duplicates or different ordering of values across indices,
            we could discover same values multiple times. Sorting the triplet and storing it in a set
            ensures only one copy of each unique value-multiset ends up in the final answer.
   - Why not unordered_set<vector<int>>:
         -> vector<int> doesn't have a std::hash defined; you'd need to write your own hasher.
         -> Writing a correct, fast hasher must consider collisions and be tested. Using std::set
            keeps correctness simple and obvious. For brute-force clarity, std::set is fine.

3) Loop decisions:
   - We loop i from 0 to n-1, j from i+1 to n-1, k from j+1 to n-1. This enforces i < j < k.
   - Rationale: we only want combinations of three different indices. Using ordered indices
     ensures each triple of indices is considered only once.
   - Example for j = i+1, k = j+1:
       nums = [a, b, c, d]
       possible (i,j,k) with i<j<k are:
         (0,1,2), (0,1,3), (0,2,3), (1,2,3)
       Without ordering we'd also have permutations like (1,0,2) which are the same elements at the same indices,
       but we'd waste time and risk duplicates. i<j<k reduces the search space to combinations only.

4) Check sum:
   - For each distinct triplet of indices, compute nums[i] + nums[j] + nums[k] and check equality with 0.

5) Canonicalization:
   - When the sum is 0, create a vector<int> of the three values and immediately sort it.
   - Sorting makes the vector canonical: the set can now reliably test equality without considering order.

6) Deduplication and result building:
   - If the sorted triplet is not yet in the set, insert it and push it to ans.

7) Return ans:
   - All unique triplets found will be in ans. The set was used only for deduplication and does not
     preserve insertion order of vectors (but we used ans to store in the order we find them).

=========================================================================================
Why this approach is correct but inefficient:
=========================================================================================
- Correctness:
    -> We examine every unique combination of indices (i<j<k). For each combination we test the condition.
       No valid triplet is missed.
- Inefficiency:
    -> O(n^3) growth in comparisons. For n ~ 500-3000 (typical LeetCode sizes), this becomes impractical.
    -> The set insertion/log factor adds extra overhead.
- Real-world LeetCode behavior:
    -> Most LeetCode testcases will cause TLE for n larger than ~200-300 depending on time limits.
    -> This approach is fine for educational demonstration and tiny inputs.

=========================================================================================
Better approach (summary) - what to do in practice:
=========================================================================================
1) Sort the input array nums (O(n log n)).
2) For each index i from 0 to n-3:
   - Use two-pointer technique on subarray nums[i+1...n-1]: left = i+1, right = n-1.
   - Move left/right based on current sum to find combinations that sum to -nums[i].
   - Skip duplicates by moving left/right while same values repeat.
3) Time complexity: O(n^2), Space: O(1) extra (excluding result storage).
4) This is the intended and accepted solution on LeetCode.

=========================================================================================
Important details & key sights (bullet points)
=========================================================================================
- ALWAYS handle n < 3 case early.
- Sorting each trip (3 elements) is constant time but necessary to canonicalize values.
- Using i<j<k reduces repeated index permutations.
- std::set provides correctness with no hashing headaches but has O(log M) operations.
- unordered_set could be faster in practice if you implement a robust hash for triplet.
- When doing optimal solution, sort the full array and use two pointers for O(n^2).
- Edge cases:
    -> All zeros: nums = [0,0,0,0,...] should produce one triplet [0,0,0].
    -> Multiple duplicates scattered: deduplication must be robust.
    -> Large arrays: brute-force will fail due to time limits.
=========================================================================================
End of textual notes.
=========================================================================================
*/

// -----------------------------
// Helper printing functions for example run
// -----------------------------
void printTriplets(const vector<vector<int>>& triplets) {
    cout << "[\n";
    for (const auto &t : triplets) {
        cout << "  [";
        for (size_t i = 0; i < t.size(); ++i) {
            cout << t[i];
            if (i + 1 < t.size()) cout << ", ";
        }
        cout << "]";
        if (&t != &triplets.back()) cout << ",";
        cout << "\n";
    }
    cout << "]\n";
}

// -----------------------------
// Working example in main()
// -----------------------------
int main() {
    

    // Example input: the classic LeetCode sample
    // nums = [-1, 0, 1, 2, -1, -4]
    // Expected unique triplets (order may differ): [-1, -1, 2], [-1, 0, 1]
    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    Solution sol;
    vector<vector<int>> result = sol.threeSum(nums);

    // Print the resulting unique triplets
    cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]\n\n";

    cout << "Unique triplets that sum to 0 (brute-force output):\n";
    printTriplets(result);

    // Quick analysis print (handy while running)
    cout << "\nAnalysis:\n";
    cout << "- Brute-force time complexity: O(n^3) (practically will TLE on large n).\n";
    cout << "- Number of triplets found: " << result.size() << "\n";
    cout << "- For production / LeetCode: use sorting + two-pointer for O(n^2).\n";

    return 0;
}

/*
=========================================================================================
Sample run expected output (approx):
-----------------------------------------------------------------------------------------
Input: [-1, 0, 1, 2, -1, -4]

Unique triplets that sum to 0 (brute-force output):
[
  [-1, -1, 2],
  [-1, 0, 1]
]

Analysis:
- Brute-force time complexity: O(n^3) (practically will TLE on large n).
- Number of triplets found: 2
- For production / LeetCode: use sorting + two-pointer for O(n^2).
=========================================================================================
Final words (brutally honest):
- Your brute-force is correct conceptually and is an excellent learning step.
- But it's not acceptable performance-wise for LeetCode's hidden larger tests — it'll TLE.
- Next step: implement the sorted + two-pointer O(n^2) solution (I can write that for you
  in the same commented "book-style" format if you want).
=========================================================================================
*/
