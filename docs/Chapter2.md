---
title: Chapter 2
nav_order: 2
---

# Chapter 2 #
{:.no_toc}
## Types and Functions ##
{:.no_toc}

* TOC
{:toc}

----------------

### Challenge 1 ###

In C++ we can memoize a function by wrapping it in a function object which
holds the cache,
```c++
#include <map>
#include <functional>

template <class A, class B>
struct Memoized
{
private:
    std::function<B(A)> func;
    std::map<A,B>       cache;

public:
    Memoized(std::function<B(A)> f) : func(f) {}     
    Memoized(B (*f)(A)) : func(f) {}

    B operator()(A a) {
        auto it = cache.find(a);
        if (it != cache.end())
            return it->second;
        B b = func(a);
        cache[a] = b;
        return b;
    }
};
```
We can test this by memoizing this naive Fibonnaci function:
```c++
int fib(int n) {
    if (n <= 0) return 1;
    return fib(n-1) + fib(n-2);
}

int main() {
    Memoized<int,int> m_fib(fib);

    m_fib(50);
    std::cout << "first\n";
    m_fib(50);
    std::cout << "second\n";

    return 0;
}
```
The first call takes several seconds to return, but second returns immediately.
`m_fib` can be improved on by writing a version that memoizes its intermediate
results.

### Challenge 2 ###

We want memoize `rand()` from `cstdlib`, but in order to do so it needs to take
input. The Unit type is C++ is called `std::monostate` so we can wrap the call
to `rand` in a new function:
```c++
int rand_unit(std::monostate a) {
    return rand();
}
```
Memoizing this produces the behavior we expect, but not the behavior we want 
from a random number generator, because of `rand()`'s impurity:
```c++
int main() {
    srand(1);
    std::cout << rand() << " unmemoized \n";
    std::cout << rand() << " unmemoized \n";

    Memoized<std::monostate,int> m_rand(rand_unit);
    std::cout << m_rand({}) << " memoized \n";
    std::cout << m_rand({}) << "\n";

    return 0;
}

// returns:
// 1804289383 unmemoized 
// 846930886  unmemoized 
// 1681692777 memoized 
// 1681692777 memoized  
```

### Challenge 3 ###

```c++
int fixed_seed_rand(int seed) {
    srand(seed);
    return rand();
}
```
This function can be considered pure, since it always returns the same output
for a given input, and therefore it can be memoized.

### Challenge 4 ###

1. The factorial function is pure; its output is fully determined from its input.
2. `std::getchar()` is not pure; it depends on user input. In fact if it were pure it could only ever return one thing, since its input type is unit (called `void` in c++, confusingly).
3. This function is not pure because writing to the terminal is a side effect and not reflected in the output.
4. The use of `static` makes the function impure. If `f` is called twice with the same input, the outputs will differ.

### Challenge 5 ###

There are $2^2 = 4$ functions from `Bool` to `Bool`. In Haskell they are
```haskell
not :: Bool -> Bool
not True  = False
not False = True

-- Also known as `const True`
true :: Bool -> Bool
true _ = True

-- Also known as `const False`
false :: Bool -> Bool
false _ = False

-- Also known as `id`
same :: Bool -> Bool
same b = b
```

### Challenge 6 ###

Omitting identity arrows, which are always there:

![diagram]({{site.baseurl}}/assets/img/ch2c6.png)

We need to consider the composition of these arrows, but since 
`const a . f == const a` for all `a` and `f`, these are the only ones!
