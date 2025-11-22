// Bubble Sort Algorithm with Explanation

// for sdescending order : in line 21 replace '>' with '<' in nums[j]>nums[j+1]

#include<iostream>
#include<vector>
using namespace std;

// Function to perform Bubble Sort
vector<int> BubbleSort(vector<int>& nums) {
    size_t size = nums.size(); // Total number of elements in the array

    // Outer loop runs (n - 1) times because after n-1 passes, array is sorted
    for (size_t i = 0; i < size - 1; i++) {
        bool isSwap = false; // to avoid more operations if array already sorted before all iterations

        // Inner loop goes up to (n - i - 1)
        // Because after each pass, the largest element "bubbles up" to the correct position at the end,
        // so no need to check the last i elements—they're already sorted
        for (size_t j = 0; j < size - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                // Swap if the left element is greater than the right
                swap(nums[j], nums[j + 1]);
                isSwap = true; // A swap has occurred, so the array may not be sorted yet.
                               // If no swap occurs in an entire pass, the array is already sorted.

            }
        }

        if(!isSwap)return nums;
    }

    return nums; // Return the sorted array
}

/*  LOOP LOGIC :

Why  n-1  Iterations in the Outer Loop:
In Bubble Sort, we need a maximum of n-1 passes (where n is the number of elements) to fully sort the array.
This is because, in each pass, the largest unsorted element "bubbles up" to its correct position at the end of the array by repeated swapping.
After the first pass, the largest element is sorted and placed at the last index.
After the second pass, the second-largest is placed at the second-last index, and so on.
So, after n-1 such passes, all elements are in their correct position—hence the outer loop runs n-1 times.

 Why  n-i-1  Iterations in the Inner Loop:
In each outer loop iteration i, the last i elements are already sorted and in their correct positions.
So there’s no need to compare or swap them again in the current pass.
Therefore, the inner loop only needs to run up to index n-i-2, which means n-i-1 comparisons/swaps are done.
This reduces the search space with each pass, making the algorithm more efficient.
*/

int main() {
    // Example array
    vector<int> arr = {1, 12, 78, 5, 54, 6, 98, 44, 3, 14, 46, 2, 55};

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
    BubbleSort(arr);

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
