// Selection Sort Algorithm with Full Explanation

// for sorting in descending order : in line 22, replace '<' with '>' in nums[j]<nums[smallestIdx]

#include<iostream>
#include<vector>
using namespace std;

// Function to perform Selection Sort
vector<int> SelectionSort(vector<int>& nums) {
    size_t n = nums.size(); // Total number of elements in the array

    // Outer loop runs from 0 to n-2 because the last element will automatically be in correct position
    for (size_t i = 0; i <=n - 2; i++) {

        // Assume the current index holds the smallest element
        size_t smallestIdx = i;

        // Inner loop starts from i+1 to n-1 to find the smallest element in the unsorted part
        for (size_t j = i + 1; j < n; j++) {
            // If a smaller element is found, update the smallestIdx
            if (nums[j] < nums[smallestIdx]) {
                smallestIdx = j;
            }
        }

        // Swap the smallest element found with the current element at index i
        if (smallestIdx != i) {
            swap(nums[i], nums[smallestIdx]);
        }
    }

    return nums; // Return the sorted array
}

/*
    📘 SELECTION SORT – MAIN LOGIC AND EXPLANATION

    🔷 What is Selection Sort?
    - Selection Sort is a comparison-based sorting algorithm.
    - It divides the array into two parts: sorted and unsorted.
    - It repeatedly selects the smallest (or largest) element from the unsorted part
      and swaps it with the first unsorted element.

    🔷 Why `i < n - 1` in the outer loop?
    - After placing n-1 elements in their correct positions, the last one is already sorted.
    - So only `n-1` passes are needed to sort an array of size `n`.

    🔷 Why `smallestIdx = i`?
    - At the beginning of each outer loop, we **assume** the current index `i` holds
      the smallest value in the unsorted part.
    - Then we check the rest to verify or update this assumption.

    🔷 Why inner loop runs from `j = i+1` to `j < n`?
    - We search the remaining unsorted elements **after index `i`** to find the smallest one.
    - Comparing earlier elements would be pointless—they are already sorted.

    🔷 What does the inner `if` check?
    - It checks if any element in the unsorted part is **smaller than our current minimum**.
    - If so, we update `smallestIdx`.

    🔷 Why do we swap only if `smallestIdx != i`?
    - To avoid unnecessary swapping if the current element is already the smallest.

    🔷 Time and Space Complexity:
    - Best, Average, Worst Time Complexity: O(n^2)
    - Space Complexity: O(1) – No extra space is used
    - Stable: ❌ Not stable (swaps can disrupt original order)

*/

int main() {
    vector<int> arr = {29, 10, 14, 37, 13};

    // Print original array
    cout << "Before Sorting : \nArray = [ ";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i != (arr.size() - 1)) {
            cout << arr[i] << ", ";
        } else {
            cout << arr[i] << " ]" << endl;
        }
    }

    // Sort the array
    SelectionSort(arr);

    // Print sorted array
    cout << "After Sorting : \nArray = [ ";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i != (arr.size() - 1)) {
            cout << arr[i] << ", ";
        } else {
            cout << arr[i] << " ]" << endl;
        }
    }

    return 0;
}
