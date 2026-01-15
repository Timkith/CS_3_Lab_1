#pragma once

#include "IGenerator.h"

namespace gens
{

    template <class T>
    class AppendGenerator : public IGenerator<T>
    {
        using Generator = GeneratorT<T>;

        Generator _gen;
        T _value;
        bool _is_expired = false;

    public:
        AppendGenerator(Generator g, T val) : _gen(smartptr::MoveRef(g)),
                                              _value(smartptr::MoveRef(val)),
                                              _is_expired(false) {}

        IGenerator<T> &Next() override
        {
            if (_gen->HasNext())
            {
                _gen->Next();
                return *this;
            }
            if (!_is_expired)
            {
                _is_expired = true;
                return *this;
            }

            throw Exceptions::IndexOutOfRange();

            if (!_is_expired && _gen->HasNext())
            {
                _gen->Next();
                if (!_gen->HasNext())
                {
                    _is_expired = true;
                }
                return *this;
            }

            if (_is_expired)
            {
                throw Exceptions::IndexOutOfRange();
            }

            _is_expired = true;
            return *this;
        }

        bool HasNext() const override
        {
            return _gen->HasNext() || !_is_expired;
        }

        const T &GetCurrent() const override
        {
            if (_gen->HasNext())
            {
                return _gen->GetCurrent();
            }

            if (!_is_expired)
            {
                return _value;
            }

            throw Exceptions::IndexOutOfRange();
        }
    };


    template <class T>
    GeneratorT<T> append(GeneratorT<T> base, T v)
    {
        return smartptr::MakeUnique<AppendGenerator<T>>(smartptr::MoveRef(base), smartptr::MoveRef(v));
    }
} // namespace gens