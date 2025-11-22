// METHOD 2 (usin xor)  CAUTION : it'll only work when there's in only one single number

#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> vec = {4,1,2,6,1,8,6,2,4};
    int single = 0;
    for(int num : vec){
        single ^= num;  // XOR cancels out all duplicates
    }
    cout << "Single Number : " << single << endl; // Only 8 appears once. All others appeared twice and canceled out through XOR.

    /*
 (1) XOR of a number with itself is 0 (a ^ a = 0)
 (2) XOR of a number with 0 is the number itself (a ^ 0 = a)
 (3) So all duplicate numbers cancel out, and you're left with the single one.
    */
    return 0;
}
