// TYPECASTING

/*
Conversion -> Implicit (done by compiler) : small to big
Casting --> Explicit (done by programmer) : big to small
*/

#include <iostream>
using namespace std;

int main() { 

    // IMPLICIT
    float a = 3.14;
    int b = (int)a;  // or int(a)

    cout << "a = " << a << "\n" << "b = " << b << endl;

    char grade = 'A';
    cout << "ASCII value of 'A': " << (int)grade << endl; // Prints ASCII value of 'A'

    // EXPLICIT
    double price = 100.99; // Rounding off gives 100.00
    int new_price = static_cast<int>(price); // Converted from double to int

    cout << "price = " << price << "\nnew_price = " << new_price << endl;

    return 0;
}
