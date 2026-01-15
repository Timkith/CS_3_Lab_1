#pragma once

#include "IFunctor.h"

namespace functors {
    template<class T>
    class Fib2Functor : public IFunctor<T,T> {
        T _prev{};
        T _beforePrev{};
    public:

        Fib2Functor(T beforePrev, T prev) : _prev(prev), _beforePrev(beforePrev) {}

        T operator()() override{
            T curr = _prev + _beforePrev;
            _beforePrev = _prev;
            _prev = curr;
            return curr;
        }

        T eval() override {
            T curr = _prev + _beforePrev;
            _beforePrev = _prev;
            _prev = curr;
            return curr;
        }
    };
}

