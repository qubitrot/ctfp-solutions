#include <iostream>
#include <map>
#include <functional>
#include <cstdlib>
#include <variant>

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

int fib(int n) {
    if (n <= 0) return 1;
    return fib(n-1) + fib(n-2);
}

int rand_unit(std::monostate a) {
    return rand();
}

int fixed_seed_rand(int seed) {
    srand(seed);
    return rand();
}

int main() {
    Memoized<int,int> m_fib(fib);

    //m_fib(50);
    std::cout << "first\n";
    //m_fib(50);
    std::cout << "second\n";

    srand(1);
    std::cout << rand() << " unmemoized \n";
    std::cout << rand() << " unmemoized \n";

    Memoized<std::monostate,int> m_rand(rand_unit);
    std::cout << m_rand({}) << " memoized \n";
    std::cout << m_rand({}) << "\n";

    Memoized<int,int> m_fsr(fixed_seed_rand);
    std::cout << m_fsr(1) << "\n";
    std::cout << m_fsr(1) << "\n";

    return 0;
}
