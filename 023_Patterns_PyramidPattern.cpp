// PYRAMID PATTERN

#include<iostream>
using namespace std;  

int main(){
  
/* PRINT                                   3 loops
      1          i=0->3 spaces = n-i-1    --> spaces
    1 2 1        i=1->2 spaces = n-i-1    --> first set of numbers
  1 2 3 2 1      i=2->1 spaces = n-i-1    --> second set of numbers
1 2 3 4 3 2 1    i=3->0 spaces = n-i-1

*/

int n = 9;

for(int i = 0;i<n;i++){
    // spaces : n-i-1
    for(int j=0;j<n-i-1;j++){
        cout<<" ";
    }
    // nums1 : i+1
    for(int j=1;j<=i+1;j++){
        cout<<j;
    }
    // nums2 : 
    for(int j=i;j>0;j--){
        cout<<j;
    }
    cout<<"\n";
}

return 0;
}