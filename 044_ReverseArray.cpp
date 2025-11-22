// REVERSE AN ARRAY

// 2 pointer method

#include<iostream>
using namespace std;  

/*void reverseArr(int arr[], int size){
    int a;
    for(int i=0;i<(size/2);i++){
        a = arr[i];
        arr[i]=arr[size-i-1];
        arr[size-i-1]=a;
    }
}*/

void reverseArr(int arr[], int size){
    int temp;
    int start = 0;
    int end = size-1;
    while(start<end){
        temp = arr[start];
        arr[start]=arr[end];
        arr[end]=temp;
        start++;
        end--;
    }
}

int main(){

cout<<"\n";

int arr1[]={4,2,7,8,1,2,5};

cout<<"Before reverse : ";

for(int i = 0;i<7;i++){cout<<arr1[i]<<" ";}

reverseArr(arr1,7);

cout<<"\n";

cout<<"After reverse : ";

for(int i = 0;i<7;i++){cout<<arr1[i]<<" ";}

cout<<"\n\n";

int arr2[]={1,2,3,4,5,6,7,8,9};

cout<<"Before reverse : ";

for(int i = 0;i<9;i++){cout<<arr2[i]<<" ";}

cout<<"\n";

reverseArr(arr2,9);

cout<<"After reverse : ";

for(int i = 0;i<9;i++){cout<<arr2[i]<<" ";}

cout<<"\n\n";

// cout<<int(&arr[0])<<endl;
// cout<<int(&arr[1])<<endl;
// cout<<int(&arr[2])<<endl;
// cout<<int(&arr[3])<<endl;

return 0;
}