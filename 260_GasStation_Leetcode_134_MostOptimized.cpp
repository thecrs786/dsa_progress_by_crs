/*
LeetCode 134 - Gas Station

QUESTION (in brief):
You are given two integer arrays 'gas' and 'cost' of length n, representing a circular route with n gas stations.
- 'gas[i]' is the amount of gas at station i.
- 'cost[i]' is the amount of gas needed to travel from station i to the next station.

You need to find the starting station's index from which you can travel the entire circuit without running out of gas.
If it's not possible, return -1.

IMPORTANT NOTE:
If a solution exists, it is guaranteed to be unique.

EXAMPLES:
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation: Starting at station 3 allows completing the circuit.

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation: No station allows completing the journey.

CONSTRAINTS:
1 <= gas.length == cost.length <= 10^5
0 <= gas[i], cost[i] <= 10^4

APPROACH USED:
Greedy approach with single traversal
- First, check if total gas is enough to cover total cost.
- Then, track the current gas balance while iterating once.
- If current gas balance drops below zero, reset the start position and current gas.

TIME COMPLEXITY:
✔ O(n), where n is the number of stations.
Each station is processed once.

SPACE COMPLEXITY:
✔ O(1), constant extra space is used.

IS THIS THE MOST OPTIMAL SOLUTION?
✅ Yes. This is the best possible solution using linear time and constant space.

WILL IT BE ACCEPTED BY LEETCODE?
✅ It will be accepted for all inputs without TLE (Time Limit Exceeded) or MLE (Memory Limit Exceeded).
*/

/*
C++ STL – accumulate()

WHAT IT DOES:
✔ accumulate() is a function from the <numeric> header.
✔ It calculates the sum (or any operation) of elements in a range.
✔ By default, it sums up the elements starting from an initial value.

HEADER REQUIRED:
#include <numeric>

SYNTAX:
accumulate(start_iterator, end_iterator, initial_value);

- start_iterator → beginning of the range
- end_iterator → end of the range (one past the last element)
- initial_value → starting point for the accumulation

EXAMPLES:

1. Sum of elements in a vector
2. Using accumulate with different operations (like multiplication, custom functions)
3. Applying it to count elements or perform advanced operations

TIME COMPLEXITY:
✔ O(n), where n is the number of elements between start and end.

SPACE COMPLEXITY:
✔ O(1), uses constant extra space.
*/

/*-------------------- CODE STARTS HERE --------------------*/
#include <iostream>
#include <vector>
#include<numeric> // required for accumulate.
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        
        // Step 1: Calculate total gas and total cost across all stations
        // STEP 2: If total gas is less than total cost, return -1 (impossible to complete
        if(accumulate(gas.begin(), gas.end(),0)<accumulate(cost.begin(), cost.end(),0)) return -1;
        // accumulate(start iterator, end iterator, initial sum)
        /*
        // Step 1: Calculate total gas and total cost across all station
        int sumgas = 0;
        int sumcost = 0;
        for(int i = 0; i < gas.size(); i++){
            sumgas += gas[i];
            sumcost += cost[i];
        

        // Step 2: If total gas is less than total cost, return -1 (impossible to complete circuit)
        if(sumcost > sumgas) return -1;
        */

        int start = 0;   // Potential starting station index
        int currGas = 0; // Current gas balance while traversing

        // Step 3: Traverse the stations once to find the valid start point
        for(int i = 0; i < gas.size(); i++){
            currGas += gas[i] - cost[i]; // Update current gas balance
            if(currGas < 0){             // If at any point gas balance drops below 0
                start = i + 1;          // Move start to the next station
                currGas = 0;            // Reset current gas balance
            }
        }

        return start; // Return the valid starting station index
    }
};

/*---------------- LOGIC & EXPLANATION -------------------*/

/*
WHY RETURN -1 BASED ON COMPARISON?
✔ We return -1 if total gas is less than total cost.
✔ This ensures that even if some stations have surplus gas, it's not enough overall to complete the journey.

WHAT DOES THAT COMPARISON ENSURE?
✔ The journey is only possible if the total available gas is at least equal to the total cost.
✔ Otherwise, even if one station has extra gas, the circuit can't be completed.

WHY DON'T WE USE NESTED LOOPS?
✔ Nested loops would check all possible starting points by simulating the journey for each → O(n^2).
✔ This is inefficient and would cause TLE for large inputs.
✔ The greedy approach eliminates unnecessary checks by identifying when a starting point fails.

WHY AREN’T WE MOVING CIRCULARLY IN THE CODE?
✔ We simulate the circular nature with a single pass.
✔ The problem guarantees that if a solution exists, it will be unique.
✔ Once a section fails (currGas < 0), the next station becomes the only valid candidate → no need to check other possibilities.

HOW CAN WE ENSURE WITHOUT TRAVELING BACK TO START?
✔ The key observation is that if the accumulated gas drops below zero at any point, all stations between 'start' and 'i' can't be starting points.
✔ Therefore, we skip them all by moving 'start' to 'i+1'.

WHY ARE WE ELIMINATING ALL ELEMENTS IN BETWEEN IF ONE INDEX RESULTS IN NEGATIVE currGas?
✔ Because the net gas deficit means you can't reach 'i+1' from 'start'.
✔ All intermediate starts would have the same or worse deficit → eliminating them ensures efficiency.

✔ This greedy observation allows solving the problem in linear time.

WORKING EXAMPLE:
gas = [1,2,3,4,5]
cost = [3,4,5,1,2]

Total gas = 15
Total cost = 15 → journey is possible

Traverse:
i=0: currGas = 1-3 = -2 → move start to 1
i=1: currGas = 2-4 = -2 → move start to 2
i=2: currGas = 3-5 = -2 → move start to 3
i=3: currGas = 4-1 = 3 → currGas = 3
i=4: currGas = 3+5-2 = 6 → currGas = 6

Return start = 3 → correct answer!

✔ Efficient and guarantees correctness.
*/

/*-------------------- MAIN FUNCTION --------------------*/
int main() {
    Solution sol;

    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    int result = sol.canCompleteCircuit(gas, cost);

    cout << "Starting index to complete circuit is: " << result << endl;

    return 0;
}

/*------------------ IMPORTANT DETAILS ------------------*/

/*
✅ KEY INSIGHTS:
- The total amount of gas must cover the total cost → this is the first feasibility check.
- If at any point the gas balance drops below zero, all stations up to that point cannot be starting points → greedy reset.
- We don’t need circular traversal because resetting the start point ensures we only find the unique valid index.

⚠ WARNINGS:
- Do not check 'sumcost >= sumgas' because equality is a valid case → only 'sumcost > sumgas' should return -1.
- Avoid nested loops → leads to inefficient solutions and TLE.
- Only use linear iteration with proper reasoning about station elimination.

📌 SIMILAR QUESTIONS:
- Find if a path through nodes with weights is feasible
- Circular array problems like "Rotate Array" or "Find Maximum Sum Subarray"
- Problems using greedy reset strategies for failed sequences

🔑 APPROACH COMPARISON:
- Brute force → O(n^2), not acceptable for large input sizes
- Optimized greedy → O(n), using gas balance and start reset
- This approach is a textbook example of how to solve problems where cumulative conditions determine feasibility.
*/
