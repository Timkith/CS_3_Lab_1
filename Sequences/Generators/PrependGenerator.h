#pragma once

#include "IGenerator.h"

namespace gens
{

    template <class T>
    class PrependGenerator : public IGenerator<T>
    {
        using Generator = GeneratorT<T>;

        Generator _gen;
        T _value;
        bool _prepended = true;

    public:
        PrependGenerator(Generator g, T val) : _gen(smartptr::MoveRef(g)),
                                               _value(smartptr::MoveRef(val)),
                                               _prepended(true)
        {
        }

        IGenerator<T> &Next() override
        {
            if (_prepended)
            {
                _prepended = false;
                return *this;
            }

            _gen->Next();
            return *this;
        }

        [[nodiscard]] bool HasNext() const override
        {
            if (_prepended)
            {
                return true;
            }

            return _gen->HasNext();
        }

        const T &GetCurrent() const override
        {
            if (_prepended)
            {
                return _value;
            }

            return _gen->GetCurrent();
        }
    };

    template <class T>
    GeneratorT<T> prepend(GeneratorT<T> base, T v)
    {
        return smartptr::MakeUnique<PrependGenerator<T>>(smartptr::MoveRef(base), smartptr::MoveRef(v));
    }

} // namespace gens