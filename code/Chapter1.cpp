#include <iostream>
#include <functional>

using namespace std;

template<class T>
T id(T a) {
    return a;
}

template<class A, class B, class C>
function<C(A)> compose(function<C(B)>& f, function<B(A)>& g) {
    return [&](A a){ return f(g(a)); }; 
}

template<class A, class B>
bool respects_id_with(function<B(A)>& f, A a) {
    function<A(A)> idA = id<A>;
    B x = f(a);
    B y = compose<A,A,B>(f,idA)(a);
    B z = compose<A,B,B>(idA,f)(a);
    return (x == y && x == z);
}
