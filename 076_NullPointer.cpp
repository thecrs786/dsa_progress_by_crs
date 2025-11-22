// NULL POINTER  -> doesn't point to any location

#include<iostream>
using namespace std;

int main(){

    
    
    // int *ptr; or int **ptr; stores garbage value if unsigned
    // so we use NULL so that we can use pointers later

    // NULL pointer cannot be dereferenced

    int **ptr = NULL;

    cout<<ptr<<endl; // 0

    // but cout<<*ptr or **ptr will cause error

    return 0;
}
