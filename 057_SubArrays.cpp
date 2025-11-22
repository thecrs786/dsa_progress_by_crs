// SUBARRAYS

#include<iostream>
using namespace std;

/*
A subarray is a contiguous part of an array.
That means it’s a slice of elements that appear next to 
each other in the original array — no skipping allowed.
*/

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    /*
    Possible subarrays:

    LENGTH 1 : [1], [2], [3], [4], [5]       --> 5
    LENGTH 2 : [1, 2], [2, 3], [3, 4], [4, 5] --> 4
    LENGTH 3 : [1, 2, 3], [2, 3, 4], [3, 4, 5]--> 3
    LENGTH 4 : [1, 2, 3, 4], [2, 3, 4, 5]     --> 2
    LENGTH 5 : [1, 2, 3, 4, 5]                --> 1

    TOTAL = 5 + 4 + 3 + 2 + 1 = 15
    
    Formula: n*(n+1)/2
    */

    int n = 5; // size of array

    // Print all possible subarrays
    for (int start = 0; start < n; start++) {
        for (int end = start; end < n; end++) {
            cout << "[";
            for (int i = start; i <=end; i++) {
                cout << arr[i];
                if (i != end) cout << ", ";
            }
            cout << "] ";
        }
        cout << endl;
    }

    return 0;
}
