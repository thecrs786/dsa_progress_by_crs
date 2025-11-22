// INPUT --> use cin>>

#include<iostream>
using namespace std;  

int main(){

int age; // declared but not assigned
cout<<age<<endl; // returns garbage value as value is not assigned

cout << "Enter age : ";

cin >> age;

cout<< "Your age is : " << age << endl;


return 0;
}