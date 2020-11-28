#include <iostream>
using namespace std;

//class A {
//public:
//    A() { cout << "A "; }
//    virtual ~A() { cout << "a "; }
//};
//
//class B : public virtual A {
//public:
//    B() { cout << "B "; }
//    virtual ~B() { cout << "b "; }
//};
//
//class C : public virtual A {
//public:
//    C() { cout << "C "; }
//    virtual ~C() { cout << "c "; }
//};
//
//class D : public B, public C {
//public:
//    D() { cout << "D "; }
//    virtual ~D() { cout << "d "; }
//};
class Vehicle {
public:
    virtual void honk() = 0;
};

class Car : public Vehicle {
public:
    void honk() { cout << "Beep!"; }
};

class Boat : public Vehicle {
public:
    void honk() { cout << "Toot!"; }
};

class Hovercraft : public Car, public Boat {
public:
   
};

int main()
{
    Hovercraft h;
    Car::h.honk()
    return 0;
}