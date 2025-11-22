// PAIR SUM -> return pair in sorted array with target sum

#include<iostream>
using namespace std;  

bool findPair(int arr[], int size, int target){
    for(int i =0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(arr[i]+arr[j]==target){
                cout<<"Pair Found : ("<<arr[i]<<", "<<arr[j]<<")"<<endl;
                return true;
            }
        }
    }
    cout<<"No such pair found "<<endl;
    return false;
}

int main(){

int arr[]= {2,7,11,15};


findPair(arr,4,18);
findPair(arr,4,8);

return 0;
}