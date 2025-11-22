// HOLLOW DIAMOND PATTERN

#include<iostream>
using namespace std;  

int main(){

/* PRINT
   *       i=0  spaces: 3, 0
  * *      i=1  spaces: 2, 1(2*i-1) for(0<i<n)
 *   *     i=2  spaces: 1, 3(2*i-1)
*     *    i=3  spaces: 0, 5(2*i-1)  
 *   *     i=4  spaces: 1, 3
  * *      i=5  spaces: 2, 1
   *       i=6  spaces: 3, 0
breakdown:
(1) spaces -> cout<<"*"
(2) spaces --> cout<<"*" (not in i=0  and i=6)
*/

int n=4;

// TOP

for(int i=0;i<n;i++){
    // spaces
    for(int j=0;j<n-i-1;j++){
        cout<<" ";
    }
    cout<<"*";

    if(i!=0){
    // spaces
    for(int j=0;j<2*i-1;j++){
        cout<<" ";}
    cout<<"*";

    }
    cout<<"\n";

}

// BOTTOM --> for(i=0;i<(n-1);i++)

for(int i=0;i<n-1;i++){  // 0 to n-2
    // spaces
    for(int j=0;j<i+1;j++){
        cout<<" ";
    }
    cout<<"*";

    if(i!=n-2){
    // spaces
    for(int j=0;j<2*(n-i)-5;j++){ // 2*(n-2-i)-1 = 2*(n-i)-5  Logic -> spaces are in decreasing order -> -i involved also odd number of spaces -> 2(something-i)-1
        cout<<" ";}                                          // also n is involved -> 2*(n-i-something)-1 --> by hit and trial we get -> 2*(n-i-2)-1
    cout<<"*";  

    }
    cout<<"\n";
}
return 0;
}