// PASS BY REFERENCE: Two Ways:
// 1) Using Pointers
// 2) Using Reference Variables

#include <iostream>
using namespace std;

// Function to modify the value using a pointer
int changeValue(int* ptr) { // a pointer variable is used as parameter
    *ptr += 10;     // Dereferencing the pointer to modify the actual value
    return *ptr;    // Returning the updated value
}

int main() {
    int x = 5;

    // Passing the address of 'x' to the function
    cout << "Returned value: " << changeValue(&x) << endl;  // since the parameter is a pointer, we must pass an address to it
    cout << "Value of x after function call: " << x << endl;

    // Explanation:
    // This time, no copy of the variable was created.
    // The actual memory address of 'x' was passed to the function.
    // The function directly modified the original value through the pointer.
    // This is known as Pass by Reference using Pointers.

    return 0;
}
