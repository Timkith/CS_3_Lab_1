#pragma once

#include <AppendGenerator.h>
#include <SmartPtr.h>
#include <IGenerator.h>
#include <HashMap.h>
#include <Cardinal.h>
#include <ConcatGenerator.h>
#include <PrependGenerator.h>
#include <TakeSkipGenerator.h>

namespace lazy {
    template<typename T>
    class LazySequence : public  gens::Generamble<T>
    {
        cardinality::cardinal<T> size = cardinality::cardinal<T>(0);
        smartptr::UniquePtr<containers::HashMap<size_t,T>> _elems{};
        gens::GeneratorT<T> _gen;

    public:
        LazySequence() = delete;
        LazySequence(gens::Generamble<T>& contain) : _gen(contain.GetGenerator()){}
        LazySequence(gens::GeneratorT<T> gen) : _gen(smartptr::MoveRef(gen)){}
        LazySequence(LazySequence<T>&& other) noexcept : _gen(smartptr::MoveRef(other._gen)),
        size(other.size) {}

        T GetFirst() {
            return _elems->at(0);
        }

        T GetLast() {
            if (size.is_inf()) throw Exceptions::LazySequenceIsInf();
            return _elems->at(size.get_value());
        }

        T Get(size_t index) {
            return _elems->at(index);
        }

        [[nodiscard]] cardinality::cardinal<T> GetLength() const {
            return size;
        }

        LazySequence<T> GetSubSequence(size_t start, size_t end) {
            if (start > end) throw Exceptions::InvalidIndex();

            auto g = GetGenerator();
            auto skipped = gens::skip<T>(smartptr::MoveRef(g), start);
            auto taken = gens::take<T>(smartptr::MoveRef(skipped), end - start + 1);

            return LazySequence<T>(smartptr::MoveRef(taken));
        }

        gens::GeneratorT<T> GetGenerator() override {
            return smartptr::MoveRef(_gen);
        }

        LazySequence<T> Append(T item) {
            auto append_gen = gens::append<T>(GetGenerator(), item);
            return LazySequence<T>(smartptr::MoveRef(append_gen));
        }

        LazySequence<T> Prepend(T item) {
            auto prepend_gen = gens::prepend<T>(GetGenerator(), item);
            return LazySequence<T>(smartptr::MoveRef(prepend_gen));
        }


        LazySequence<T> Concat(LazySequence<T>&& other) {
            auto first = GetGenerator();
            auto second = other.GetGenerator();

            auto c_gen = gens::concat(smartptr::MoveRef(first), smartptr::MoveRef(second));
            return LazySequence<T>(smartptr::MoveRef(c_gen));
        }

    };
}
