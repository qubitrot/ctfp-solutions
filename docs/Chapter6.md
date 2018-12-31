---
title: Chapter 6
nav_order: 6
---

# Chapter 6 #
{:.no_toc}

## Simple Algebraic Data Types ##
{:.no_toc}

* TOC
{:toc}

-----------------

### Challenge 1 ###

Here it is explicitly:
```haskell
f :: Maybe a -> Either () a
f Nothing  = Left ()
f (Just a) = Right a

f_inv :: Either () a -> Maybe a
f_inv (Left  _) = Nothing
f_inv (Right a) = Just a
```

### Challenge 2 ###

```c++
class Shape
{
public:
    virtual ~Shape();
    virtual double area() =0;
};

class Circle : public Shape
{
public:
    Circle(double r) : _r(r) {}
    double area() {
        return pi * _r * _r;
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

private:
    double _d;
    double _h;
};
```

### Challenge 3 ###

To add the `circ()` method I had to change three definitions, adding:
```c++
class Shape
{
public:
    virtual ~Shape();
    virtual double area() =0;
    virtual double circ() =0;
};

double Circle::circ() {
    return 2*pi*_r;
}

double Rectangle::circ() {
    return 2*_d + 2*_h;
}
```
This could quickly become inconvienent if there are many derived classes.

### Challenge 4 ###

Adding `Square` to the haskell version is easy:
```haskell
data Shape = Circle Float
           | Rect   Float Float
           | Square Float
```
We need to modify our functions too:
```haskell
area (Square w) = w * W
circ (Square w) = 4 * w
```

In C++, it's also easy and we can avoid some duplication of effort by reusing
the methods from `Rect`.
```c++
class Square : public Rectangle
{
public:
    Square(double w) : Rectangle(w,w) {}
};
```

### Challenge 5 ###

Does $a + a = 2 * a$ hold for types? That is, is `Either a a` isomorphic to 
`(Bool,a)`? It is:
```haskell
f :: Either a a -> (Bool,a)
f (Left  a) = (False, a)
f (Right a) = (True,  a)

f_inv :: (Bool,a) -> Either a a
f_inv (False, a) = Left  a
f_inv (True,  a) = Right a
```
