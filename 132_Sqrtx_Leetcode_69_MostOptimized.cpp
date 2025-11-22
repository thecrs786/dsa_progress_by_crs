/***************************************************************

✅ Problem: Implement `int mySqrt(int x)`
🔍 Goal: Return the floor of the square root of a non-negative integer `x`.

    - Example: mySqrt(8) → 2 (since sqrt(8) ≈ 2.828 and floor is 2)

🎯 Approach Used: **Binary Search**
📌 Time Complexity: O(log x)
📌 Space Complexity: O(1)

⚙️ Method Name: mySqrt()
🧠 Is this optimal? → YES. This is the most efficient integer-based approach.
✅ Will this be accepted on LeetCode? → YES. It avoids TLE and MLE.
❌ Does it risk overflow? → NOT ANYMORE. Overflow is prevented using `long long` in key places.

****************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        // Handle edge case directly
        if (x == 0) return 0;

        // Start binary search from 1 to x
        int st = 1, end = x;
        int ans = 0;

        while (st <= end) {
            // We use 'long long' here to avoid integer overflow
            // when mid*mid becomes larger than INT_MAX
            long long mid = st + (end - st) / 2;

            long long sq = mid * mid; // avoid overflow

            if (sq == x) {
                // Found perfect square
                return mid;
            } 
            else if (sq < x) {
                // We store the last mid that worked because 
                // it's the closest integer <= sqrt(x)
                ans = mid;
                st = mid + 1;
            } 
            else {
                // Mid squared is too high, so try lower
                end = mid - 1;
            }
        }

        // Return the closest integer <= sqrt(x)
        return ans;
    }
};

/***************************************************************

📘 Explanation of the Function (Step-by-step):

1. We are finding the **floor of square root** of a number `x`.
   That means: the **largest integer `y` such that `y * y <= x`**.

2. A brute-force approach would check 1 through x and test squares.
   But that's O(x) and too slow.

3. Instead, we use **binary search** over the range [1, x].

4. At every step, we compute `mid = (start + end)/2`.

   ✅ If mid^2 == x → return mid (perfect square)
   ✅ If mid^2 < x → this might be the answer, but we try higher
   ❌ If mid^2 > x → mid is too big, try smaller range

5. We update `ans = mid` whenever mid^2 < x so that we always 
   remember the last working candidate.

6. Why use `long long` for mid and sq?
   Because when x is close to INT_MAX (2,147,483,647), `mid * mid`
   can easily exceed the `int` limit during calculation, even though
   mid itself fits in an int.

📛 Cause of Integer Overflow:
- In C++, when two `int` values are multiplied, the result is also
  computed as an `int`, **before assignment**.
- So even assigning it to a `long long` doesn’t help **unless**
  the multiplication is **promoted beforehand**.

💉 Fix:
- Either cast before multiplication:
    `long long sq = 1LL * mid * mid;`
- Or just declare `mid` and `sq` as `long long`, which promotes the
  expression automatically.

****************************************************************/

/********** 🔎 Example Run (For analysis) **********/

int main() {
    Solution obj;

    int x = 2147395599;
    int result = obj.mySqrt(x);

    cout << "Input: " << x << endl;
    cout << "Square Root (floor): " << result << endl;

    return 0;
}

/* 💡 OUTPUT:
Input: 2147395599
Square Root (floor): 46339
*/

/***************************************************************

🧠 Final Summary:

- We are using binary search to find the square root.
- We store the last mid that worked, since we want floor(sqrt(x))
- We prevent overflow by using `long long` on mid and square.
- This is the optimal solution with logarithmic time.
- LeetCode will accept it — no overflow, TLE, or MLE risk.

***************************************************************/
