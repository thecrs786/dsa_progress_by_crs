/***************************************************************
 *  LeetCode 155 — Min Stack (C++)
 *  ------------------------------------------------------------
 *  Problem (in brief):
 *    Design a stack that supports:
 *      - void push(int val)
 *      - void pop()
 *      - int top()
 *      - int getMin()   // return current minimum element
 *
 *  Typical LeetCode example:
 *    MinStack st;
 *    st.push(-2); st.push(0); st.push(-3);
 *    st.getMin(); // -> -3
 *    st.pop();
 *    st.top();    // -> 0
 *    st.getMin(); // -> -2
 *
 *  Constraints (typical on LC as of 2025; ops up to ~3e4):
 *    - Values fit in 32-bit int.
 *    - Calls are valid (they won't call pop/top/getMin on empty).
 *
 *  ------------------------------------------------------------
 *  METHOD NAME:
 *    "Min-at-each-node" (a single stack of pairs: {value, min_so_far})
 *
 *  CORE IDEA (why this works):
 *    On each push, store both:
 *      - the value itself, and
 *      - the minimum value in the stack *up to and including* this node.
 *    Then:
 *      - top() = pair.first
 *      - getMin() = pair.second       // O(1), no search needed
 *    This duplicates the running minimum per node, but guarantees O(1)
 *    across all operations with brutally simple code and no edge-case traps.
 *
 *  TIME & SPACE:
 *    - push / pop / top / getMin: O(1) worst-case.
 *    - Extra space: O(n) pairs (value + min_so_far).
 *
 *  IS THIS THE MOST OPTIMAL?
 *    - Time: Yes, you cannot beat O(1) per op deterministically for this API.
 *    - Space: Asymptotically optimal O(n). There are space-tweaks (e.g., store
 *      minima only when they change, with counts; or encode diffs) that reduce
 *      constants, but worst-case space is still O(n). Your approach is clean,
 *      robust, and interview-approved.
 *
 *  WILL IT BE ACCEPTED? Any risk of TLE/MLE?
 *    - Accepted. With ~3e4 ops and O(1) per op, TLE is not a thing.
 *    - MLE: Only if you intentionally push huge counts beyond constraints.
 *      Within constraints, pair<int,int> per push is fine.
 *
 *  IMPORTANT DETAILS & KEY INSIGHTS:
 *    1) Duplicates of the minimum are handled naturally: every node keeps the
 *       min_so_far, so when you pop the last global min, the previous node’s
 *       min_so_far is instantly the new min.
 *    2) No INT overflow shenanigans here, unlike the "encoded difference" trick.
 *       Using plain pairs avoids subtle bugs.
 *    3) Don’t call pop/top/getMin on an empty stack in your own code; LC promises
 *       they won’t do that, but your standalone tests should guard.
 *    4) Two-stack variant (values + mins-with-count) is equally optimal in time
 *       and can use slightly less memory when values are mostly increasing.
 *       Still O(n) worst-case; your pair approach is simpler and safer.
 *
 *  FULL STEP-BY-STEP EXPLANATION OF EACH OP:
 *    - push(val):
 *        If stack is empty: min_so_far = val.
 *        Else: min_so_far = min(val, stack.top().second).
 *        Push {val, min_so_far}.
 *      Why: caching the current min means getMin() is trivial O(1).
 *
 *    - pop():
 *        Stack pop. We discard exactly one node’s value and its cached min.
 *      Why: After popping, the new top already has the correct min_so_far.
 *
 *    - top():
 *        Return stack.top().first (the stored value).
 *      Why: The pair’s first element is always the true top value.
 *
 *    - getMin():
 *        Return stack.top().second (the cached min at the top node).
 *      Why: By construction, that’s the minimum of all elements currently in stack.
 *
 ****************************************************************/

#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include <string>
#include <limits>
#include <cassert>

using namespace std;

/*
 * YOUR PROVIDED SOLUTION (kept verbatim in spirit, with comments):
 * - Single stack of {value, min_so_far}.
 * - O(1) per operation, O(n) space.
 */
class MinStack {
public:
    // We keep this public exactly like your snippet (though 'private' would be more idiomatic).
    stack<pair<int, int>> s;

    MinStack() {
        // Nothing needed; the stack starts empty.
    }
    
    void push(int val) {
        if (s.empty()) {
            // First element: its own value is the current min.
            s.push({val, val});
        } else {
            // Compare with previous min_so_far to compute new min_so_far.
            int minVal = std::min(val, s.top().second);
            s.push({val, minVal});
        }
    }
    
    void pop() {
        // Assumes non-empty (LeetCode guarantees valid calls).
        s.pop();
    }
    
    int top() {
        // Assumes non-empty.
        return s.top().first;
    }
    
