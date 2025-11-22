/*
    🐄 Aggressive Cows Problem (Binary Search on Answer)

    ❓ Problem Statement:
    You are given `N` stalls located at positions given in an array `arr[]` of size `N`.
    You have `C` cows that need to be placed in these stalls such that **no two cows are placed in the same stall**.
    
    The goal is to place the cows in such a way that the **minimum distance** between any two of them is **as large as possible**.

    🔍 Your task is to find the **maximum possible minimum distance** between any two cows.

    ✅ Constraints:
    - 2 ≤ C ≤ N ≤ 10^5
    - Stall positions are distinct and in any order.
*/

#include<iostream>
#include<vector>
#include<algorithm> // for sort()
using namespace std;

// -----------------------------------------------------
// ✅ Function to check if it's possible to place 'C' cows
//    such that minimum distance between any two is at least 'minAllowedDistance'
// -----------------------------------------------------
bool isPossible(vector<int> &arr, int N, int C, int minAllowedDistance) {
    int cows = 1;                      // Place first cow in the first stall
    int lastStallPosition = arr[0];   // Track where the last cow was placed

    // Try placing the rest of the cows greedily
    for (int i = 1; i < N; i++) {
        // If the current stall is at least 'minAllowedDistance' away from last placed cow
        if (arr[i] - lastStallPosition >= minAllowedDistance) {
            cows++;                         // Place another cow
            lastStallPosition = arr[i];    // Update the last placed cow's stall
        }

        // If we managed to place all cows, this distance is valid
        if (cows == C) return true;
    }

    // Not enough distance to place all cows
    return false;
}

// -----------------------------------------------------
// ✅ Function to perform Binary Search on the distance
//    to find the maximum possible minimum distance
// -----------------------------------------------------
int getDistance(vector<int> &arr, int N, int C) {
    // Sort stall positions to place cows in increasing order
    sort(arr.begin(), arr.end());

    // Binary Search boundaries:
    // 'st' = minimum possible distance = 1
    // 'end' = maximum possible distance = last stall - first stall
    int st = 1;
    int end = arr[N - 1] - arr[0];
    int ans = -1;

    // Binary Search: try different distances
    while (st <= end) {
        int mid = st + (end - st) / 2;  // This is the distance we're testing

        // Check if it's possible to place all cows with at least 'mid' distance apart
        if (isPossible(arr, N, C, mid)) {
            ans = mid;         // This is a valid answer, store it
            st = mid + 1;      // Try for a bigger distance (right half)
        } else {
            end = mid - 1;     // Too big, try smaller distance (left half)
        }
    }

    // 'ans' will store the maximum minimum distance found
    return ans;
}

// -----------------------------------------------------
// ✅ Driver Code
// -----------------------------------------------------
int main() {
    int N = 5; // Number of stalls
    int C = 3; // Number of cows to place

    vector<int> arr = {1, 2, 4, 8, 9}; // Stall positions (unsorted is fine)

    // Output the maximum minimum distance between cows
    cout << getDistance(arr, N, C) << endl;

    return 0;
}
