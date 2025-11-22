// CHARACTER ARRAYS

#include<iostream>
#include<vector>
#include<cstring>  // required for strlen
using namespace std;

int main() {

    // A character array (not null-terminated)
    char arr[] = {'a', 'b', 'c', 'd', 'e'};

    // 'arr' decays to a pointer to the first element, i.e., &arr[0]
    cout << "Pointer to the 0th index of arr = " << arr << endl;
    // This will print the array like a string until it hits a null terminator,
    // but since there's no '\0', it may print garbage beyond 'e'

    cout << "Value at 0th index of arr (using *arr) = " << *arr << endl;
    cout << "Value at 0th index of arr (using arr[0]) = " << arr[0] << endl;

    cout << "Value at 2nd index of arr (using *(arr + 2)) = " << *(arr + 2) << endl;
    cout << "Value at 2nd index of arr (using arr[2]) = " << arr[2] << endl;

    // Since arr decays to a pointer, pointer arithmetic using '+' and '-' is allowed
    // This is valid for arrays and also for random access iterators (like vector, deque)
    // But not valid for general (non-random access) iterators like those of list, set, etc.

    // ─────────────────────────────────────────────────────────────
    // 🔹 CONCEPT OF NULL CHARACTER ('\0') IN CHARACTER ARRAYS
    // ─────────────────────────────────────────────────────────────

    // If we store the null character '\0' at the end of a character array,
    // then it becomes a proper C-style string.
    // Printing the array will print characters until '\0' is encountered.
    // If '\0' is missing, printing will continue into garbage memory.

    char arr1[] = {'a', 'b', 'c', 'd', 'e', '\0'};

    cout << "Value at index 1 (using *(arr1 + 1)) = " << *(arr1 + 1) << endl;
    cout << "Value at index 1 (using arr1[1]) = " << arr1[1] << endl;
    cout << "Printing arr1 as a string = " << arr1 << endl;

    // ─────────────────────────────────────────────────────────────
    // 🔹 Additional Examples
    // ─────────────────────────────────────────────────────────────

    // A proper string literal is null-terminated by default
    char arr2[] = "abcde"; // same as {'a', 'b', 'c', 'd', 'e', '\0'}

    cout << "Printing arr2 (initialized using string literal) = " << arr2 << endl;

    // Printing memory address explicitly (to show it's actually a pointer)
    cout << "Memory address of arr2 = " << static_cast<void*>(arr2) << endl;

    // Length using strlen (works only on null-terminated strings)
    cout << "Length of arr2 using strlen() = " << strlen(arr2) << endl;

    // Printing char array without '\0'
    char arr3[] = {'x', 'y', 'z'};
    cout << "Printing arr3 (without null terminator) = " << arr3 << " (garbage may follow)" << endl;

    // Input & Output

   // ─────────────── Input with cin >> ───────────────
    char str[100];

    cout << "Enter the str: ";
    cin >> str; 
    cout << "str: " << str << endl;

    // cin >> str reads input only until the first whitespace (space, tab, or newline)
    // So only the first word is stored in 'str'
    // Everything after the first space remains in the input buffer (including the '\n')

    // ─────────────── How cin.getline(...) works ───────────────
    // Syntax: cin.getline(char_array, max_length, delimiter);
    // - char_array → the array to store input
    // - max_length → maximum number of characters to read (including '\0')
    // - delimiter  → optional (default is '\n')
    // Input ends when:
    //   - (max_length - 1) characters are read, or
    //   - the delimiter character is encountered (delimiter is consumed and not stored)

    // ─────────────── Flush leftover input before getline ───────────────
    cin.ignore(1000, '\n');  // Discard characters up to the next newline

    // ─────────────── Input using getline ───────────────
    char strr[100];

    cout << "Enter strr: ";
    cin.getline(strr, 100, '.');  // Input ends at '.' or after 99 chars

    // ─────────────── Final Output ───────────────
    cout << "str: " << str << endl;
    cout << "strr: " << strr << endl;

// ───────────────────── Output C-Style String (char array) ─────────────────────

// Range-based for loop (also called for-each loop)
// This works on C-style arrays like 'char strr[100]' because arrays decay to pointers,
// and the compiler knows the size at compile-time.

for (char ch : strr) {
    if (ch == '\0') break;  // Stop printing when null terminator is encountered
    cout << ch << " ";
}
cout << endl;

// ✅ Note:
// This prints only valid characters of the string, stopping at '\0'
// (which marks the end of a C-style string).
// If we don’t check for '\0', it may print garbage values beyond the string.

// ───────────────────── Traditional Index-Based Loop ─────────────────────

for (int i = 0; strr[i] != '\0'; i++) {
    cout << strr[i] << " ";
}
cout << endl;

// ✅ Note:
// This is the standard way to iterate over a C-style string.
// It checks each character until it hits the null terminator '\0',
// which means the end of valid input stored in the char array.

// ───────────────────── Summary ─────────────────────

// ✔ Both loops above do the same thing: print characters of 'strr' one by one.
// ✔ The range-based loop is cleaner and safer, but remember to break manually at '\0'.
// ✔ Index-based loops give more control (like accessing the index itself).

// ⚠ Be careful not to write incorrect loop conditions like:
//    for (int i = 0; i < strr[i] != '\0'; i++)   ← ❌ This is logically incorrect.


    return 0;
}
