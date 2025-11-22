// Destructor : Opposite of Constructor
// It is a special member function of a class that deallocates memory
// It is called automatically when an object goes out of scope or is deleted
// // BUT it does NOT automatically deallocate dynamically allocated memory
// For dynamically allocated memory, we must define our own destructor to free it
// when we use 'new' to allocate memory, we must use 'delete' to free it since it's dynamically allocated

// Syntax: ~ClassName(){ // code to free memory or other cleanup tasks }
// Destructor has the same name as the class but with a tilde (~) prefix
// It does not take any parameters and does not return any value

#include<iostream>
using namespace std;

class Student{
    public:
    string name;
    double *cgpaptr;

    Student(string name, double cgpa){ // parameterized constructor
        // we are using dynamic memory allocation to allocate memory for cgpa
        this->name = name;
        cgpaptr = new double; // dynamically allocating memory
        *cgpaptr = cgpa; // dereferencing pointer to assign value
    }

    // Destructor
    ~Student(){ // destructor to free dynamically allocated memory
        cout<<"Destructor called for "<<name<<endl;
        delete cgpaptr; // free the dynamically allocated memory
        // normal variables are automatically cleaned up, but pointers need manual cleanup
        // in real, the pointer isn't deleted, but the memory it points to is freed
    }

    void getInfo(){
        cout<<"Name: "<<name<<" | "<<"CGPA: "<<*cgpaptr<<endl; // dereferencing pointer to get value
    }


};

int main(){

    Student s1("thecrs" , 9.9); // parameterized constructor called
    s1.getInfo(); // prints s1 info 

    // Destructor will be called automatically when s1 goes out of scope (end of main function)
    // so we don't need to call it explicitly

    cout<<s1.cgpaptr<<endl; // prints address of cgpa
    cout<<*(s1.cgpaptr)<<endl; // prints value of cgpa


    cout<<"End of main"<<endl; // deconstructor is called after the end of program
    return 0;
}