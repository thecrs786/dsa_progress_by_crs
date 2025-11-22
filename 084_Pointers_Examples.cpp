#include<iostream>
using namespace std;

int main(){
    int arr[] = {10, 20, 30, 40};
    int *ptr = arr; // arr refers to address of arr[0], so address of arr[0] is passed in the pointer
    
    // since arr = pointer of 0th index of array
    // ptr is a pointer variable
    // so now, ptr has the memory address of arr[0]
    // which means ptr and arr both would work same

    cout<<*(ptr+1)<<endl; // *(arr+1) = arr[1] = 20
    cout<<*(ptr+3)<<endl; // *(arr+3) = arr[3] = 40

    ptr++;

    cout<<*ptr<<endl; // ptr incrementedd by one block, initially ptr referred to arr[0]
                      // but now ptr refers to arr[1]
                    // so *ptr = *(arr+1) = arr[1] = 20
    ptr--; // restoring to original 

    cout<<(ptr==arr)<<endl; // since they both stores the same memory address, OUTPUT -> true i.e 1

    return 0;
}
