#include <iostream>
using namespace std;

int main() {

    int a = 10;
    int b = 5;

    cout << "Address of a: " << &a << endl; // &a gives the memory address of variable 'a' (in hexadecimal form)

    // A pointer is a special variable that stores the address of another variable.

    // Pointer declaration and initialization:
    int *ptr = &a; // 'int' indicates that the pointer will point to an int type variable.
                   // '*' before the variable name indicates that 'ptr' is a pointer.
                   // 'ptr' is storing the address of variable 'a'.

    // int* ptr and int *ptr both are same.

    cout << "Address of a (using pointer): " << ptr << endl;

    // int *ptr_ = b; // ❌ This is invalid because 'b' is an int, not an address.

    // Ways to print the value of 'a':

    cout << "Value of a: " << a << endl;         // Direct access to value stored in 'a'
    cout << "Value of a (via using address of a ): " << *(&a) << endl;         // value stord at address of 'a'
    cout << "Value of a (via pointer): " << *ptr << endl; // Dereferencing the pointer gives the value at that address

    // Explanation: '*ptr' means "value at the memory address stored in ptr"
    // So, '*ptr == a' will be true

    cout << "*ptr == a is " << (*ptr == a) << " which means true." << endl;

    // Ways to get the address of 'a':

    // 1.

    cout << "Address of a (using &a): " << &a << endl;     // Method 1: Using '&a' directly
    
    // 2.

    cout << "Address of a (stored in pointer): " << ptr << endl; // Method 2: Pointer 'ptr' already stores address of 'a'

    // 3 (important) -> use of &(*ptr)

    cout << "Address of a (using &(*ptr)): " << &(*ptr) << endl; // Method 3: Dereferencing ptr and then taking address again gives the original address

    // Adress of pointer

    cout<<"Address of pointer ptr using (&ptr) = "<<&ptr<<endl;


    return 0;
}
