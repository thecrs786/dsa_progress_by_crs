// OOPS in C++ (Object Oriented Programming System)

//Topics to be covered:

// 1. Class and Objects
// 2. Access specifiers
// 3. Encapsulation
// 4. Constructor and Destructor
// 5. this pointer
// 6. Shallow and Deep Copy
// 7. Inheritance
// 8. Polymorphism
// 9. Function Overloading 
// 10. Virtual Functions
// 11. Abstraction
// 12. Static Keyword

// CLASS AND OBJECTS

/* objects are entities in the real world
   class is a like a blueprint of these entities 
*/
#include<iostream>

using namespace std;

// Syntax to create a class

class Teacher{ // class followed by class name
    public: // access specifier
    // we can't access private members outside the class
    // by default, all members are private
    // so, we need to specify public to access them outside the class

    // properties/attributes

    string name;
    string dept;
    string subject;

    // methods/member functions

    void changeDept(string newDept){
        dept = newDept;
    }

    private: // encapsulated data

    double salary; // private member, can't be accessed outside the class

    // but we can access it using public member functions

    public:
    void setSalary(double s){  // setter function
        salary = s;
    }
    void showSalary(){ // getter function
        cout<<"Salary: "<<salary<<endl;
    }

}; // class ends with a semicolon

int main(){

    // creating objects

    Teacher t1; // object of class Teacher, creating one object
    Teacher t2, t3; // creating multiple objects

    // accessing properties and methods of a class is done using the dot operator

    t1.name = "John";
    t1.dept = "CSE";
    t1.subject = "Data Structures";
    // t1.salary = 50000; invalid as salary is private

    cout<<t1.name<<endl; //we can't access it as name is private by default

    // ACCESS SPECIFIERS

    /*
    1. Public: members are accessible from outside the class
    2. Private: members are not accessible from outside the class
    3. Protected: members are not accessible from outside the class, but are accessible in derived classes
    4. Default: members are private by default
    */
   
    t1.setSalary(50000); // setting salary using public member function
    t1.showSalary(); // showing salary using public member function

// THERE ARE 4 PILLARS OF OOPs
// 1. Abstraction
// 2. Encapsulation
// 3. Inheritance
// 4. Polymorphism

// Encapsulation in OOPs

// Encapsualtion is the wrapping up of data and functions into a single unit called class
// Helps in data hiding
// Data can be made private and can be accessed using public member functions


    return 0;
}
