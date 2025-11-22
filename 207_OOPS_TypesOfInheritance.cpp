// Types of Inheritance in C++
/*
1. Single Inheritance: A class inherits from one base class.
2. Multiple Inheritance: A class inherits from more than one base class.
3. Multilevel Inheritance: A class inherits from a derived class, forming a chain.
4. Hierarchical Inheritance: Multiple classes inherit from a single base class.
5. Hybrid Inheritance: A combination of two or more types of inheritance.   
    (e.g., multiple + multilevel)
*/

#include <iostream>
using namespace std;

// =====================================
// Base Classes
// =====================================
class Person { // Base class
public:
    string name;
    int age;

    Person(string n, int a) {
        name = n;
        age = a;
        cout << "Person constructor called\n";
    }

    void displayPerson() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Teacher { // Another base class for multiple inheritance
public:
    string subject;

    Teacher(string s) {
        subject = s;
        cout << "Teacher constructor called\n";
    }

    void displayTeacher() {
        cout << "Subject: " << subject << endl;
    }
};

// =====================================
// 1. Single Inheritance
// =====================================
class Student : public Person {
public:
    int rollNo;

    Student(string n, int a, int r) : Person(n, a) {
        rollNo = r;
        cout << "Student constructor called\n";
    }

    void displayStudent() {
        displayPerson();  // Accessing base class method
        cout << "Roll No: " << rollNo << endl;
    }
};

// =====================================
// 2. Multiple Inheritance
// =====================================
class TA : public Teacher, public Student {
public:
    TA(string n, int a, int r, string s) : Teacher(s), Student(n, a, r) {
        cout << "TA constructor called\n";
    }

    void displayTA() {
        displayStudent();  // From Student -> Person
        displayTeacher();  // From Teacher
    }
};

// =====================================
// 3. Multilevel Inheritance
// =====================================
class Graduate : public Student {
public:
    string researchTopic;

    Graduate(string n, int a, int r, string topic) : Student(n, a, r) {
        researchTopic = topic;
        cout << "Graduate constructor called\n";
    }

    void displayGraduate() {
        displayStudent();
        cout << "Research Topic: " << researchTopic << endl;
    }
};

// =====================================
// 4. Hierarchical Inheritance
// =====================================
class Professor : public Person {
public:
    string dept;

    Professor(string n, int a, string d) : Person(n, a) {
        dept = d;
        cout << "Professor constructor called\n";
    }

    void displayProfessor() {
        displayPerson();
        cout << "Department: " << dept << endl;
    }
};

// =====================================
// 5. Hybrid Inheritance
// =====================================
class HybridTA : public Graduate, public Teacher {
public:
    HybridTA(string n, int a, int r, string topic, string s) 
        : Graduate(n, a, r, topic), Teacher(s) {
        cout << "HybridTA constructor called\n";
    }

    void displayHybridTA() {
        displayGraduate();
        displayTeacher();
    }
};

// =====================================
// MAIN FUNCTION - TESTING
// =====================================
int main() {
    cout << "=== Single Inheritance ===\n";
    Student s("Alice", 20, 101);
    s.displayStudent();

    cout << "\n=== Multiple Inheritance ===\n";
    TA ta("Bob", 25, 201, "Mathematics");
    ta.displayTA();

    cout << "\n=== Multilevel Inheritance ===\n";
    Graduate g("Charlie", 24, 301, "AI Research");
    g.displayGraduate();

    cout << "\n=== Hierarchical Inheritance ===\n";
    Professor p("Dr. Smith", 45, "Physics");
    p.displayProfessor();

    cout << "\n=== Hybrid Inheritance ===\n";
    HybridTA hta("David", 26, 401, "Quantum Computing", "Physics");
    hta.displayHybridTA();

    return 0;
}

