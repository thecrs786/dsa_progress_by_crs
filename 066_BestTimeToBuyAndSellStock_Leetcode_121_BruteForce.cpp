// NOT FOR SUBMISSION -> WIL LEAD TO TLE

// 📘 Leetcode 121: Best Time to Buy and Sell Stock
// 🔍 Problem:
// Given an array `prices[]` where prices[i] is the stock price on day i.
// You are allowed to buy once and sell once (sell must happen after buy).
// Return the maximum profit. If no profit is possible, return 0.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;

        for(size_t i = 0; i < prices.size() - 1; i++) {
            for(size_t j = i + 1; j < prices.size(); j++) {
                int profit = prices[j] - prices[i];
                maxProfit = max(maxProfit, profit);
            }
        }
    

        return maxProfit;
    }
};

//size_t is an unsigned integer type used to represent sizes and indices.
//It is the return type of .size() in STL containers like vector, string, etc.
//Prevents signed/unsigned comparison warnings in loops.

int main() {
    // 🧪 Example Input
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    // 🚀 Create object and call method
    Solution obj;
    int result = obj.maxProfit(prices);

    // 📤 Output
    cout << "\nMaximum Profit: " << result << "\n"<<endl;

    return 0;
}

/*
Expected Output:
Maximum Profit: 5

Explanation:
Buy on Day 2 (price = 1), Sell on Day 5 (price = 6), Profit = 6 - 1 = 5
All possible profit combinations are checked, and max is returned.
*/
