#pragma once

#include <SmartPtr.h>

namespace gens
{

    template <typename T>
    class IGenerator
    {
    public:
        virtual ~IGenerator() = default;

        virtual IGenerator<T> &Next() = 0;
        virtual const T &GetCurrent() const = 0;
        [[nodiscard]] virtual bool HasNext() const = 0;
        [[nodiscard]] virtual bool GetGuar() const = 0;
    };

    template <typename T>
    using GeneratorT = smartptr::UniquePtr<IGenerator<T>>;

    template <class T>
    class Generamble
    {
    public:
        virtual ~Generamble() = default;

        virtual GeneratorT<T> GetGenerator() = 0;
    };

} // namespace gens
