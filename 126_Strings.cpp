// STRINGS  -> like vector<int>  also allow iterators like s.begin() etc

#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int main(){

    /// Character array initialized with a string literal
    char str[] = "Hello";

    cout << str[0] << endl; // Output: H

    str[0] = 'K';  // Valid: modifies the first character
    cout << str[0] << endl; // Output: K

    // str = "Banana"; 
    // ❌ Invalid: cannot assign to an array after declaration
    // Use std::string for such operations

    // Strings -> not actually a primitive type
    //            it's a class for which we make objects (string literals)
    //            header #include<string>  (not necessary)

     // ──────────────────────────────────────────────
    // ✅ STRING INITIALIZATION METHODS (std::string)
    // ──────────────────────────────────────────────

    string s = "Hello World";        // Method 1: Direct initialization with string literal
    // string s("Hello World");     // Method 2: Constructor style
    // string s = string("Hello");  // Method 3: Explicit constructor call
    
    // string s3 = s1 + "  " + s2 + "something";  (COCATENATION)

    
// ──────────────────────────────────────────────
// ✅ STRING INPUT METHODS
// ──────────────────────────────────────────────

// cin >> s; 
// ✅ Takes input only up to the first space
// For example, entering "John Doe" → s = "John" only

// getline(cin, s); 
// ✅ Reads entire line including spaces until newline '\n' is encountered

// Example:
string inputStr;
cout << "Enter a single-word string: ";
cin >> inputStr;
cout << "You entered: " << inputStr << endl;

cin.ignore();  // Clears leftover newline from previous input

cout << "Enter a full line with spaces: ";
getline(cin, inputStr);  // Now it reads the full line
cout << "You entered full line: " << inputStr << endl;

// 🔹 Tip: Use `cin.ignore()` before `getline()` to flush the leftover newline
// 🔹 `getline()` has an optional second parameter: delimiter (default is '\n')
//    Example: getline(cin, s, '#');  → reads until '#' is encountered

    // ──────────────────────────────────────────────
    // ✅ INDEXING & LENGTH
    // ──────────────────────────────────────────────

    cout << s[0] << endl;  // Indexing is allowed → prints 'H'

    // ❌ int n = strlen(s);
    // strlen() works only with C-style strings (char[] or const char*)
    // It counts characters until the null terminator '\0'
    // std::string is a C++ class with internal size tracking — use .length() or .size()

    int n = s.length();    // ✅ returns number of characters

    // ──────────────────────────────────────────────
    // ✅ METHODS TO PRINT A STRING
    // ──────────────────────────────────────────────

    // Method 1: Range-based for loop (for-each)
    for (char c : s) {
        cout << c;
    }
    cout << endl;

    // Method 2: Index-based for loop
    for (int i = 0; i < n; i++) {
        cout << s[i];
    }
    cout << endl;

    // Method 3: Direct output
    cout << s << endl;

    // ──────────────────────────────────────────────
    // ✅ STRINGS ARE DYNAMIC (can be reassigned/resized)
    // ──────────────────────────────────────────────

    s = "hello";  // Reassigning is allowed → size changes automatically

    // ──────────────────────────────────────────────
    // ✅ ADDRESSING AND POINTER BEHAVIOR
    // ──────────────────────────────────────────────

    cout << &s << endl;     // Prints memory address of string object (class instance, not the char buffer)

    // ⚠️ BUT: &s[n] gives pointer to character at index n
    // This works because std::string internally stores characters in a contiguous array (like char[])
    // So &s[n] is a pointer to the n-th character, and printing it behaves like printing a C-style string from that point

    cout << &s[0] << endl;  // Prints full string → hello
    cout << &s[1] << endl;  // Prints from index 1 → ello
    cout << &s[2] << endl;  // → llo
    cout << &s[3] << endl;  // → lo
    cout << &s[4] << endl;  // → o

    // ⚠️ Note: These work only if there's no null character ('\0') earlier and string is not empty
    // It exploits that &s[n] gives a const char* starting from position n

    // CONCATENATION OF STRINGS

    string s1 = "Hello";
    string s2 = "World";

    string s3 = s1+" "+s2; // strings can be concatenated by +

    cout<<"s3 (by concatenation) : "<<s3<<endl;

    s1 = "apple";
    s2 = "banana";

    // To print boolean values as 'true' or 'false' instead of 1/0
    cout << boolalpha;

    // ──────────────────────────────────────
    // ✅ Equality and Inequality
    // ──────────────────────────────────────
    cout << "s1 == s2 : " << (s1 == s2) << endl;     // false → different strings
    cout << "s1 != s2 : " << (s1 != s2) << endl;     // true  → they are different

    // ──────────────────────────────────────
    // ✅ Lexicographical Comparisons (ASCII based)
    // ──────────────────────────────────────
    cout << "s1 < s2  : " << (s1 < s2) << endl;      // true  → "apple" comes before "banana"
    cout << "s1 <= s2 : " << (s1 <= s2) << endl;     // true
    cout << "s1 > s2  : " << (s1 > s2) << endl;      // false
    cout << "s1 >= s2 : " << (s1 >= s2) << endl;     // false

    // ──────────────────────────────────────
    // ✅ compare() method
    // Returns:
    //    0  → if equal
    //   <0  → if s1 < s2
    //   >0  → if s1 > s2
    // ──────────────────────────────────────
    int cmp = s1.compare(s2);
    cout << "s1.compare(s2) = " << cmp << endl;

    // Example: using compare() safely
    if (cmp == 0) {
        cout << "s1 and s2 are equal" << endl;
    } else if (cmp < 0) {
        cout << "s1 comes before s2" << endl;
    } else {
        cout << "s1 comes after s2" << endl;
    }



    return 0;
}
