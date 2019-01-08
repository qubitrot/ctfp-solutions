---
title: Chapter 7
nav_order: 7
---

# Chapter 7 #
{:.no_toc}

## Functors ##
{:.no_toc}

* TOC
{:toc}

-----------------

### Challenge 1 ###

A functor `F` must preserve identity, which `fmap _ _ = Nothing` fails to do:
```haskell
fmap id (Just a) == Nothing /= Just a
```

### Challenge 2 ###

The reader functor is defined with
```haskell
instance Functor ((->) r) where
  fmap f g = f . g 
```
and we can see that it satisfies the laws:

1. Respects identity: `fmap id g == id . g == g`
2. Respects compoosition: 
   ```haskell
   (fmap f . fmap g) r == fmap f (g . r) == f . g . r == fmap (f . g) r
   ```

### Challenge 3 ###

```c++
template<class R, class A>
struct Reader
{
    function<A(R)> runReader;
};

template<class R, class A, class B>
Reader<R,B> fmap(function<B(A)> f, Reader<R,A> rdr)
{
    return Reader<R,B>{ [&](R r){ return f(rdr.runReader(r)); } };
}
```

### Challenge 4 ###

`[a]` is a functor with
```haskell
fmap f []     = []
fmap f (x:xs) = f x : fmap f xs
```

*Proof:* Use induction. `[]` is the base case: 
```haskell
fmap id      [] = [] -- Check
fmap (f . g) [] = [] = fmap f . fmap g $ [] -- Check
```
The inductive step: assume `xs` satifies the laws,
```haskell
fmap id      (x:xs) = id x : fmap id xs = x : id xs = (x:xs) -- Check
fmap (f . g) (x:xs) = (f . g) x : fmap (f . g) xs 
                    = f (g x) : fmap f (fmap g xs) -- Assumption enters here
                    = fmap f (g x : fmap g xs)
                    = fmap f . fmap g $ (x:xs) -- Check
```
