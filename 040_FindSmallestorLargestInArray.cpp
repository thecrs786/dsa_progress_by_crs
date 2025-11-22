// FIND SMALLEST/LARGEST element in an array

#include<iostream>
#include <climits>  // REQUIRED FOR INT_MAX AND INT_MIN
using namespace std;  

// smallest integer = INT_MIN in c++ --> any integer would be greater than it
// greatest integer = INT_MAX in c++ --> any integer would be smaller than it

int getsmallest(int arr[], int size) {
    int smallest = INT_MAX;  // Initialize with the first element
    for(int i = 0; i < size; i++) {  // Correct loop condition
        if (smallest > arr[i]) {  // Correct comparison
            smallest = arr[i];
        }
    }
    return smallest;
}


/* or without using infinty

int getsmallest(int arr[], int size) {
    int smallest = arr[0];  // Initialize with the first element
    for(int i = 1; i < size; i++) {  // Correct loop condition
        if (smallest > arr[i]) {  // Correct comparison
            smallest = arr[i];
        }
    }
    return smallest;
}

*/

int getgreatest(int arr[], int size) {
    int greatest = INT_MIN;  // Initialize with the first element
    for(int i = 0; i < size; i++) {  // Correct loop condition
        if (greatest < arr[i]) {  // Correct comparison
            greatest = arr[i];
        }
    }
    return greatest;
}


/* or without using -infinty

int getgreatest(int arr[], int size) {
    int greatest = arr[0];  // Initialize with the first element
    for(int i = 1; i < size; i++) {  // Correct loop condition
        if (greatest < arr[i]) {  // Correct comparison
            greatest = arr[i];
        }
    }
    return greatest;
}

*/

int main() {
    int arr[] = {10, 98, 5, 7, 90, 1, 15, 6};
    int size = sizeof(arr) / sizeof(arr[0]);  // Get array size

    cout << "Smallest : "<<getsmallest(arr, size) << endl;
    cout <<"Greatest : "<<getgreatest(arr, size) << endl;

    return 0;
}
