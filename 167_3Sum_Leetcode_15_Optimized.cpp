// =======================================================================================
// 3Sum - Brute/Hash hybrid implementation (your two-loop + per-i set approach)
// =======================================================================================
// Problem brief (short, then expanded):
//
// Short: Given an integer array nums, return all unique triplets [a,b,c] such that a + b + c == 0.
//       Triplets must be unique by value (not index) and each element comes from a distinct index.
//
// Expanded:
//    - Input: vector<int> nums
//    - Output: vector<vector<int>> of unique triplets (each triplet sorted internally, overall order not required)
//    - Constraints (typical LeetCode): n up to several hundreds / thousands; values may repeat and range can be large/negative.
//    - Goal: produce all unique value-combinations of three elements that sum to 0.
//
// =======================================================================================
// The method implemented below (name):
//    "Fix-One + Two-Sum-Hash (per i)" — for each fixed i, reduce the problem to two-sum on elements after i.
//    Implementation detail: we use a nested loop (i, j) and a set<int> 's' to store previously seen numbers
//    in the current i iteration and detect the complement.
//
// Why this approach (intuition):
//    - Brute force checks every combination (O(n^3)). This method reduces to O(n^2) average by checking pairs
//      with a hash/set lookup (Two-Sum is O(n) with hashing).
//    - For each i, we look for pairs of numbers after i that sum to -nums[i].
//    - Using a set to record seen numbers inside the inner loop allows O(log n) (std::set) or O(1) average (unordered_set)
//      membership checks for the complement needed.
//
// =======================================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------------------------
// Your provided solution (kept logically the same as you gave, with n-check and comments).
// ---------------------------------------------------------------------------------------
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();

        // Using std::set<vector<int>> to store unique triplets.
        // Reason: vector<int> has lexicographic operator< defined; set provides automatic uniqueness
        // and ordered iteration without requiring custom hashing.
        set<vector<int>> uniqueTriplets;

        // Outer loop: fix element at index i
        // We iterate i from 0 to n-1 (we could stop at n-3 but leaving as n is harmless because inner loop won't run)
        for(int i = 0; i < n; i++){
            int tar = -nums[i];       // target sum for the other two numbers
            unordered_set<int> s;               // set of values we've seen so far in this i-iteration
                                      // Note: using std::set<int> -> O(log n) operations
                                      // Alternative: unordered_set<int> s; // average O(1) operations

            // For each j > i, check if there exists a value 'third' seen earlier (between i+1 and j-1)
            // that completes nums[j] to the target.
            for(int j = i + 1; j < n; j++){
                int third = tar - nums[j];

                // If third exists among previously seen numbers (note: those came from indices between i+1 and j-1)
                // then indices are distinct: i, some index-of-third, j. All > =? i+1 and distinct from i.
                if(s.find(third) != s.end()){
                    // We found three values that sum to 0: nums[i], nums[j], third.
                    vector<int> trip = {nums[i], nums[j], third};

                    // Sort triplet to canonical order (important for deduplication).
                    // Without sorting, identical multisets might appear in different orders and be considered distinct.
                    // Example: values chosen might be {2, -1, -1} or {-1, 2, -1}, sorting makes both [-1,-1,2].
                    sort(trip.begin(), trip.end());

                    // Insert into a set of triplets to avoid duplicates.
                    // set<vector<int>> provides deduplication by lexicographic comparison.
                    uniqueTriplets.insert(trip);
                }
                // Mark nums[j] as seen for subsequent j's in this i-iteration.
                s.insert(nums[j]);
            }
        }

        // Convert set to vector for return
        vector<vector<int>> ans(uniqueTriplets.begin(), uniqueTriplets.end());
        return ans;
    }
};

