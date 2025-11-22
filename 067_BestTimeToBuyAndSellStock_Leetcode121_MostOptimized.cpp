// Leetcode 121: Best Time to Buy and Sell Stock
// Optimized Solution: O(N) Time, O(1) Space
// We assume each day as the "selling day" and look for the best "buy day" before it.

#include <iostream>
#include <vector>
#include <algorithm>  // for min and max
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;              // Stores the maximum profit found so far
        int bestBuy = prices[0];        // Tracks the lowest price (best day to buy)
        int profit = 0;

        for (size_t i = 1; i < prices.size(); i++) {
            bestBuy = min(bestBuy, prices[i - 1]); // update bestBuy if a lower price is found
            profit = prices[i] - bestBuy;          // calculate today's profit if sold
            maxProfit = max(maxProfit, profit);    // update maxProfit if this profit is better
        }

        return maxProfit;
    }
};

int main() {
    // Example:
    // Prices on each day = [7, 1, 5, 3, 6, 4]
    // Buy on day 2 (price = 1), sell on day 5 (price = 6) → profit = 5
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    Solution sol;
    int result = sol.maxProfit(prices);
    cout << "Maximum Profit: " << result << endl; // Expected Output: 5

    return 0;
}
