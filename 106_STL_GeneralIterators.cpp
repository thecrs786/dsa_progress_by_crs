// Creating Iterator

#include<iostream>
#include<vector>
using namespace std;

int main(){

vector<int> nums = {1, 2, 3, 4, 5};

vector<int>::iterator itr;
// type(vector) then iterator then name.
// currently this iterator is empty

for(itr=nums.begin();itr!=nums.end();itr++){  // forward loop
     cout<<*(itr)<<" ";
}cout<<endl;

/* or
for(vector<int>::iterator itr=nums.begin();itr!=nums.end();itr++){  // forward loop
    cout<<*(itr)<<" ";
}cout<<endl;
*/

//  if we want to a apply backward loop on a vector, we use reverse iterator
// it starts from bakward to forward

/* vec.rbegin() -> points to the last last (n-1)th index of the vector
   vec.rend()-> points to the memory just before the f0th index of vector
                does't point to the 0th index of the vector

*/

  vector<int>::reverse_iterator it; // currently empty
  // reverse iterator

  for(it=nums.rbegin(); it!= nums.rend(); it++){
    cout<<*(it)<<" ";
  }cout<<endl;

  /* or
  for(vector<int>::reverse_iterator it=nums.rbegin(); it!= nums.rend(); it++){
    cout<<*(it)<<" ";
  }cout<<endl;
  */

  // or easier way than defining the type or iterator each time -> use auto
  // auto automatically defines the type of variable

  vector<int> vec = {6, 7, 8, 9, 10};

  // for forward loop
  for(auto iterator = nums.begin(); iterator!=nums.end(); iterator++){
    cout<<*(iterator)<<" ";
  }cout<<endl;

  // for backward loop

  for(auto riterator = nums.rbegin(); riterator!=nums.rend(); riterator++){
    cout<<*(riterator)<<" ";
  }cout<<endl;

    return 0;
}
