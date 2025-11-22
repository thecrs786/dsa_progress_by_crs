// LINEAR SEARCH

#include<iostream>
using namespace std;  

int linearSearch(int arr[],int size,int target){
    for(int i=0;i<size;i++){
        if(arr[i]==target){ // if found would return i and funcction stops there
            return i;
        }
    }
    return -1; // indicates target ain't found
}

int main(){

int arr[] = {4,2,7,8,1,2,5};

int size = sizeof(arr)/sizeof(arr[0]);

int target;

cout<<"Enter target : ";
cin>>target;

cout<<linearSearch(arr,size,target)<<endl;



return 0;
}