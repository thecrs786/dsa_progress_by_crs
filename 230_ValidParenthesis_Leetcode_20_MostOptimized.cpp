/*
LeetCode 20: Valid Parentheses
------------------------------
Problem Summary:
Given a string `s` containing just the characters '(', ')', '{', '}', '[' and ']', 
determine if the input string is valid.

Rules for validity:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.

Examples:
- Input: s = "()"        -> Output: true
- Input: s = "()[]{}"    -> Output: true
- Input: s = "(]"        -> Output: false
- Input: s = "([)]"      -> Output: false
- Input: s = "{[]}"      -> Output: true
*/

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Solution using stack (LIFO principle)
class Solution {
public:
    bool isValid(string s) {
        stack<char> st; // Stack to keep track of opening brackets

        // Traverse each character in the string
        for(char ch : s){
            if(ch=='{' || ch=='[' || ch=='('){
                st.push(ch); // Push opening brackets to stack
            }
            else{
                // Case 1: Stack is empty but we encountered a closing bracket
                // This checks if the string doesn't begin with a closing bracket
                // OR there exists a closing bracket without its corresponding opening one
                if(st.empty()) return false;

                // Case 2: Check for matching brackets

                if((ch=='}' && st.top()=='{') || (ch==')' && st.top()=='(') || (ch==']' && st.top()=='[')) st.pop();
                else return false;

                // OR another way to write that


                /*if(ch == '}' && st.top()=='{') st.pop();
                else if(ch == ')' && st.top()=='(') st.pop();
                else if(ch == ']' && st.top()=='[') st.pop();
                else return false; */


                // Mismatch case: closing bracket does not match top of stack
                // Example: stack top = '(', current char = '}'
            }
        }

        // Final check:
        // Ensure no unmatched opening brackets remain
        // Example: "((((){}{()[}]" -> first three brackets are still not closed
        return st.empty();
    }
};

/*
Solution Details:
-----------------
Method Name       : Stack-based approach
Time Complexity   : O(n) -> each character is pushed and popped at most once
Space Complexity  : O(n) -> stack stores opening brackets (worst case all are opening)
Optimality        : Yes, this is the standard optimal approach for this problem
LeetCode Accepted : Yes, will not cause TLE or MLE
Logic Explanation :
1. Use a stack to store opening brackets.
2. For each character:
   - If it's an opening bracket, push it onto the stack.
   - If it's a closing bracket:
       a. If stack is empty -> invalid (no matching opening bracket)
       b. If top of stack matches current closing bracket -> pop it
       c. Else -> invalid (mismatched brackets)
3. After traversal, stack must be empty -> all brackets matched.
Key Sights:
- Always check stack is not empty before calling top()
- LIFO principle naturally matches bracket nesting
- Sentinel return false handles invalid cases early
*/

int main() {
    Solution sol;

    // Test cases
    string test1 = "()";
    string test2 = "()[]{}";
    string test3 = "(]";
    string test4 = "([)]";
    string test5 = "{[]}";

    cout << test1 << " -> " << (sol.isValid(test1) ? "true" : "false") << endl;
    cout << test2 << " -> " << (sol.isValid(test2) ? "true" : "false") << endl;
    cout << test3 << " -> " << (sol.isValid(test3) ? "true" : "false") << endl;
    cout << test4 << " -> " << (sol.isValid(test4) ? "true" : "false") << endl;
    cout << test5 << " -> " << (sol.isValid(test5) ? "true" : "false") << endl;

    // Custom example to visualize failure
    string test6 = "((((){}{()[}])";
    cout << test6 << " -> " << (sol.isValid(test6) ? "true" : "false") << endl;

    return 0;
}

/*
Working:
--------
- Stack keeps track of opening brackets.
- Each closing bracket matches with top of stack.
- Early mismatch returns false.
- At the end, stack must be empty for the string to be valid.

Important Details:
-----------------
- Stack ensures correct order of brackets (LIFO)
- Empty stack check prevents runtime errors
- Works for nested and sequential brackets
- Optimal in both time and space for this problem
*/
