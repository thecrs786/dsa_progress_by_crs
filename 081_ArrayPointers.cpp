// Array Pointers

#include <iostream>
using namespace std;

int main() {

    // When we create an array, the variable name is actually a pointer to the 0th index.
    // That means: arr == &arr[0]
    // It is a constant pointer, i.e cannot be changed like normal pointers
    // So, the array name itself refers to the memory address of arr[0]

    int arr[] = {15, 14, 13, 12, 11};

    cout << (arr == &arr[0]) << endl; // IMPORTANT: This will print 1 (true)

    // The array name 'arr' is the address of the 0th index

    cout << *arr << endl;     // Value at arr[0]
    cout << &arr[0] << endl;  // Address of arr[0]
    cout << arr << endl;      // Also address of arr[0]

    // arr = &arr[2];  will throw error, since this is a constant pointer and cannot be modified

    // Accessing other elements of the array using pointer arithmetic
    cout << arr + 1 << endl;  // Address of arr[1]
    cout << arr + 2 << endl << endl;  // Address of arr[2]

    // NOTE -> In pointer arithmetic, adding 1 to a pointer moves it to the
    //next memory block of its data type (not just +1 byte).
    //Since arrays are stored in contiguous memory, 
    //this allows seamless traversal using pointer increments.

    // DEREFERENCING POINTERS
    // Accessing values using pointer arithmetic

    cout << "Accessing values using pointer (arr): \nArray: [";
    cout << *arr << ", ";
    cout << *(arr + 1) << ", ";
    cout << *(arr + 2) << ", ";
    cout << *(arr + 3) << ", ";
    cout << *(arr + 4) << "]" << endl << endl;

    // Notes:
    // -> arr + n gives address of nth index
    // -> *(arr + n) gives value at nth index
    // -> *arr + n means: value at arr[0] + n (not same as *(arr + n))

    cout << "Accessing values using indexing: \nArray: [";
    cout << arr[0] << ", ";
    cout << arr[1] << ", ";
    cout << arr[2] << ", ";
    cout << arr[3] << ", ";
    cout << arr[4] << "]" << endl << endl;

    // Pointer-Index Equivalence:
    // &arr[n] == arr + n
    // arr[n]  == *(arr + n)

    // Verifying equivalence:
    for (int i = 0; i < 5; i++) {
        if (&arr[i] != arr + i || arr[i] != *(arr + i)) {
            cout << "False" << endl; // Will not be printed
        }
    }

    return 0;
}
