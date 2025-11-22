#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
Problem Name: Stock Span Problem (LeetCode-style/Classic)

Problem Description:
Given the price of a stock for N consecutive days in an array 'stock', 
for each day, calculate the "span" of the stock's price.
- The span of the stock’s price on a given day i is defined as the maximum number of consecutive days 
  just before the given day, including the current day, for which the price of the stock was less than 
  or equal to its price on day i.

Examples:
Input:  stock = [100, 80, 60, 70, 60, 75, 85]
Output: span  = [1, 1, 1, 2, 1, 4, 6]
Explanation: 
Day 1: 100 → no previous higher → span=1
Day 2: 80  → no previous higher → span=1
Day 3: 60  → no previous higher → span=1
Day 4: 70  → previous 60 < 70, but 80 > 70 → span=2
Day 5: 60  → no previous higher → span=1
Day 6: 75  → previous 60, 70, 60 < 75, 80 > 75 → span=4
Day 7: 85  → previous 75, 60, 70, 60 < 85, 100 > 85 → span=6

Solution Method: Stack-based approach
Approach Used:
1. Redefine the question in terms of previous greater elements.
2. Instead of scanning all previous days, use a stack to keep track of indices of "previous higher prices".
3. For each day i:
   a. Pop all indices from stack where stock[stack.top()] <= stock[i]
   b. If stack is empty → span = i+1 (all previous prices smaller)
   c. Else → span = i - stack.top() (distance to previous higher price)
   d. Push i to stack
4. This efficiently calculates the span without re-scanning the array each time.

Time Complexity: O(N) amortized
Space Complexity: O(N) (for stack storing indices)
Is it optimal/acceptable: ✅ Yes, this is the standard and optimal solution.
Most Optimized: ✅ Yes, we use stack to compress history and avoid O(N^2) brute-force.

*/

vector<int> stockSpan(vector<int> &stock) {
    vector<int> ans;      // stores the final span results
    int n = stock.size(); // number of days
    stack<int> st;        // stack stores indices of previous days with stock prices

    for (int i = 0; i < n; i++) {

        // Pop all previous indices where price <= current price
        while (!st.empty() && stock[st.top()] <= stock[i]) {
            st.pop();
        }

        // If stack is empty, all previous prices are smaller
        if (st.empty()) {
            ans.push_back(i + 1); // i+1 because span includes current day
        } else {
            // Distance to previous higher price
            ans.push_back(i - st.top());
        }

        st.push(i); // store current day index
    }

    return ans; // return computed spans
}

/*
Logic & Key Insights:

1. Why storing indices instead of prices?
   - We need the distance between current day and previous higher price → using indices makes calculation direct: span = i - st.top()
   
2. Why popping from stack is safe?
   - Once we pop an element, its span contribution is already counted in previous iterations.
   - It will never be needed again because all elements it dominated are already covered by span calculation.
   - This is why we don't "lose" information for future days.

3. Why span = i+1 if stack empty?
   - No previous higher price exists → span covers all previous days + current day.

4. Edge cases handled automatically:
   - First day → stack empty → span=1
   - All prices decreasing → stack never pops → spans = 1 for each
   - All prices increasing → stack pops multiple → spans grow

5. Efficiency:
   - Each element pushed once, popped once → O(N) amortized
   - Stack ensures we never revisit elements unnecessarily
*/

int main() {
    // Example 1
    vector<int> stock1 = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span1 = stockSpan(stock1);

    cout << "Stock prices: ";
    for (int p : stock1) cout << p << " "; // display stock prices
    cout << "\nSpans:       ";
    for (int s : span1) cout << s << " ";  // display corresponding spans
    cout << "\n\n";

    // Example 2
    vector<int> stock2 = {10, 4, 5, 90, 120, 80};
    vector<int> span2 = stockSpan(stock2);

    cout << "Stock prices: ";
    for (int p : stock2) cout << p << " ";
    cout << "\nSpans:       ";
    for (int s : span2) cout << s << " ";
    cout << "\n";

    return 0;
}

/*
Expected Output:

Stock prices: 100 80 60 70 60 75 85
Spans:       1 1 1 2 1 4 6

Stock prices: 10 4 5 90 120 80
Spans:       1 1 2 4 5 1

Other Key Sights:
- Stack stores "only relevant history" → we pop dominated elements
- The algorithm efficiently compresses previous comparisons into the stack
- No brute-force scanning → optimized to O(N)
- This pattern can be adapted to similar "previous greater/smaller" problems
- Important to remember: always store index, not value, for span-type problems
*/
