//  INSERTION SORT

// for sorting in descendion order : in line 18, replace '>' with '<' in nums[prev]>curr

#include<iostream>
#include<vector>
using namespace std;

vector<int> InsertionSort(vector<int> &nums) {
    int n = nums.size();  // Get the number of elements in the vector

    // Outer loop runs from the 1st element to the last (0th is considered already sorted)
    for(int i = 1; i < n; i++) {
        int curr = nums[i];      // Current element to be inserted into sorted part
        int prev = i - 1;        // Index of the last sorted element

        // Shift elements of the sorted segment forward if they are greater than curr
        while(prev >= 0 && nums[prev] > curr) {  // nums[prev]<curr for descending sorting
            nums[prev + 1] = nums[prev];  // Shift larger element to the right
            prev--;                       // Move backward in the sorted segment
        }

        nums[prev + 1] = curr;  // Insert the current element at its correct position
    }

    return nums;
}

/*
------------------------- Insertion Sort Explanation --------------------------

Insertion Sort is a comparison-based, in-place, stable sorting algorithm.

🔷 Main Idea:
At each iteration, the algorithm picks one element (called `curr`) and inserts it 
into its correct position among the already sorted elements (to its left).

For example, in the array: [29, 10, 14, 37, 13]
- Initially, [29] is sorted.
- Pick 10, compare with 29, shift 29 → [10, 29]
- Pick 14, compare with 29 → shift → [10, 14, 29]
- Pick 37 → no shift needed → [10, 14, 29, 37]
- Pick 13 → shift 37, 29 → [10, 13, 14, 29, 37]

🔷 Why loop starts from i = 1:
Because we assume the 0th element is already "sorted".
We insert elements one by one into the sorted sub-array.

🔷 Why `prev = i-1`:
We compare the current element with elements to its left (i.e., the sorted part).
So `prev` helps us iterate backward from the current position.

🔷 Why `while(prev >= 0 && nums[prev] > curr)`:
We keep shifting elements to the right as long as they are greater than `curr`.
This makes space for `curr` to be inserted in its correct place.

🔷 Why `nums[prev + 1] = curr`:
After all bigger elements are shifted, we place `curr` just after the smaller element.

🔷 Time Complexity:
- Best Case (already sorted): O(n)
- Worst Case (reverse sorted): O(n^2)
- Space: O(1) (in-place)

Insertion sort is efficient for small datasets or nearly sorted arrays.

-------------------------------------------------------------------------------
*/

int main() {
    vector<int> arr = {29, 10, 14, 37, 13};  // Unsorted array

    // Print original array
    cout << "Before Sorting:\nArray = [ ";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i != (arr.size() - 1)) {
            cout << arr[i] << ", ";
        } else {
            cout << arr[i] << " ]" << endl;
        }
    }

    // Sort the array using insertion sort
    InsertionSort(arr);

    // Print sorted array
    cout << "After Sorting:\nArray = [ ";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i != (arr.size() - 1)) {
            cout << arr[i] << ", ";
        } else {
            cout << arr[i] << " ]" << endl;
        }
    }

    return 0;
}
