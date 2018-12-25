#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

template<class L, class R>
class Either {
    L    _left;
    R    _right;
    bool _is_left;

    Either(L l, R r, bool il) 
        : _left(l), _right(r), _is_left(il) {}

public:
    static Either<L,R> left(L l)  { return Either(l, NULL, true);  }
    static Either<L,R> right(R r) { return Either(NULL, r, false); }

    bool is_left() const { return _is_left; }
    L    left()    const { return _left;    }
    R    right()   const { return _right;   }
};

int m(Either<int,bool> const& e) {
    if (e.is_left()) return i(e.left()); //same as just e.left()
    else             return j(e.right());
}
