// WAF TO PRINT ALL UNIQUE VALUES IN AN ARRAY (values that doesn't repeat)

#include<iostream>
using namespace std;  

void unique(int arr[], int size){
    for(int i = 0; i < size; i++){
        bool isUnique = true;

        for(int j = 0; j < size; j++){
            if(i != j && arr[i] == arr[j]){
                isUnique = false;
                break;
            }
        }

        if(isUnique==true){
            cout << "Unique element: " << arr[i] << endl;
        }
    }
}


int main(){

int arr1[] = {1,2,3,4,5,3,2,1,5}; // size = 9
int arr2[] = {6,7,8,8,7,6,9,1,2,3,1,3}; // size = 12

unique(arr1,9);

cout<<"\n";

unique(arr2,12);



return 0;
}