#include<iostream>

using namespace std;

class Teacher{
    public:

    string name;
    string dept;
    string subject;

    // non-parameterized constructor
    Teacher(){
        dept = "CSE"; //default value for all objects
    }

    // parameterized constructor
    Teacher(string name, string dept, string subject){
        this->name = name; // 'this' pointer to distinguish between class member and parameter
        this->dept = dept;
        this->subject = subject;
        
    }

    void changeDept(string newDept){
        dept = newDept;
    }

    void getinfo(){
        cout<<"Name: "<<name<<endl;
        cout<<"Dept: "<<dept<<endl;
        cout<<"Subject: "<<subject<<endl<<endl;
    }

    // Copy Constructor
    Teacher(const Teacher &t){ // reference to another object of same class
        // however const was not necessary, it is a good practice to use it
        // because we don't want to modify the original object while copying
        // name = "bob"  we cannot do this, we need to copy from object t

        cout<<"i am in copy constructor"<<endl;
        name = t.name; // copying values from object t to current object
        dept = t.dept;
        subject = t.subject;
        // if no copy constructor is defined, compiler provides a default copy constructor
        // if we define our own, it overrides the default one

        // Changes in object through copy constructor does not reflects in original object
        // because we are copying values, not references (deep copy)
        // if we want changes to reflect in original object, we need to use pointers

        
    }
};

// Shallow Copy vs Deep Copy

/* A shallow copy of an object copies all of the member values from
   one object to another. For example, Teacher t2(t1) and the default copy constructor
   create a shallow copy of t1 into t2. 
   If the members are value types (like int, double, std::string), the objects behave independently. 
   If the members are pointers, both objects share the same memory.

   A deep copy, on the other hand, not only copies the member values but also
   make copies of any dynamically allocated memory that the member points to.

*/

/*| Copy type             | our code (`std::string`)  | Members are pointers                         |
  | --------------------- | ------------------------- | -------------------------------------------- |
  | our copy constructor  | behaves deep              | would be shallow unless manually deep copied |
  | Default compiler copy | behaves deep              | shallow → same memory shared                 |

*/

/* Normally when we use int x =5, the memory is allocated at the compile time
   but when we use int *p = new int(5), the memory is allocated at the runtime
   and we need to free it using delete p;

   If we have a class with a pointer member, and we use the default copy constructor,
   both objects will point to the same memory location. So, if we modify one object,
   the other object will also be affected. This is called shallow copy.

   To avoid this, we need to define our own copy constructor that performs a deep copy.
   In deep copy, we allocate new memory for the pointer member and copy the value
   from the original object to the new memory location.
    This way, both objects will have their own copies of the pointer member,
        
*/

int main(){
    Teacher t1("Alice", "ECE", "Signals"); // Object creation, parameterized constructor is called here
   t1.getinfo();
    // cout<<t1.salary<<endl; // Error: salary is private

    // before defining copy constructor
    Teacher t2(t1); //default Copy constructor, creates t2 as a copy of t1
    t2.getinfo();



    return 0;
}
