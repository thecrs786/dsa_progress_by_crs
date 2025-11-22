// OPERATORS

/*
(1) Arithmetic  --> + , - , * , / , %
(2) Relational --> == , != , > , < , >= , <=
(3) Logical    --> && -> and , || -> or , ! -> not
*/

#include<iostream>
using namespace std;  

int main() {
    int a = 5, b = 10, c = 3; // Declaring multiple variables of the same type in one statement

    // ARITHMETIC OPERATIONS
    cout << "Sum: " << (a + b) << endl;
    cout << "Difference: " << (a - b) << endl;
    cout << "Product: " << (a * b) << endl;
    cout << "Quotient (int division): " << (a / b) << endl;  // 5 / 10 = 0.5 --> 0 as integer
    cout << "Quotient (float division): " << (float)a / b << endl; // 5 / 10 = 0.5
    cout << "Remainder: " << (a % c) << endl;

    // Note: int/float = float, int/double = double (output data type follows the larger type)

    // RELATIONAL OPERATIONS
    cout << "Is a >= b? " << (a >= b) << endl; // false (0)
    cout << "Is a <= b? " << (a <= b) << endl; // true (1)
    cout << "Is a != b? " << (a != b) << endl; // true (1)

    // LOGICAL OPERATIONS
    cout << "(3 > 2) AND (3 > 4): " << ((3 > 2) && (3 > 4)) << endl; // 1 && 0 --> 0 (false)
    cout << "(3 > 2) OR (3 > 4): " << ((3 > 2) || (3 > 4)) << endl; // 1 || 0 --> 1 (true)

    return 0;
}
