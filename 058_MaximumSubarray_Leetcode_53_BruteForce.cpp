// MAIMUM SUBARRAY SUM

// brute force approach

#include<iostream>
#include<climits>
using namespace std;  

int main(){

    int arr[] = {3, -4, 5, 9, -1, 7, -8};

    int n = 7; // size of array

    int maxSum = INT_MIN;

    for (int start = 0; start < n; start++) {
        int currSum = 0;
        for (int end = start; end < n; end++) {
            currSum+=arr[end];
            maxSum = max(currSum, maxSum);
           
        }
    }

    cout<<"Maximum Subarray Sum : "<<maxSum<<endl;

return 0;
}