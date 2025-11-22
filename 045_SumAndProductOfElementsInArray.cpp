// WAF TO CALCULATE SUM & PRODUCT OF ALL NUMBERS IN AN ARRAY

#include<iostream>
using namespace std;

int returnSum(int arr[], int size){
    int sum = 0;
    int i =0;
    while(i<size){
        sum+=arr[i];
        i++;
    }
    return sum;
}

int returnProd(int arr[], int size){
    int prod = 1;
    int i =0;
    while(i<size){
        prod*=arr[i];
        i++;
    }
    return prod;
}

int main(){

int arr1[] ={1,2,3,4,5,6,7,8,9};
int arr2[]={2,4,6,8,10};

cout<<"\n";

cout<<"Sum of elements in arr1 : "<<returnSum(arr1,9)<<endl;
cout<<"Product of elements in arr1 : "<<returnProd(arr1,9)<<endl;

cout<<"\n";

cout<<"Sum of elements in arr2 : "<<returnSum(arr2,5)<<endl;
cout<<"Product of elements in arr2 : "<<returnProd(arr2,5)<<endl;


return 0;
}