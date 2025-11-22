/*
    Painter's Partition Problem  (Same as Book Allocation Problem)

    Problem:
    Given N boards with lengths stored in an array,
    and M painters — each takes 1 unit time to paint 1 unit of board length.

    Goal:
    Allocate contiguous boards to each painter such that the time
    to paint all boards is minimized.

    Constraint:
    - Each painter must paint at least one board
    - Boards assigned must be contiguous
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ✅ Helper Function to check if painting can be done within 'maxAllowedTime'
bool isPossible(vector<int>& arr, int n, int m, int maxAllowedTime) {
    int painters = 1;
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > maxAllowedTime)
            return false; // A single board can't exceed allowed time

        if (time + arr[i] <= maxAllowedTime) {
            time += arr[i]; // Add to current painter's work
        } else {
            painters++;        // Assign to next painter
            time = arr[i];     // Start fresh for next painter

            if (painters > m)
                return false; // Too many painters needed
        }
    }
    return true;
}

// ✅ Main function to find minimum time using binary search
int minTimeToPaint(vector<int>& arr, int n, int m) {
    if (m > n)
        return -1; // More painters than boards — invalid

    int sum = 0;
    int maxVal = INT_MIN;

    for (int i = 0; i < n; i++) {
        maxVal = max(arr[i], maxVal);
        sum += arr[i];
    }

    int st = maxVal;  // Lower bound = max board length
    int end = sum;    // Upper bound = sum of all board lengths
    int ans = -1;

    while (st <= end) {
        int mid = st + (end - st) / 2;

        if (isPossible(arr, n, m, mid)) {
            ans = mid;      // Valid — try smaller time
            end = mid - 1;
        } else {
            st = mid + 1;   // Invalid — need more time
        }
    }

    return ans;
}

// ✅ Driver Code
int main() {
    vector<int> arr = {40, 30, 10, 20};
    int n = arr.size();
    int m = 2;

    cout << "Minimum time to paint all boards: " << minTimeToPaint(arr, n, m) << endl;

    return 0;
}
