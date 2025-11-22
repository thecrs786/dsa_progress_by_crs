#include <iostream>
using namespace std;

// Function demonstrating pass by value (not reference)
void changeA(int a) {
    a += 5;
    cout << "Inside function: a = " << a << endl;
}

int main() {
    int a = 5;

    cout << "Before calling function: a = " << a << endl;
    cout << "While calling function: ";
    changeA(a);  // Function modifies the copy of 'a'

    cout << "After calling function: a = " << a << endl;

    // Explanation:
    // The function 'changeA' receives a copy of 'a'.
    // It modifies the copy, not the original variable.
    // Therefore, the original 'a' remains unchanged.
    // This is known as Pass by Value.

    return 0;
}
