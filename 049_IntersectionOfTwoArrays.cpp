// WAF TO PRINT INTERSECTION OF TWO ARRAYS

#include<iostream>
using namespace std;  

void intersection(int arr1[],int size1,int arr2[],int size2){
    for(int i=0;i<size1;i++){
        bool a = false;
        for(int j=0;j<size2;j++){
            if(arr1[i]==arr2[j]){
                a = true;
                break;
            }
        }
        if (a==true){cout<<arr1[i]<<" ";}
    }
}

int main(){

int arr1[]={1,2,3,4,5,6,7,22,44};
int arr2[] ={5,4,1,8,22,3,9,2,33};

intersection(arr1,9,arr2,9);

return 0;
}