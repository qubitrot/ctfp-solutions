#include <iostream>
#include <functional>

using namespace std;

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

