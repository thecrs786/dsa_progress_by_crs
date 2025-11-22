// CONSTRUCTOR

/* Constructor is a special method invoked automatically at time of object creation.
   Used for Initialization.

    Characteristics:
    1. Name of constructor is same as class name
    2. It has no return type, not even void
    3. It is automatically invoked at the time of object creation
    4. Memory allocation happens when constructor is called
    5. It can have default arguments
    6. We cannot refer to constructor by its name, we can call it only once
*/

/* TYPES OF CONSTRUCTORS:
   1. Default constructor: No parameters
   2. Parameterized constructor: with parameters
   3. Copy constructor: Initializes an object using another object of the same class
*/

#include<iostream>

using namespace std;

class Account{
    public:

    // Default Constructor (no parameters)

    Account(){ // Default Constructor (Name same as class name)
        cout<<"Constructor called!"<<endl; // will be called automatically when object is created   
        // Will be printed automatically when object is created

        username = "abc"; // automatic initialization
        password = "default"; // automatic initialization
    }
    string name;
    string username;

    private:
    double balance;
    string password;
    
};

class Teacher {
public:

    // we declare constructor always in public section because it does have access to private members
    // as it is called from main function where object is created

    Teacher() {
       // string dept = "CSE"; WRONG 
       // If we want dept to be a member of the class, 
       // we must declare it inside the class scope, not in constructor
       dept = "CSE"; // ✅ works fine because dept is a class member
       // for all objects, dept will be initialized to "CSE"
       // for all other members, we can initialize them here or leave them uninitialized
    }

    string name;    // member of the class
    string dept;    // member of the class
    string subject; // member of the class

    void changeDept(string newDept) {
        dept = newDept;  
        // ✅ works fine because dept is a class member
        // ❌ would not work if dept was declared only inside the constructor
    }
    private:
    double salary;

    public:
    void setSalary(double s){
        salary = s;
    }
    void showSalary(){
        cout<<"Salary: "<<salary<<endl;
    }

};

//Parameterized Constructor

class Student {
public:
    string name;
    int age;
    int rollNo;

    // Parameterized Constructor
    Student(string n, int a) { // constructor with parameters, can have multiple parameters
        name = n; // initializing class members with parameters
      //  name = class' name , n = parameter's name
      // if we don't use different names, we can use 'this' pointer
      // this->name = name; // 'this' pointer points to the current object

        age = a;  // initializing class members with parameters

    }

    // example of this pointer usage
    
   // Student(int rollNo){ //no difference in parameter name and class member name
    //    this->rollNo = rollNo; // using 'this' pointer to distinguish between class member and parameter
    //} we cannot have two constructors with the same signature (int) even if you intend one to set rollNo and one to set age.

   // There can be multiple constructors in a class with different parameters (Constructor Overloading)

   Student(){ // another constructor with no parameters (default constructor)
    cout<<"Hello from default constructor"<<endl;
   }

   Student(int b){ // another constructor with one parameter
     age= b;
   }
    void info(){
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Roll: "<<rollNo<<endl;
    }
};




int main(){

    Account acc1; // Object creation, constructor is called here

    cout<<acc1.name<<endl; // default value (garbage value) because not initialized

    cout<<acc1.username<<endl; // prints "abc" because initialized in constructor

    Teacher t1; // Object creation, constructor is called here

    cout<<t1.dept<<endl; // prints "CSE" because initialized in constructor
    
    // initializing object using parameterized constructor
    Student s1("Alice", 20); // Object creation, parameterized constructor is called here

    cout<<s1.name<<endl; // prints "Alice"
    cout<<s1.age<<endl;  // prints 20

    s1.info(); // prints name and age

    // Student s1(20); wrong because s1 is already declared above

    Student s2; // Object creation, default constructor is called here
    Student s3(22); // Object creation, parameterized constructor with one parameter is called

    s3.info(); // prints age 22 and name garbage value
    s2.info(); // prints garbage values for both name and age
    
    // Note: If we define any constructor, the default constructor is not provided by the compiler
    // So, if we want a default constructor, we must define it ourselves

    // this pointer in constructor

    // this pointer is a special pointer that points to the current object
    // it is used to access the members of the current object
    // this->prop is same as *(this).prop

    Student s4(22);
    s4.info(); // prints age 22
    

    return 0;
}
