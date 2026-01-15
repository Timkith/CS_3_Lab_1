#pragma once

#include <SmartPtr.h>
#include <IGenerator.h>
#include <HashMap.h>
#include <Cardinal.h>

namespace lazy {
    template<typename K, typename V>
    class LazySequence : Generamble<types::pair<K,V>>
    {
        using pair_t = types::pair<K, V>;

        smartptr::UniquePtr<containers::HashMap<K,V>> _elems{};
        gens::GeneratorT _gen;

    public:
        LazySequence(Generamble<pair_t> contain) : _gen(contain.GetGenerator()){}
        LazeSequence()

    };
}
