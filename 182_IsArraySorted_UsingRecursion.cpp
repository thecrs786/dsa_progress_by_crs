#include <bits/stdc++.h>
using namespace std;

/*
    ✅ QUESTION: Check if an array (vector) is sorted using recursion.

    🎯 GOAL:
    Given an array of integers, determine if it is sorted in non-decreasing order
    (each element is greater than or equal to the previous one).

    Example:
      Input: {1, 2, 3, 4, 5}
      Output: true

      Input: {1, 3, 2, 4}
      Output: false

    🔑 Key Requirements:
    - Use recursion to check if the array is sorted.
    - Only need to "read" the array, no modifications required.
    - Return true if sorted, false otherwise.
*/

/*
    ⚡ Important Concepts Before the Function:

    1. The concept of `&` (reference):
       - Passing a parameter as `vector<int>& v` means:
         "Don’t copy the vector, work with the same one."
       - No extra memory is wasted in recursion.
       - But any modification will affect the original vector.

    2. The concept of `const`:
       - Writing `const vector<int>& v` means:
         "This is the real vector, but I promise not to change it."
       - Compiler enforces read-only. If you try to modify: compile error.
       - Example:
            const vector<int>& v = arr;
            v[0] = 10;  // ❌ error, not allowed

    3. The concept of `const &` together:
       - Both benefits at once:
         - Avoids copies (`&`)
         - Protects original vector from modification (`const`)
       - This is the **safest and most efficient** option when we only need to check values.

    4. What if we use only `&` and modify?
       - Then we directly modify the caller’s vector. Example:
            void f(vector<int>& v) { v[0] = 999; }
            // original array gets changed
       - That’s dangerous if unintended. Hence in read-only functions,
         always use `const &`.
*/

/*
    ✅ SOLUTION PROVIDED:
    Method Name: Recursive backward check
    Approach:
      - Compare the last two elements of the array:
          if nums[n-1] < nums[n-2], not sorted → return false.
      - Otherwise, recursively check the first (n-1) elements.
      - Base case: if n == 1, return true (single element is trivially sorted).
*/

bool issorted(const vector<int>& nums, int n){ // n = size of vector
    // Base case: Single element or empty vector is always sorted
    if(n == 1 || n==0) return true;

    // Check the last two elements
    if(nums[n-1] < nums[n-2]) return false;

    // Recurse for the rest of the array
    return issorted(nums, n-1);

    // or return nums[n-1]>=nums[n-2] && issorted(nums, n-1);
}

/*
    🔎 Explanation of Each Step:
    1. Base Case (n == 1):
       - When only one element is left, it is always sorted by definition.
       - This stops recursion.

    2. nums[n-1] < nums[n-2]:
       - If the last element is smaller than the second-last, order is violated.
       - Immediately return false.

    3. Recursive Call:
       - If last two are sorted, check the remaining n-1 elements.
       - Eventually reduces problem size until base case is reached.

    🔎 Working Example (nums = {1,2,3,4}, n=4):
       issorted(nums, 4)
       → checks nums[3] and nums[2] → (4 >= 3) OK
       → calls issorted(nums, 3)
       → checks nums[2] and nums[1] → (3 >= 2) OK
       → calls issorted(nums, 2)
       → checks nums[1] and nums[0] → (2 >= 1) OK
       → calls issorted(nums, 1)
       → returns true (base case)
       → all recursive calls return true → array is sorted

    🔎 Time Complexity:
       - Each recursive step checks one pair → O(n).
       - No extra work.

    🔎 Space Complexity:
       - Recursion depth = n → O(n) stack space.
       - No extra vector copies due to const &.
       - Much more efficient than pass-by-value.

    🔎 Optimality:
       - This solution is correct and efficient enough for small-medium arrays.
       - Iterative check (loop) would be slightly more optimal (O(1) stack),
         but recursion here is perfectly acceptable and passes constraints.
*/

/*
    🔑 Key Insights:
    - Base case is crucial: prevents out-of-bounds.
    - Recursion mirrors how we "reduce the problem size" until trivial case.
    - `const &` is the best choice: avoids copies + guarantees no modification.
    - Without const, accidental changes could corrupt the original vector.
*/

int main() {
    vector<int> nums1 = {1,2,3,4,5,6,7,8,9};
    vector<int> nums2 = {1,3,2,4,5};

    cout << "nums1 sorted? " << (issorted(nums1, nums1.size()) ? "Yes" : "No") << endl;
    cout << "nums2 sorted? " << (issorted(nums2, nums2.size()) ? "Yes" : "No") << endl;

    return 0;
}

/*
    ✅ Example Output:

    nums1 sorted? Yes
    nums2 sorted? No

    🔹 Observations:
      - The function correctly identifies sorted and unsorted arrays.
      - Uses recursion cleanly and safely with const &.
*/
