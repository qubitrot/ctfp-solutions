---
title: Chapter 1
nav_order: 1
---

# Chapter 1 #
{:.no_toc}

## Category: The Essence of Composition ##
{:.no_toc}

* TOC
{:toc}

-----------------

### Challenge 1 ###

In C++, the identity is
```c++
template<class T>
T id(T a) {
    return a;
}
```

### Challenge 2 ###

We can compose function in C++ like so:
```c++
#include <functional>

template<class A, class B, class C>
function<C(A)> compose(function<C(B)>& f, function<B(A)>& g) {
    return [&](A a){ return f(g(a)); }; 
}
```
Isn't that excessively verbose? 

### Challenge 3 ###

We can start by defining this predicate:
```c++
template<class A, class B>
bool respects_id_with(function<B(A)>& f, A a) {
    function<A(A)> idA = id<A>;
    B x = f(a);
    B y = compose<A,A,B>(f,idA)(a);
    B z = compose<A,B,B>(idA,f)(a);
    return (x == y && x == z);
}
```
If this predicate returns `true` for all functions `f` with all possible inputs
`a`, then we know that our implementation of compose respects identity. Of 
course testing this explicitly is impossible.

### Challenge 4 ###

The world-wide web cannot be considered a category, at least not with links as
morphisms. Links fail to satisfy the composability condition; if site A links
to site B, and B links to C, it isn't necessarily the case that A links to C. 
Furthermore, sites need not link to themselves! We could instead consider 
"paths" as morphisms: a path exists from A to B if it is possible to reach site
B from A by any number of links (even 0). Then the web could be considered a
category.

### Challenge 5 ###

Facebook fails to be a category (with people as object and friendship as 
morphisms) for the same reason the web does: Friendship isn't transitive!
And are you friends with yourself?

### Challenge 6 ###

A directed a graph is a category when:
* Every node has a edge to itself, and
* For all nodes A and B which have a path (of any length) betwen them, there is an 
  edge from A to B. This is just like the world-wide web example above.
