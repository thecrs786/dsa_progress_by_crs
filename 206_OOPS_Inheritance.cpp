// Inheritance

/* Inheritance is a mechanism where a new class (derived class) 
inherits properties and behaviors (attributes and methods) from an 
existing class (base class). 
This promotes code reusability and establishes a hierarchical relationship between classes.
*/

#include<iostream>
using namespace std;

class Person{ // name & age
    public:
    string name;
    int age;

    Person(string name, int age){
        this->name = name;
        this->age = age;
     }


};

// syntax -> class DerivedClass : accessSpecifier BaseClass{ // accessSpecifier can be public, private or protected

// public -> public members of base class become public members of derived class
// private -> public members of base class become private members of derived class
// protected -> public members of base class become protected members of derived class
// if no access specifier is mentioned, it is private by default

class Student : public Person{ //name, age & rollNo
    public:
    int rollNo;

    // Student() {}  
    // This won’t compile unless Person has a default constructor.  
    // Because Person has only a parameterized constructor, every derived constructor 
    // must explicitly call Person’s constructor using an initializer list.

     Student(string name, int age, int rollNo) : Person (name, age){
        // syntax -> DerivedClass(constructor parameters) : BaseClass(base constructor parameters) { // constructor body }
        // this way, we are calling the base class constructor
        
         this->rollNo = rollNo; // own member
     }

     // If the parent class has no default constructor,
    // then every constructor of the derived class (including default)
    // must explicitly call one of the parent’s parameterized constructors
    // using an initializer list.

    //  Student(string name, int age, int rollNo){ 
    //      // If no constructor is defined in the parent, compiler provides a default one automatically.
    //      //But if we define any constructor (like Person(string, int)), 
    //      //then the default is not auto-generated anymore.
           //but if we define a constructor in parent class, we must call it using initializer list
    //      this->name = name; // inherited from Person class
    //      this->age = age; // inherited from Person class
    //      this->rollNo = rollNo; // own member
    //  }

    void getinfo(){
        cout<<"Name: "<<name<<endl; // inherited from Person class
        cout<<"Age: "<<age<<endl; // inherited from Person class
        cout<<"Roll No: "<<rollNo<<endl; // own member
    }

};

// even if we don't define a constructor in parent class,
// we can still access its members in the derived class

// if we don't define values for name and age, they will have garbage values
// string initializes to empty string by default (not garbage)
// int without initialization will hold garbage value


int main(){

// Student s1;  // ❌ This fails
// Because Person has no default constructor.
// When creating a Student object, the base class constructor is called first.
// Since Person has only a parameterized constructor, you must provide arguments
// via an initializer list when defining Student constructors.


    /* If there was no constructor in base class and we would have initialized a default constructor in derived class then : 
    
    s1.getinfo(); // prints garbage values as we have not initialized anything

        s1.name = "Alice"; // inherited from Person class
        s1.age = 20; // inherited from Person class
        s1.rollNo = 101; // own member
        s1.getinfo(); // prints initialized values*/

        Student s2("crs", 21, 102); // parameterized constructor called
        s2.getinfo(); // prints initialized values

    return 0;
}
// Flow of constructor calls in inheritance:

// 1. When creating a derived class object (Student s2):
//      a) Base class constructor (Person) is called first.
//         - Ensures all base class members are initialized properly.
//         - If base has only parameterized constructors, you must call one explicitly.
//      b) Then derived class constructor (Student) executes.
//         - Initializes derived class members (e.g., rollNo).

// 2. If the base class has a default constructor:
//      - Derived class can call it automatically if no initializer list is provided.
//      - You can still use an initializer list to call a parameterized base constructor.

// 3. If the base class has no default constructor:
//      - Every derived class constructor must call a base class constructor explicitly using initializer list.
//      - Otherwise, compilation will fail.

// 4. Member initialization order:
//      - Base class members initialized first, in the order they are declared.
//      - Derived class members initialized next, in the order they are declared in the derived class.

// 5. Why initializer list is preferred:
//      - Directly initializes members instead of assigning values inside constructor body.
//      - More efficient, especially for const members, references, or classes without default constructor.


// MODE OF INHERITANCE

//
// Base Class Member   | Derived Class: Private | Derived Class: Protected | Derived Class: Public
// -------------------|----------------------|------------------------|--------------------
// public             | becomes private      | becomes protected      | remains public
// protected          | becomes private      | becomes protected      | remains protected
// private            | not inherited        | not inherited          | not inherited

