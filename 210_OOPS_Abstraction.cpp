// ABSTRACTION IN C++ - 10/10 EXAMPLE

/*
Abstraction: Hiding implementation details and showing only essential features.
- Implemented using access specifiers (public, private, protected).
- Abstract classes define "what to do" but not "how to do it".
- Encapsulation is the data hiding part of abstraction.
- Abstract classes cannot be instantiated; they are meant to be inherited.
*/

#include <iostream>
using namespace std;

// Abstract base class (interface / blueprint)
class Shape {
public:
    // Pure virtual function -> makes Shape an abstract class
    virtual void draw() = 0;    // no implementation, must be overridden
    virtual double area() = 0;  // another pure virtual function example
    virtual ~Shape(){}          // virtual destructor for safe polymorphic deletion
};

// Derived class 1
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    void draw() override { // overriding pure virtual function
        cout << "Drawing a Circle with radius " << radius << endl;
    }

    double area() override {
        return 3.14159 * radius * radius;
    }
};

// Derived class 2
class Rectangle : public Shape {
private:
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    void draw() override {
        cout << "Drawing a Rectangle of " << length << " x " << width << endl;
    }

    double area() override {
        return length * width;
    }
};

// Derived class 3
class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    void draw() override {
        cout << "Drawing a Triangle with base " << base << " and height " << height << endl;
    }

    double area() override {
        return 0.5 * base * height;
    }
};

int main() {
    // ❌ Cannot create object of abstract class
    // Shape s; // ❌ Error

    // ✅ Use pointers/references for abstract class
    Shape* shapes[3]; // array of Shape pointers

    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);
    shapes[2] = new Triangle(3.0, 7.0);

    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();                // calls derived class's draw() at runtime
        cout << "Area: " << shapes[i]->area() << endl;
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }

    return 0;
}

/*
Key Points & Insights:
1. Pure virtual function (`= 0`) is what makes a class abstract.
2. Abstract classes cannot be instantiated directly.
3. Abstract classes can contain multiple pure virtual functions.
4. Derived classes MUST override all pure virtual functions to become concrete (instantiable).
5. Use base class pointers/references to achieve runtime polymorphism (dynamic binding).
6. Virtual destructors are important to safely delete derived objects via base pointers.
7. Abstract classes act as interfaces or blueprints for derived classes.
8. You can mix abstract and non-abstract functions in the same class.
9. Multiple abstract classes can be inherited (interface-like multiple inheritance).
10. Abstraction improves code reusability, flexibility, and maintainability.
*/
