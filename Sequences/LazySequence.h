#pragma once

#include <AppendGenerator.h>
#include <SmartPtr.h>
#include <IGenerator.h>
#include <HashMap.h>
#include <Cardinal.h>
#include <ConcatGenerator.h>
#include <PrependGenerator.h>
#include <TakeSkipGenerator.h>
#include <Pair.h>

namespace lazy {
    template<typename T>
    class LazySequence : public  gens::Generamble<T>
    {
        size_t _gen_count = 0;
        cardinality::cardinal<T> size = cardinality::cardinal<T>(0);
        smartptr::UniquePtr<containers::HashMap<size_t,T>> _elems{};
        gens::GeneratorT<T> _gen;
    private:
        void Generate(size_t index) {
            if (!_elems) {
                _elems = smartptr::UniquePtr<containers::HashMap<size_t, T>>(new containers::HashMap<size_t, T>());
            }

            while (_gen_count <= index) {
                if (!_gen->HasNext()) {
                    break;
                }

                T value = _gen->GetCurrent();
                (*_elems)[_gen_count] = value;

                _gen_count++;

                _gen->Next();

                if (!size.is_inf()) {
                    size = cardinality::cardinal<T>(_gen_count);
                }
            }
        }
    public:
        LazySequence() = delete;
        LazySequence(gens::Generamble<T>& contain) : _gen(contain.GetGenerator()){}
        LazySequence(gens::GeneratorT<T> gen) : _gen(smartptr::MoveRef(gen)) {
            if (_gen->GetGuar()) size = cardinality::cardinal<T>();
        }
        LazySequence(LazySequence<T>&& other) noexcept : _gen(smartptr::MoveRef(other._gen)),
        size(other.size),_elems(smartptr::MoveRef(other._elems)),
              _gen_count(other._gen_count) {}

        T GetFirst() {
            return _elems->at(0);
        }

        T GetLast() {
            if (size.is_inf()) throw Exceptions::LazySequenceIsInf();
            while (_gen && _gen->HasNext()) {
                Generate(_gen_count);
            }

            if (_gen_count == 0) throw Exceptions::InvalidIndex();
            return _elems->at(_gen_count - 1);
        }

        T Get(size_t index) {
            Generate(index);

            if (index >= _gen_count) {
                throw Exceptions::InvalidIndex();
            }

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
            bool is_result_inf = this->size.is_inf() || other.size.is_inf();

            auto first = GetGenerator();
            auto second = other.GetGenerator();

            auto c_gen = gens::concat(smartptr::MoveRef(first), smartptr::MoveRef(second));

            LazySequence<T> result(smartptr::MoveRef(c_gen));

            if (is_result_inf) {
                result.size = cardinality::cardinal<T>();
            } else {
                result.size = this->size + other.size;
            }

            return result;
        }

    };
}
