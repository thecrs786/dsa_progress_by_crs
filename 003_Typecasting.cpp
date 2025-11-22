// TYPECASTING

/*
Conversion -> Implicit (done by compiler) : small to big
Casting --> Explicit (done by programmer) : big to small
*/

#include <iostream>
using namespace std;

int main() { 

    // IMPLICIT CASTING
    float a = 3.14;
    int b = (int)a;  // or int(a), explicit cast
    cout << "a = " << a << "\n" << "b = " << b << endl;

    char grade = 'A';
    cout << "ASCII value of 'A': " << (int)grade << endl; // Prints ASCII value of 'A'

    // EXPLICIT CASTING
    double price = 100.99; // Rounding off gives 100.00
    int new_price = static_cast<int>(price); // Converted from double to int
    cout << "price = " << price << "\nnew_price = " << new_price << endl;

    // ------------------------------
    // INT TO CHAR CONVERSION (Useful in Sudoku, digits, etc.)
    int dig = 5;

    // '0' has ASCII value 48, '1' = 49, ..., '9' = 57
    char ch = dig + '0'; // Converts integer 0-9 to corresponding character '0'-'9'

    cout << "Integer: " << dig << " -> Char: " << ch << endl;

    // WHY + '0' ?
    // Adding '0' shifts the integer to its corresponding ASCII code.
    // Example: dig = 5
    // '0' = 48
    // 48 + 5 = 53 -> ASCII 53 = '5'
    // This is **only valid for digits 0 to 9**.
    // Using any number > 9 or < 0 will not give a valid digit character.

    return 0;
}
