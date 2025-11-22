#include <iostream>
#include <cmath>
using namespace std;

/*
    ARMSTRONG NUMBER CHECKER — COMPLETE WITH RAW LOGIC AND EXAMPLES

    ✅ Definition:
    An Armstrong number of 'd' digits is a number such that the sum of its digits
    raised to the power 'd' equals the number itself.

    Examples:
    ---------
    - 153 (3 digits): 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153 ✔️
    - 9474 (4 digits): 9^4 + 4^4 + 7^4 + 4^4 = 9474 ✔️
    - 123 (3 digits): 1^3 + 2^3 + 3^3 = 36 ≠ 123 ❌

    ❌ Negative numbers can't be Armstrong — they break the math logic.
    ✅ 0 is considered Armstrong — 0^1 = 0.

    🔁 Time Complexity: O(log₁₀N × log d)
    (log N to extract digits, log d inside pow function — acceptable for small inputs)

    🚀 Optimized:
    - No vector to store digits (saves space)
    - No string conversions (faster)
*/

bool isArmstrong(int n) {
    if (n < 0) return false;         // ❌ Negative numbers are not Armstrong
    if (n == 0) return true;         // ✅ 0 is a valid Armstrong number

    int original = n;                // Save the number to compare later
    int numofdig = 0;
    int temp = n;

    // 🔢 Step 1: Count number of digits (d)
    while (temp > 0) {
        numofdig++;                  // Increase digit count
        temp /= 10;                  // Remove last digit
    }

    // 💥 Step 2: Calculate sum of each digit raised to power 'numofdig'
    int sum = 0;
    temp = n;
    while (temp > 0) {
        int r = temp % 10;               // Extract last digit
        sum += pow(r, numofdig);         // Raise digit to power and add to sum
        temp /= 10;                      // Remove digit
    }

    // ✅ Step 3: Check if calculated sum equals original number
    return sum == original;
}

int main() {


    cout << " 3-digit Armstrong numbers:\n";
    for (int i = 100; i <= 999; i++) {
        if (isArmstrong(i)) cout << i << " ";
    }
    cout << "\n\n";

    cout << " 4-digit Armstrong numbers:\n";
    for (int i = 1000; i <= 9999; i++) {
        if (isArmstrong(i)) cout << i << " ";
    }
    cout << "\n\n";

    cout << " 5-digit Armstrong numbers:\n";
    for (int i = 10000; i <= 99999; i++) {
        if (isArmstrong(i)) cout << i << " ";
    }
    cout << "\n\n";

    return 0;
}

/*
    ✅ OUTPUT:
    -----------------------------
    🔍 3-digit Armstrong numbers:
    153 370 371 407 

    🔍 4-digit Armstrong numbers:
    1634 8208 9474 

    🔍 5-digit Armstrong numbers:
    54748 92727 93084 

    🔥 Summary:
    - No wasted space
    - Simple digit count and digit power sum
    - Fast for all practical inputs
*/
