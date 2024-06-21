#include <bits/stdc++.h>
using namespace std;
class Shape {
  public:
    virtual double area() = 0;
    virtual string shapeName() = 0;
};

class Circle: public Shape {
  int radius;
  public:
    Circle(int r) {
        radius = r;
    }
    double area() override {
      return 3.14*radius*radius;
    }

    string shapeName() override {
      return "Circle";
    }

};

class Rectangle: public Shape {
  int length;
  int breadth;
  public:
    // different way of writing constructor
    Rectangle(int l, int b) : length(l), breadth(b) {}
    double area() override {
      return length * breadth;
    }

    string shapeName() override {
      return "Rectangle";
    }
};

void printArea(Shape *s) {
  cout << "Area of " << s->shapeName() << " is "  << s->area() << endl;
}

int main() {
  Shape* ptr;
  Circle *circle = new Circle(10);
  Rectangle *rect = new Rectangle(10,20);

  // area of circle
  ptr = circle;
  printArea(ptr);

   // area of rectangle
   ptr = rect;
   printArea(ptr);
  return 0;
}


/*

Virtual Function: is a function which is defined in base class, but overriden in derived class.
Pure Virtual Function: is a virtual function, which does not have any implementation in base class, and is implemented in defined class.
    - pure virtual function is defined in bases class as virtual void area() = 0;
    - pure virtual function always returns 0 in base class
    - pure virtual function makes the class abstract.
    - if derived class does not implement pure virtual function, it also becomes abstract class.
Abstract class:
    - A Abstract class is a class which is meant to be derived.
    - Class becomes abstract when it has at least 1 virtual function.
    - Abstract class cannot be instantiated.

*/