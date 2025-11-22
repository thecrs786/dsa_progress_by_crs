/*
LeetCode 155 - Min Stack (C++)

--- Brief problem (one-line):
Design a stack that supports push(x), pop(), top() and getMin() in O(1) time.

--- Example (LeetCode sample):
Input/operations:
  MinStack st;
  st.push(-2); st.push(0); st.push(-3);
  st.getMin(); // -> -3
  st.pop();
  st.top();    // -> 0
  st.getMin(); // -> -2

--------------------------------------------------------------------------------
This file contains:
  - The "encoded value" solution you provided (single stack, encoded values).
  - Full boilerplate and a runnable `main()` with several tests.
  - Deep inline comments explaining exactly why the formulas work, step-by-step.
  - Complexity, tradeoffs, pitfalls (INT overflow), and best-practice notes.

Method name: "Encoded-min trick" (also called difference / encoded-delta trick)
Core idea: When pushing a value that becomes the new minimum, we push a
special *encoded* value (2*val - prevMin) instead of val. We then set minVal=val.
The encoded marker both tells us "this element encoded the previous min" and
lets us recover the previous minimum during pop using prevMin = 2*min - encoded.

Why use long long? Because expressions like 2*val - prevMin can overflow 32-bit
int for extreme values (e.g., INT_MIN). Use 64-bit arithmetic (long long) for safety.

Time & Space:
  - push / pop / top / getMin: O(1) time each.
  - Space: O(n) worst-case (one long long per pushed element).

Is it "most optimal"?
  - Time: Yes, O(1) for each API call is optimal.
  - Space: Asymptotically O(n) — you can't do better than storing the elements.
    In practice, this method stores one 64-bit per element. The simpler
    pair<int,int> method stores two ints (typically 2*32-bit) — similar memory
    footprint on many platforms after alignment. The encoded trick can reduce
    memory if you used pair<int,int> and strictly needed to avoid the second int
    when minima change rarely — but using long long may negate those savings.

Will LeetCode accept it? Yes — provided you use 64-bit arithmetic to avoid overflow.
No TLE or MLE under typical constraints (calls up to ~3e4).

--------------------------------------------------------------------------------
FULL CODE (single-file). Everything is self-contained and heavily commented.
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------
// Encoded MinStack implementation
// -----------------------------
class MinStack {
private:
    // store either the raw pushed values or encoded markers
    stack<long long> s;          // use long long to avoid overflow in formulas
    long long minVal;           // current minimum (valid only if stack not empty)

public:
    // Constructor
    MinStack() {
        // We'll keep minVal undefined until the stack has at least one element.
        // Many LeetCode tests guarantee no invalid calls, but our demo avoids
        // calling getMin/top/pop on empty stack.
        while (!s.empty()) s.pop();
        minVal = 0; // meaningless until first push
    }

    // Push x onto stack.
    // If x is the new minimum, push encoded value: encoded = 2*x - oldMin
    // and set minVal = x. Otherwise push x normally.
    void push(int val) {
        if (s.empty()) {
            // first element: store it as-is and set minVal to it
            s.push((long long)val);
            minVal = val;
        } else {
            if ((long long)val < minVal) {
                // val becomes the new minimum. Push encoded marker.
                // encoded = 2*val - prevMin
                long long encoded = 2LL * (long long)val - minVal;
                s.push(encoded);
                // update current minimum
                minVal = val;
            } else {
                // normal push
                s.push((long long)val);
            }
        }
    }

    // Pop top element.
    // If top was encoded (top < minVal), it means the popped element was the
    // current minimum and we must recover the previous minimum using:
    //    prevMin = 2*minVal - encodedTop
    void pop() {
        if (s.empty()) return; // guard for demo; LeetCode guarantees valid calls

        long long topVal = s.top();
        s.pop();

        if (topVal < minVal) {
            // encoded marker — restore previous min
            // derivation: encoded = 2*val - prevMin, and after push minVal==val.
            // So prevMin = 2*minVal - encoded.
            long long prevMin = 2LL * minVal - topVal;
            minVal = prevMin;
        }

        // If stack becomes empty after pop, minVal is meaningless again. For
        // safety, we won't rely on its value until next push.
        if (s.empty()) minVal = 0;
    }

    // Return the top element (actual value). If the stored top is encoded,
    // the real top value equals minVal (because we encoded only when new min
    // was pushed and minVal was set to that pushed value).
    int top() {
        if (s.empty()) {
            // for demo safety; LeetCode promises valid calls
            cerr << "top() called on empty stack\n";
            return INT_MIN; // sentinel
        }
        long long topVal = s.top();
        if (topVal < minVal) {
            // encoded marker indicates the real value is minVal
            return (int)minVal;
        } else {
            return (int)topVal;
        }
    }

    // Return current minimum
    int getMin() {
        if (s.empty()) {
            cerr << "getMin() called on empty stack\n";
            return INT_MIN; // sentinel
        }
        return (int)minVal;
    }

    // Debug helper: print raw stored stack and interpreted (actual) values
    // from bottom -> top. This is only for demonstration and understanding.
    void debug_print_stack() {
        // copy stack to vector to inspect bottom->top
        stack<long long> tmp = s;
        vector<long long> raw;
        while (!tmp.empty()) {
            raw.push_back(tmp.top());
            tmp.pop();
        }
        reverse(raw.begin(), raw.end()); // now raw is bottom->top

        cout << "RAW stored values (bottom -> top): ";
        for (auto v : raw) cout << v << " ";
        cout << '\n';

        // Reconstruct actual pushed values and running min from bottom->top
        vector<long long> actual;
        long long runningMin = LLONG_MAX; // unknown until first element
        for (size_t i = 0; i < raw.size(); ++i) {
            long long x = raw[i];
            if (i == 0) {
                // first element always stored as-is
                actual.push_back(x);
                runningMin = x;
            } else {
                if (x < runningMin) {
                    // encoded marker; recover the pushed value
                    long long pushedVal = (x + runningMin) / 2LL; // exact integer
                    actual.push_back(pushedVal);
                    runningMin = pushedVal;
                } else {
                    actual.push_back(x);
                    if (x < runningMin) runningMin = x;
                }
            }
        }

        cout << "INTERPRETED actual values (bottom -> top): ";
        for (auto v : actual) cout << v << " ";
        cout << "\nCurrent minVal = ";
        if (!s.empty()) cout << minVal << '\n'; else cout << "<empty>\n";
    }
};

// --------------------------------------------------------------------------------
// Walkthrough & formula derivation (short version):
//  - When pushing new value v:
//      if v < prevMin:
//          push encoded = 2*v - prevMin
//          set minVal = v
//      else
//          push v
//  - Why encoded = 2*v - prevMin ?
//      encoded stores enough information to both detect an encoded entry
//      (encoded < new min) and to recover the previous minimum.
//      Derivation during pop:
//         encoded = 2*v - prevMin
//         after push, minVal == v
//         to recover prevMin when popping encoded:
//           prevMin = 2*minVal - encoded
//  - Example numbers:
//      prevMin = 10, push v = 7
//        encoded = 2*7 - 10 = 4 (push 4), minVal = 7
//      Now top() sees stored 4 < minVal(7) so real top is 7
//      On pop(), encodedTop = 4 < minVal (7)
//        prevMin = 2*7 - 4 = 10 => min restored
// --------------------------------------------------------------------------------

// -----------------------------
// Runnable demonstration
// -----------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Demo: Encoded MinStack (LeetCode 155) ===\n\n";

    MinStack st;

    cout << "Test 1 (LeetCode sample):\n";
    st.push(-2);
    st.push(0);
    st.push(-3);
    st.debug_print_stack();
    cout << "getMin() -> " << st.getMin() << " (expect -3)\n";
    st.pop();
    st.debug_print_stack();
    cout << "top()    -> " << st.top() << " (expect 0)\n";
    cout << "getMin() -> " << st.getMin() << " (expect -2)\n\n";

    // Clear (pop remaining)
    while (true) {
        // avoid infinite loop on empty check
        // We rely on st.top/getMin guards printing sentinel on empty.
        // For this demo we know stack isn't empty here; but pop until empty safely.
        // Simpler: just construct a fresh object for next test.
        break;
    }

    cout << "Test 2 (show encoding & decoding with explanation):\n";
    MinStack st2;
    st2.push(10);
    cout << "pushed 10\n"; st2.debug_print_stack();
    st2.push(7);
    cout << "pushed 7 (new min -> encoded stored)\n"; st2.debug_print_stack();
    st2.push(8);
    cout << "pushed 8\n"; st2.debug_print_stack();
    st2.push(6);
    cout << "pushed 6 (new min -> encoded stored)\n"; st2.debug_print_stack();

    cout << "\nNow popping step by step and observing min restoration:\n";
    cout << "pop() ->\n"; st2.pop(); st2.debug_print_stack(); // popping 6
    cout << "pop() ->\n"; st2.pop(); st2.debug_print_stack(); // popping 8
    cout << "pop() ->\n"; st2.pop(); st2.debug_print_stack(); // popping 7, min restored to 10

    cout << "\nTest 3 (INT_MIN edge-case demonstration)\n";
    MinStack st3;
    st3.push(INT_MIN);
    cout << "pushed INT_MIN -> min = " << st3.getMin() << "\n";
    st3.push(-1);
    cout << "pushed -1 -> min = " << st3.getMin() << "\n";
    st3.debug_print_stack();

    // Summary advice:
    cout << "\nSUMMARY ADVICE:\n";
    cout << " - The encoded trick is neat and saves you from storing an extra int per element\n";
    cout << "   (but you must use 64-bit arithmetic to avoid overflow).\n";
    cout << " - The pair<int,int> approach is simpler and less error-prone; use it\n";
    cout << "   in interviews unless you need the micro-optimization.\n";

    return 0;
}

/*
-----------------------------
Important details & key sights (final notes):

1) Detection rule: A stored element x is encoded iff x < current minVal. That
   single inequality both identifies encoded entries and distinguishes them from raw values.

2) Why it works algebraically:
   - When pushing v where v < prevMin:
       encoded = 2*v - prevMin
     After push minVal = v.
   - On pop of encoded (call it E): previous min = 2*minVal - E.
     Proof: E = 2*v - prevMin, and minVal==v after push.
            => prevMin = 2*v - E = 2*minVal - E.

3) Overflow caution: computing 2*val can overflow 32-bit. Use 64-bit stores and
   arithmetic (long long). That is why `stack<long long>` and `long long minVal`
   are used. Without this, pushing INT_MIN could wrap and produce the wrong result.

4) Space-time tradeoffs:
   - Pair approach (stack<pair<int,int>>) is clearer and stores two ints per
     element; encoded approach stores one long long per element. On many
     platforms these are comparable; choose based on clarity vs micro-optimization.

5) Safety: Always guard top/pop/getMin when using this class outside LeetCode
   (LeetCode guarantees valid calls). Demo code includes prints and guards.

6) Alternatives:
   - Two-stack (values + mins-with-count): store minima only when they change with counts.
     This can be memory efficient when min changes infrequently.

Bottom line: Your provided implementation (with long long) is correct, efficient,
and accepted by LeetCode. Prefer the pair approach for clarity unless you know
why you need the encoded trick.
*/
