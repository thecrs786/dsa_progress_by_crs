// WAF TO SWAP THE MAX AND MIN NUMBER OF AN ARRAY

#include<iostream>
using namespace std;

void swapMaxMin(int arr[], int size){
    if(size == 0) return;

    int maxIndex = 0;
    int minIndex = 0;

    for(int i = 1; i < size; i++){
        if(arr[i] > arr[maxIndex]){
            maxIndex = i;
        }
        if(arr[i] < arr[minIndex]){
            minIndex = i;
        }
    }

    // Swap the elements
    int temp = arr[maxIndex];
    arr[maxIndex] = arr[minIndex];
    arr[minIndex] = temp;
}

void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main(){
    int arr1[] = {4, 9, 2, 1, 7, 6, 3};  // min = 1, max = 9
    int size = sizeof(arr1)/sizeof(arr1[0]);

    cout << "Before swap: ";
    printArray(arr1, size);

    swapMaxMin(arr1, size);

    cout << "After swap : ";
    printArray(arr1, size);

    return 0;
}
