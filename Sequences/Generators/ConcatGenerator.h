#pragma once

#include "IGenerator.h"

namespace gens
{

    template <class T>
    class ConcatGenerator : public IGenerator<T>
    {
        using Generator = GeneratorT<T>;

        Generator _first;
        Generator _second;
        bool _using_first = true;

    public:
        ConcatGenerator(Generator first, Generator second) : 
            _first(smartptr::MoveRef(first)),
            _second(smartptr::MoveRef(second)),
            _using_first(true)
        {
            if (!_first->HasNext())
            {
                _using_first = false;
            }
        }

        IGenerator<T>& Next() override
        {
            if (_using_first)
            {
                _first->Next();
                if (!_first->HasNext())
                {
                    _using_first = false;
                }
            }
            else
            {
                _second->Next();
            }
            
            return *this;
        }

        bool HasNext() const override
        {
            if (_using_first)
            {
                return _first->HasNext();
            }            
            return _second->HasNext();
        }

        const T& GetCurrent() const override
        {
            if (_using_first)
            {
                return _first->GetCurrent();
            }
            
            return _second->GetCurrent();
        }
    };

    template <class T>
    GeneratorT<T> concat(GeneratorT<T> first, GeneratorT<T> second)
    {
        return smartptr::MakeUnique<IGenerator<T>>(std::in_place_type<ConcatGenerator<T>>,
            smartptr::MoveRef(first), smartptr::MoveRef(second));
    }

} // namespace gens