/*
========================================
BOOK-STYLE NOTES (detailed explanations)
========================================

1) Correctness (why this finds all unique triplets)
   - For each index i we want two other indices p and q (both > i and distinct) such that:
         nums[p] + nums[q] = -nums[i]
   - The inner loop iterates j over indices i+1..n-1. For a given j (acting as q),
     we want to know if there's any previously encountered p in i+1..j-1 with value 'third' such that:
         third + nums[j] == -nums[i]  => third == -nums[i] - nums[j] (we compute 'third' above)
   - The set 's' stores values of nums at indices we have already passed in this inner loop.
     If 'third' exists in 's', that means we previously saw a value equal to the required third element,
     so we have indices (i, some p, j) with distinct positions and sum zero.
   - Sorting the triplet and inserting into uniqueTriplets ensures we only keep unique value-based triplets,
     even if different index combinations produce the same value multiset.

2) Time complexity (precise)
   - Outer loop: O(n).
   - Inner loop: for each i runs up to (n - i - 1) ~ O(n) on average; nested leads to O(n^2) iterations.
   - Each inner iteration does:
       * s.find(third) and s.insert(nums[j]) -> O(log n) each when s is std::set<int>.
       * uniqueTriplets.insert(trip) -> O(log T) when insertion happens, where T is number of unique triplets so far.
       * sort(trip) -> sorting 3 elements is constant time O(1) (bounded small constant).
   - So total: O(n^2 * log n) with std::set<int> for 's'. If you use unordered_set<int> for 's', average becomes O(n^2).
   - The set<vector<int>> uniqueTriplets insert has additional cost but is bounded by number of unique triplets T; worst-case
     T could be O(n^2) in contrived inputs, adding additional log factors. For typical inputs it's manageable.

3) Space complexity
   - 's' temporary set: O(n) worst-case per i (but reused each i, not accumulating across i).
   - uniqueTriplets: O(T * 3) -> O(T) where T is count of unique triplets (each triplet stores 3 ints).
   - Overall extra space: O(n + T).

4) Will LeetCode accept this? Will it TLE/MLE?
   - This method is commonly accepted on LeetCode if implemented carefully.
   - With std::set<int> for 's' we have O(n^2 log n) — still usually acceptable for n up to a few thousands but slower than optimal.
   - Using unordered_set<int> for 's' reduces the inner operation to average O(1), giving average O(n^2), which is the expected complexity.
   - Using set<vector<int>> is convenient and safe for deduplication; however it adds log T factor when inserting to uniqueTriplets.
   - Most likely outcome:
       * Will not cause MLE in usual tests.
       * Might approach time limits for very large arrays but typically passes. However the official optimal solution is sort+two-pointer O(n^2)
         and avoids storing a set<vector<int>> for dedup (by skipping duplicates while scanning) — that is faster and lower overhead.

5) Why `j = i + 1`? Why scanning only future indices?
   - We must ensure indices are distinct and not reuse the same element.
   - By scanning only j > i and storing values seen among indices > i, we guarantee p and j are indices greater than i (distinct).
   - This prevents using the same index twice and avoids permutations of the same index-triplet.
   - Example: nums = [1, -1, 0]
       * i=0 (nums[i] = 1), we search pairs among indices {1,2}.
       * j starts at 1 (i+1), so we consider pairs like (p=1, j=2) or (p=2, j=1) depending on ordering, but because seen stores earlier elements,
         each combination of indices with p<j is considered exactly once.

6) Why sort each triplet before inserting into set<vector<int>>?
   - Values can occur in any order across indices. Sorting normalizes the representation.
     Example: indices (i=0,j=2,p=1) might produce {nums[0],nums[2],nums[1]} = {2,-1,-1}.
     Another index combination might produce {-1,2,-1}. Without sorting these two are distinct vectors; with sorting both become {-1,-1,2}.
   - Canonical order is necessary so set<vector<int>> can reliably check duplicates by value and not by position or insertion order.

7) Why use set<vector<int>> for uniqueTriplets instead of unordered_set?
   - vector<int> does not have a default std::hash specialization, so unordered_set<vector<int>> is not available without a custom hasher.
   - A custom hash must be robust (combine 3 integers) and handle collisions; it's doable but adds complexity you may not want.
   - std::set<vector<int>> provides correctness out of the box via lexicographic ordering; insertion is O(log T).
   - If performance is critical, you can:
       * Implement a custom hash for unordered_set<string> using a packed string key like "a#b#c" (watch collisions and formatting),
       * Or better: sort the entire input and use two-pointer method which deduplicates without global set.
   - For clarity and safety in demonstration code, set<vector<int>> is fine.

8) Why set<int> s inside the i-loop (instead of global)?
   - It's specific to the current fixed i. It should only contain numbers from indices > i that we have seen so far while scanning j.
   - If s were global, you'd mix values from multiple i's and incorrectly pair elements that appear before i.

9) Use of std::vector<std::vector<int>> as return type:
   - The function returns a list-of-lists where each inner vector is a triple of ints.
   - This structure is directly compatible with LeetCode's expected return type and easy to iterate/print.

10) Practical suggestions (optimizations & tradeoffs):
    - Replace set<int> s with unordered_set<int> s; // average O(1) membership -> faster run-time
    - Use vector<int> nums; sort(nums.begin(), nums.end()); and then two-pointer approach to avoid creating set<vector<int>> for dedup:
          For i in 0..n-3:
             if i > 0 and nums[i] == nums[i-1] -> continue (skip duplicate first element)
             left = i+1, right = n-1
             while left < right:
                sum = nums[i] + nums[left] + nums[right]
                if sum == 0 -> record [nums[i], nums[left], nums[right]]; move left&right skipping duplicates
                else adjust pointers accordingly
       This is the canonical optimal solution: O(n^2) time, O(1) extra space (excluding result).
    - If you prefer to keep unsorted input order and use the hash approach, use unordered_set<int> and then convert triplets to e.g., tuple<int,int,int> normalized before inserting into unordered_set with a custom hasher.

==========================================
Working main() with multiple test cases
==========================================
Below is a simple runner and print helper so you can test different arrays and observe result.
*/

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    // Test 1: the classic example
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    auto res1 = sol.threeSum(nums1);
    cout << "Input 1: [-1, 0, 1, 2, -1, -4]\nResult 1:\n";
    printTriplets(res1);
    cout << "Count: " << res1.size() << "\n\n";

    // Test 2: all zeros -> only one triplet [0,0,0]
    vector<int> nums2 = {0,0,0,0,0};
    auto res2 = sol.threeSum(nums2);
    cout << "Input 2: [0,0,0,0,0]\nResult 2:\n";
    printTriplets(res2);
    cout << "Count: " << res2.size() << "\n\n";

    // Test 3: negatives and positives with duplicates
    vector<int> nums3 = {3, -2, -1, 0, 1, 2, -1, -4, 2};
    auto res3 = sol.threeSum(nums3);
    cout << "Input 3: [3, -2, -1, 0, 1, 2, -1, -4, 2]\nResult 3:\n";
    printTriplets(res3);
    cout << "Count: " << res3.size() << "\n\n";

    // Test 4: small/no possible triplets
    vector<int> nums4 = {1,2,3,4};
    auto res4 = sol.threeSum(nums4);
    cout << "Input 4: [1,2,3,4]\nResult 4:\n";
    printTriplets(res4);
    cout << "Count: " << res4.size() << "\n\n";

    // Test 5: edge case: fewer than 3 elements
    vector<int> nums5 = {1, -1};
    auto res5 = sol.threeSum(nums5);
    cout << "Input 5: [1, -1]\nResult 5:\n";
    printTriplets(res5);
    cout << "Count: " << res5.size() << "\n\n";

    // Quick runtime notes printed for developer (you)
    cout << "Notes:\n";
    cout << "- This implementation retains your original choice of std::set<int> for 's' and std::set<vector<int>>\n";
    cout << "  for deduplication. Consider switching s to unordered_set<int> for speed.\n";
    cout << "- For best performance and lower memory overhead, implement sort(nums) + two-pointer approach.\n";

    return 0;
}

