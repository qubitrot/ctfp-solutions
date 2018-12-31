#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

constexpr double pi = 3.14159;

class Shape
{
public:
    virtual ~Shape();
    virtual double area() =0;
    virtual double circ() =0;
};

class Circle : public Shape
{
public:
    Circle(double r) : _r(r) {}
    double area() {
        return pi * _r * _r;
    }
    double circ() {
        return 2*pi*_r;
    }

private:
    double _r;
};

class Rectangle : public Shape
{
public:
    Rectangle(double d, double h) : _d(d), _h(h) {}
    double area() {
        return _d * _h;
    }
    double circ() {
        return 2*_d + 2*_h;
    }

private:
    double _d;
    double _h;
};

class Square : public Rectangle
{
public:
    Square(double w) : Rectangle(w,w) {}
};

int main() {
    return 0;
}
    
