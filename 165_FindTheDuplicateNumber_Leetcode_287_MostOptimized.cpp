// ======================================================================================
// Problem: Find the Duplicate Number (LeetCode #287) - Floyd's Tortoise and Hare Method
// ======================================================================================
//
// Brief:
// Given an array `nums` of length n+1 where each element is in the range [1, n], there is
// exactly one value that appears more than once. Return that duplicate value.
//
// Constraints that matter for this solution:
//  - nums.size() == n + 1
//  - All nums[i] are integers in [1, n] (i.e., never 0, never > n)
//  - There is at least one duplicate (maybe repeated multiple times)
//
// Method name: Floyd's Cycle Detection (Tortoise & Hare / slow & fast pointers)
//
// Time Complexity: O(n)
// Space Complexity: O(1)
// Optimal: Yes — this is the standard optimal approach (O(n) time, O(1) extra space).
// Accepted on LeetCode: Yes
// --------------------------------------------------------------------------------------

#include <bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    // Book-style documented function
    int findDuplicate(vector<int>& nums) {
        // ---------------------------
        // Phase 1: Detect intersection
        // ---------------------------
        // We treat the array as a function f(i) = nums[i].
        // Starting point = index 0, but we use value nums[0] as first node:
        //   slow = f(start)  (one step)
        //   fast = f(f(start)) (two steps)
        //
        // We use do-while because we want to move at least once before comparing.
        // If we used while(slow != fast) with both initialized equal, we'd exit immediately.
        int slow = nums[0]; // can also use 0 or any index k instead of nums[0]
        int fast = nums[0]; // can also use 0 or any index k instead of nums[0]

        // Move slow by 1 and fast by 2 until they meet inside the cycle.
        do {
            slow = nums[slow];           // one step
            fast = nums[nums[fast]];     // two steps (apply f twice)
        } while (slow != fast);

        // --------------------------------------------------
        // Phase 2: Find the entry point of the cycle (duplicate)
        // --------------------------------------------------
        // Reset slow to start (nums[0]) and move both pointers one step at a time.
        // The point they meet is the start of the cycle -> the duplicate value.
        slow = nums[0]; // can also use 0 or any index k instead of nums[0]
        while (slow != fast) {
            slow = nums[slow];     // +1
            fast = nums[fast];     // +1
        }
        return slow; // or fast, same value
    }
};

// function to print vector

void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution sol;

    vector<vector<int>> tests = {
        {1, 3, 4, 2, 2},                // duplicate = 2
        {3, 1, 3, 4, 2},                // duplicate = 3
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 6}  // duplicate = 6
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        vector<int> nums = tests[i];
        cout << "Test " << i+1 << ": ";
        printVec(nums);
        cout << "\n -> Duplicate: " << sol.findDuplicate(nums) << "\n\n";
    }

    return 0;
}

