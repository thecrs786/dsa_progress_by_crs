// BINARY TO DECIMAL

/* EX -> 1011 -> [ (1 * 2^3) + (0 * 2^2) + (1 * 2^1) + (1 * 2^0) ]

*/

#include<iostream>
using namespace std;  

int binaryToDecimal(int binaryNum){
    int ans = 0;
    int pow = 1; // 2^0
    while(binaryNum>0){
        int rem = binaryNum%10;
        binaryNum/=10;
        ans += rem*pow;
        pow*=2; // 1 --> 2 --> 4 --> 8 ->
    }
    return ans;
}

int main(){
int binaryNum;
cout<<"Enter a binary number : ";
cin>>binaryNum;

cout<< binaryNum << " --> " << binaryToDecimal(binaryNum)<<endl;

return 0;
}