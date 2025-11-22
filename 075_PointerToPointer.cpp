// Pointer to Pointer

#include <iostream>
using namespace std;

int main() {

    int a = 10;

    int* ptr = &a; // 'ptr' is a pointer to int and stores the address of variable 'a'

    int** ptr_ = &ptr; // 'ptr_' is a pointer to a pointer, storing the address of 'ptr'

    // Printing values using pointer-to-pointer

    cout << *ptr_ << endl;       // Prints the address stored in ptr_, which is the address of ptr
    cout << **ptr_ << endl;      // Prints the value at the address ptr_ points to, i.e., value of 'a'

    // Printing the value of 'a' in different ways:
    cout << "Values of a:\n" << endl;

    cout << "a (direct access) = " << a << endl;           // Direct access of variable a
    cout<<"a (value at address of a) = "<<*(&a)<<endl;     // value at address of a 
    cout << "a (via *ptr) = " << *ptr << endl;             // Dereferencing ptr gives value of a
    cout << "a (via **ptr_) = " << **ptr_ << endl << "\n"; // Double dereferencing ptr_ gives value of a
    cout << "a (via *(*ptr_)) = " << *(*ptr_) << endl << "\n"; // Double dereferencing ptr_ gives value of a

    // Printing the address of 'a' in multiple forms:
    cout << "Address of a:\n" << endl;

    cout << "Address of a (via &(**ptr_)) = " << &(**ptr_) << endl; // Address of value pointed by ptr_
    cout << "Address of a (via ptr) = " << ptr << endl;             // ptr directly holds address of a
    cout << "Address of a (via &a) = " << &a << endl;               // &a gives address of variable a
    cout << "Address of a (via &(*ptr)) = " << &(*ptr) << endl << "\n"; // Dereferencing and then referencing again gives address of a

    // Printing the address of 'ptr':
    cout << "Address of ptr:\n" << endl;

    cout << "Address of ptr (via &ptr) = " << &ptr << endl;         // &ptr gives address of pointer ptr
    cout << "Address of ptr (via ptr_) = " << ptr_ << endl;         // ptr_ stores address of ptr
    cout << "Address of ptr (via &(*ptr_)) = " << &(*ptr_) << endl << "\n"; // Dereferencing and referencing again gives address of ptr

    // Printing the address of 'ptr_':
    cout << "Address of ptr_:\n" << endl;

    cout << "Address of ptr_ (via &ptr_) = " << &ptr_ << endl;      // &ptr_ gives address of pointer-to-pointer ptr_

    return 0;
}
