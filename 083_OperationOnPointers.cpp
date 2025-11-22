#include<iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 10;

    int *p = &a;
    int *q = &b;

    // NOTE: Addition of two pointers is not allowed in C++
    // ONLY SUBTRACTION AND COMPARISON ARE ALLOWED

    // Subtraction is allowed only if both pointers point to the same data type
    // The result of (p - q) gives the number of elements (not bytes) between them
    // Byte distance = (p - q) * sizeof(data type)

    cout << p - q << endl; // e.g., -1 means p is one element *behind* q in memory

    // INTERPRETATION:
    // If p - q = -n, then p is located 'n' elements behind q in memory
    // Pointer arithmetic respects the data type size (int = 4 bytes, char = 1 byte, etc.)

    // COMPARISONS BETWEEN POINTERS:
    // These comparisons check the relative memory positions (addresses)
    cout << (q > p) << endl;   // true: q is ahead of p
    cout << (p > q) << endl;   // false
    cout << (q >= p) << endl;  // true
    cout << (p <= q) << endl;  // true
    cout << (p == q) << endl;  // false: different variables
    cout << (p != q) << endl;  // true: pointers point to different locations

    return 0;
}