/*
==========================================
Extra: deep dive on data structure choices
==========================================

1) std::set<int> s (inside i-loop)
   - What it does: ordered container of unique integers; O(log n) insertion and lookup.
   - Pros: deterministic performance, simple API, no hash required.
   - Cons: log factor on each operation; slower than unordered_set average-case.
   - Recommendation: use unordered_set<int> unless you have reason to need ordering or worry about pathological hash attacks.

2) std::set<vector<int>> uniqueTriplets
   - What it does: stores unique vectors (triplets) in lexicographic order; duplicates are automatically ignored.
   - Pros: no custom hash, automatic uniqueness, easy conversion to vector<vector<int>> for return.
   - Cons: each insertion costs O(log T) comparisons (vector compare lexicographically), which can be heavier than hashing.
   - Recommendation: it's fine for clarity and safety. For maximum performance you can:
       a) use unordered_set<string> with encoded triplet strings (careful with separators),
       b) use sorted input + two-pointer to avoid the global set entirely.

3) Sorting a 3-element vector (sort(trip.begin(), trip.end()))
   - Complexity: constant small-time (3 elements).
   - Purpose: canonicalization to deduplicate by value rather than by order-of-discovery or index.
   - Explanation: Two different index triples that correspond to the same values can produce different ordering of values.
     Sorting ensures consistent representation.

==========================================
Typical pitfalls and gotchas
==========================================
- Forgetting to ensure indices are distinct (this implementation guarantees that by only scanning j > i and by using seen values from indices > i).
- Using unordered_set<vector<int>> incorrectly (vector has no built-in std::hash).
- Not sorting the triplet before deduplication -> duplicate value-sets get stored multiple times.
- Using naive brute O(n^3) when n is large — will TLE.

==========================================
Final recommendation (brutally honest)
==========================================
- Your approach is solid and commonly used in interviews for a quick O(n^2) style solution.
- Replace the per-iteration std::set<int> with std::unordered_set<int> for speed.
- For the absolute best combination of runtime and memory, sort the original array and implement the two-pointer O(n^2) solution which avoids storing a set<vector<int>> altogether and performs fewer allocations/copies.
- If you want, I can now convert this exact file into an optimized two-pointer version with the same exhaustive comments and test cases. Want that next?
*/
