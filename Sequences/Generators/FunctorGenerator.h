#pragma once

#include "IGenerator.h"
#include <IFunctor.h>


namespace gens {

    template<typename T>
    using IEndoFunctor = functors::IFunctor<T,T>;

    template<class T>
    class FunctorGenerator : public IGenerator<T>
    {
        T _current{};
        IEndoFunctor<T>& _func{};
    public:
        FunctorGenerator(IEndoFunctor<T>& func) : _func(func){}

        IGenerator<T>& Next() override {
            _current = _func.eval();
            return *this;
        }

        const T& GetCurrent() const override{
            return _current;
        }

        [[nodiscard]] bool HasNext() const override {
            return true;
        }
    };

    template<typename T>
smartptr::UniquePtr<IGenerator<T>> functor(IEndoFunctor<T>& func) {
        return smartptr::MakeUnique<FunctorGenerator<T>>(func);
    }
}