// ======================================================================================
// Deep Explanation, Proofs, and Answers to your specific questions
// ======================================================================================
//
// 1) Why nums[0] != 0?
// ---------------------
// The problem guarantees nums[i] ∈ [1, n], so no element can be 0. This is crucial because
// we use values as indices: we always do nums[x] for some x. If a value were 0 we'd jump to
// index 0 and might break the intended "linked-structure". Because values are 1..n, every
// nums[i] points to a valid index in the range [1..n], and we never attempt to read nums[n+1].
//
// If input violates this constraint (contains 0 or > n), the algorithm is not applicable.
// But for the problem as stated, nums[0] != 0 is guaranteed.
//
//
// 2) Why model the array as a linked structure?
// ----------------------------------------------
// Consider f(i) = nums[i]. Starting at i0 = 0, following indices by applying f gives:
//   i0 -> f(i0) -> f(f(i0)) -> ...
// The presence of a duplicate value means two indices map to the same next index, which
// creates a cycle in this functional graph. Detecting that cycle gives the duplicate.
//
//
// 3) Why do we move slow by 1 and fast by 2? (slow = nums[slow]; fast = nums[nums[fast]];)
// -----------------------------------------------------------------------------------------
// This is the classic tortoise-and-hare approach:
// - slow moves one step per iteration: slow = f(slow)
// - fast moves two steps per iteration: fast = f(f(fast))
//
// Intuition: If there is a cycle, a faster walker will eventually catch up with the slower
// walker inside the cycle. Algebraically, inside a cycle of length λ, consider their
// positions modulo λ — because fast advances 2 each step and slow advances 1, the gap
// between them reduces by 1 each iteration modulo λ; eventually gap ≡ 0 (mod λ).
//
// Explanation of `nums[nums[fast]]` being "two steps":
// - Evaluate inner: tmp = nums[fast]  // one step from `fast` to tmp
// - Then nums[tmp]  // second step from tmp to next
// So `fast = nums[nums[fast]]` performs two applications of f in one line, i.e., two steps.
//
//
// 4) Will slow++ and fast+=2 always meet?
// ----------------------------------------
// Yes — if a cycle exists. Proof sketch:
// - Let μ be the index of the first node in the cycle (distance from start).
// - Let λ be the cycle length.
// - After μ steps from the start, you enter the cycle.
// - Once both pointers are inside the cycle, relative positions move with speed 1
//   (because 2 - 1 = 1 per iteration), so the distance between them decreases modulo λ.
//   Therefore they will meet within at most λ iterations once both are inside.
//
// The algorithm's do-while ensures we actually move into the cycle before checking equality.
// It ensures we don't compare the unadvanced initial pointers (which would incorrectly
// indicate equality because both started as nums[0]).
//
//
// 5) Why use do-while (move first, then check) instead of while?
// --------------------------------------------------------------
// If we used while(slow != fast) with slow and fast initialized to nums[0], they would be
// equal immediately before any movement (both equal nums[0]) and loop body would never run.
// We NEED to advance at least once so that the algorithm explores the structure. The
// do-while ensures pointers move first, then we check equality, which is the correct flow.
//
//
// 6) After meeting, why reset slow to nums[0] and move both by 1? Why will they meet at cycle entry?
// -------------------------------------------------------------------------------------------------
// Standard formal proof (sketch):
// - Let μ = distance from start to cycle entry
// - Let λ = cycle length
// - When slow and fast meet first time, suppose slow has traveled t steps.
//   Then fast traveled 2t steps. Difference = t ≡ 0 (mod λ) after subtracting path to cycle.
//   More precisely, t = μ + k where k ≡ (some offset within cycle).
// - One can show that t - μ is a multiple of λ, hence t ≡ μ (mod λ).
// - If you now set one pointer at start (0) and the other at meeting point and move both
//   at speed 1, after μ steps both will be at the cycle entry. This follows from the
//   congruence relation and simple modular arithmetic.
//
// Intuitively: meeting point is at some position in cycle; distance from meeting point to
// cycle entry equals the distance from start to cycle entry. So moving both pointers
// synchronously by +1 will cause them to collide exactly at cycle start.
//
//
// 7) What if nums[i] == i? Is that a problem (self-loop)? Will algorithm get stuck?
// ---------------------------------------------------------------------------------
// If some index i satisfies nums[i] == i (i.e., a self-loop), that's a cycle of length 1.
// The algorithm handles cycles of any length ≥ 1. If the duplicate value creates a
// self-loop at some index, the slow and fast pointers will enter and meet at that self-loop
// (fast catches slow quickly). So a self-loop doesn't break the method.
//
// Note: Because values are in [1, n] and indices are 0..n, nums[i] == i is possible only if
// i ∈ [1..n] and nums[i] has that same value. It's still valid and handled correctly.
//
//
// 8) Why is this method optimal?
// -------------------------------
// - Time O(n): each pointer advances at most O(n) steps before termination.
// - Space O(1): only a few ints used.
// - No modification of the input required.
//
//
// 9) Small dry-run example (trace):
// ---------------------------------
// Example: nums = [3,1,3,4,2]  (n+1 = 5 elements, values in [1..4], duplicate = 3)
//
// Index:   0 1 2 3 4
// Value:   3 1 3 4 2
//
// Start:
// slow = nums[0] = 3
// fast = nums[0] = 3
//
// do-while first iteration:
// slow = nums[3] = 4
// fast = nums[nums[3]] = nums[4] = 2
// slow != fast -> continue
//
// next iteration:
// slow = nums[4] = 2
// fast = nums[nums[2]] = nums[3] = 4
// slow != fast
//
// next:
// slow = nums[2] = 3
// fast = nums[nums[4]] = nums[2] = 3
// Now slow == fast -> break from do-while
//
// reset slow = nums[0] = 3
// now while(slow != fast) loop:
// slow == fast already (both 3) -> loop skipped -> return 3
//
// Duplicate found: 3
//
// --------------------------------------------------------------------------------------
// End of detailed notes
// --------------------------------------------------------------------------------------
