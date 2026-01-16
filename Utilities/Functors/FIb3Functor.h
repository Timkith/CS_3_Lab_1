#pragma once

#include "IFunctor.h"

namespace functors {
    template<class T>
    class Fib3Functor : public IFunctor<T,T> {
        T _prev{};
        T _beforePrev{};
        T _beforePrevPrev{};
    public:

        Fib3Functor(T beforePrevPrev,T beforePrev, T prev) : _prev(prev), _beforePrev(beforePrev),
        _beforePrevPrev(beforePrevPrev){}

        T operator()() override{
            T curr = _prev + _beforePrev + _beforePrevPrev;
            _beforePrevPrev = _beforePrev;
            _beforePrev = _prev;
            _prev = curr;
            return curr;
        }

        T eval() override {
            T curr = _prev + _beforePrev + _beforePrevPrev;
            _beforePrevPrev = _beforePrev;
            _beforePrev = _prev;
            _prev = curr;
            return curr;
        }
    };
}

