#pragma once

#include <SmartPtr.h>
// #include <FunctorGenerator.h>

namespace functors {

    template<typename U, typename V>
    class IFunctor {
    public:
        virtual V eval() = 0;
        virtual V operator()() = 0;

        virtual ~IFunctor() = default;
    };


    // template <typename T>
    // using FunctorT = smartptr::UniquePtr<gens::IEndoFunctor<T>>;
    //
    // template<typename T, typename... Args>
    // FunctorT<T> MakeFunctor(Args&&... args) {
    //     return FunctorT<T>(T(smartptr::MoveRef(args)...));
    // }
}

