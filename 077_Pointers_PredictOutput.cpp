// Q) Preidct Output

#include<iostream>
using namespace std;

int main(){

    int a = 5;
    int *p = &a;
    int **q = &p;

    cout<< *p <<endl; // va;ue of a i.e 5
    cout<< **q <<endl; // value of a i.e 5 (deferenced twice)
    cout<< p <<endl; // address of a stored in p -> &a
    cout<< *q <<endl; // address of a stored in p (dereferenced once) -> &a
   
    cout<<&a<<endl; //(for verification of above two statements)

    return 0;
}
