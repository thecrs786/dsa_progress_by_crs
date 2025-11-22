#include <bits/stdc++.h>
using namespace std;

/*
    =============================== NOTES ===============================

    ❓ WHAT THIS PROGRAM DOES:
    ---------------------------------
    - Generates and prints ALL subsets of a given array (the power set).
    - Uses recursion + backtracking to explore all include/exclude decisions.

     ⚡ BACKTRACKING — WHAT IT IS AND WHY IT’S HERE:
    ------------------------------------------------------------------------------
    - At every index i, you make a binary decision:
        (I)  include nums[i]  → push_back
        (E)  exclude nums[i]  → do nothing
    - After exploring the **include** branch, you MUST undo that choice
      before exploring the **exclude** branch. That “undo” is **backtracking**:
        - include → recurse → **pop_back** → exclude → recurse
      If you forget pop_back, your "exclude" path is contaminated and wrong.



    ⚡ BASE CASE:
    ---------------------------------
    - When i == nums.size(), we’ve made decisions for all elements.
    - Print the current subset (vector<int> ans).
    - Then return.

    ⚡ WHY BACKTRACKING IS NEEDED:
    ---------------------------------
    - After including nums[i] and exploring deeper recursion,
      we must remove it (pop_back) before exploring the exclude case.
    - This ensures the subset vector stays consistent and doesn’t
      accumulate wrong values.
      ---------------------------------------------------
    🔍 EXPLANATION OF BACKTRACKING
    ---------------------------------------------------
    - Think of the recursion as a decision tree.
    - Each level of the tree corresponds to an index `i` of `nums`.
    - Each node branches into:
         → LEFT branch = include nums[i]
         → RIGHT branch = exclude nums[i]
    - Base case (leaf node): when i == nums.size() → print current subset.

    ---------------------------------------------------
    🌳 RECURSION TREE for nums = {1,2,3}
    ---------------------------------------------------

    Start: i = 0, ans = []

                (i=0, ans=[])
                /                \
        Include 1               Exclude 1
        (ans=[1])               (ans=[])
          /     \                  /     \
  Include 2   Exclude 2     Include 2   Exclude 2
  (ans=[1,2]) (ans=[1])     (ans=[2])   (ans=[])
      /   \       /   \        /   \       /   \
Inc 3  Exc3  Inc3   Exc3  Inc3   Exc3  Inc3   Exc3
[1,2,3][1,2][1,3][1] [2,3][2]   [3]    []

    ---------------------------------------------------
    🔎 STEP-BY-STEP TRAVERSAL
    ---------------------------------------------------
    1. Start with [], i=0.
    2. Include nums[0]=1 → ans=[1], recurse to i=1.
    3. Include nums[1]=2 → ans=[1,2], recurse to i=2.
    4. Include nums[2]=3 → ans=[1,2,3], i=3 → base case → print [1,2,3].
       BACKTRACK: pop_back() → ans=[1,2].
    5. Exclude nums[2]=3 → ans=[1,2], i=3 → base case → print [1,2].
       BACKTRACK to [1].
    6. Exclude nums[1]=2 → ans=[1], recurse i=2.
        → Include 3 → [1,3], print.
        → Exclude 3 → [1], print.
    7. Exclude nums[0]=1 → ans=[], recurse i=1.
        → Include 2 → [2], then include/exclude 3.
        → Exclude 2 → [], then include/exclude 3.
    8. End when all paths explored.
    ⏱ TIME COMPLEXITY (no sugarcoating):
    ------------------------------------------------------------------------------
    - There are 2 choices per element → total leaves = 2^n subsets.
    - Each leaf prints up to O(n) elements (in the worst case subset).
    - Total work = O(n * 2^n). You cannot beat this if you must print all subsets.

    💾 SPACE COMPLEXITY:
    ------------------------------------------------------------------------------
    - Recursion depth = n → O(n) stack frames.
    - The `ans` vector holds up to n elements at any time → O(n) auxiliary.
    - Overall auxiliary space: O(n). (Output itself is exponential; that’s separate.)

    ✅ KEY INSIGHTS:
    ------------------------------------------------------------------------------
    - The **order** (Include → Exclude) determines the print order.
    - **pop_back()** is non-negotiable. It’s the spine of correct backtracking.
    - **Base case** must both print and return. Miss either → broken traversal.
    - The function is **purely functional** w.r.t. input; it doesn’t mutate `nums`.

    ⚠️ WARNINGS:
    ------------------------------------------------------------------------------
    - Don’t access nums[i] after i == nums.size(). Check base case first.
    - Forgetting pop_back() means your exclude branch starts from a dirty state.
    - For large n, output is huge (2^n lines). That’s inherent, not an algorithm bug.

    🧠 LOGIC (compressed):
    ------------------------------------------------------------------------------
    - Depth = index i.
    - Node action:
        • If i == n → print ans.
        • Else:
            Include nums[i] → recurse
            Backtrack (pop)
            Exclude nums[i] → recurse
*/
void printsubsets(vector<int> &nums, vector<int> &ans, int i) {
    if (i == nums.size()) {                     // ✅ Base case: all elements processed
        cout << "[";
        for(int i =0; i<ans.size(); i++){
            cout<<ans[i];
            i!=ans.size()-1 ? cout<<", " : cout<<"]";
        }if(ans.size()==0) cout<<"]";  // closing bracket for the null subset because above statement won't do that
        cout<<endl;
        return;                            // ✅ Return after printing
    }

    // ---------- INCLUDE CASE ----------
    ans.push_back(nums[i]);                     // ✅ Choose nums[i]
    printsubsets(nums, ans, i + 1);             // ✅ Recurse with it included

    // ---------- BACKTRACK ----------
    ans.pop_back();                             // ✅ Undo the include choice

    // ---------- EXCLUDE CASE ----------
    printsubsets(nums, ans, i + 1);             // ✅ Recurse WITHOUT nums[i]
}

