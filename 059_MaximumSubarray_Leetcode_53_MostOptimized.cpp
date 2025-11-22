// KADANE'S ALGORITHM -> most optimised

#include<iostream>
#include<climits>
using namespace std;  

int main(){

    int arr[] = {3, -4, 5, 9, -1, 7, -8};

    int n = 7; // size of array

    int maxSum = INT_MIN;
    int currSum = 0;

    for(int val : arr){
        currSum+=val;
        maxSum=max(currSum,maxSum);
        if(currSum<0){currSum=0;}
    }

    cout<<"Maximum Subarray Sum : "<<maxSum<<endl;

return 0;
}