#include<iostream>

using namespace std;

class Student{
    public:

    string name;
    double *cgpaptr; // pointer to double

    Student(string name, double cgpa){ // parameterized constructor
        // we are using dynamic memory allocation to allocate memory for cgpa
        this->name = name;
        cgpaptr = new double; // dynamically allocating memory
        *cgpaptr = cgpa; // dereferencing pointer to assign value
    
    }

    Student(Student &s){ // copy constructor
        this->name = s.name;
        // this->cgpaptr = s.cgpaptr; // copies the pointer (shallow copy), so both objects share the same memory
        // Deep Copy: create a new memory location and copy the value
        cgpaptr = new double; // allocate new memory

        *cgpaptr = *(s.cgpaptr); // copy the value from the other object's pointer
    }

    void getInfo(){
        cout<<"Name: "<<name<<" | "<<"CGPA: "<<*cgpaptr<<endl; // dereferencing pointer to get value
    }
};

int main(){
    Student s1("thecrs" , 9.9); // parameterized constructor called
    Student s2(s1); // copy constructor called  

    cout<<"s1 created using parameterized constructor"<<endl;
    s1.getInfo(); // prints s1 info
    cout<<"s2 created using copy constructor"<<endl;
    s2.getInfo(); // prints s2 info, should be same as s1

    s2.name = "hamid"; // modifying s2's name
    *(s2.cgpaptr) = 8.9; // modifying s2's cgpa

    cout<<"After modifying s2's cgpa & name"<<endl;
    s1.getInfo(); // prints s1 info, should remain unchanged if deep copy is done
    s2.getInfo(); // prints s2 info, should reflect the change


    return 0;
}

/*
LOGIC BEHIND POINTER, DEREFERENCING, AND COPY CONSTRUCTOR (DEEP COPY)
=====================================================================

1. Why create a pointer in the class?
   - Instead of storing the value (cgpa) directly, we store it on the heap.
   - This is done using a pointer member (double *cgpaptr).
   - Advantage: shows how shallow vs deep copy behave when memory is dynamically managed.

2. What happens when we allocate memory with 'new'?
   - new double; --> allocates space on the heap for a double value.
   - cgpaptr now holds the address of that memory.
   - This means cgpaptr points to a memory location on the heap.

3. Why dereference the pointer?
   - We can’t directly assign a value to cgpaptr (because it only stores an address).
   - So, to store the actual CGPA value into that memory, we use *cgpaptr = cgpa.
   - Dereferencing (*) means "go to the memory address stored in cgpaptr and place the value there".

4. What happens in shallow copy (default copy constructor)?
   - If object A has cgpaptr → [address X],
   - and we copy it into object B without special handling,
   - then B.cgpaptr will also → [address X].
   - Both A and B now point to the SAME heap memory.
   - Changing value via one object will also affect the other.

5. Why create a new pointer inside the copy constructor (deep copy)?
   - In deep copy, we don’t want two objects to share the same memory.
   - So instead of copying the pointer’s address, we allocate a NEW memory block for the new object.
   - Example:
        A.cgpaptr → [address X with value 9.9]
        B.cgpaptr → [new address Y]
        *B.cgpaptr = *A.cgpaptr (so copy the value, not the address).
   - Now A and B have the same value but live in different memory locations.

6. Flowchart of logic:
   -----------------------------------------------------
   Constructor:
       create cgpaptr → allocate heap memory → store value via dereference
   -----------------------------------------------------
   Shallow Copy:
       new object’s pointer just copies the address → same memory shared
   -----------------------------------------------------
   Deep Copy:
       new object creates its own heap memory → copy value into it → independent
   -----------------------------------------------------
*/

