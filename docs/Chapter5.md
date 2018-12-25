---
title: Chapter 5
nav_order: 5
---

# Chapter 5 #
{:.no_toc}

## Products and Coproducts ##
{:.no_toc}

* TOC
{:toc}

-----------------

### Challenge 1 ###

Let $A$ and $B$ both be terminal objects in some category. By definition, there
is a unique morphism $f : A \to B$ and a unique morphism $g : B \to A$. 
Consider the composition $g \circ f \in \text{Hom}(A,A)$. Since $A$ is a 
terminal object, there can only be one morphism in $\text{Hom}(A,A)$, namely 
$\text{id}\_A$, so $g \circ f = \text{id}\_A$. Likewise $f \circ g = id\_B$. 
Therefore $f$ is the unique isomorphism between $A$ and $B$, with $g$ as its 
inverse.

### Challenge 2 ###

The product of objects $A$ and $B$ in a poset does not always exists.
When it does exist, it is the largest object $P$ such that $P \le A$ and 
$P \le B$.

*Proof:* Let $P$ and $P'$ be candidates for the product between $A$ and $B$,
with projectors $f : P \to A$, $g : P \to B$, $f' : P' \to A$, and $g' \to B$.
There are two cases:

1. If $P$ and $P'$ are incomparable, then a morphism cannot be found between
   them and so the product doesn't exist.

2. If they are comparable, then suppose without loss of generality that 
   $P' \le P$. Then by definition there exists a unique morphism $h : P' 
   \to P$. Since a poset is a thin category, this must satisfy

   $$ f \circ h = f' \,\, \land \,\, g \circ h = g'$$

   as there are no other morphisms in the hom-sets. Therefore $P$ is the
   superior candidate for the product.

If we're considering a total order, case 1 doesn't apply and the product always
exists. It is also interesting to note that with only a slight modification the 
above proof can be applied to any thin category.

### Challenge 3 ###

The coproduct of objects $A$ and $B$ in a poset does not always exist.
When it does exist, is the smallest object $P$ such that $P \ge A$ and
$P \ge B$.

*Proof:* Just reverse the arrows.

### Challenge 4 ###

```c++
template<class L, class R>
class Either {
    L    _left;
    R    _right;
    bool _is_left;

    either(L l, R r, bool il) 
        : _left(l), _right(r), _is_left(il) {}

public:
    static either<L,R> left(L l)  { return either(l, NULL, true);  }
    static either<L,R> right(R r) { return either(NULL, r, false); }

    bool is_left() const { return _is_left; }
    L    left()    const { return _left;    }
    R    right()   const { return _right;   }
};
```

### Challenge 5 ###

`Either<int,bool>` is a "better" coproduct than `int` equipped with these
injections:
```c++
int i(int n)  { return n; }
int j(bool b) { return b? 0: 1; }
```
We can see this by defining
```c++
int m(Either<int,bool> const& e) {
    if (e.is_left()) return i(e.left()); //same as just e.left()
    else             return j(e.right());
}
```
and noting that
```c++
m(left(int))   == i(int)
m(right(bool)) == j(bool)
```

### Challenge 6 ###

`int` cannot be a better coproduct than `Either` because there is no way to
tell which object an element is 'sourced' from. Is 0 from `int` or from `bool`?

### Challenge 7 ###

The injections
```c++
int i(int n) { 
    if (n < 0) return n; 
    return n + 2;
}
int j(bool b) { return b? 0: 1; }
```
can be factorized by by the same function `m` above (substituting the new `i`).

However, it's interesting to note that `m` is *almost* invertible. It fails
because `i` maps both `INT_MAX` and `INT_MIN+1` to `INT_MIN+2`. If we instead
use an unbounded type `Integer`, then we'd have `Integer ~ Either<Integer,Bool>`.

### Challenge 8 ###

Here's one: `Either<int,pair<bool,bool>>`.
