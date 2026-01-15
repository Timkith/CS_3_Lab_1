#pragma once

#include "IGenerator.h"
#include <Fib2Functor.h>
#include <IFunctor.h>
#include <Pair.h>
#include <IFunctor.h>






namespace gens {
    
    template<typename T>
    using IEndoFunctor = functors::IFunctor<T,T>;

    template<class T>
    class FunctorGenerator : public IGenerator<T>
    {
        T _current{};
        IEndoFunctor<T> _func{};
    public:
        FunctorGenerator(IEndoFunctor<T> func) : _current(func),_func(func){}

        IGenerator<T>& Next() override {
            _current = _func.eval();
            return *this;
        }

        const T& GetCurrent() const override{
            return _current;
        }

        [[nodiscard]] static bool HasNext() {
            return true;
        }
    };

    template<typename T>
    functors::FunctorT<T> functor(IEndoFunctor<T> funс) {
        return smartptr::MakeUnique<FunctorGenerator<T>>(smartptr::MoveRef(func));
    }
}



