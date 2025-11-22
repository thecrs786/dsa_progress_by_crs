#include <iostream>
#include <climits>  // For INT_MIN, INT_MAX
using namespace std;

/*
  🔢 Problem: Count the number of digits in a given integer.
             Also print the digits from least significant to most significant.
             
  ✅ Constraints:
    - Input can be any 32-bit signed integer (including negative numbers and INT_MIN)
    - Must not use abs(n) directly due to risk of overflow for INT_MIN.

  🔧 Method: Sign-safe division approach
    - We don't take abs(n) to avoid undefined behavior.
    - Instead, we loop while n != 0 and count how many times we can divide it by 10.
    - To print digits, we use n % 10 which works for negative numbers too.
  
  🕒 Time Complexity: O(log₁₀N) where N is the absolute value of the number
  📦 Space Complexity: O(1)

*/

int countDigits(int n) {
    if (n == 0) return 1;  // Edge case: 0 has 1 digit

    int count = 0;
    int temp = n;

    while (temp != 0) {
        temp /= 10;  // Removes the last digit (even for negative numbers)
        count++;
    }

    return count;
}

// 🖨️ Prints each digit from least significant to most significant
void printDigits(int n) {
    if (n == 0) {
        cout << "0\n";
        return;
    }

    cout << "Digits of " << n << " (in reverse order): ";
    while (n != 0) {
        int digit = n % 10;     // Extract the last digit
        cout << abs(digit) << " ";  // Print digit as positive
        n /= 10;                // Remove the last digit
    }
    cout << endl;
}

int main() {
    // 🔬 Working Example 1
    int a = 123456;
    cout << "Number of digits in " << a << " is: " << countDigits(a) << endl;
    printDigits(a);

    // 🔬 Working Example 2 (Negative Number)
    int b = -987;
    cout << "\nNumber of digits in " << b << " is: " << countDigits(b) << endl;
    printDigits(b);

    // 🔬 Working Example 3 (INT_MIN)
    int c = INT_MIN;
    cout << "\nNumber of digits in INT_MIN: " << countDigits(c) << endl;
    printDigits(c);

    // 🔬 Working Example 4 (Zero)
    int d = 0;
    cout << "\nNumber of digits in 0 is: " << countDigits(d) << endl;
    printDigits(d);

    return 0;
}

/*
🧠 Full Explanation:

1. ✅ Why we don't use abs(n):
   - abs(INT_MIN) causes overflow because INT_MIN = -2147483648 and INT_MAX = 2147483647.
   - abs(INT_MIN) = 2147483648, which can't be stored in a signed int → undefined behavior.

2. ✅ Why n/10 and n%10 work for negative numbers:
   - In C++, integer division and modulus handle negatives gracefully:
     - (-987) / 10 = -98
     - (-987) % 10 = -7
   - So we can loop without converting sign, just use abs(digit) when printing.

3. ✅ Why 0 is a special case:
   - log10(0) is undefined.
   - We manually return 1 for 0 to represent it has 1 digit.

4. 🧠 Output for INT_MIN will be:
   - Digit count: 10 (because INT_MIN has 10 digits)
   - Printed digits: from LSB to MSB, all correct.

💡 Tips:
  - To print digits in correct order (MSB to LSB), use a stack or recursion.
  - To reverse digits, build a new number using remainder and multiplication.

*/
