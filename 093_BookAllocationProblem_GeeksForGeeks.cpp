/*   HARD PROBLEM
  
Problem Statement:
   ------------------
   There are N books, each ith book has A[i] number of pages (unsorted).

   Allocate the books to M students so that:
   -> (1) Each book is allocated to exactly one student.
   -> (2) Each student gets at least one book.
   -> (3) Allocation must be in contiguous order (no skipping).

   Objective:
   Minimize the maximum number of pages allocated to any student.

   Return -1 if allocation is not possible.
*/

/*
   Key Cases:
   ----------
   Case 1: M > N → Not enough books for students → return -1.
   Case 2: M = N → Each student gets exactly one book → answer = max(A[i]).
   Case 3: M < N → Needs optimal allocation logic (Binary Search + Greedy).
*/

/*
   Binary Search on Answer:
   ------------------------
   Minimum pages per student = max(A)   (can't go below thickest book)
   Maximum pages per student = sum(A)   (one student gets all books)

   So, we binary search on this range to find the minimum "maximum pages"
   that still allows valid allocation to M students.
*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


// -------------------------------------------------------------
// Helper function to check if a given page limit is a valid solution
// -------------------------------------------------------------
bool isValid(vector<int> &arr, int n, int m, int maximumAllowedPages) {

    int student = 1;  // Start with first student
    int pages = 0;    // Pages currently assigned to that student

    for(int i = 0; i < n; i++) {

        // If a single book has more pages than the allowed limit,
        // then we can’t assign it to any student → invalid configuration
        if(arr[i] > maximumAllowedPages) {
            return false;
        }

        // If current book can be added to the current student without exceeding the limit
        if(pages + arr[i] <= maximumAllowedPages) {
            pages += arr[i]; // Accumulate pages for current student
        }
        else {
            // If not, allocate this book to the next student
            student++;        // Move to next student
            pages = arr[i];   // Start counting from this book

            // No early return — continue to check all books
        }
    }

    // Final check: Did we use more students than allowed?
    return student > m ? false : true;
}

 

// -------------------------------------------------------------
// Main function to allocate books optimally
// -------------------------------------------------------------
int allocateBooks(vector<int> &arr, int n, int m) {

    // Case 1: Impossible to allocate (more students than books)
    if(m > n) {
        return -1;
    }

    // Calculate total number of pages (upper bound for binary search)
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }

    int st = 0;        // Lower bound (min pages per student)
    int end = sum;     // Upper bound (one student gets all books)
    int ans = -1;      // Store the minimum valid answer

    while(st <= end) {
        int mid = st + (end - st) / 2;  // Possible max pages for a student

        if(isValid(arr, n, m, mid)) {
            // If allocation is possible with this limit:
            ans = mid;     // Save this as a possible answer
            end = mid - 1; // Try for a smaller limit
        }
        else {
            // If not possible → need to increase the limit
            st = mid + 1;
        }
    }

    return ans;  // This is the minimum maximum pages a student will get
}



// -------------------------------------------------------------
// Driver code with test case
// -------------------------------------------------------------
int main() {

    vector<int> arr = {2, 1, 3, 4};  // Number of pages in books
    int n = 4;  // Total number of books
    int m = 2;  // Number of students

    // Expected Output: 6
    // Explanation:
    //   One optimal allocation:
    //   Student 1: [2, 1, 3] = 6 pages
    //   Student 2: [4]       = 4 pages
    //   Maximum = 6, and this is the minimum such maximum

    cout << allocateBooks(arr, n, m) << endl;

    return 0;
}
