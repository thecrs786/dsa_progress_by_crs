#include <iostream>
using namespace std;

// Function to modify the value using a reference variable
int changevalue(int &a) {// This is not a memory address; '&' here creates an alias
    a += 10;               // Directly modifies the original variable
    return a;              // Returns the updated value
}

int main() {
    int x = 10;

    cout << "x before using function : " << x << endl;
    cout << "x while using function  : " << changevalue(x) << endl;
    cout << "x after using function  : " << x << endl;

    // Explanation:
    // In this function, we are using a reference variable as a parameter.
    // The parameter 'a' is not a new variable; it is simply another name (alias) for the original variable 'x'.
    // This means that any modification to 'a' inside the function is directly applied to 'x'.
    // No copy is created, and no address needs to be manually passed.
    // This method is called "Pass by Reference using Reference Variables".
    // It is cleaner and safer than pointers, and avoids syntax complexity like dereferencing (*).

    return 0;
}