    int getMin() {
        // Assumes non-empty.
        return s.top().second;
    }
};

/****************************************************************
 * RUNTIME DEMO (Working example):
 * --------------------------------------------------------------
 * We execute a sequence of operations and print results so you
 * can analyze the behavior. This mirrors and expands LC examples.
 ****************************************************************/

struct Op {
    string name;       // "push", "pop", "top", "getMin"
    int arg = 0;       // used only for push
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MinStack st;

    // Test 1: LeetCode sample
    {
        cout << "=== Test 1: LeetCode sample ===\n";
        st.push(-2);
        st.push(0);
        st.push(-3);
        cout << "getMin() -> " << st.getMin() << " (expect -3)\n";
        st.pop();
        cout << "top()    -> " << st.top()    << " (expect 0)\n";
        cout << "getMin() -> " << st.getMin() << " (expect -2)\n\n";
    }

    // Clear by popping remaining elements to avoid mixing tests
    while (!st.s.empty()) st.pop();

    // Test 2: Duplicates & increasing/decreasing patterns
    {
        cout << "=== Test 2: Duplicates & patterns ===\n";
        vector<Op> ops = {
            {"push", 5}, {"push", 5}, {"push", 7}, {"push", 3},
            {"getMin"},  // -> 3
            {"pop"},     // pop 3
            {"getMin"},  // -> 5 (since 5 repeated twice)
            {"pop"},     // pop 7
            {"getMin"},  // -> 5
            {"pop"},     // pop 5
            {"getMin"},  // -> 5 (still one 5 remains)
            {"top"},     // -> 5
        };

        for (auto &op : ops) {
            if (op.name == "push") {
                st.push(op.arg);
                cout << "push(" << op.arg << "), min=" << st.getMin() << ", top=" << st.top() << "\n";
            } else if (op.name == "pop") {
                if (!st.s.empty()) {
                    st.pop();
                    cout << "pop(), ";
                    if (!st.s.empty())
                        cout << "new top=" << st.top() << ", min=" << st.getMin() << "\n";
                    else
                        cout << "stack empty\n";
                } else {
                    cout << "pop() skipped (stack empty)\n";
                }
            } else if (op.name == "top") {
                if (!st.s.empty()) cout << "top() -> " << st.top() << "\n";
                else cout << "top() skipped (stack empty)\n";
            } else if (op.name == "getMin") {
                if (!st.s.empty()) cout << "getMin() -> " << st.getMin() << "\n";
                else cout << "getMin() skipped (stack empty)\n";
            }
        }
        cout << "\n";
    }

    // Clear for next test
    while (!st.s.empty()) st.pop();

    // Test 3: Stress-ish pattern within small bounds (sanity)
    {
        cout << "=== Test 3: Mixed pushes/pops sanity ===\n";
        vector<int> seq = {10, 9, 12, 8, 8, 15, -1, -1, 3};
        for (int x : seq) {
            st.push(x);
            cout << "push(" << x << ") -> min=" << st.getMin() << ", top=" << st.top() << "\n";
        }

        for (int i = 0; i < 5; ++i) {
            st.pop();
            cout << "pop() -> ";
            if (!st.s.empty())
                cout << "min=" << st.getMin() << ", top=" << st.top() << "\n";
            else
                cout << "stack empty\n";
        }
        cout << "\n";
    }

    /************************************************************
     * LOGIC & WALKTHROUGH (summary, as comments):
     *
     * 1) After each push, the node remembers the best (smallest)
     *    value so far. That makes getMin() constant-time: we just
     *    read the cached second field on the top node.
     *
     * 2) Example continuous state (values | min_so_far):
     *      push(5)  -> [ (5|5) ]
     *      push(7)  -> [ (5|5), (7|5) ]
     *      push(3)  -> [ (5|5), (7|5), (3|3) ]    // new min
     *      getMin() -> top.second = 3
     *      pop()    -> [ (5|5), (7|5) ]
     *      getMin() -> top.second = 5
     *
     * 3) Duplicates handled:
     *      push(5), push(5):
     *      [ (5|5), (5|5) ]
     *      pop() -> still (5|5), min remains 5.
     *
     * 4) Negative values / INT_MIN:
     *      Works fine—no arithmetic on values, only comparisons.
     *
     * 5) Alternatives (for completeness):
     *      - Two stacks: values + mins-with-count (decrement count on pop).
     *      - Encoded single stack (store diff = val - current_min). Saves a
     *        few ints sometimes but requires careful overflow handling and
     *        is easier to mess up. Your pair approach avoids those pitfalls.
     *
     * Bottom line: Your implementation is clean, optimal in time, and fully
     * acceptable for LeetCode and interviews.
     ************************************************************/

    return 0;
}
