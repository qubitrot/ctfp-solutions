---
title: Chapter 4
nav_order: 4
---

# Chapter 4 #
{:.no_toc}

## Kleisli Categories ##
{:.no_toc}

* TOC
{:toc}

-----------------

### Challenge 1 ###

Composition is straightforward. If the first function returns invalid, return
invalid. Otherwise extract the value and feed it into the second function.
```c++
template<class A, class B, class C>
function<optional<C>(A)> 
compose_optional(function<optional<C>(B)> f, function<optional<B>(A)> g) {
    return [&](A a){ optional<B> b = g(a);
                     if (b.isValid()) return f(b.value());
                     else             return optional<C>();
                   };
}
```
The identity must satisfy $f \circ \text{id} = \text{id} \circ f = f$. 
To make the types work with our composition we need $\text{id} :
A \to \text{optional\<A\>}$. It can only be
```c++
optional<A> id(A a) {
    return optional<A>(a);
}
```
### Challenge 2 ###

In the same vein as `safe_root`:
```c++
optional<double> safe_reciprocal(double x) {
    if (x != 0) return optional<double>{1/x};
    else        return optional<double>{};
}
```

### Challenge 3 ###

```c++
optional<double> safe_root_reciprocal(double x) {
    auto f = function<optional<double>(double)>(safe_root);
    auto g = function<optional<double>(double)>(safe_reciprocal);
    return compose_optional(f,g)(x);
}
``
