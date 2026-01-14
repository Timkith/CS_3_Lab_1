#pragma once

#include "IGenerator.h"

namespace gens
{

    template <class T>
    class TakeGenerator : public IGenerator<T>
    {
        using Generator = GeneratorT<T>;

        Generator _gen;
        size_t _count;
        size_t _taken = 0;

    public:
        TakeGenerator(Generator g, size_t count) : 
            _gen(smartptr::MoveRef(g)),
            _count(count),
            _taken(0) 
        {}

        IGenerator<T>& Next() override
        {
            if (!HasNext())
            {
                throw Exceptions::IndexOutOfRange();
            }
            
            _gen->Next();
            _taken++;
            return *this;
        }

        bool HasNext() const override
        {
            return _taken < _count && _gen->HasNext();
        }

        const T& GetCurrent() const override
        {
            if (!HasNext())
            {
                throw Exceptions::IndexOutOfRange();
            }
            
            return _gen->GetCurrent();
        }
    };

    template <class T>
    class SkipGenerator : public IGenerator<T>
    {
        using Generator = GeneratorT<T>;

        Generator _gen;
        size_t _skip_count;
        size_t _skipped {};

    public:
        SkipGenerator(Generator g, size_t skip_count) : 
            _gen(smartptr::MoveRef(g)),
            _skip_count(skip_count)
        {
            while (_skipped < _skip_count && _gen->HasNext())
            {
                _gen->Next();
                _skipped++;
            }
        }

        IGenerator<T>& Next() override
        {
            if (!HasNext())
            {
                throw Exceptions::IndexOutOfRange();
            }
            
            _gen->Next();
            return *this;
        }

        bool HasNext() const override
        {
            return _gen->HasNext();
        }

        const T& GetCurrent() const override
        {
            if (!HasNext())
            {
                throw Exceptions::IndexOutOfRange();
            }
            
            return _gen->GetCurrent();
        }
    };

    template <class T>
    GeneratorT<T> take(GeneratorT<T> base, size_t count)
    {
        return smartptr::MakeUnique<IGenerator<T>>(std::in_place_type<TakeGenerator<T>>,
            smartptr::MoveRef(base), count);
    }

    template <class T>
    GeneratorT<T> skip(GeneratorT<T> base, size_t count)
    {
        return smartptr::MakeUnique<IGenerator<T>>(std::in_place_type<TakeGenerator<T>>,
            smartptr::MoveRef(base), count);
    }

} // namespace gens