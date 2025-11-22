// We already discussed the defination
// of constructor in previous file

#include<iostream>
using namespace std;

class Student{
    public:

    string name;
    double cgpa;

    Student(string name, double cgpa){
        this->name = name;
        this->cgpa = cgpa;
    }

    Student(Student &s){ // copy constructor, reference to another object of same class
        this->name = s.name; // copying values from object s to current object
        this->cgpa = s.cgpa;

        // however this pointer was not necessary, it is a good practice to use it
    }

    void getInfo(){
        cout<<"Name: "<<name<<" | "<<"CGPA: "<<cgpa<<endl;
    }
};

class Student2{
    public:
    string name;
    double *cgpaptr; // pointer to double

    Student2(string name, double cgpa){ // parameterized constructor
        // we are using dynamic memory allocation to allocate memory for cgpa
        this->name = name;
        cgpaptr = new double; // dynamically allocating memory

        // that's the way, pointer name = new dataType;

        *cgpaptr = cgpa; // dereferencing pointer to assign value
    
    }

    Student2(Student2 &s){ // copy constructor
        this->name = s.name;
        this->cgpaptr = s.cgpaptr; // copies the pointer (shallow copy), so both objects share the same memory
    }

    void getInfo(){
        cout<<"Name: "<<name<<" | "<<"CGPA: "<<*cgpaptr<<endl; // dereferencing pointer to get value
    }
};

int main(){

    Student s1("thecrs" , 9.9); // parameterized constructor called
   Student s2(s1);

   cout<<"s1 created using parameterized constructor"<<endl;
   s1.getInfo(); // prints original value 9.9

   cout<<"s2 created using copy constructor"<<endl;
   s2.getInfo(); // prints same values as s1

   s2.cgpa = 9.0;

   cout<<"After changing value of s2.cgpa to 9.0"<<endl;
   s2.getInfo(); // prints updated value 9.0

   cout<<"s1 remains unchanged"<<endl;
   s1.getInfo(); // prints original value 9.9 because of deep copy


    Student2 s3("hamid", 9.8); // parameterized constructor called

    Student2 s4(s3); // copy constructor called

    cout<<"s3 created using parameterized constructor"<<endl;
    s3.getInfo(); // prints original value 9.8

    cout<<"s4 created using copy constructor"<<endl;
    s4.getInfo(); // prints same values as s3

    *(s4.cgpaptr) = 7.4; // changing value using dereferencing pointer

    cout<<"After changing value of s4.cgpa to 7.4"<<endl;
    s4.getInfo(); // prints updated value 7.4

    cout<<"s3 also gets changed due to shallow copy"<<endl;
    s3.getInfo(); // also prints updated value 7.4 because of shallow copy 
    
        // this happenned because of shallow copy
        // both s3 and s4 share the same memory location for cgpaptr

        // NOTE: same issue will happen if we use default copy constructor
        // which does a shallow copy by default

        //To avoid this, we need to implement deep copy in copy constructor
        // by allocating new memory for pointer and copying value
        // but we will not do that here to keep it simple
        // we'll do that in next file

    return 0;
}
