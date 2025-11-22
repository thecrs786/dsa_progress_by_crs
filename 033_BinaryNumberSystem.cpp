// 0-9 : BASE 10

// 0 and 1 : binary number system

/* decimal to binary

repeatedly divide with 2, remainder on right side, keep doing until remainder is 0 
from bottom to top sequence of remainders is binary form

(42) in 10 base = (101010) in decimal form

TYPES-> 4 bit, 8 bit, 16 bit etc.

*/ 


#include<iostream>
using namespace std;  

int decToBinary(int decNum){
    int ans=0;
    int pow = 1; // 10^0

    while(decNum>0){
       int rem = decNum%2;
        decNum/=2;
        ans+=(rem*pow);
        pow*=10; // 1 -> 10 -> 100 -> 1000 ---

    }
    return ans;
}

int main(){

   int num;

   cout<<"Enter a number or character : ";

  if (cin >> num) {
        // User entered a number
        cout << "Binary form: " << decToBinary(num) << endl;
    } else {
        cin.clear(); // clear error
        char ch;
        cin >> ch;
        num = int(ch);
        cout << "Binary form: " << decToBinary(num) << endl;
    }



return 0;
}