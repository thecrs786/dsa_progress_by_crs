// min and max function

#include<iostream>
#include<climits>
using namespace std;  

int main(){

cout<<min(3,4)<<endl;
cout<<max(3,4)<<endl;

// another way to get smallest in an array

int arr[] = {10, 98, 5, 7, 90, 1, 15, 6};
int size = sizeof(arr) / sizeof(arr[0]);  // Get array size

int smallest = INT_MAX;
int greatest = INT_MIN;

for(int i =0;i<size;i++){
     smallest = min(arr[i],smallest);
}

int index_smallest;

for(int i=0;i<size;i++){
    if(arr[i]==smallest){
        index_smallest=i;
        break;
    }
}

cout<<"Smallest : "<<smallest<< " at index "<<index_smallest<<endl;

for(int i =0;i<size;i++){
    greatest = max(arr[i],greatest);
}
int index_greatest;

for(int i=0;i<size;i++){
    if(arr[i]==greatest){
        index_greatest=i;
        break;
    }
}
cout<<"Greatest : "<<greatest<<" at index "<<index_greatest<<endl;


return 0;

}