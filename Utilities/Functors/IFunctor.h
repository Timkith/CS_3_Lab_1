#pragma once


namespace functors {

    template<typename U, typename V>
    class IFunctor {
    public:
        virtual V eval() = 0;
        virtual V operator()() = 0;

        virtual ~IFunctor() = default;
    };
}

