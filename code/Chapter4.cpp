#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

template<class A> class optional {
    bool _isValid;
    A    _value;
public:
    optional()    : _isValid(false) {}
    optional(A v) : _isValid(true), _value(v) {}
    bool isValid() const { return _isValid; }
    A value() const { return _value; }
};

optional<A> id(A a) {
    return optional<A>(a);
}

optional<double> safe_root(double x) {
    if (x >= 0) return optional<double>{sqrt(x)};
    else        return optional<double>{};
}

optional<double> safe_reciprocal(double x) {
    if (x != 0) return optional<double>{1/x};
    else        return optional<double>{};
}

template<class A, class B, class C>
function<optional<C>(A)> 
compose_optional(function<optional<C>(B)> f, function<optional<B>(A)> g) {
    return [&](A a){ optional<B> b = g(a);
                     if (b.isValid()) return f(b.value());
                     else             return optional<C>();
                   };
}

optional<double> safe_root_reciprocal(double x) {
    auto f = function<optional<double>(double)>(safe_root);
    auto g = function<optional<double>(double)>(safe_reciprocal);
    return compose_optional(f,g)(x);
}

int main() {
    auto a = safe_root_reciprocal(4);
    cout << a.value() << "\n";
    cout << a.isValid() << "\n";

    return 0;
}
