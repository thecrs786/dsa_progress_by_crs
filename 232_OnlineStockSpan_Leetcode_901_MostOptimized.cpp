#include <iostream>
#include <stack>
using namespace std;

/*
Problem No: 901
Problem Name: Online Stock Span (LeetCode)

Problem Description:
- Implement the StockSpanner class:
  - StockSpanner() Initializes the object.
  - int next(int price) Returns the span of the stock's price given today.
- Span: The number of consecutive days (including today) the stock price was less than or equal to today's price.

Examples:
Example 1:
Input: ["StockSpanner","next","next","next","next","next","next","next"]
       [[],[100],[80],[60],[70],[60],[75],[85]]
Output: [null,1,1,1,2,1,4,6]

Explanation:
Day 1: 100 → span=1
Day 2: 80  → span=1
Day 3: 60  → span=1
Day 4: 70  → previous 60 < 70 → span=2
Day 5: 60  → span=1
Day 6: 75  → previous 60,70,60 < 75 → span=4
Day 7: 85  → previous 75,60,70,60 < 85 → span=6

Solution Method: Stack-based approach (same logic as stock span problem)
- We use a stack to store pairs of (price, span)
- For each new price:
  - Pop all previous prices ≤ current price
  - Sum spans of popped elements to get today's span
  - Push (current price, today's span) onto stack

Time Complexity: O(1) amortized per `next()` call → overall O(N)
Space Complexity: O(N) (stack stores previous prices)
Optimal: ✅ Yes
Acceptable for LeetCode: ✅ Yes
Most Optimized: ✅ Yes, no brute-force scanning

*/

class StockSpanner {
public:
    stack<pair<int,int>> st; // pair<price, span>

    StockSpanner() {
        // Constructor initializes empty stack
    }
    
    int next(int price) {
        int span = 1; // at least today counts as 1

        // Pop all previous prices less than or equal to current price
        // Sum their spans
        while(!st.empty() && st.top().first <= price){
            span += st.top().second; // accumulate spans
            st.pop(); // safe to pop: data already counted in span
        }

        st.push({price, span}); // push today's price and span

        return span; // return span for today
    }
};

/*
Logic & Key Insights:

1. Why store (price, span) in stack instead of just price?
   - So we can **accumulate spans** in O(1) time.
   - Popping elements won’t lose data; their spans are added to today’s span.

2. Edge Cases:
   - First day → stack empty → span = 1
   - Monotonically decreasing prices → span = 1 each day
   - Monotonically increasing prices → stack pops multiple elements → spans grow

3. Why this works efficiently:
   - Each element pushed once, popped once → amortized O(1) per next()
   - Avoids re-scanning all previous prices

4. Span calculation:
   - Initialize span = 1
   - While top of stack ≤ current price → pop and add top’s span
   - Push {price, span} → stack always contains only elements that are “strictly higher” than all previous popped prices

5. Key sight for LeetCode:
   - Using stack of pairs (price, span) is **crucial** for O(1) amortized
   - Pure index-based stack (like stockSpan earlier) works if you store all previous prices in a vector, but this online method is more elegant and efficient

*/

int main() {
    StockSpanner sp; // create object

    cout << sp.next(100) << " "; // returns 1 → first day, span=1
    cout << sp.next(80) << " ";  // returns 1 → 80 < 100
    cout << sp.next(60) << " ";  // returns 1 → 60 < 80
    cout << sp.next(70) << " ";  // returns 2 → 70 > 60, span includes previous day
    cout << sp.next(60) << " ";  // returns 1 → 60 < 70
    cout << sp.next(75) << " ";  // returns 4 → 75 > 60,70,60
    cout << sp.next(85) << " ";  // returns 6 → 85 > 75,60,70,60
    cout << "\n";

    return 0;
}

/*
Expected Output:

1 1 1 2 1 4 6

Explanation:
- Day by day, the stack keeps track of previous relevant prices and their spans.
- Pop operation is safe because popped spans are already included.
- Stack always contains a descending sequence of prices from bottom to top.
- Efficient: amortized O(1) per call.

Other Key Sights:
- Online processing: can call next() repeatedly without needing previous array
- Stack stores only “relevant history”
- Pattern applies to similar "previous greater element with span accumulation" problems
- Each element contributes to at most one pop per future element
*/