// ================== MAIN FUNCTION (EXAMPLE) ==================
int main() {
    vector<int> arr = {1, 2, 3};   // ✅ Example array
    vector<int> ans;               // ✅ Temporary subset storage

    printsubsets(arr, ans, 0);     // ✅ Start recursion at index 0

    return 0;
}

/*   MORE IN DEPTH EXPLANATION IF NEEDED
    

nums = {1,2,3}

Start: f(i=0, ans={})

-------------------------------------------------
i=0, ans={} → include nums[0]=1
    Call f(i=1, ans={1})

        i=1, ans={1} → include nums[1]=2
            Call f(i=2, ans={1,2})

                i=2, ans={1,2} → include nums[2]=3
                    Call f(i=3, ans={1,2,3})
                        i=3 == nums.size → PRINT [1,2,3]
                        return
                    Backtrack: pop 3 → ans={1,2}

                i=2, ans={1,2} → exclude nums[2]=3
                    Call f(i=3, ans={1,2})
                        i=3 == nums.size → PRINT [1,2]
                        return
                    return to i=2
            Backtrack: pop 2 → ans={1}

        i=1, ans={1} → exclude nums[1]=2
            Call f(i=2, ans={1})

                i=2, ans={1} → include nums[2]=3
                    Call f(i=3, ans={1,3})
                        i=3 == nums.size → PRINT [1,3]
                        return
                    Backtrack: pop 3 → ans={1}

                i=2, ans={1} → exclude nums[2]=3
                    Call f(i=3, ans={1})
                        i=3 == nums.size → PRINT [1]
                        return
                    return to i=2
            return to i=1
        return to i=1
    Backtrack: pop 1 → ans={}

i=0, ans={} → exclude nums[0]=1
    Call f(i=1, ans={})

        i=1, ans={} → include nums[1]=2
            Call f(i=2, ans={2})

                i=2, ans={2} → include nums[2]=3
                    Call f(i=3, ans={2,3})
                        i=3 == nums.size → PRINT [2,3]
                        return
                    Backtrack: pop 3 → ans={2}

                i=2, ans={2} → exclude nums[2]=3
                    Call f(i=3, ans={2})
                        i=3 == nums.size → PRINT [2]
                        return
                    return to i=2
            Backtrack: pop 2 → ans={}

        i=1, ans={} → exclude nums[1]=2
            Call f(i=2, ans={})

                i=2, ans={} → include nums[2]=3
                    Call f(i=3, ans={3})
                        i=3 == nums.size → PRINT [3]
                        return
                    Backtrack: pop 3 → ans={}

                i=2, ans={} → exclude nums[2]=3
                    Call f(i=3, ans={})
                        i=3 == nums.size → PRINT []
                        return
                    return to i=2
            return to i=1
        return to i=1
    return to i=0
-------------------------------------------------

Final printed subsets in order:
[1,2,3]
[1,2]
[1,3]
[1]
[2,3]
[2]
[3]
[]


*/
    
