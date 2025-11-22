// Previous Smaller Element

// ------------------------------------------------------------
// Problem Summary:
// Given two integer arrays nums1 and nums2 where nums1 is a subset of nums2 (every element of nums1 appears in nums2),
// for each element in nums1 find the immediate previous smaller element to its left in nums2.
// If there is no previous smaller element, return -1.
//
// Constraints: 
// - All elements in nums2 are unique
// - nums1 ⊆ nums2
// - Similar to LeetCode 496 "Next Greater Element I", just reversed logic.
//
// Example:
// nums2 = [4, 2, 5, 1, 7]
// nums1 = [2, 5, 7]
// Mapping: 4→-1, 2→-1, 5→2, 1→-1, 7→1
// Answer: [-1, 2, 1]
//
// ------------------------------------------------------------
// Method: Monotonic Stack (Increasing Stack)
//
// Idea:
// - Iterate nums2 left → right.
// - Maintain a stack that is strictly increasing.
// - For current element x:
//      Pop until stack.top() < x (so that the top is the closest smaller).
//      If stack empty → previous smaller = -1
//      Else → previous smaller = stack.top()
//   Push x on stack.
// - Build a map nums2[i] → previousSmaller.
// - For nums1, lookup in the map and return answers.
//
// ------------------------------------------------------------
// Complexity:
// Time: O(N + M), where N = nums2.size(), M = nums1.size()
// Space: O(N) for stack + map
// This is the most optimal solution. No chance of TLE/MLE for typical constraints.
//
// ------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

vector<int> previousSmallerElement(vector<int> &nums1, vector<int> &nums2) {
    vector<int> ans(nums1.size());
    stack<int> st;                     // monotonic increasing stack
    unordered_map<int,int> m;          // maps nums2[i] -> its previous smaller
    m.reserve(nums2.size()*2);         // reserve to avoid rehashing

    for (int i = 0; i < (int)nums2.size(); i++) {
        int x = nums2[i];

        // Pop elements ≥ current, since they can’t be a "previous smaller"
        while (!st.empty() && st.top() >= x) {
            st.pop();
        }

        // If empty → no smaller element to the left
        if (st.empty()) m[x] = -1;
        else m[x] = st.top();

        st.push(x); // current element becomes candidate for future elements
    }

    // Fill results for nums1
    for (int i = 0; i < (int)nums1.size(); i++) {
        ans[i] = m[nums1[i]];
    }
    return ans;
}

// ------------------------------------------------------------
// Helper function to print vectors
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]";
}

// ------------------------------------------------------------
// Working Example
int main() {
    vector<int> nums2 = {4, 2, 5, 1, 7};
    vector<int> nums1 = {2, 5, 7};

    vector<int> result = previousSmallerElement(nums1, nums2);

    cout << "nums2 = "; printVector(nums2);
    cout << "\nnums1 = "; printVector(nums1);
    cout << "\npreviousSmallerElement(nums1, nums2) = "; printVector(result);
    cout << "\n";

    // Expected: [-1, 2, 1]

    return 0;
}

/*
-----------------------
Full Explanation (Logic):
1. We traverse nums2 left→right because "previous" means left side.
2. Maintain a stack of candidates for previous smaller:
   - The stack will always be increasing (bottom small → top larger).
   - Before inserting x, pop all elements ≥ x (they can’t be smaller).
3. After popping:
   - If stack empty → x has no previous smaller → -1
   - Else → stack.top() is the nearest smaller on left
4. Push x onto stack as candidate for upcoming elements.
5. Store result in map for each nums2[i].
6. Finally, answer queries for nums1 by looking up in the map.

Key Insights:
- This is the mirror of "Next Greater Element" (LeetCode 496).
- Stack ensures O(N) total pops/pushes (each element enters/exits once).
- Map ensures O(1) query time for nums1.
- Strictly optimal: can’t do better than O(N + M).

Edge Cases:
- First element of nums2 always gets -1 (no left neighbor).
- Strictly increasing array → each element’s previous smaller is its immediate left.
- Strictly decreasing array → all answers are -1.
-----------------------
*/
