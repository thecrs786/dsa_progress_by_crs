//POLYMORPHISM

/* Poymorphism is the ability of objects to take on different forms
    or behave in different ways depending on the context in which they are used.

There are two types of polymorphism in C++:
1. Compile-time polymorphism (Static polymorphism)
    - Constructor Overloading
    - Function Overloading
    - Operator Overloading
2. Run-time polymorphism (Dynamic polymorphism)
    - Achieved using Inheritance and Virtual Functions
*/

#include<iostream>
using namespace std;

class Student{
    public:
    string name;

//1. Constructor Overloading : multiple constructors with different parameters

    Student(){
        cout<<"non-parameterized constructor\n";
    }
    Student(string name){
        this->name = name;
        cout<<"parameterized constructor\n";
    }
    // compiler differentiates between constructors based on number and type of parameters
    // and then decides which constructor to call based on arguments passed during object creation

// 2. Function Overloading : multiple functions with same name but different parameters

    int add(int a, int b){ // 1. return type : int, parameters : 2 integers
        return a+b;
    }
    double add(double a, double b){ // 2. return type : double, parameters : 2 doubles
        return a+b;
    }
    int add(int a, int b, int c){ // 3. return type : int, parameters : 3 integers
        return a+b+c;
    }
    double add(double a, double b, double c){ // 4. return type : double, parameters : 3 doubles
        return a+b+c;
    }

    // The compiler differentiates between functions based on number and type of parameters
    // and decides which function to call based on arguments passed during function call

    //anothrer example of function overloading
    void display(int a){
        cout<<"Integer: "<<a<<endl;
    }
    void display(double b){
        cout<<"Double: "<<b<<endl;
    }
    // void display(string s){ // ❌ This will give error because no matching function found
    //     cout<<"String: "<<s<<endl;

// 3. Operator Overloading : giving special meaning to operators when used with user-defined data types
    
    // Overloading + operator to concatenate names of two students
    void operator + (Student &s){
        cout<<"Concatenated Name: "<<name + " " + s.name<<endl;
    }

    // Another example: Overloading == operator to compare two students by name
    bool operator == (Student &s){
        return name == s.name;
    }

    // Overloading << operator to print Student object directly
    friend ostream& operator << (ostream &out, Student &s){
        out << "Student Name: " << s.name;
        return out;
    }

    // Overloading >> operator to input Student name
    friend istream& operator >> (istream &in, Student &s){
        cout << "Enter name: ";
        in >> s.name;
        return in;
    }

    // Overloading = operator to copy name from another student
    void operator = (Student &s){
        this->name = s.name;
    }
    
};


int main(){
 
    Student s1; // no arguments passed -> non-parameterized constructor called
    Student s6("thecrs"); // argument passed -> parameterized constructor called

    // this was an example of constructor overloading (compile-time polymorphism)

    cout<<s1.add(2,3)<<endl; // calls int add(int, int)
    cout<<s1.add(2.5,3.5)<<endl; // calls double add(double, double)
    cout<<s1.add(1,2,3)<<endl; // calls int add(int, int, int)
    cout<<s1.add(1.1,2.2,3.3)<<endl; // calls double add(double, double, double)    

    // cout<<s1.add(2,3.5)<<endl; // ❌ This will give error because no matching function found

    // this was an example of function overloading (compile-time polymorphism)

    s1.display(5); // calls display(int)
    s1.display(5.5); // calls display(double)

    // s1.display("thecrs"); // ❌ This will give error because no matching function found

   Student s2("Alice");
    Student s3("Bob");

    // Using + operator to concatenate names
    s2 + s3; // prints: Concatenated Name: Alice Bob

    // Using == operator to compare names
    if(s2 == s3){
        cout << "Names are same" << endl;
    } else {
        cout << "Names are different" << endl; // prints this
    }

    // Using << operator to print object
    cout << s2 << endl; // prints: Student Name: Alice

    // Using >> operator to input object
    Student s4("");
    cin >> s4; // user inputs a name
    cout << s4 << endl; // prints entered name

    // Using = operator to copy name
    s4 = s2;
    cout << s4 << endl; // prints: Student Name: Alice



    return 0;
}
